
/*

librabbitmq

AMQP envelope

*/

#include "hbclass.ch"
#include "error.ch"

#include "hbweb.ch"
#include "hbamqp.ch"

CREATE CLASS AMQPEnvelope INHERIT  ZObject

   METHOD FromPtr( pEnvelope AS Object )
   METHOD GetPtr()
   
   METHOD Destroy()
   
   METHOD GetMessageBody()
   
   METHOD GetDeliveryTag()
   METHOD GetExchange()
   METHOD GetRoutingKey()
   
   PROTECTED:
  
   DATA pEnvelope   AS OBJECT
   
END CLASS

METHOD FromPtr( pEnvelope AS Object )  CLASS AMQPEnvelope

	::Super:New()

	IF (IsNullOrEmpty(pEnvelope))
		
		::Throw("Invalid Envelope")

	ENDIF

	::pEnvelope := pEnvelope

RETURN Self

METHOD GetPtr() CLASS AMQPEnvelope

RETURN ::pEnvelope


METHOD Destroy() CLASS AMQPEnvelope

   IF ( !IsNullOrEmpty( ::pEnvelope ) )
	
		amqp_destroy_envelope( ::pEnvelope)
		::pEnvelope := NIL
   
   ENDIF
   
RETURN NIL

METHOD GetMessageBody() CLASS AMQPEnvelope
   
   Local value

   IF ( !IsNullOrEmpty( ::pEnvelope ) )
		
		value := amqp_envelope_getmessagebody(::pEnvelope)
   
   ENDIF
   
RETURN value

METHOD GetDeliveryTag() CLASS AMQPEnvelope
   
   Local value

   IF ( !IsNullOrEmpty( ::pEnvelope ) )
		
		value := amqp_envelope_getdeliverytag(::pEnvelope)
   
   ENDIF
   
RETURN value

METHOD GetExchange() CLASS AMQPEnvelope
   
   Local value

   IF ( !IsNullOrEmpty( ::pEnvelope ) )
		
		value := amqp_envelope_getexchange(::pEnvelope)
   
   ENDIF
   
RETURN value

METHOD GetRoutingKey() CLASS AMQPEnvelope
   
   Local value

   IF ( !IsNullOrEmpty( ::pEnvelope ) )
		
		value := amqp_envelope_getroutingkey(::pEnvelope)
   
   ENDIF
   
RETURN value
