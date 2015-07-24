
/*

libxml2

APIs

http://xmlsoft.org

*/

#include "hbxml2.h"

typedef struct _XML_HANDLER
{
   PHB_ITEM pErrorBlock;
} XML_HANDLER, * PXML_HANDLER;

static PXML_HANDLER pHandler = NULL;

//xmlGetCharEncodingName( nEncoding ) -> name
HB_FUNC( XMLGETCHARENCODINGNAME )
{
   if( HB_ISNUM( 1 ) )
      hb_retc( xmlGetCharEncodingName( hb_parni( 1 ) ) );
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}


/* TextReader */

//xmlNewTextReaderFilename( filename) -> reader
HB_FUNC( XMLNEWTEXTREADERFILENAME )
{

   if( HB_ISCHAR( 1 ) )
   {

      xmlTextReaderPtr reader = xmlNewTextReaderFilename( hb_parc( 1 ) );

      hb_retptr( reader );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

//xmlTextReaderRead( reader ) -> ret
HB_FUNC( XMLTEXTREADERREAD )
{

   if( HB_ISPOINTER( 1 ) )
   {

      xmlTextReaderPtr reader = ( xmlTextReaderPtr ) hb_parptr( 1 );

      if( reader )
         hb_retni( xmlTextReaderRead( reader ) );
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

//xmlTextReaderNext( reader ) -> ret
HB_FUNC( XMLTEXTREADERNEXT )
{

   if( HB_ISPOINTER( 1 ) )
   {

      xmlTextReaderPtr reader = ( xmlTextReaderPtr ) hb_parptr( 1 );

      if( reader )
         hb_retni( xmlTextReaderNext( reader ) );
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlFreeTextReader(reader) -> NIL

HB_FUNC( XMLFREETEXTREADER )
{
   if( HB_ISPOINTER( 1 ) )
   {
      xmlTextReaderPtr reader = ( xmlTextReaderPtr ) hb_parptr( 1 );

      if( reader )
         xmlFreeTextReader( reader );
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   hb_ret();
}

// xmlTextReaderName(reader, [cdp]) -> name
HB_FUNC( XMLTEXTREADERNAME )
{
   if( HB_ISPOINTER( 1 ) )
   {

      xmlTextReaderPtr reader = ( xmlTextReaderPtr ) hb_parptr( 1 );

      if( reader )
      {
         char *  szDest = NULL;
         HB_SIZE nDest  = 0;

         xmlChar * name = xmlTextReaderName( reader );

         if( name )
         {
            nDest  = xmlStrlen( name );
            szDest = xml_cdpUTF8ToStr( name, &nDest, hb_parc( 2 ) );

            xmlFree( name );
         }

         if( szDest )
            hb_retclen_buffer( szDest, nDest );
         else
            hb_retc_null();
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

// xmlTextReaderValue(reader, [cdp]) -> value

HB_FUNC( XMLTEXTREADERVALUE )
{
   if( HB_ISPOINTER( 1 ) )
   {
      xmlTextReaderPtr reader = ( xmlTextReaderPtr ) hb_parptr( 1 );

      if( reader )
      {
         char *  szDest = NULL;
         HB_SIZE nDest  = 0;

         xmlChar * value = xmlTextReaderValue( reader );

         if( value )
         {
            nDest  = xmlStrlen( value );
            szDest = xml_cdpUTF8ToStr( value, &nDest, hb_parc( 2 ) );

            xmlFree( value );

         }

         if( szDest )
            hb_retclen_buffer( szDest, nDest );
         else
            hb_retc_null();


      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlTextReaderNodeType(reader) -> nodeType
HB_FUNC( XMLTEXTREADERNODETYPE )
{

   if( HB_ISPOINTER( 1 ) )
   {
      xmlTextReaderPtr reader = ( xmlTextReaderPtr ) hb_parptr( 1 );

      if( reader )
      {
         hb_retni( xmlTextReaderNodeType( reader ) );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlTextReaderExpand(reader) -> node
HB_FUNC( XMLTEXTREADEREXPAND )
{
   if( HB_ISPOINTER( 1 ) )
   {
      xmlTextReaderPtr reader = ( xmlTextReaderPtr ) hb_parptr( 1 );

      if( reader )
      {

         xmlNodePtr node = xmlTextReaderExpand( reader );

         hb_retptr( node );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}


/* XmlTextWriter */


//xmlNewTextWriterFilename( filename, compression) -> writer

HB_FUNC( XMLNEWTEXTWRITERFILENAME )
{

   if( HB_ISCHAR( 1 ) && HB_ISLOG( 2 ) )
   {

      xmlTextWriterPtr writer = xmlNewTextWriterFilename( hb_parc( 1 ), hb_parl( 2 ) );

      hb_retptr( writer );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

// xmlTextWriterStartDocument( writer, version, encoding, [standalone] ) -> ok
HB_FUNC( XMLTEXTWRITERSTARTDOCUMENT )
{

   if( HB_ISPOINTER( 1 ) && HB_ISCHAR( 2 ) && HB_ISCHAR( 3 ) )
   {

      xmlTextWriterPtr writer = ( xmlTextWriterPtr ) hb_parptr( 1 );

      if( writer )
      {

         int res = xmlTextWriterStartDocument( writer,
                                               ( const char * ) hb_parc( 2 ),
                                               ( const char * ) hb_parc( 3 ),
                                               ( const char * ) hb_parc( 4 ) );

         hb_retni( res );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlTextWriterStartElement( writer, name, [cdp]) -> ok
HB_FUNC( XMLTEXTWRITERSTARTELEMENT )
{

   if( HB_ISPOINTER( 1 ) && HB_ISCHAR( 2 ) )
   {

      xmlTextWriterPtr writer = ( xmlTextWriterPtr ) hb_parptr( 1 );

      if( writer )
      {

         const char * name     = hb_parc( 2 );
         HB_SIZE      nNameLen = hb_parclen( 2 );

         xmlChar * szNameUTF8 = xml_cdpStrToUTF8( name, &nNameLen, hb_parc( 3 ) );

         int res = xmlTextWriterStartElement( writer,
                                              szNameUTF8 );

         hb_retni( res );
      }
      else
        hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
     hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}
// xmlTextWriterWriteAttribute( writer, name, content, [cdp] ) -> ok
HB_FUNC( XMLTEXTWRITERWRITEATTRIBUTE )
{

   if( HB_ISPOINTER( 1 ) && HB_ISCHAR( 2 ) && HB_ISCHAR( 3 ) )
   {

      xmlTextWriterPtr writer = ( xmlTextWriterPtr ) hb_parptr( 1 );

      if( writer )
      {

         const char * name     = hb_parc( 2 );
         HB_SIZE      nNameLen = hb_parclen( 2 );

         xmlChar * szNameUTF8 = xml_cdpStrToUTF8( name, &nNameLen, hb_parc( 4 ) );

         const char * content     = hb_parc( 3 );
         HB_SIZE      nContentLen = hb_parclen( 3 );

         xmlChar * szContentUTF8 = xml_cdpStrToUTF8( content, &nContentLen, hb_parc( 4 ) );

         int res = xmlTextWriterWriteAttribute( writer,
                                                szNameUTF8,
                                                szContentUTF8 );

         hb_retni( res );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlTextWriterWriteElement( writer, name,content, [cdp] ) -> ok
HB_FUNC( XMLTEXTWRITERWRITEELEMENT )
{
   if( HB_ISPOINTER( 1 ) && HB_ISCHAR( 2 ) && HB_ISCHAR( 3 ) )
   {

      xmlTextWriterPtr writer = ( xmlTextWriterPtr ) hb_parptr( 1 );

      if( writer )
      {

         const char * name     = hb_parc( 2 );
         HB_SIZE      nNameLen = hb_parclen( 2 );

         xmlChar * szNameUTF8 = xml_cdpStrToUTF8( name, &nNameLen, hb_parc( 4 ) );

         const char * content     = hb_parc( 3 );
         HB_SIZE      nContentLen = hb_parclen( 3 );

         xmlChar * szContentUTF8 = xml_cdpStrToUTF8( content, &nContentLen, hb_parc( 4 ) );

         int res = xmlTextWriterWriteElement( writer,
                                              szNameUTF8,
                                              szContentUTF8 );

         hb_retni( res );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}


// xmlTextWriterEndElement	( writer) -> ok
HB_FUNC( XMLTEXTWRITERENDELEMENT )
{
   if( HB_ISPOINTER( 1 ) )
   {

      xmlTextWriterPtr writer = ( xmlTextWriterPtr ) hb_parptr( 1 );

      if( writer )
      {

         int res = xmlTextWriterEndElement( writer );

         hb_retni( res );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// xmlTextWriterEndDocument	( writer) -> ok
HB_FUNC( XMLTEXTWRITERENDDOCUMENT )
{
   if( HB_ISPOINTER( 1 ) )
   {

      xmlTextWriterPtr writer = ( xmlTextWriterPtr ) hb_parptr( 1 );

      if( writer )
      {

         int res = xmlTextWriterEndDocument( writer );

         hb_retni( res );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// xmlFreeTextWriter(writer)
HB_FUNC( XMLFREETEXTWRITER )
{
   if( HB_ISPOINTER( 1 ) )
   {
      xmlTextWriterPtr writer = ( xmlTextWriterPtr ) hb_parptr( 1 );

      if( writer )
      {
         xmlFreeTextWriter( writer );

         hb_ret();
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

/*Tree API*/

// xmlNewDoc( version ) - pDoc
HB_FUNC( XMLNEWDOC )
{
   if( HB_ISCHAR( 1 ) )
   {
      xmlDocPtr doc = xmlNewDoc( ( const xmlChar * ) hb_parc( 1 ) );

      hb_retptr( doc );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}


// xmlFreeDoc( pDoc )
HB_FUNC( XMLFREEDOC )
{

   if( HB_ISPOINTER( 1 ) )
   {
      xmlDocPtr doc = ( xmlDocPtr ) hb_parptr( 1 );

      if( doc )
      {
         xmlFreeDoc( doc );

         hb_ret();
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlDocGetRootElement( pDoc ) -> pNode
HB_FUNC( XMLDOCGETROOTELEMENT )
{

   if( HB_ISPOINTER( 1 ) )
   {
      xmlDocPtr doc = ( xmlDocPtr ) hb_parptr( 1 );

      if( doc )
      {
         xmlNodePtr node = xmlDocGetRootElement( doc );

         hb_retptr( node );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

// xmlDocSetRootElement( pDoc, pNode)
HB_FUNC( XMLDOCSETROOTELEMENT )
{

   if( HB_ISPOINTER( 1 ) && HB_ISPOINTER( 2 ) )
   {

      xmlDocPtr  doc  = ( xmlDocPtr ) hb_parptr( 1 );
      xmlNodePtr root = ( xmlNodePtr ) hb_parptr( 2 );

      if( doc && root )
      {
         xmlNodePtr node = xmlDocSetRootElement( doc, root );

         hb_retptr( node );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

// xmlUnlinkNode(pNode)
HB_FUNC( XMLUNLINKNODE  )
{
   if( HB_ISPOINTER( 1 ) )
   {

      xmlNodePtr cur = ( xmlNodePtr ) hb_parptr( 1 );

      if( cur )
      {
         xmlUnlinkNode( cur );

         hb_ret();
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlFirstElementChild( pNode ) -> pNode
HB_FUNC( XMLFIRSTELEMENTCHILD  )
{

   if( HB_ISPOINTER( 1 ) )
   {
      xmlNodePtr node = ( xmlNodePtr ) hb_parptr( 1 );

      if( node )
      {
         hb_retptr( xmlFirstElementChild( node ) );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

//xmlNextElementSibling(pNode ) -> pNode
HB_FUNC( XMLNEXTELEMENTSIBLING )
{
   if( HB_ISPOINTER( 1 ) )
   {
      xmlNodePtr node = ( xmlNodePtr ) hb_parptr( 1 );

      if( node )
      {
         hb_retptr( xmlNextElementSibling( node ) );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// xmlNodeGetContent(pNode, [cdp] ) -> str
HB_FUNC( XMLNODEGETCONTENT )
{
   if( HB_ISPOINTER( 1 ) )
   {
      xmlNodePtr node = ( xmlNodePtr ) hb_parptr( 1 );

      if( node )
      {

         char *  szDest = NULL;
         HB_SIZE nDest  = 0;

         xmlChar * content = xmlNodeGetContent( node );

         if( content )
         {
            nDest  = xmlStrlen( content );
            szDest = xml_cdpUTF8ToStr( content, &nDest, hb_parc( 2 ) );

            xmlFree( content );

         }

         if( szDest )
            hb_retclen_buffer( szDest, nDest );
         else
            hb_retc_null();

      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}


// xmlGetProp( pNode, name, [cdp] ) -> value
HB_FUNC( XMLGETPROP )
{

   if( HB_ISPOINTER( 1 ) && HB_ISCHAR( 2 ) )
   {

      xmlNodePtr node = ( xmlNodePtr ) hb_parptr( 1 );

      if( node )
      {
         const char * name     = hb_parc( 2 );
         HB_SIZE      nNameLen = hb_parclen( 2 );

         xmlChar * szNameUTF8 = xml_cdpStrToUTF8( name, &nNameLen, hb_parc( 3 ) );

         char *  szDest = NULL;
         HB_SIZE nDest  = 0;

         xmlChar * value = xmlGetProp( node, szNameUTF8 );

         if( value )
         {
            nDest  = xmlStrlen( value );
            szDest = xml_cdpUTF8ToStr( value, &nDest, hb_parc( 3 ) );

            xmlFree( value );

         }

         if( szDest )
            hb_retclen_buffer( szDest, nDest );
         else
            hb_retc_null();
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

// xmlNewParserCtxt() -> pContext
HB_FUNC( XMLNEWPARSERCTXT )
{
   xmlParserCtxtPtr ctxt = xmlNewParserCtxt();

   hb_retptr( ctxt );

}

// xmlCtxtReadFile( pContext, filename, [encoding], [options]) -> pDoc
HB_FUNC( XMLCTXTREADFILE )
{

   if( HB_ISPOINTER( 1 ) && HB_ISCHAR( 2 ) )
   {

      xmlParserCtxtPtr ctxt = ( xmlParserCtxtPtr ) hb_parptr( 1 );

      if( ctxt )
      {

         xmlDocPtr doc = xmlCtxtReadFile( ctxt,
                                          ( const char * ) hb_parc( 2 ),    // filename
                                          ( const char * ) hb_parc( 3 ),    //encoding
                                          hb_parni( 4 ) );                  // options

         hb_retptr( doc );

      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// xmlCtxtReadMemory( pContext, buffer, url, [encoding], [options]) -> pDoc
HB_FUNC( XMLCTXTREADMEMORY )
{

   if( HB_ISPOINTER( 1 ) && HB_ISCHAR( 2 ) && HB_ISCHAR( 3 ) )
   {

      xmlParserCtxtPtr ctxt = ( xmlParserCtxtPtr ) hb_parptr( 1 );

      if( ctxt )
      {

         xmlDocPtr doc = xmlCtxtReadMemory( ctxt,
                                          ( const char * ) hb_parc( 2 ),    // buffer
                                          hb_parclen(2),					// size
										  ( const char * ) hb_parc( 3 ),    // url
										  ( const char * ) hb_parc( 4 ),    // encoding
                                          hb_parni( 5 ) );                  // options

         hb_retptr( doc );

      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}


// xmlFreeParserCtxt(pContext)
HB_FUNC( XMLFREEPARSERCTXT )
{
   if( HB_ISPOINTER( 1 ) )
   {

      xmlParserCtxtPtr ctxt = ( xmlParserCtxtPtr ) hb_parptr( 1 );

      if( ctxt )
      {
         xmlFreeParserCtxt( ctxt );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// XmlNodeGetProperty( pNode, nIndex ) -> xProperty
HB_FUNC( XMLNODEGETPROPERTY )
{
   if( HB_ISPOINTER( 1 ) && HB_ISNUM( 2 ) )
   {

      xmlNodePtr node  = ( xmlNodePtr ) hb_parptr( 1 );
      int        index = hb_parni( 2 );


      if( node )
      {

         switch( index )
         {
            case 1:
               hb_retni( node->type );
               break;
            case 2:
               hb_retc( ( const char * ) node->name );
               break;
            case 3:
               hb_retptr( node->children );
               break;
            case 4:
               hb_retptr( node->last );
               break;
            case 5:
               hb_retptr( node->parent );
               break;
            case 6:
               hb_retptr( node->next );
               break;
            case 7:
               hb_retptr( node->prev );
               break;
            case 8:
               hb_retptr( node->doc );
               break;
            case 9:
               hb_retptr( node->ns );
               break;
            case 10:
               hb_retc( ( const char * ) node->content );
               break;
            case 11:
               hb_retptr( node->properties );
               break;
            default:
               hb_ret();
               break;
         }
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}


/*XPath API*/

// xmlXPathNewContext(doc) -> ctx
HB_FUNC( XMLXPATHNEWCONTEXT )
{

   if( HB_ISPOINTER( 1 ) )
   {

      xmlDocPtr doc = ( xmlDocPtr ) hb_parptr( 1 );

      if( doc )
      {

         xmlXPathContextPtr context = xmlXPathNewContext( doc );

         hb_retptr( context );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlXPathFreeContext(ctx)

HB_FUNC( XMLXPATHFREECONTEXT )
{
   if( HB_ISPOINTER( 1 ) )
   {
      xmlXPathContextPtr ctx = ( xmlXPathContextPtr ) hb_parptr( 1 );

      if( ctx )
      {
         xmlXPathFreeContext( ctx );
         hb_ret();
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlXPathSetContextNode ( node, ctx ) -> nOk
HB_FUNC( XMLXPATHSETCONTEXTNODE )
{

   if( HB_ISPOINTER( 1 ) && ( HB_ISPOINTER( 2 ) ) )
   {

      xmlNodePtr node        = ( xmlNodePtr ) hb_parptr( 1 );
      xmlXPathContextPtr ctx = ( xmlXPathContextPtr ) hb_parptr( 2 );

      if( node && ctx )
      {
         int ret = xmlXPathSetContextNode( node, ctx );

         hb_retni( ret );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlXPathEval( expr, ctx, [cdp]) -> obj
HB_FUNC( XMLXPATHEVAL )
{

   if( HB_ISCHAR( 1 ) && ( HB_ISPOINTER( 2 ) ) )
   {

      const char * expr     = hb_parc( 1 );
      HB_SIZE      nExprLen = hb_parclen( 1 );

      xmlXPathContextPtr ctx = ( xmlXPathContextPtr ) hb_parptr( 2 );

      if( expr && ctx )
      {
         xmlChar * szExprUTF8 = xml_cdpStrToUTF8( expr, &nExprLen, hb_parc( 3 ) );

         xmlXPathObjectPtr xPathObj = xmlXPathEval( szExprUTF8, ctx );

         hb_retptr( xPathObj );
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlXPathFreeObject( obj )
HB_FUNC( XMLXPATHFREEOBJECT )
{
   if( HB_ISPOINTER( 1 ) )
   {

      xmlXPathObjectPtr obj = ( xmlXPathObjectPtr ) hb_parptr( 1 );

      if( obj )
      {

         xmlXPathFreeObject( obj );
         hb_ret();
      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// xmlXPathObjectGetProperty( pXPathObject, nIndex ) -> xProperty
HB_FUNC( XMLXPATHOBJECTGETPROPERTY )
{

   if( HB_ISPOINTER( 1 ) && HB_ISNUM( 2 ) )
   {

      xmlXPathObjectPtr obj = ( xmlXPathObjectPtr ) hb_parptr( 1 );
      int index = hb_parni( 2 );

      if( obj )
      {

         switch( index )
         {
            case 1:
               hb_retni( obj->type );
               break;
            case 2:
               hb_retptr( obj->nodesetval );
               break;
            case 3:
               hb_retni( obj->boolval );
               break;
            case 4:
               hb_retc( ( const char * ) obj->stringval );              // TODO UTF
               break;
            default:
               hb_ret();
         }

      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}


// xmlXPathNodeSetGetProperty( pNodeSet, nIndex ) -> xProperty
HB_FUNC( XMLXPATHNODESETGETPROPERTY )
{
   if( HB_ISPOINTER( 1 ) && HB_ISNUM( 2 ) )
   {

      xmlNodeSetPtr nodeset = ( xmlNodeSetPtr ) hb_parptr( 1 );
      int index = hb_parni( 2 );

      if( nodeset )
      {
         switch( index )
         {
            case 1:
               hb_retni( nodeset->nodeNr );
               break;
            case 2:
               hb_retni( nodeset->nodeMax );
               break;
            case 3:
            {
               // array nodeTab

               PHB_ITEM pArray = hb_itemArrayNew( nodeset->nodeNr );

               if( nodeset->nodeTab )
               {
                  int i;
                  for( i = 0; i < nodeset->nodeNr; i++ )
                  {
                     hb_arraySetPtr( pArray, i + 1, nodeset->nodeTab[ i ] );
                  }
               }

               hb_itemReturnRelease( pArray );
            }
            break;
            default:
               hb_ret();
         }

      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );


}

// Errors

// xmlGetLastError() -> pError

HB_FUNC( XMLGETLASTERROR )
{
   xmlErrorPtr pError = xmlGetLastError();

   hb_retptr( pError );
}

// XmlErrorGetProperty( pErr, nIndex ) -> pProperty
HB_FUNC( XMLERRORGETPROPERTY )
{
   if( HB_ISPOINTER( 1 ) && HB_ISNUM( 2 ) )
   {

      xmlErrorPtr pError = ( xmlErrorPtr ) hb_parptr( 1 );
      int         index  = hb_parni( 2 );

      if( pError )
      {

         switch( index )
         {
            case 1:
               hb_retni( pError->domain );
               break;
            case 2:
               hb_retni( pError->code );
               break;
            case 3:
               hb_retc( pError->message );
               break;
            case 4:
               hb_retc( pError->file );
               break;
            case 5:
               hb_retni( pError->line );
               break;
            case 6:
               hb_retni( pError->int2 );        // col
               break;
            case 7:
               hb_retc( pError->str1 );
               break;
            case 8:
               hb_retc( pError->str2 );
               break;
            case 9:
               hb_retc( pError->str3 );
               break;
         }

      }
      else
         hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// XmlErrorSetBlock( bError ) -> pHandler
HB_FUNC( XMLERRORSETBLOCK )
{
   if( HB_ISBLOCK( 1 ) )
   {
      pHandler = hb_xgrab( sizeof( XML_HANDLER ) );
      pHandler->pErrorBlock = hb_itemNew( hb_param( 1, HB_IT_BLOCK ) );

      xmlSetStructuredErrorFunc( NULL, xml_errorHandler );

      hb_ret();
   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}

// XmlErrorFreeBlock( )
HB_FUNC( XMLERRORFREEBLOCK )
{
   if( pHandler )
   {
      if( pHandler->pErrorBlock )
         hb_itemRelease( pHandler->pErrorBlock );

      hb_xfree( pHandler );
   }
}

// UTF8 conversion stuff

static char * xml_cdpUTF8ToStr( xmlChar * szStr, HB_SIZE * pnLen, const char * pszCdpOut )
{

   PHB_CODEPAGE cdpIn  = hb_cdpFindExt( XML_UTF8_HB_CDP );
   PHB_CODEPAGE cdpOut = pszCdpOut ? hb_cdpFindExt( pszCdpOut ) : hb_vmCDP();

   char * szDest = NULL;

   if( cdpIn && cdpOut && szStr )
   {
      int len = xmlStrlen( szStr );
      memcpy( pnLen, &len, sizeof( len ) );

      szDest = hb_cdpnDup( ( const char * ) szStr, pnLen, cdpIn, cdpOut );
   }

   return szDest;
}

static xmlChar * xml_cdpStrToUTF8( const char * szStr, HB_SIZE * pnLen, const char * pszCdpIn )
{

   PHB_CODEPAGE cdpIn  = pszCdpIn ? hb_cdpFindExt( pszCdpIn ) : hb_vmCDP();
   PHB_CODEPAGE cdpOut = hb_cdpFindExt( XML_UTF8_HB_CDP );

   char * szDest = NULL;

   if( cdpIn && cdpOut && szStr )
   {
      int len = strlen( szStr );
      memcpy( pnLen, &len, sizeof( len ) );

      szDest = hb_cdpnDup( szStr, pnLen, cdpIn, cdpOut );
   }

   return ( xmlChar * ) szDest;
}

static void xml_errorHandler( void * unused, xmlErrorPtr pError )
{

   if( ! unused && pError && pHandler )
   {

      /*
                HB_TRACE( HB_TR_ERROR, ( "libxml2 error: file=%s domain=%d code=%d message=%s line=%d col=%d s1=%s s2=%s s3=%s",
                               pError->file,
                               pError->domain,
                               pError->code,
                               pError->message,
                               pError->line,
                               pError->int2,
                               pError->str1,
                               pError->str2,
                               pError->str3 ) );
       */

      /* codeblock */


      PHB_ITEM pCallback = pHandler->pErrorBlock;
    
      if( HB_IS_BLOCK( pCallback ) )
      {        
         if( hb_vmRequestReenter() )
         {
           
            //int iResult;

            hb_vmPushEvalSym();
            hb_vmPush( pCallback );
            hb_vmPushPointer( pError );

            hb_vmSend( 1 );

            //iResult = hb_parni( -1 );

            hb_vmRequestRestore();
         }
      }


   }
}
