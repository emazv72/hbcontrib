
/*
libxml2

TextWriter API

http://xmlsoft.org
*/

#include "hbclass.ch"
#include "hbxml2.ch"

CREATE CLASS XMLTextWriter INHERIT XMLBase

 /*
 Create a writer
 */

	METHOD New( fileName AS Character, compression AS Logical )

 /*
 Release resources
 */
   METHOD Free()


   METHOD StartDocument( encoding AS Numeric, standalone AS Logical )

   METHOD StartElement( name  AS Character )

   METHOD WriteAttribute( name  AS Character, content AS Character )

   METHOD WriteElement( name  AS Character, content AS Character )

   METHOD EndElement()

   METHOD EndDocument()

   // Misc
   
   METHOD SetAutoTrim( autoTrim as Logical)		 
   
   PROTECTED:

   // underlying XMLTextWriterPtr
   DATA pWriter AS OBJECT

   DATA encodingName AS Character
   
   DATA autoTrim AS Logical

END CLASS

METHOD New( fileName AS Character, compression AS Logical ) CLASS XMLTextWriter

	::Super:New()

   IF ( compression == NIL )

      compression := .F.

   ENDIF

   ::autoTrim := .F.
   
   ::pWriter := xmlNewTextWriterFilename( filename, compression )

RETURN Self


METHOD StartDocument( encoding AS Numeric, standalone AS Logical )  CLASS XMLTextWriter

   LOCAL strStandalone
   LOCAL ret

   IF ( encoding != NIL)
      
	  ::encodingName := xmlGetCharEncodingName(encoding)
   
   ELSE
   
	  ::encodingName := xmlGetCharEncodingName(XML_CHAR_ENCODING_UTF8)
   
   ENDIF

   IF ( standalone != NIL )
      
	  strStandalone := iif ( standalone, "yes", "no" )
   
   ENDIF

   IF ( !IsNullOrEmpty( ::pWriter ) )

      ret := xmlTextWriterStartDocument( ::pWriter, XML_DEFAULT_VERSION, ::encodingName, strStandalone )

   ENDIF

RETURN ret

METHOD StartElement( name  AS Character ) CLASS XMLTextWriter

   LOCAL ret

   IF ( !IsNullOrEmpty( ::pWriter )  )

      ret := xmlTextWriterStartElement( ::pWriter, name )

   ENDIF

RETURN ret

METHOD WriteAttribute( name  AS Character, content AS Character ) CLASS XMLTextWriter

   LOCAL ret

   IF ( ::autoTrim )
   
		content := ALLTRIM( content )
	
   ENDIF
   
   IF ( !IsNullOrEmpty( ::pWriter ) )

      ret := xmlTextWriterWriteAttribute( ::pWriter, name, content )

   ENDIF

RETURN ret

METHOD WriteElement( name  AS Character, content AS Character ) CLASS XMLTextWriter

   LOCAL ret

   IF ( !HB_ISSTRING( name ))
   
	::Throw("Errore ( name )")
   
   ENDIF

   IF ( content == NIL)
   
	content := ""
   
   ENDIF
   
   IF ( !HB_ISSTRING( content ))
   
	::Throw("Errore ( content )")
   
   ENDIF
   
   IF ( ::autoTrim )
   
		content := ALLTRIM( content )
	
   ENDIF

   IF ( !IsNullOrEmpty( ::pWriter ) )

	 ret := xmlTextWriterWriteElement( ::pWriter, name, content )

   ENDIF

RETURN ret

METHOD EndElement() CLASS XMLTextWriter

   LOCAL ret

   IF ( !IsNullOrEmpty( ::pWriter ) )

      ret := xmlTextWriterEndElement( ::pWriter )

   ENDIF

RETURN ret

METHOD EndDocument() CLASS XMLTextWriter

   LOCAL ret

   IF ( !IsNullOrEmpty( ::pWriter ) )

      ret := xmlTextWriterEndDocument( ::pWriter )

   ENDIF

RETURN ret

METHOD Free() CLASS XMLTextWriter

   IF ( !IsNullOrEmpty( ::pWriter ) )

      xmlFreeTextWriter( ::pWriter )

   ENDIF

RETURN NIL

METHOD SetAutoTrim( autoTrim as Logical)	 CLASS XMLTextWriter	 

	::autoTrim := autoTrim

RETURN NIL