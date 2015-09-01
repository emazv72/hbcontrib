/*

   liburiparser wrapper API ( http://uriparser.sourceforge.net/ )

   Emanuele Zavallone ( emanuele.zavallone@next-informatica.com)

*/

#include "hburiparser.h"

// UriParse( cUri, @nResult ) -> aParts
HB_FUNC( URIPARSE )
{

   if( HB_ISCHAR( 1 ) )
   {
      const char * uriString = hb_parc( 1 );

      PHB_ITEM pArrayParts = hb_itemArrayNew( HB_URIPARSER_PARTS_LEN );

      UriParserStateA state;
      UriUriA         uri;

      state.uri = &uri;
      int result = uriParseUriA( &state, uriString );

      hb_storni( result, 2 );

      if( result == URI_SUCCESS )
      {

         if( uri.scheme.first )
         {
            hb_arraySetCL( pArrayParts, 1, uri.scheme.first, RANGELEN( uri.scheme ) );
         }
         if( uri.userInfo.first )
         {
            hb_arraySetCL( pArrayParts, 2, uri.userInfo.first, RANGELEN( uri.userInfo ) );
         }
         if( uri.hostText.first )
         {
            hb_arraySetCL( pArrayParts, 3, uri.hostText.first, RANGELEN( uri.hostText ) );
         }
         if( uri.portText.first )
         {
            hb_arraySetCL( pArrayParts, 4, uri.portText.first, RANGELEN( uri.portText ) );
         }

         PHB_ITEM pArrayPath = hb_itemArrayNew( 0 );

         if( uri.pathHead )
         {

            const UriPathSegmentA * p = uri.pathHead;
            for(; p; p = p->next )
            {
               PHB_ITEM temp = hb_itemPutCL( NULL, p->text.first, RANGELEN( p->text ) );
               hb_arrayAdd( pArrayPath, temp );
               hb_itemRelease( temp );
            }

         }

         hb_arraySet( pArrayParts, 5, pArrayPath );

         if( uri.query.first )
         {
            hb_arraySetCL( pArrayParts, 6, uri.query.first, RANGELEN( uri.query ) );
         }
         if( uri.fragment.first )
         {
            hb_arraySetCL( pArrayParts, 7, uri.fragment.first, RANGELEN( uri.fragment ) );
         }

         hb_arraySetNI( pArrayParts, 8, uri.absolutePath );

      }

      hb_itemReturnRelease( pArrayParts );

      uriFreeUriMembersA( &uri );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

}

// UriToString( aParts, @nResult ) -> cUri
HB_FUNC( URITOSTRING )
{
   if( HB_ISARRAY( 1 ) )
   {

      // Result
      char * uriString = hb_xgrab( 1 );
      uriString[ 0 ] = '\0';

      UriUriA uri;
      UriPathSegmentA * pPathHead = NULL;
      int charsRequired;
      int result = 0;

      memset( &uri, 0, sizeof( uri ) );

      /* Retrieve uri info from array*/
      PHB_ITEM pArrayParts = hb_param( 1, HB_IT_ARRAY );

      if( hb_arrayLen( pArrayParts ) >= HB_URIPARSER_PARTS_LEN )
      {
         PHB_ITEM pArrItem;

         /* Scheme */
         pArrItem = hb_arrayGetItemPtr( pArrayParts, 1 );

         if( HB_IS_STRING( pArrItem ) )
         {
            const char * pszScheme = hb_itemGetCPtr( pArrItem );

            uri.scheme.first     = pszScheme;
            uri.scheme.afterLast = pszScheme + strlen( pszScheme );
         }

         /* userInfo  */
         pArrItem = hb_arrayGetItemPtr( pArrayParts, 2 );
         if( HB_IS_STRING( pArrItem ) )
         {
            const char * pszUserInfo = hb_itemGetCPtr( pArrItem );

            uri.userInfo.first     = pszUserInfo;
            uri.userInfo.afterLast = pszUserInfo + strlen( pszUserInfo );
         }
         
         /* hostText  */
         pArrItem = hb_arrayGetItemPtr( pArrayParts, 3 );
         if( HB_IS_STRING( pArrItem ) )
         {
            const char * pszHostText = hb_itemGetCPtr( pArrItem );

            uri.hostText.first     = pszHostText;
            uri.hostText.afterLast = pszHostText + strlen( pszHostText );
         }

         /* portText  */
         pArrItem = hb_arrayGetItemPtr( pArrayParts, 4 );
         if( HB_IS_STRING( pArrItem ) )
         {
            const char * pszPortText = hb_itemGetCPtr( pArrItem );

            uri.portText.first     = pszPortText;
            uri.portText.afterLast = pszPortText + strlen( pszPortText );
         }

         /*Path*/

         pArrItem = hb_arrayGetItemPtr( pArrayParts, 5 );
         if( HB_IS_ARRAY( pArrItem ) )
         {
            int nLen = hb_arrayLen( pArrItem );

            if( nLen > 0 )
            {

               UriPathSegmentA * lastSegment = NULL;
               const char *      pszPath;
               int segment;

               for( segment = 0; segment < nLen; segment++ )
               {
                  PHB_ITEM pPathItem = hb_arrayGetItemPtr( pArrItem, segment + 1 );

                  if( HB_IS_STRING( pPathItem ) )
                  {
                     pszPath = hb_itemGetCPtr( pPathItem );

                     UriPathSegmentA * pPath = hb_xgrab( sizeof( UriPathSegmentA ) );
                     memset( pPath, 0, sizeof( UriPathSegmentA ) );

                     pPath->text.first     = pszPath;
                     pPath->text.afterLast = pszPath + strlen( pszPath );

                     if( ! pPathHead )
                        pPathHead = pPath;

                     // linked list
                     if( lastSegment )
                        lastSegment->next = pPath;

                     lastSegment = pPath;
                  }
                  else
                     hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );

               }

               uri.pathHead = pPathHead;

            }
         }

         /* query  */
         pArrItem = hb_arrayGetItemPtr( pArrayParts, 6 );
         if( HB_IS_STRING( pArrItem ) )
         {
            const char * pszQuery = hb_itemGetCPtr( pArrItem );

            uri.query.first     = pszQuery;
            uri.query.afterLast = pszQuery + strlen( pszQuery );
         }

         /* fragment  */
         pArrItem = hb_arrayGetItemPtr( pArrayParts, 7 );
         if( HB_IS_STRING( pArrItem ) )
         {
            const char * pszFragment = hb_itemGetCPtr( pArrItem );

            uri.fragment.first     = pszFragment;
            uri.fragment.afterLast = pszFragment + strlen( pszFragment );
         }

         /*absolutePath*/
         pArrItem = hb_arrayGetItemPtr( pArrayParts, 8 );
         if( HB_IS_NUMERIC( pArrItem ) )
         {
            uri.absolutePath = hb_itemGetNI( pArrItem );
         }

         /*Fill uri*/
         result = uriToStringCharsRequiredA( &uri, &charsRequired );

         if( result == URI_SUCCESS )
         {
            charsRequired++;

            uriString = hb_xrealloc( uriString, charsRequired );

            result = uriToStringA( uriString, &uri, charsRequired, NULL );

            if( result != URI_SUCCESS )
            {
               HB_TRACE( HB_TR_ERROR, ( "uriToStringA - result %d", result ) );
            }
         }
         else
            HB_TRACE( HB_TR_ERROR, ( "uriToStringCharsRequiredA - result %d", result ) );

         // free
         UriPathSegmentA * p = pPathHead;
         for(; p; p = p->next )
            if( p )
               hb_xfree( p );

         hb_storni( result, 2 );

         hb_retc( uriString );
         hb_xfree( uriString );

      }
      else
         hb_errRT_BASE( EG_BOUND, 1131, NULL, hb_langDGetErrorDesc( EG_ARRDIMENSION ), HB_ERR_ARGS_BASEPARAMS );

   }
   else
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
}
