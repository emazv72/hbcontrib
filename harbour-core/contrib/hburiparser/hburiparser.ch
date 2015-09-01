/*

   liburiparser wrapper API ( http://uriparser.sourceforge.net/ )

   Emanuele Zavallone ( emanuele.zavallone@next-informatica.com)

*/

#ifndef _HBURIPARSER_CH
#define  _HBURIPARSER_CH

/* Shared errors */
#define URI_SUCCESS                        0
#define URI_ERROR_SYNTAX                   1 /* Parsed text violates expected format */
#define URI_ERROR_NULL                     2 /* One of the params passed was NULL
                                                although it mustn't be */
#define URI_ERROR_MALLOC                   3 /* Requested memory could not be allocated */
#define URI_ERROR_OUTPUT_TOO_LARGE         4 /* Some output is to large for the receiving buffer */
#define URI_ERROR_NOT_IMPLEMENTED          8 /* The called function is not implemented yet */
#define URI_ERROR_RANGE_INVALID            9 /* The parameters passed contained invalid ranges */


/* Errors specific to ToString */
#define URI_ERROR_TOSTRING_TOO_LONG        URI_ERROR_OUTPUT_TOO_LARGE /* Deprecated, test for URI_ERROR_OUTPUT_TOO_LARGE instead */

/* Errors specific to AddBaseUri */
#define URI_ERROR_ADDBASE_REL_BASE         5 /* Given base is not absolute */

/* Errors specific to RemoveBaseUri */
#define URI_ERROR_REMOVEBASE_REL_BASE      6 /* Given base is not absolute */
#define URI_ERROR_REMOVEBASE_REL_SOURCE    7 /* Given base is not absolute */

#define HB_URI_SCHEME                      1
#define HB_URI_USERINFO                    2
#define HB_URI_HOSTTEXT                    3
#define HB_URI_PORTTEXT                    4
#define HB_URI_PATH                        5
#define HB_URI_QUERY                       6
#define HB_URI_FRAGMENT                    7
#define HB_URI_ABSOLUTEPATH                8

#endif
