#ifndef _HBXML2_CH

#define  _HBXML2_CH

#define XML_DEFAULT_VERSION				"1.0"
 
//xmlCharEncoding;

#define    XML_CHAR_ENCODING_ERROR     -1 /* No char encoding detected */
#define    XML_CHAR_ENCODING_NONE 	    0 /* No char encoding detected */
#define    XML_CHAR_ENCODING_UTF8 	    1 /* UTF-8 */
#define    XML_CHAR_ENCODING_UTF16LE 	2 /* UTF-16 little endian */
#define    XML_CHAR_ENCODING_UTF16BE 	3 /* UTF-16 big endian */
#define    XML_CHAR_ENCODING_UCS4LE 	4 /* UCS-4 little endian */
#define    XML_CHAR_ENCODING_UCS4BE 	5 /* UCS-4 big endian */
#define    XML_CHAR_ENCODING_EBCDIC 	6 /* EBCDIC uh! */
#define    XML_CHAR_ENCODING_UCS4_2143  7 /* UCS-4 unusual ordering */
#define    XML_CHAR_ENCODING_UCS4_3412  8 /* UCS-4 unusual ordering */
#define    XML_CHAR_ENCODING_UCS2 		9 /* UCS-2 */
#define    XML_CHAR_ENCODING_8859_1 	10/* ISO-8859-1 ISO Latin 1 */
#define    XML_CHAR_ENCODING_8859_2 	11/* ISO-8859-2 ISO Latin 2 */
#define    XML_CHAR_ENCODING_8859_3 	12/* ISO-8859-3 */
#define    XML_CHAR_ENCODING_8859_4 	13/* ISO-8859-4 */
#define     XML_CHAR_ENCODING_8859_5 	14/* ISO-8859-5 */
#define     XML_CHAR_ENCODING_8859_6 	15/* ISO-8859-6 */
#define     XML_CHAR_ENCODING_8859_7 	16/* ISO-8859-7 */
#define     XML_CHAR_ENCODING_8859_8 	17/* ISO-8859-8 */
#define     XML_CHAR_ENCODING_8859_9 	18/* ISO-8859-9 */
#define     XML_CHAR_ENCODING_2022_JP   19/* ISO-2022-JP */
#define     XML_CHAR_ENCODING_SHIFT_JIS 20/* Shift_JIS */
#define     XML_CHAR_ENCODING_EUC_JP    21/* EUC-JP */
#define     XML_CHAR_ENCODING_ASCII     22 /* pure ASCII */
 
// xmlElementType

#define     XML_ELEMENT_NODE		1
#define     XML_ATTRIBUTE_NODE		2
#define     XML_TEXT_NODE		3
#define     XML_CDATA_SECTION_NODE	4
#define     XML_ENTITY_REF_NODE	5
#define     XML_ENTITY_NODE		6
#define     XML_PI_NODE		7
#define     XML_COMMENT_NODE		8
#define     XML_DOCUMENT_NODE		9
#define     XML_DOCUMENT_TYPE_NODE	10
#define     XML_DOCUMENT_FRAG_NODE	11
#define     XML_NOTATION_NODE		12
#define     XML_HTML_DOCUMENT_NODE	13
#define     XML_DTD_NODE		14
#define     XML_ELEMENT_DECL		15
#define     XML_ATTRIBUTE_DECL		16
#define     XML_ENTITY_DECL		17
#define     XML_NAMESPACE_DECL		18
#define     XML_XINCLUDE_START		19
#define     XML_XINCLUDE_END		20

// xmlXPathObjectType
#define XPATH_UNDEFINED 0
#define XPATH_NODESET  1
#define XPATH_BOOLEAN  2
#define XPATH_NUMBER  3
#define XPATH_STRING  4
#define XPATH_POINT  5
#define XPATH_RANGE  6
#define XPATH_LOCATIONSET  7
#define XPATH_USERS  8
#define XPATH_XSLT_TREE  9  /* An XSLT value tree non modifiable */

//xmlParserOption 
#define XML_PARSE_RECOVER  1 // recover on errors
#define XML_PARSE_NOENT  2 // substitute entities
#define XML_PARSE_DTDLOAD  4 // load the external subset
#define XML_PARSE_DTDATTR  8 // default DTD attributes
#define XML_PARSE_DTDVALID  16 // validate with the DTD
#define XML_PARSE_NOERROR  32 // suppress error reports
#define XML_PARSE_NOWARNING  64 // suppress warning reports
#define XML_PARSE_PEDANTIC  128 // pedantic error reporting
#define XML_PARSE_NOBLANKS  256 // remove blank nodes
#define XML_PARSE_SAX1  512 // use the SAX1 interface internally
#define XML_PARSE_XINCLUDE  1024 // Implement XInclude substitition
#define XML_PARSE_NONET  2048 // Forbid network access
#define XML_PARSE_NODICT  4096 // Do not reuse the context dictionnary
#define XML_PARSE_NSCLEAN  8192 // remove redundant namespaces declarations
#define XML_PARSE_NOCDATA  16384 // merge CDATA as text nodes
#define XML_PARSE_NOXINCNODE  32768 // do not generate XINCLUDE START/END nodes
#define XML_PARSE_COMPACT  65536 // compact small text nodes; no modification of the tree allowed afterwards (will possibly crash if you try to modify the tree)
#define XML_PARSE_OLD10  131072 // parse using XML-1.0 before update 5
#define XML_PARSE_NOBASEFIX  262144 // do not fixup XINCLUDE xml//base uris
#define XML_PARSE_HUGE  524288 // relax any hardcoded limit from the parser
#define XML_PARSE_OLDSAX  1048576 // parse using SAX2 interface before 2.7.0
#define XML_PARSE_IGNORE_ENC  2097152 // ignore internal document encoding hint
#define XML_PARSE_BIG_LINES  4194304 // Store big lines numbers in text PSVI field

// xmlReaderTypes -> XMLTextReader:NodeType()

#define     XML_READER_TYPE_NONE  					0
#define     XML_READER_TYPE_ELEMENT  				1
#define     XML_READER_TYPE_ATTRIBUTE  				2
#define     XML_READER_TYPE_TEXT  					3
#define     XML_READER_TYPE_CDATA  					4
#define     XML_READER_TYPE_ENTITY_REFERENCE  		5
#define     XML_READER_TYPE_ENTITY  				6
#define     XML_READER_TYPE_PROCESSING_INSTRUCTION  7
#define     XML_READER_TYPE_COMMENT  				8
#define     XML_READER_TYPE_DOCUMENT  				9
#define     XML_READER_TYPE_DOCUMENT_TYPE  			10
#define     XML_READER_TYPE_DOCUMENT_FRAGMENT  		11
#define     XML_READER_TYPE_NOTATION  				12
#define     XML_READER_TYPE_WHITESPACE  			13
#define     XML_READER_TYPE_SIGNIFICANT_WHITESPACE  14
#define     XML_READER_TYPE_END_ELEMENT  			15
#define     XML_READER_TYPE_END_ENTITY  			16
#define     XML_READER_TYPE_XML_DECLARATION  		17

#endif