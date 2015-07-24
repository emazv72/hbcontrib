/*

libxml2

APIs

http://xmlsoft.org

*/

#include <windows.h>
#include <string.h>
#include <time.h>

#include "hbapi.h"
#include "hbapierr.h"
#include "hbapiitm.h"
#include "hbwinuni.h"
#include "hbstack.h"
#include "hbvm.h"

#include <libxml/parser.h>
#include <libxml/encoding.h>
#include <libxml/xpath.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>

#define XML_UTF8_HB_CDP  "UTF8EX"

HB_FUNC( XMLGETCHARENCODINGNAME );

/*xmlTextReader API*/

HB_FUNC( XMLNEWTEXTREADERFILENAME );
HB_FUNC( XMLTEXTREADERREAD );
HB_FUNC( XMLTEXTREADERNEXT );
HB_FUNC( XMLFREETEXTREADER );
HB_FUNC( XMLTEXTREADERNAME );
HB_FUNC( XMLTEXTREADERVALUE );
HB_FUNC( XMLTEXTREADERNODETYPE );
HB_FUNC( XMLTEXTREADEREXPAND );

/*xmlTextWriter API*/

HB_FUNC( XMLNEWTEXTWRITERFILENAME );
HB_FUNC( XMLTEXTWRITERSTARTDOCUMENT );
HB_FUNC( XMLTEXTWRITERSTARTELEMENT );
HB_FUNC( XMLTEXTWRITERWRITEATTRIBUTE );
HB_FUNC( XMLTEXTWRITERWRITEELEMENT );
HB_FUNC( XMLTEXTWRITERENDELEMENT );
HB_FUNC( XMLTEXTWRITERENDDOCUMENT );
HB_FUNC( XMLFREETEXTWRITER );

/*Parser*/

HB_FUNC( XMLNEWPARSERCTXT );
HB_FUNC( XMLCTXTREADFILE );
HB_FUNC( XMLCTXTREADMEMORY );
HB_FUNC( XMLFREEPARSERCTXT );

/*Tree API*/
HB_FUNC( XMLDOCGETROOTELEMENT );
HB_FUNC( XMLDOCSETROOTELEMENT );

HB_FUNC( XMLNEWDOC );
HB_FUNC( XMLFREEDOC );
//HB_FUNC ( XMLNEWNODE);
HB_FUNC( XMLNODEGETPROPERTY );
HB_FUNC( XMLUNLINKNODE  );
HB_FUNC( XMLFIRSTELEMENTCHILD  );
HB_FUNC( XMLNEXTELEMENTSIBLING );
HB_FUNC( XMLNODEGETCONTENT );

HB_FUNC( XMLGETPROP );

/*XPath API*/
HB_FUNC( XMLXPATHNEWCONTEXT );
HB_FUNC( XMLXPATHFREECONTEXT );
HB_FUNC( XMLXPATHSETCONTEXTNODE );
HB_FUNC( XMLXPATHEVAL );
HB_FUNC( XMLXPATHFREEOBJECT );

HB_FUNC( XMLXPATHOBJECTGETPROPERTY );
HB_FUNC( XMLXPATHNODESETGETPROPERTY );
// HB_FUNC(XMLXPATHNODEEVAL);


/////
HB_FUNC( XMLGETLASTERROR );
HB_FUNC( XMLERRORGETPROPERTY );

HB_FUNC( XMLERRORSETBLOCK );
HB_FUNC( XMLERRORFREEBLOCK );


// C
static char* 	xml_cdpUTF8ToStr( xmlChar * szStr, HB_SIZE * pnLen, const char * pszCdpOut );
static xmlChar* xml_cdpStrToUTF8( const char * szStr, HB_SIZE * pnLen, const char * pszCdpIn );
static void 	xml_errorHandler(void *unused, xmlErrorPtr err);