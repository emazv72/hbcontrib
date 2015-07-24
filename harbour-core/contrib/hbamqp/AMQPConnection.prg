
/*

librabbitmq

AMQP Connection

*/

#include "hbclass.ch"
#include "error.ch"

#include "hbweb.ch"
#include "hbamqp.ch"

CREATE CLASS AMQPConnection INHERIT  ZObject

   METHOD New( )
   
   METHOD SetAuth( user As Character, password AS Character, method AS Numeric )
 
   METHOD SetHost( host  )			INLINE ::host  := host
   METHOD SetPort( port  )			INLINE ::port  := port
   
   METHOD SetVirtualHost( virtualHost  )	INLINE ::virtualHost := virtualHost
   METHOD SetFramSize( frameSize )			INLINE ::frameSize 	 := frameSize
   
   METHOD Connect()
   
   METHOD Login()
   
   METHOD OpenChannel( channel AS Numeric )
   METHOD CloseChannel( channel AS Numeric )
   
   METHOD SetMandatory( mandatory  )		INLINE ::mandatory := mandatory   
   METHOD SetImmediate( immediate  )		INLINE ::immediate := immediate
   
   METHOD SetMessageProperties( hMessageProperties )		INLINE ::hMessageProperties := hMessageProperties
   
   METHOD BasicPublish(data AS Character, channel AS Numeric, exchange As Character, routingKey as Character  )

   METHOD ExchangeDeclare(channel AS Numeric, exchange AS Character, exchangeType AS Character, passive AS Logical, durable AS Logical) 

   METHOD BasicConsume(channel AS Numeric, queueName AS Character, consumerTag AS Character, noLocal AS Numeric, noAck AS Numeric, exclusive AS Numeric )
   
   METHOD CreateEnvelope()   
   METHOD ConsumeMessage(envelope AS Object, timeoutMs AS Numeric )  
   METHOD BasicAck(channel AS Numeric, deliveryTag As Numeric, multiple AS Numeric  )
   
   METHOD MaybeReleaseBuffers()
   
   METHOD Close( )
  
   METHOD GetStatus()							INLINE ::status
   METHOD GetResponse()							INLINE ::response
  
   PROTECTED:
  
   DATA pConn   AS OBJECT	// MQ_CONN* 
   DATA pSocket AS OBJECT   // amqp_socket_t*
   
   DATA status   AS Numeric		// AMQP_STATUS_xxx
   DATA response AS Numeric		// AMQP_RESPONSE_xxx
   
   DATA user  	AS Character			INIT "guest"
   DATA password  AS Character			INIT "guest"
   DATA loginMethod AS Numeric 			INIT AMQP_SASL_METHOD_PLAIN
   
   DATA virtualHost AS Character 				INIT "/"
   
   DATA host   		AS Character		INIT "localhost"
   DATA port    	AS Numeric		    INIT 5672
   DATA frameSize 	AS Numeric			INIT AMQP_FRAME_SIZE 
   
   DATA exchange 	AS Character 		INIT ""
   DATA routingKey	AS Character		INIT ""
   DATA mandatory   AS Numeric			INIT	1
   DATA immediate   AS Numeric			INIT	0	// NOT_IMPLEMENTED - immediate=true
   
   DATA hMessageProperties AS Object			INIT { AMQP_HB_PROP_CONTENT_TYPE => MEDIA_TEXT, AMQP_HB_PROP_DELIVERY_MODE =>  AMQP_DELIVERY_PERSISTENT }
   
END CLASS

METHOD New( ) CLASS AMQPConnection
   				
	::pConn := amqp_new_connection()
	
	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
		
RETURN Self

METHOD Connect() CLASS AMQPConnection

	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
		
	::pSocket := amqp_tcp_socket_new( ::pConn ) 
	
	IF IsNullOrEmpty( ::pSocket )
	
      ::Throw ( "Socket Error" )
	
	ENDIF
	
	::status := amqp_socket_open( ::pSocket, ::host, ::port )

RETURN ::status

METHOD Close( ) CLASS AMQPConnection

	IF  ( !IsNullOrEmpty( ::pConn ) )
		
		amqp_connection_close( ::pConn )
		amqp_destroy_connection( ::pConn)
	
	ENDIF

RETURN NIL

METHOD SetAuth( user As Character, password AS Character, method AS Numeric ) CLASS AMQPConnection

	::user := user
	::password := password 
	
	IF ( HB_ISNUMERIC ( method ))
	
		::loginMethod := method
		
	ENDIF

RETURN NIL

METHOD Login() CLASS AMQPConnection

	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
			
	IF IsNullOrEmpty( ::pSocket )
	
      ::Throw ( "Socket Error" )
	
	ENDIF
	
	::response := amqp_login( ::pConn, ::virtualHost, ::frameSize, ::loginMethod, ::user, ::password )
				
RETURN ::response

