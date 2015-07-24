
/*
libxml2

XPath API

http://xmlsoft.org
*/

#include "hbclass.ch"
#include "hbxml2.ch"

CREATE CLASS XMLXPathContext INHERIT XMLBase

   METHOD New( doc AS Object )


   METHOD SetContextNode( node AS OBJECT )
   METHOD XPathEval( expr AS Character )

   METHOD Free()


   PROTECTED:

   // underlying xmlXPathContextPtr
   DATA pXPathContext AS OBJECT

END CLASS

METHOD New( doc as OBJECT ) CLASS XMLXPathContext

	::Super:New()

   ::pXPathContext := xmlXPathNewContext( doc:GetPtr() )

RETURN Self


METHOD SetContextNode( node AS OBJECT ) CLASS XMLXPathContext

   LOCAL res

   IF ( !IsNullOrEmpty( ::pXPathContext ) .AND. node != NIL )

      res := xmlXPathSetContextNode ( node:GetPtr(), ::pXPathContext )

   ENDIF

RETURN res

METHOD XPathEval( expr AS Character ) CLASS XMLXPathContext

   LOCAL pXPathObj
   LOCAL oXPathObj

   IF ( !IsNullOrEmpty( ::pXPathContext ) )

      pXPathObj := xmlXPathEval( expr, ::pXPathContext )

   ENDIF

   IF ( !IsNullOrEmpty( pXPathObj ) )

      oXPathObj := XMLXPathObject():New( pXPathObj )

   ENDIF

RETURN oXPathObj

METHOD Free() CLASS XMLXPathContext

   IF ( !IsNullOrEmpty( ::pXPathContext ) )

      xmlXPathFreeContext( ::pXPathContext )

   ENDIF

RETURN NIL
