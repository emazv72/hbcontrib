
/*

librabbitmq

AMQP Consumer

*/


#include "hbclass.ch"
#include "error.ch"

#include "hbweb.ch"
#include "hbamqp.ch"

CREATE CLASS AMQPConsumer INHERIT  ZObject

   METHOD New( connection AS Object )
   
   METHOD SetChannel( channel )			INLINE	::channel   := channel
   METHOD SetQueueName( queueName )		INLINE	::queueName := queueName
   METHOD SetTimeoutMs( timeoutMs )		INLINE	::timeoutMs := timeoutMs
   METHOD SetAction( action )		   
   
   METHOD OpenChannel()
   METHOD ConsumeAndDispatch()   
   METHOD CloseChannel()
   
   PROTECTED:

   METHOD DumpAction( hEnvelope)
   
   DATA connection       AS Object	// AMQPConnection
   DATA channel		     AS Numeric   INIT 1
   DATA timeoutMs        AS Numeric   INIT AMQP_TIMEOUT_INFINITE
   DATA queueName	 	 AS Character INIT "DEFAULT"
   DATA action	         AS Object 
      
END CLASS

METHOD New( connection AS Object  ) CLASS AMQPConsumer
   									
	IF IsNullOrEmpty( connection )
	
      ::Throw ( "Connection Error" )
	
	ENDIF
	
	::connection := connection
	
	::action := { | e | ::DumpAction( e )} 
			
RETURN Self

METHOD OpenChannel() CLASS AMQPConsumer

	IF !( ::connection:OpenChannel(::channel) == AMQP_RESPONSE_NORMAL)

		RETURN .F.
		
	ENDIF

	IF !( ::connection:BasicConsume(::channel, ::queueName) ==  AMQP_RESPONSE_NORMAL)
		
		RETURN .F.
		
	ENDIF		


RETURN .T.

METHOD CloseChannel() CLASS AMQPConsumer
	
	IF !( ::connection:CloseChannel(::channel) ==  AMQP_RESPONSE_NORMAL)
		
		RETURN .F.
	
	ENDIF	

RETURN .T.

METHOD ConsumeAndDispatch() CLASS AMQPConsumer

	Local oEnvelope := ::connection:CreateEnvelope()
	Local hEnvelope := { => }	
	Local result
	
	::connection:MaybeReleaseBuffers()

	result := ::connection:ConsumeMessage( oEnvelope, ::timeoutMs )
	
	IF ( result == AMQP_RESPONSE_NORMAL)	
		
		// build enveloper
		
		hEnvelope["exchange"] 	 := oEnvelope:GetExchange() 
		hEnvelope["routingKey"]  := oEnvelope:GetRoutingKey() 
		hEnvelope["deliveryTag"] := oEnvelope:GetDeliveryTag()
		hEnvelope["messageBody"] := oEnvelope:GetMessageBody() 
	
		// call action

		DO CASE
		
			CASE HB_ISBLOCK ( ::action)

				result := EVAL ( ::action, hEnvelope)
			
			CASE HB_ISSTRING( ::action )
			
				result := HB_ExecFromArray ( {::action, hEnvelope} )
			
			OTHERWISE 
			
				::Throw("ConsumeAndDispatch action error")
		
		ENDCASE
				
		
		IF ( !HB_ISLOGICAL(result) )
			result := .F.
		ENDIF
		
		// action returns .T. -> ack message
		IF (  result )
	
			IF ( ::connection:BasicAck(::channel, oEnvelope:GetDeliveryTag()) != 0) 
				
				LogWrite("AMQPConsumer", "basicAck error")
				
			ELSE
				
				LogWrite("AMQPConsumer", "basicAck OK")
				
			ENDIF
		
		ELSE
		
			LogWrite("AMQPConsumer", "action block error")
		
		ENDIF

	ELSE
			
		LogWrite("AMQPConsumer", hb_StrFormat("consume Error (result=%d, response=%s)", result, ::connection:GetResponse()))
		
	ENDIF
		
	oEnvelope:Destroy()
	 	
RETURN NIL

// Simple message dump
METHOD DumpAction(hEnvelope) CLASS AMQPConsumer

	Local exchange := hEnvelope["exchange"] 	 
	Local routingKey := hEnvelope["routingKey"]  
	Local deliveryTag := hEnvelope["deliveryTag"] 
	Local messageBody := hEnvelope["messageBody"] 
	
	LogWrite("AMQPConsumer", hb_StrFormat("***MESSAGE DUMP**** exchange=%s, routingKey=%s, deliveryTag=%d, messageBody=%s", exchange, routingKey, deliveryTag, messageBody))
	
RETURN .T.

METHOD SetAction( action )	CLASS AMQPConsumer

	DO CASE
	
		CASE HB_ISBLOCK ( action)

			RETURN NIL
		
		CASE HB_ISSTRING( action )
		
			IF ( !HB_ISFUNCTION( action ) )
			
				::Throw("action is not a function")
			
			ENDIF
		
		OTHERWISE 
		
			::Throw("Invalid action")
	
	ENDCASE

	::action = action

RETURN NIL   