METHOD OpenChannel( channel AS Numeric ) CLASS AMQPConnection

	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
			
	IF IsNullOrEmpty( ::pSocket )
	
      ::Throw ( "Socket Error" )
	
	ENDIF
	
	IF ( !HB_ISNUMERIC ( channel ))
	
		channel := 1
		
	ENDIF

	
	::response :=  amqp_channel_open( ::pConn, channel )
	
RETURN ::response

METHOD CloseChannel( channel AS Numeric ) CLASS AMQPConnection

	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
			
	IF IsNullOrEmpty( ::pSocket )
	
      ::Throw ( "Socket Error" )
	
	ENDIF

	IF ( !HB_ISNUMERIC ( channel ))
	
		channel := 1
		
	ENDIF
	
	::response := amqp_channel_close( ::pConn, channel )

RETURN ::response

METHOD BasicPublish(data AS Character, channel AS Numeric, exchange As Character, routingKey as Character  ) CLASS AMQPConnection

	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
			
	IF IsNullOrEmpty( ::pSocket )
	
      ::Throw ( "Socket Error" )
	
	ENDIF
	
	IF ( !HB_ISNUMERIC ( channel ))
	
		channel := 1
		
	ENDIF

	IF ( data == NIL)
	
	  LogWrite("BasicPublish", "data error (null)")
      data := ""
	
	ENDIF
	
	::status := amqp_basic_publish( ::pConn, channel, exchange, routingKey, ::mandatory, ::immediate, ::hMessageProperties, data )

RETURN ::status

METHOD ExchangeDeclare(channel AS Numeric, exchange AS Character, exchangeType AS Character, passive AS Logical, durable AS Logical) CLASS AMQPConnection

	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
			
	IF IsNullOrEmpty( ::pSocket )
	
      ::Throw ( "Socket Error" )
	
	ENDIF
	
	::response := amqp_exchange_declare( ::pConn, channel, exchange, exchangeType, passive, durable)
	
RETURN ::response

METHOD BasicConsume(channel AS Numeric, queueName AS Character, consumerTag AS Character, noLocal AS Numeric, noAck AS Numeric, exclusive AS Numeric ) CLASS AMQPConnection

	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
			
	IF IsNullOrEmpty( ::pSocket )
	
      ::Throw ( "Socket Error" )
	
	ENDIF
		
	IF ( !HB_ISSTRING ( queueName ))
	
		::Throw ( "Queue Name Error" )
		
	ENDIF
	
	IF ( !HB_ISNUMERIC ( channel ))
	
		channel := 1
		
	ENDIF
	
	IF ( !HB_ISSTRING ( consumerTag ))
	
		consumerTag := ""
		
	ENDIF
	
	IF ( !HB_ISNUMERIC ( noLocal ))
	
		noLocal := 0
		
	ENDIF
	
	IF ( !HB_ISNUMERIC ( noAck ))
	
		noAck := 0
		
	ENDIF
	
	IF ( !HB_ISNUMERIC ( exclusive ))
	
		exclusive := 0
		
	ENDIF
	
	::status := amqp_basic_consume( ::pConn, channel, queueName, consumerTag, noLocal, noAck, exclusive )

RETURN ::status

METHOD CreateEnvelope()  CLASS AMQPConnection

RETURN AMQPEnvelope():FromPtr( amqp_envelope_new() )

METHOD ConsumeMessage(envelope AS OBJECT, timeoutMs AS Numeric ) CLASS AMQPConnection

	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
			
	IF IsNullOrEmpty( ::pSocket )
	
      ::Throw ( "Socket Error" )
	
	ENDIF
	
	IF IsNullOrEmpty( envelope )
	
      ::Throw ( "Envelope Error" )
	
	ENDIF

	::status := amqp_consume_message( ::pConn, envelope:GetPtr(), timeoutMs )

RETURN ::status

METHOD BasicAck(channel AS Numeric, deliveryTag As Numeric, multiple AS Numeric  ) CLASS AMQPConnection

	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
			
	IF IsNullOrEmpty( ::pSocket )
	
      ::Throw ( "Socket Error" )
	
	ENDIF
	
	IF ( !HB_ISNUMERIC ( channel ))
	
		channel := 1
		
	ENDIF
	
	IF ( !HB_ISNUMERIC ( deliveryTag ))
	
		 ::Throw ( "Delivery Tag Error" )
		
	ENDIF
	
	IF ( !HB_ISNUMERIC ( multiple ))
	
		multiple := 0
		
	ENDIF
		
	::status := amqp_basic_ack( ::pConn, channel, deliveryTag, multiple)

RETURN ::status

METHOD MaybeReleaseBuffers() CLASS AMQPConnection

	IF IsNullOrEmpty( ::pConn )
	
      ::Throw ( "Connection Error" )
	
	ENDIF

	amqp_maybe_release_buffers( ::pConn)
	
RETURN NIL