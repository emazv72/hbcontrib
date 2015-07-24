/*

libxml2

Base class

http://xmlsoft.org/html/libxml-tree.html

*/

#include "hbclass.ch"
#include "hbxml2.ch"
#include "error.ch"

CREATE CLASS XMLBase INHERIT  ZObject
	
   METHOD New()
   METHOD GetLastError( )

   METHOD SetErrorBlock( bError  )	INLINE 	::bError := bError

   // TODO
	// SetCodePage..

   PROTECTED:
   
   METHOD LogXmlError( oError AS Object)
   
   CLASSDATA	clsInitialized	AS Logical		INIT .F.   
   
   DATA	bError AS Object
      
END CLASS

METHOD GetLastError( ) CLASS XMLBase

   Local oError
   Local pError := xmlGetLastError()
   
   IF ( !IsNullOrEmpty( pError  ))
   
		oError := XMLError():FromPtr( pError )
     		
   ENDIF

RETURN oError

METHOD New() CLASS XMLBase
	
	IF ( !::clsInitialized )
		
		XmlErrorSetBlock( { |pError| ::LogXmlError( XmlError():FromPtr(pError) )} )
		
		::clsInitialized := .T.
	ENDIF 

RETURN Self

/*
METHOD Dispose( )

	XmlErrorFreeBlock()

RETURN NIL
*/

METHOD LogXmlError( oError AS Object) CLASS XMLBase

	IF ( oError != NIL )

		LogWrite( "XML2", hb_StrFormat("File %s - Error %d (%s) (Line %d/%d)", ;
			oError:GetFile() ,;
			oError:GetCode() ,;
			oError:GetMessage() ,;
			oError:GetLine() ,;
			oError:GetCol() ;
		))
		
		IF HB_ISBLOCK( ::bError )
		
			Eval ( ::bError, oError )
		
		ENDIF

	ENDIF


RETURN NIL