
/*
libxml2

TextReader API

http://xmlsoft.org
*/

#include "hbclass.ch"
#include "hbxml2.ch"

CREATE CLASS XMLTextReader INHERIT XMLBase

 /*
 Create a reader
 */

   METHOD New( fileName AS Character )

 /*
 Release resources
 */
   METHOD Free()


 /*
 Moves the position of the current instance to the next node in the stream, exposing its properties.

 Returns:
   1 in case of success,
   0 if the reader was not positionned on an ttribute node or all the attribute values have been read
   -1 in case of error.

 */
   METHOD Read()

 /*
 Skip to the node following the current one in document order while avoiding the subtree if any.
 Returns:
  1 if the node was read successfully
  0 if there is no more nodes to read
  -1 in case of error
 */
   METHOD Next()

 /*
 The qualified name of the node, equal to Prefix :LocalName.

 Returns: the local name or NULL if not available
 */
   METHOD Name()

 /*
 Provides the text value of the node if present

 Returns: the string or NULL if not available
 */
   METHOD Value()

  /*
 Get the node type of the current node Reference: http://www.gnu.org/software/dotgnu/pnetlib-doc/System/Xml/XmlNodeType.html

 Returns:
  the xmlNodeType of the current node or -1 in case of error

 */
   METHOD NodeType()

 /*
 Reads the contents of the current node and the full subtree. It then makes the subtree available until the next xmlTextReaderRead() call

 Returns: XMLNode
       a node valid until the next xmlTextReaderRead() call or NULL in case of error.

 */
   METHOD Expand()

 /*
 Hacking interface allowing to get the xmlDocPtr correponding to the current document being accessed by the xmlTextReader. NOTE: as a result of this call,
 the reader will not destroy the associated XML document and calling xmlFreeDoc() on the result is needed once the reader parsing has finished.

  Returns: XMLDoc or NULL in case of error.

 */
   // METHOD CurrentDoc()


   PROTECTED:

   // underlying xmlTextReaderPtr
   DATA pReader AS OBJECT

END CLASS

METHOD New( fileName AS Character ) CLASS XMLTextReader

	::Super:New()

   ::pReader = xmlNewTextReaderFilename( filename )

RETURN Self

METHOD Read() CLASS XMLTextReader

   Local result := -1

   IF ( !IsNullOrEmpty( ::pReader ) )
   
		result := xmlTextReaderRead( ::pReader )
   
   ENDIF

RETURN result

METHOD Next() CLASS XMLTextReader

   Local result := -1

   IF ( !IsNullOrEmpty( ::pReader ) )
   
		result := xmlTextReaderNext( ::pReader )
   
   ENDIF

RETURN result

METHOD Free() CLASS XMLTextReader

	IF ( !IsNullOrEmpty( ::pReader ) )

		xmlFreeTextReader( ::pReader )

	ENDIF

RETURN NIL

METHOD Name() CLASS XMLTextReader

   Local result

   IF ( !IsNullOrEmpty( ::pReader ) )
   
		result := xmlTextReaderName( ::pReader )
   
   ENDIF

RETURN result

METHOD Value() CLASS XMLTextReader

   Local result

   IF ( !IsNullOrEmpty( ::pReader ) )
   
		result :=  xmlTextReaderValue( ::pReader )
   
   ENDIF

RETURN result

METHOD NodeType() CLASS XMLTextReader

   Local result

   IF ( !IsNullOrEmpty( ::pReader ) )
   
		result :=  xmlTextReaderNodeType( ::pReader )
   
   ENDIF

RETURN result

METHOD Expand() CLASS XMLTextReader

   Local result

   IF ( !IsNullOrEmpty( ::pReader ) )
   
		result :=  XMLNode():FromPtr( xmlTextReaderExpand( ::pReader ) )
   
   ENDIF

RETURN result

