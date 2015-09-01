/*

   liburiparser wrapper API ( http://uriparser.sourceforge.net/ )

*/

#include <windows.h>
#include <string.h>
#include <time.h>

#include "hbapi.h"
#include "hbapierr.h"
#include "hbapilng.h"
#include "hbapiitm.h"
#include "hbwinuni.h"
#include "hbstack.h"

#include <uriparser/Uri.h>

#define RANGE( x )     ( int ) ( ( x ).afterLast - ( x ).first ), ( ( x ).first )
#define RANGELEN( x )  ( int ) ( ( x ).afterLast - ( x ).first )

#define HB_URIPARSER_PARTS_LEN  8

HB_FUNC( URIPARSE );
HB_FUNC( URITOSTRING );
