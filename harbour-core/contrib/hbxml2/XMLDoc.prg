

/*

libxml2

Module tree

http://xmlsoft.org/html/libxml-tree.html

*/

#include "hbclass.ch"
#include "hbxml2.ch"

CREATE CLASS XMLDoc INHERIT XMLBase

   METHOD New()

   METHOD FromPtr( pDoc AS Object )

   METHOD GetPtr()

   METHOD XPathContext()

   METHOD GetRootElement()

   METHOD SetRootElement(oNodeRoot AS Object)
   
   METHOD Free()

   PROTECTED:

   // underlying XMLDocPtr
   DATA pDoc AS OBJECT

END CLASS

METHOD New() CLASS XMLDoc

	::Super:New()

	::pDoc := xmlNewDoc( XML_DEFAULT_VERSION )

RETURN Self

METHOD FromPtr( pDoc AS Object )  CLASS XMLDoc

	::Super:New()

	IF (!IsNullOrEmpty(pDoc))

		::pDoc := pDoc

	ELSE

		::Throw("Invalid Document")

	ENDIF

RETURN Self

METHOD GetRootElement() CLASS XMLDoc

   LOCAL oNode
   LOCAL pNode

   IF ( !IsNullOrEmpty( ::pDoc ) )

      pNode := xmlDocGetRootElement( ::pDoc )

      IF ( !IsNullOrEmpty( pNode ) )

         oNode := XMLNode():FromPtr( pNode  )

      ENDIF

   ENDIF

RETURN oNode

METHOD SetRootElement(oNodeRoot AS Object)  CLASS XMLDoc
	
	Local pNode
	
	IF ( !IsNullOrEmpty( ::pDoc ) )

      pNode := xmlDocSetRootElement( ::pDoc, oNodeRoot:GetPtr() )

   ENDIF

RETURN pNode

METHOD Free() CLASS XMLDoc

   IF ( !IsNullOrEmpty( ::pDoc ) )

      xmlFreeDoc( ::pDoc )

   ENDIF

RETURN NIL

METHOD XPathContext() CLASS XMLDoc

RETURN XMLXPathContext():New( Self )

METHOD GetPtr() CLASS XMLDoc

RETURN ::pDoc
