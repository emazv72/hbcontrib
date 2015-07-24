
/*

librabbitmq

Basic Publish and Consume API Test

*/

#include "hbamqp.ch"

FUNCTION Main(  cTest )

    DO CASE
		CASE cTest == "1"		
		
			Publish()
		
		CASE cTest == "2"		
		
			Consume()
		
	ENDCASE

RETURN NIL

STATIC FUNCTION Publish( )

	Local data := "test"
	Local oConn := AMQPConnection():New()
	Local exchange := "amq.direct"
	Local routingKey := "TEST-KEY"
	
	Local host := "localhost"
	Local user := "guest"
	Local password := "guest"
	
	oConn:SetHost( host )
	oConn:SetAuth( user, password )	
	
	IF !( oConn:Connect() == AMQP_STATUS_OK)
		? "Connect status=", oConn:GetStatus()
		RETURN NIL
	ENDIF

	IF !( oConn:Login() == AMQP_RESPONSE_NORMAL)
		? "Login response=", oConn:GetResponse()
		RETURN NIL
	ENDIF
					
	IF !( oConn:OpenChannel(1) == AMQP_RESPONSE_NORMAL)
		? "OpenChannel response=", oConn:GetResponse()
		RETURN NIL
	ENDIF
			
	
	IF !( oConn:BasicPublish( data, 1, exchange, routingKey ) ==  AMQP_STATUS_OK )
		? "Publish status=", oConn:GetStatus()
		RETURN NIL
	ENDIF
	
	? "Message Published"
	
	IF !( oConn:CloseChannel() ==  AMQP_RESPONSE_NORMAL)
		? "CloseChannel status=", oConn:GetResponse()
		RETURN NIL
	ENDIF			 
					
	
	oConn:Close()
	 	 
RETURN NIL

STATIC FUNCTION Consume( )

	Local oConn := AMQPConnection():New()
	Local oEnvelope
	
	Local host := "localhost"
	Local user := "guest"
	Local password := "guest"
	Local queueName := "TEST-QUEUE"
	
	oConn:SetHost( host )
	oConn:SetAuth( user, password )
		
	IF !( oConn:Connect() == AMQP_STATUS_OK)
		? "Connect status=", oConn:GetStatus()
		RETURN NIL
	ENDIF

	IF !( oConn:Login() == AMQP_RESPONSE_NORMAL)
		? "Login response=", oConn:GetResponse()
		RETURN NIL
	ENDIF
					
	IF !( oConn:OpenChannel( 1 ) == AMQP_RESPONSE_NORMAL)
		? "OpenChannel response=", oConn:GetResponse()
		RETURN NIL
	ENDIF
		
	IF !( oConn:BasicConsume(1, queueName) ==  AMQP_RESPONSE_NORMAL)
		? "BasicConsume status=", oConn:GetResponse()
		RETURN NIL
	ENDIF
	
	DO WHILE .T.
	
		oEnvelope := oConn:CreateEnvelope()
		
		oConn:MaybeReleaseBuffers()
	
		IF !(oConn:ConsumeMessage( oEnvelope ) == AMQP_RESPONSE_NORMAL)
			? "ConsumeMessage status=", oConn:GetResponse()
			EXIT
		ELSE
		
			? "GetExchange=", oEnvelope:GetExchange()
			? "GetRoutingKey=", oEnvelope:GetRoutingKey()
			? "GetMessageBody=", oEnvelope:GetMessageBody()
			
			IF (oConn:BasicAck(1, oEnvelope:GetDeliveryTag()) != 0) 
				? "BasicAck error"
			ENDIF
		
			
		ENDIF

		oEnvelope:Destroy()
	
	ENDDO
	
	IF !( oConn:CloseChannel() ==  AMQP_RESPONSE_NORMAL)
		? "CloseChannel status=", oConn:GetResponse()
		RETURN NIL
	ENDIF			 
						 	
	oConn:Close()
	 	 
RETURN NIL
