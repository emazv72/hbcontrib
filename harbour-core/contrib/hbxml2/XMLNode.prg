
/*
libxml2  - Module tree

http://xmlsoft.org
*/

#include "hbclass.ch"
#include "hbxml2.ch"

CREATE CLASS XMLNode INHERIT XMLBase

   // TODO
   // METHOD New( ns AS Character, name AS Character)

   METHOD FromPtr( pNode AS Object )
   METHOD GetPtr()

   METHOD GetChildren()
   METHOD GetNext()
   METHOD GetDoc()

   METHOD FirstElementChild()
   METHOD NextElementSibling()
   METHOD GetContent()

   METHOD Unlink()
   
   METHOD GetType()     INLINE XmlNodeGetProperty ( ::pNode, 1 )
   METHOD GetName()     INLINE XmlNodeGetProperty ( ::pNode, 2 )

   METHOD GetProp( name AS Character )

   METHOD XPathEval( expr AS Character )

   METHOD Free()

   METHOD Dump()

   PROTECTED:

   METHOD DumpInternal(  indent AS Numeric, oNode AS Object )


   // underlying XMLNodePtr
   DATA pNode AS OBJECT

END CLASS

// METHOD New( ns AS Character, name AS Character) CLASS XMLNode

// ::pNode := xmlNewNode(ns, name)

// Return Self

METHOD FromPtr( pNode AS Object ) CLASS XMLNode

	::Super:New()

   IF ( !IsNullOrEmpty( pNode  ) )

      ::pNode := pNode

   ELSE

      ::Throw("Invalid Node" )

   ENDIF

RETURN Self

METHOD GetPtr() CLASS XMLNode

RETURN ::pNode

METHOD Free() CLASS XMLNode

RETURN NIL

METHOD GetDoc() CLASS XMLNode

   LOCAL oDoc
   LOCAL pDoc

   IF ( !IsNullOrEmpty( ::pNode ) )

      pDoc := XmlNodeGetProperty( ::pNode, 8 )

      IF ( !( IsNullOrEmpty( pDoc ) ) )

         oDoc := XMLDoc():FromPtr( pDoc )

      ENDIF

   ENDIF

RETURN oDoc

METHOD GetChildren() CLASS XMLNode

   LOCAL oNode
   LOCAL pNodeResult

   IF ( !IsNullOrEmpty( ::pNode ) )

      pNodeResult := XmlNodeGetProperty( ::pNode, 3 )

      IF ( !( IsNullOrEmpty( pNodeResult ) ) )

         oNode := XMLNode():FromPtr( pNodeResult )

      ENDIF

   ENDIF

RETURN oNode

METHOD GetNext() CLASS XMLNode

   LOCAL oNode
   LOCAL pNodeResult

   IF ( !IsNullOrEmpty( ::pNode ) )

      pNodeResult := XmlNodeGetProperty( ::pNode, 6 )

      IF ( !( IsNullOrEmpty( pNodeResult ) ) )

         oNode := XMLNode():FromPtr( pNodeResult )

      ENDIF

   ENDIF

RETURN oNode

METHOD FirstElementChild() CLASS XMLNode

   LOCAL oChild
   LOCAL pChild

   IF ( !IsNullOrEmpty( ::pNode ) )

      pChild := xmlFirstElementChild( ::pNode )

      IF ( !IsNullOrEmpty( pChild ) )

         oChild := XMLNode():FromPtr( pChild  )

      ENDIF

   ENDIF

RETURN oChild

METHOD GetContent() CLASS XMLNode

   LOCAL content

   IF ( !IsNullOrEmpty( ::pNode ) )

      content := xmlNodeGetContent( ::pNode )

   ENDIF

RETURN content

METHOD Unlink()  CLASS XMLNode

   IF ( !IsNullOrEmpty( ::pNode ) )

      xmlUnlinkNode( ::pNode )

   ENDIF

   
RETURN NIL

METHOD GetProp( name AS Character )  CLASS XMLNode

   LOCAL value

   IF ( !IsNullOrEmpty( ::pNode ) )

      value := xmlGetProp( ::pNode, name )

   ENDIF

RETURN value

METHOD NextElementSibling() CLASS XMLNode

   LOCAL oSibling
   LOCAL pSibling

   IF ( !IsNullOrEmpty( ::pNode ) )

      pSibling := xmlNextElementSibling( ::pNode )

      IF ( !IsNullOrEmpty( pSibling ) )

         oSibling := XMLNode():FromPtr( pSibling  )

      ENDIF

   ENDIF

RETURN oSibling


METHOD XPathEval( expr AS Character ) CLASS XMLNode

   LOCAL oDoc
   LOCAL oCtx
   LOCAL oXPathObj

   oDoc := ::GetDoc()

   IF ( oDoc == NIL )

      RETURN NIL

   ENDIF

   oCtx := oDoc:XPathContext()

   IF ( oCtx  != NIL )

	   IF ( oCtx:SetContextNode( Self )  == 0 )

		  oXPathObj := oCtx:XPathEval( expr )

		  oCtx:Free()

	   ENDIF

   ENDIF
   
RETURN oXPathObj


METHOD Dump() CLASS XMLNode

   LogWrite( "XMLNode:Dump", "Inizio" )

   ::DumpInternal( 0, Self )

   LogWrite( "XMLNode:Dump", "Fine" )

RETURN NIL

METHOD DumpInternal(  indent AS Numeric, oNode AS Object ) CLASS XMLNode

   LOCAL oCurr := oNode

   DO WHILE oCurr != NIL

      IF oCurr:GetType() == XML_ELEMENT_NODE

         LogWrite( "XMLNode:Dump", "-->" + Space( indent ) + oCurr:GetName() )

      ENDIF

      ::DumpInternal( indent + 1, oCurr:GetChildren() )

      oCurr := oCurr:GetNext()

   ENDDO

RETURN NIL

