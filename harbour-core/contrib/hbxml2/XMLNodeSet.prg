
/*
libxml2

http://xmlsoft.org
*/

#include "hbclass.ch"
#include "hbxml2.ch"


CREATE CLASS XMLNodeSet INHERIT XMLBase

   
   METHOD FromPtr( pNodeSet AS Object )


   METHOD Eval( bBlock AS OBJECT )

   PROTECTED:

   METHOD	GetNodeNr()			    INLINE	xmlXPathNodeSetGetProperty( ::pNodeSet, 1)
   METHOD	GetNodeMax()			INLINE	xmlXPathNodeSetGetProperty( ::pNodeSet, 2)
   METHOD	GetNodeTab()			INLINE	xmlXPathNodeSetGetProperty( ::pNodeSet, 3)
   
   /* WARNING The nodes in this node-set point to the nodes in the original XML document*/
   // underlying XMLNodeSetPtr
   DATA pNodeSet AS OBJECT

END CLASS

// METHOD New( ) CLASS XMLNodeSet

// Return Self

METHOD FromPtr( pNodeSet AS Object ) CLASS XMLNodeSet

	::Super:New()

   IF ( !IsNullOrEmpty( pNodeSet ) )

      ::pNodeSet := pNodeSet

   ELSE

      ::Throw("Invalid NodeSet")

   ENDIF

RETURN Self

METHOD Eval( bBlock AS OBJECT )  CLASS XMLNodeSet

   LOCAL pNode
   Local nodeNr := ::GetNodeNr()
   Local nodeTab := ::GetNodeTab()
   
   IF ( nodeNr > 0 )
		
	  FOR EACH pNode IN nodeTab
	
		 Eval ( bBlock, XMLNode():FromPtr( pNode ) )
			
      NEXT

   ENDIF

RETURN NIL
