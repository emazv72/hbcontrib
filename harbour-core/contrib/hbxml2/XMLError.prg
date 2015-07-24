
/*

libxml2

Error handling

*/

#include "hbclass.ch"
#include "hbxml2.ch"
#include "error.ch"

CREATE CLASS XMLError INHERIT  XMLBase
	
	METHOD FromPtr( pError )

	METHOD GetDomain 	INLINE	::domain 
	METHOD GetCode 		INLINE	::code 	
	METHOD GetMessage	INLINE  ::message
	METHOD GetFile		INLINE  ::file
	METHOD GetLine 		INLINE  ::line 	
	METHOD GetCol 	    INLINE  ::col 	
	METHOD GetStr1 	    INLINE  ::str1 	
	METHOD GetStr2 		INLINE  ::str2 	
	METHOD GetStr3 		INLINE  ::str3 	
					
	PROTECTED:

	DATA domain 	AS Numeric
	DATA code 		AS Numeric
	DATA message 	AS Character
	DATA file 		AS Character
	DATA line 		AS Numeric
	DATA col 		AS Numeric
	DATA str1 		AS Character
	DATA str2 		AS Character
	DATA str3 		AS Character
	
	DATA pError		AS Object 
   
END CLASS


METHOD FromPtr( pError ) CLASS XMLError

	::pError := pError
	
	IF ( !IsNullOrEmpty(pError))
	
		::domain 	:= XmlErrorGetProperty( pError, 1 )
		::code 		:= XmlErrorGetProperty( pError, 2 )
		::message 	:= XmlErrorGetProperty( pError, 3 )
		::file		:= XmlErrorGetProperty( pError, 4 )		
		::line 		:= XmlErrorGetProperty( pError, 5 )
		::col 		:= XmlErrorGetProperty( pError, 6 )
		::str1 		:= XmlErrorGetProperty( pError, 7 )
		::str2 		:= XmlErrorGetProperty( pError, 8 )
		::str3 		:= XmlErrorGetProperty( pError, 9 )	
	
	ENDIF

RETURN Self


