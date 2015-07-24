/*

libxml2

XPath API

http://xmlsoft.org

*/

#include "hbclass.ch"
#include "hbxml2.ch"

CREATE CLASS XMLXPathObject INHERIT XMLBase

   METHOD New( pXPathObject AS OBJECT )

   METHOD Eval( bBlock AS OBJECT )

   METHOD Free()

   PROTECTED:

   METHOD		GetType()				INLINE	xmlXPathObjectGetProperty( ::pXPathObject, 1 )
   METHOD		GetNodeSetVal()			INLINE	xmlXPathObjectGetProperty( ::pXPathObject, 2 )
   METHOD		GetBoolVal()			INLINE	xmlXPathObjectGetProperty( ::pXPathObject, 3 )
   METHOD		GetStringVal()			INLINE	xmlXPathObjectGetProperty( ::pXPathObject, 4 )
   
   // underlying XMLXPathObjectPtr
   DATA pXPathObject AS OBJECT

   DATA oNodeSet AS OBJECT // XMLNodeSet

END CLASS



METHOD New( pXPathObject AS OBJECT ) CLASS XMLXPathObject

	Local pNodeSetVal

	::Super:New()

   ::pXPathObject := pXPathObject

   IF ( !IsNullOrEmpty( ::pXPathObject ) )

      DO CASE

		  CASE ::GetType() == XPATH_NODESET

			 pNodeSetVal := ::GetNodeSetVal() 
			 
			 IF ( !IsNullOrEmpty( pNodeSetVal ) )
		  
				::oNodeSet := XMLNodeSet():FromPtr( pNodeSetVal )
			 
			 ENDIF

      ENDCASE

   ENDIF

RETURN Self

METHOD Eval( bBlock AS OBJECT )  CLASS XMLXPathObject

   IF ( !IsNullOrEmpty( ::pXPathObject ) )

      DO CASE

		  CASE ::GetType() == XPATH_NODESET

			 IF ( ::oNodeSet != NIL )
			 
				::oNodeSet:Eval( bBlock )
				
			ENDIF

		  CASE ::GetType() == XPATH_BOOLEAN

			 Eval( bBlock, ::GetBoolVal() )

		  CASE ::GetType() == XPATH_NUMBER

			 ::Throw( "XPATH_NUMBER - unsupported" )

		  CASE ::GetType() == XPATH_STRING

			 Eval( bBlock, ::GetStringVal() )

      ENDCASE

   ENDIF

RETURN NIL

METHOD Free() CLASS XMLXPathObject

   IF ( !IsNullOrEmpty ( ::pXPathObject ) )

      xmlXPathFreeObject( ::pXPathObject )

   ENDIF

RETURN NIL
