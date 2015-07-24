
/*

librabbitmq

APIs

*/

#include "hbamqp.h"

/*
        Creates a new amqp_connection_state_t object.
        amqp_connection_state_t objects created with this function should be freed with amqp_destroy_connection

        amqp_new_connection() -> pConn
 */

HB_FUNC( AMQP_NEW_CONNECTION )
{

   PMQ_CONN pConn = hb_xgrab( sizeof( MQ_CONN ) );

   if( pConn )
      pConn->conn = amqp_new_connection();

   hb_retptr( pConn );
}

// amqp_connection_close(pConn) -> nResponse
HB_FUNC( AMQP_CONNECTION_CLOSE )
{
   if( HB_ISPOINTER( 1 ) )
   {
      PMQ_CONN pConn = ( PMQ_CONN ) hb_parptr( 1 );

      if( pConn )
      {
         int response = decode_reply(
            amqp_connection_close(
               pConn->conn,
               AMQP_REPLY_SUCCESS ),
            "amqp_connection_close" );
      
	    hb_retni( response );
      }
	  else
		hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

// amqp_destroy_connection(pConn)
HB_FUNC( AMQP_DESTROY_CONNECTION )
{

   if( HB_ISPOINTER( 1 ) )
   {
      PMQ_CONN pConn = ( PMQ_CONN ) hb_parptr( 1 );

      if( pConn )
      {
         amqp_destroy_connection( pConn->conn );
         hb_xfree( pConn );
      
		 hb_ret();
      }
	  else
		  hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// amqp_tcp_socket_new( pConn ) -> pSocket
HB_FUNC( AMQP_TCP_SOCKET_NEW )
{
   if( HB_ISPOINTER( 1 ) )
   {
      PMQ_CONN pConn = ( PMQ_CONN ) hb_parptr( 1 );

      if( pConn )
      {
         amqp_socket_t * pSocket = amqp_tcp_socket_new( pConn->conn );
         hb_retptr( pSocket );
      }
      else
		hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

/*
        Attempts to open a socket to hostname on portnumber

        amqp_socket_open( pSocket, cHost, nPort ) -> nStatus
 */

HB_FUNC( AMQP_SOCKET_OPEN )
{

   if( HB_ISPOINTER( 1 ) && HB_ISCHAR( 2 ) && HB_ISNUM( 3 ) )
   {
      amqp_socket_t * pSocket = ( amqp_socket_t * ) hb_parptr( 1 );

      hb_retni( amqp_socket_open( pSocket, hb_parc( 2 ), hb_parni( 3 ) ) );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

/*
        Login to the broker.
        After using amqp_open_socket and amqp_set_sockfd, call amqp_login to complete connecting to the broker

        amqp_login( pConn, cVHost, nFrameSize, nMethod, user, pwd ) -> nResponse
 */
HB_FUNC( AMQP_LOGIN )
{
   if( HB_ISPOINTER( 1 ) && HB_ISCHAR( 2 ) && HB_ISNUM( 3 ) && HB_ISNUM( 4 ) && HB_ISCHAR( 5 ) && HB_ISCHAR( 6 ) )
   {

      PMQ_CONN pConn    = ( PMQ_CONN ) hb_parptr( 1 );
      int      response = AMQP_RESPONSE_NONE;

      if( pConn )
      {

         response = decode_reply(
            amqp_login(
               pConn->conn,
               hb_parc( 2 ),                                    // vhost
               0,                                               // ch max
               hb_parni( 3 ),                                   // frame size, default 128K
               0,                                               // heartbeat  - unsupported
               hb_parni( 4 ),                                   // AMQP_SASL_METHOD_PLAIN
               hb_parc( 5 ),                                    // user
               hb_parc( 6 ) ),                                  // pwd
            "amqp_login" );
      
		hb_retni( response );

      }
	  else
		  hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

// amqp_channel_open( pConn, nChannel) -> nResponse
HB_FUNC( AMQP_CHANNEL_OPEN )
{

   if( HB_ISPOINTER( 1 ) && HB_ISNUM( 2 ) )
   {
      PMQ_CONN pConn    = ( PMQ_CONN ) hb_parptr( 1 );
      int      response = AMQP_RESPONSE_NONE;

      if( pConn )
      {
         amqp_channel_open( pConn->conn, hb_parni( 2 ) );

         response = decode_reply( amqp_get_rpc_reply( pConn->conn ), "amqp_channel_open" );

		hb_retni( response );
      }
	  else
        hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// amqp_channel_close( pConn, nChannel) -> nResponse
HB_FUNC( AMQP_CHANNEL_CLOSE )
{

   if( HB_ISPOINTER( 1 ) && HB_ISNUM( 2 ) )
   {
      PMQ_CONN pConn    = ( PMQ_CONN ) hb_parptr( 1 );
      int      response = AMQP_RESPONSE_NONE;

      if( pConn )
      {
         response = decode_reply(
            amqp_channel_close(
               pConn->conn,
               hb_parni( 2 ),
               AMQP_REPLY_SUCCESS ),
            "amqp_channel_close" );
		 
		 hb_retni( response );
      
	  }
	  else
        hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// amqp_exchange_declare(pConn, nChannel, cExchange, cExchangeType, bPassive, bDurable) -> nResponse
HB_FUNC( AMQP_EXCHANGE_DECLARE )
{
   if( HB_ISPOINTER( 1 ) && HB_ISNUM( 2 ) && HB_ISCHAR( 3 ) && HB_ISCHAR( 4 ) && HB_ISLOG( 5 ) && HB_ISLOG( 6 ) )
   {
      PMQ_CONN pConn    = ( PMQ_CONN ) hb_parptr( 1 );
      int      response = AMQP_RESPONSE_NONE;

      if( pConn )
      {
         amqp_exchange_declare( pConn->conn,
                                hb_parni( 2 ),                                                  // channel
                                amqp_cstring_bytes( hb_parc( 3 ) ),                             // exchange
                                amqp_cstring_bytes( hb_parc( 4 ) ),                             // type
                                hb_parl( 5 ),                                                   // passive
                                hb_parl( 6 ),                                                   // durable
                                amqp_empty_table );

         response = decode_reply(
            amqp_get_rpc_reply(
               pConn->conn ),
            "amqp_exchange_declare" );
		
		 hb_retni( response );
      
	  }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

/*
   Publish a message to the broker.

   amqp_basic_publish( pConn, nChannel, cExchange, cKey, nMandatory, nImmediate, hProperties, cBody ) -> nStatus

   - hProperties keys: content_type, delivery_mode

 */

HB_FUNC( AMQP_BASIC_PUBLISH )
{

   if( HB_ISPOINTER( 1 ) && HB_ISNUM( 2 ) && HB_ISCHAR( 3 ) && HB_ISCHAR( 4 ) && HB_ISNUM( 5 ) && HB_ISNUM( 6 ) && HB_ISHASH( 7 ) && HB_ISCHAR( 8 ) )
   {
      PMQ_CONN pConn  = ( PMQ_CONN ) hb_parptr( 1 );

      if( pConn )
      {
         PHB_ITEM pProps = hb_param( 7, HB_IT_HASH );

         const char * pszContentType = hb_itemGetCPtr( hb_hashGetCItemPtr( pProps, "content_type"  ) );
         int          deliveryMode   = hb_itemGetNI( hb_hashGetCItemPtr( pProps, "delivery_mode"   ) );

         amqp_basic_properties_t props;

         props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG |
                        AMQP_BASIC_DELIVERY_MODE_FLAG;


         props.content_type  = amqp_cstring_bytes( pszContentType );
         props.delivery_mode = deliveryMode;                /* AMQP_DELIVERY_xxx*/

         int status = decode_status(
            amqp_basic_publish( pConn->conn,
                                hb_parni( 2 ),                                                                                  // channel
                                amqp_cstring_bytes( hb_parc( 3 ) ),                                                             // exchange
                                amqp_cstring_bytes( hb_parc( 4 ) ),                                                             // routing_key
                                hb_parni( 5 ),                                                                                  // mandatory
                                hb_parni( 6 ),                                                                                  // immediate
                                &props,                                                                                         // properties
                                amqp_cstring_bytes( hb_parc( 8 ) ) ),                                                           // body
            "amqp_basic_publish" );
         
		 hb_retni( status );
      
	  }
      else
        hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

/*

	amqp_basic_consume( pConn, nChannel, cQueueName, cConsumerTag, nNoLocal, nNoAck, nExclusive ) -> nResponse

*/

HB_FUNC( AMQP_BASIC_CONSUME )
{

   if( HB_ISPOINTER( 1 ) && HB_ISNUM( 2 ) && HB_ISCHAR( 3 ) && HB_ISCHAR( 4 ) && HB_ISNUM( 5 ) && HB_ISNUM( 6 ) && HB_ISNUM( 7 ))
   {
      PMQ_CONN pConn  = ( PMQ_CONN ) hb_parptr( 1 );
      
	  if( pConn )
      {
			amqp_basic_consume( pConn->conn,
                                hb_parni( 2 ),                                                                                  // channel
                                amqp_cstring_bytes( hb_parc( 3 ) ),                                                             // queuename
                                amqp_cstring_bytes( hb_parc( 4 ) ),                                                             // consumer_tag
                                hb_parni( 5 ),                                                                                  // no_local
                                hb_parni( 6 ),                                                                                  // no_ack
                                hb_parni( 7 ),                                                                                  // exclusive
                                amqp_empty_table );
           

            int response = decode_reply( amqp_get_rpc_reply( pConn->conn ), "amqp_basic_consume" );
			
			hb_retni( response );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

/*
**
 * Acknowledges a message
 
 
 amqp_basic_ack( pConn, nChannel, nDeliveryTag, nMultiple) -> nResponse
 

*/
 
HB_FUNC( AMQP_BASIC_ACK)
{
if( HB_ISPOINTER( 1 ) && HB_ISNUM( 2 ) && HB_ISNUM( 3 ) && HB_ISNUM( 4 ) )
   {
      PMQ_CONN pConn  = ( PMQ_CONN ) hb_parptr( 1 );
      
	  if( pConn )
      {
            int response = 
				amqp_basic_ack( pConn->conn,															// state
                                hb_parni( 2 ),                                                          // channel
                                hb_parnll( 3 ),                                                         // delivery_tag
                                hb_parni( 4 ));                                                         // multiple
      
	  
			hb_retni( response );
           

      }
	  else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
  
  }


/* 

	Wait for and consume a message

amqp_consume_message(pConn, pEnvelope, nTimeoutMs) -> nResponse

*/

HB_FUNC( AMQP_CONSUME_MESSAGE )
{
   if( HB_ISPOINTER( 1 ) && HB_ISPOINTER( 2 ) )
   {
      PMQ_CONN pConn = ( PMQ_CONN ) hb_parptr( 1 );
	  PENVELOPE pEnvelope = ( PENVELOPE ) hb_parptr( 2 );
     	  
	  if( pConn && pEnvelope)
      {
		  
		  struct timeval* pTimeout = NULL; // Infinite
		  
		  if ( HB_ISNUM(3))
		  {
			   pTimeout = (struct timeval*) hb_xgrab(sizeof(struct timeval));
			   memset( pTimeout, 0, sizeof(struct timeval));
			   pTimeout->tv_usec = hb_parni(3) * 1000l;	//ms->us
		  }
		  
         int response = decode_reply(
            amqp_consume_message(
               pConn->conn,
               pEnvelope,
			   pTimeout,
			   0),
            "amqp_consume_message" );

		  if ( HB_ISNUM(3) && pTimeout)
		  {
			   hb_xfree( pTimeout);
		  }
			
	     hb_retni( response );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

HB_FUNC( AMQP_ENVELOPE_NEW )
{	
	PENVELOPE pEnvelope = hb_xgrab( sizeof(amqp_envelope_t));
	memset( pEnvelope, 0 , sizeof(amqp_envelope_t));
	
	hb_retptr(pEnvelope);
}

/**
 * Frees memory associated with a amqp_envelope_t allocated in amqp_consume_message()
 
 amqp_destroy_envelope( pEnvelope)
 
 */

HB_FUNC( AMQP_DESTROY_ENVELOPE )
{
   if( HB_ISPOINTER( 1 ) )
   {
      PENVELOPE pEnvelope = ( PENVELOPE ) hb_parptr( 1 );
      
      if( pEnvelope )
      {
            amqp_destroy_envelope(
               pEnvelope);               
   
            hb_xfree( pEnvelope );
      }
	  else
		hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
      
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

// amqp_envelope_getmessagebody( pEnvelope) -> cMessage
HB_FUNC( AMQP_ENVELOPE_GETMESSAGEBODY )
{
   if( HB_ISPOINTER( 1 )  )
   {
	  PENVELOPE pEnvelope = ( PENVELOPE ) hb_parptr( 1 );

      if( pEnvelope)
      {
		hb_retclen( pEnvelope->message.body.bytes, pEnvelope->message.body.len);
      }
	  else
        hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

// amqp_envelope_getdeliverytag( pEnvelope) -> nDeliveryTag
HB_FUNC( AMQP_ENVELOPE_GETDELIVERYTAG )
{
   if( HB_ISPOINTER( 1 )  )
   {
	  PENVELOPE pEnvelope = ( PENVELOPE ) hb_parptr( 1 );

      if( pEnvelope)
      {
		hb_retnll( pEnvelope->delivery_tag);
      }
	  else
        hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

HB_FUNC( AMQP_ENVELOPE_GETROUTINGKEY)
{
   if( HB_ISPOINTER( 1 )  )
   {
	  PENVELOPE pEnvelope = ( PENVELOPE ) hb_parptr( 1 );

      if( pEnvelope)
      {
		hb_retclen( pEnvelope->routing_key.bytes, pEnvelope->routing_key.len);
      }
	  else
        hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

HB_FUNC( AMQP_ENVELOPE_GETEXCHANGE)
{

   if( HB_ISPOINTER( 1 )  )
   {
	  PENVELOPE pEnvelope = ( PENVELOPE ) hb_parptr( 1 );

      if( pEnvelope)
      {
		hb_retclen( pEnvelope->exchange.bytes, pEnvelope->exchange.len);
      }
	  else
        hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// amqp_maybe_release_buffers( pConn)
HB_FUNC( AMQP_MAYBE_RELEASE_BUFFERS)
{
   if( HB_ISPOINTER( 1 ) )
   {
      PMQ_CONN pConn = ( PMQ_CONN ) hb_parptr( 1 );

      if( pConn )
      {         
		amqp_maybe_release_buffers(pConn->conn);
      
	    hb_ret();
      }
	  else
		hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );		
}

/*

   Internal

 */

static amqp_response_type_enum decode_reply( amqp_rpc_reply_t x, char const * context )
{
   switch( x.reply_type )
   {
      case AMQP_RESPONSE_NORMAL:
         break;

      case AMQP_RESPONSE_NONE:
         HB_TRACE( HB_TR_ERROR, ( "amqp - %s: missing RPC reply type!", context ) );
         break;

      case AMQP_RESPONSE_LIBRARY_EXCEPTION:
         HB_TRACE( HB_TR_ERROR, ( "amqp  - %s: %s", context, amqp_error_string2( x.library_error ) ) );
         break;

      case AMQP_RESPONSE_SERVER_EXCEPTION:
         switch( x.reply.id )
         {
            case AMQP_CONNECTION_CLOSE_METHOD:
            {
               amqp_connection_close_t * m = ( amqp_connection_close_t * ) x.reply.decoded;
               HB_TRACE( HB_TR_ERROR, ( "amqp  - %s: server connection error %d, message: %.*s",
                                        context,
                                        m->reply_code,
                                        ( int ) m->reply_text.len, ( char * ) m->reply_text.bytes ) );

               break;
            }
            case AMQP_CHANNEL_CLOSE_METHOD:
            {
               amqp_channel_close_t * m = ( amqp_channel_close_t * ) x.reply.decoded;

               HB_TRACE( HB_TR_ERROR, ( "amqp  - %s: server channel error %d, message: %.*s",
                                        context,
                                        m->reply_code,
                                        ( int ) m->reply_text.len, ( char * ) m->reply_text.bytes ) );
               break;
            }
            default:
               HB_TRACE( HB_TR_ERROR, ( "amqp  - %s: unknown server error, method id 0x%08X", context, x.reply.id ) );
               break;
         }
         break;

      default:
         HB_TRACE( HB_TR_ERROR, ( "amqp  - %s: Unknown Reply Type %d", context, x.reply_type ) );
         break;
   }

   return x.reply_type;

}

static int decode_status( int status, char const * context )
{
   if( status != AMQP_STATUS_OK )
   {
      HB_TRACE( HB_TR_ERROR, ( "amqp  - %s status=%d (%s)", context, status, amqp_error_string2( status ) ) );
   }

   return status;
}

