#include "hburiparser.ch"

FUNCTIOn Main()

	Local nRes
	Local uri := hb_argv( 1 )
	Local aUriParts := UriParse( uri, @nRes ) 
	
	IF ( nRes != URI_SUCCESS )
	
		? "Errore nei dati"
	
    ELSE
    
        ? "Scheme=", aUriParts[HB_URI_SCHEME]
        ? "User=", aUriParts[HB_URI_USERINFO]
        ? "Host=", aUriParts[HB_URI_HOSTTEXT]
        ? "Port=", aUriParts[HB_URI_PORTTEXT]
        ? "Path=", aUriParts[HB_URI_PATH]
        ? "Query=", aUriParts[HB_URI_QUERY]
        ? "Fragment=", aUriParts[HB_URI_FRAGMENT]
        ? "absPath=", aUriParts[HB_URI_ABSOLUTEPATH]

	ENDIF
    
RETURN NIL


