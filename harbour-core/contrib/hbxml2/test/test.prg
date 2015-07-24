/*

libxml2

Test API

http://xmlsoft.org/html/libxml-tree.html

*/

#include "hbxml2.ch"

Function Main()

	Local reader, writer
	Local node, xPathObj
	Local tmp

	Local oCtx 
	Local oDoc 
	Local oRootNode 

	? "DOM parser"
  
	oCtx := XMLParserContext():New( )
	oDoc := oCtx:ReadFile("simple.xml")
	
	IF ( oDoc != NIL )
		
		oRootNode := oDoc:GetRootElement()
		
		IF ( oRootNode  != NIL )

				oRootNode:Dump()
		
		ENDIF
		
		oDoc:Free()
	
	ENDIF
	
	oCtx:Free()


	? "SAX like - parser"

	// Leggo il file
	reader := XmlTextReader():New( "simple.xml" )

	  // keep reading
	  DO WHILE ( reader:Read() > 0  )

		 // node reached
		 IF ( reader:Name() == "test" )

			// expand nodes ( mandatory for xpath )
			node := reader:Expand()

			// evaluate xpath
			xPathObj := node:XPathEval( "//node" )

			IF ( xPathObj == NIL )

			   ? "XML Error"

			ELSE

			   // evaluates a code block for each node in the path result set
			   xPathObj:Eval( {| n| ProcessNode( n ) } )

			   // Release 
			   xPathObj:Free()

			ENDIF

			EXIT

		 ENDIF

	  ENDDO


   reader:Free()

   ENDIF
   
   ? "SAX like - Writer"

   writer := XmlTextWriter():New( "test-out.xml" )

   writer:StartDocument( XML_CHAR_ENCODING_8859_1 )

   writer:StartElement( "EXAMPLE" )

   writer:WriteAttribute( "version", "1.0" )

   writer:WriteElement( "NAME_1", "<>&à" )
   
   tmp := "12345"
   hb_MemoWrit("test.txt", tmp) 

   writer:WriteElement( "NAME_1", hb_MemoRead( "test.txt" ) )

   writer:EndDocument()

   writer:Free()

RETURN NIL


STATIC FUNCTION ProcessNode( n )

   LOCAL node

   // first child of type element
   node := n:FirstElementChild()

   // loop through siblings
   DO WHILE ( ( node := node:NextElementSibling() ) != NIL )

      ?  node:GetName()  +  node:GetContent() )

   ENDDO

RETURN NIL

