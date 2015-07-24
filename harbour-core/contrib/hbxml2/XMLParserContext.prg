
/*
libxml2

Parser API

http://xmlsoft.org
*/

#include "hbclass.ch"
#include "hbxml2.ch"

CREATE CLASS XMLParserContext INHERIT XMLBase

   METHOD New()

   METHOD ReadFile( filename as Character, encoding as Character, options as numeric )
   
   METHOD ReadMemory( buffer as Character, documentUrl as Character, encoding as Character, options as numeric )
   
   METHOD Free()


   PROTECTED:

   // underlying xmlParserCtxtPtr
   DATA pParserCtxt AS OBJECT

END CLASS

METHOD New() CLASS XMLParserContext

   ::Super:New()

   ::pParserCtxt := xmlNewParserCtxt()

RETURN Self

METHOD ReadFile( filename as Character, encoding as Character, options as numeric ) CLASS XMLParserContext

   LOCAL oDoc
   LOCAL pDoc

   IF ( options == NIL )

      options := 0

   ENDIF

   IF ( !IsNullOrEmpty( ::pParserCtxt ) )
      
	  IF (!HB_ISNUMERIC( options ))
	  
		options := 0
	  
	  ENDIF

      pDoc := xmlCtxtReadFile( ::pParserCtxt, filename, encoding, options )

      IF ( !IsNullOrEmpty( pDoc ) )

         oDoc := XMLDoc():FromPtr( pDoc  )

      ENDIF

   ENDIF

RETURN oDoc

METHOD ReadMemory( buffer as Character, documentUrl as Character, encoding as Character, options as numeric ) CLASS XMLParserContext

   LOCAL oDoc
   LOCAL pDoc

   IF ( options == NIL )

      options := 0

   ENDIF

   IF ( documentUrl == NIL )

      documentUrl := ""

   ENDIF

   IF ( !IsNullOrEmpty( ::pParserCtxt ) )
      
	  IF (!HB_ISNUMERIC( options ))
	  
		options := 0
	  
	  ENDIF

      pDoc := xmlCtxtReadMemory( ::pParserCtxt, buffer, documentUrl, encoding, options )

      IF ( !IsNullOrEmpty( pDoc ) )

         oDoc := XMLDoc():FromPtr( pDoc  )

      ENDIF

   ENDIF

RETURN oDoc


METHOD Free() CLASS XMLParserContext

   IF ( !IsNullOrEmpty( ::pParserCtxt ) )

      xmlFreeParserCtxt( ::pParserCtxt )

   ENDIF

RETURN NIL
