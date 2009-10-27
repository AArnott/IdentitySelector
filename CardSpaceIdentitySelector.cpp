/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Identity Selector extension.
 *
 * The Initial Developer of the Original Code is
 * Kevin Miller (Iolo Solutions, Inc).
 * Portions created by the Initial Developer are Copyright (C) 2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "stdafx.h"
#include "CardSpaceIdentitySelector.h"
#include "nsMemory.h"
#include "infocard.h"

NS_IMPL_ISUPPORTS1(CardSpaceIdentitySelector, IIdentitySelector)

#define RETURN_ERROR( error ) \
	{\
		m_currentErrorNumber = error; \
		m_currentErrorString = error##_STRING; \
		goto cleanup; \
	}

/* Lazy method to return a string to the caller */
NS_IMETHODIMP ReturnString(char **_retval, const char* result)
{
	if(!_retval)
        return NS_ERROR_NULL_POINTER;

    *_retval = (char*) nsMemory::Clone(result, sizeof(char)*(strlen(result)+1));

    return *_retval ? NS_OK : NS_ERROR_OUT_OF_MEMORY;
}

/* Lazy method to return a string to the caller */
NS_IMETHODIMP ReturnSizedString(char **_retval, const char* result, int size)
{
	if(!_retval)
        return NS_ERROR_NULL_POINTER;

    *_retval = (char*) nsMemory::Clone(result, size+1 );
	// null terminate!
	(*_retval)[size] = 0;

    return *_retval ? NS_OK : NS_ERROR_OUT_OF_MEMORY;
}


NS_IMETHODIMP ReturnString(wchar_t **_retval, const wchar_t* result)
{
	if(!_retval)
        return NS_ERROR_NULL_POINTER;

    *_retval = (wchar_t*) nsMemory::Clone(result, sizeof(wchar_t)*(wcslen(result)+1));

    return *_retval ? NS_OK : NS_ERROR_OUT_OF_MEMORY;
}


bool IsWhitespace( wchar_t character )
{
	const char whitespaces[] = {' ','\t', '\r','\n' };

	for( int i = 0; i< sizeof(whitespaces); i++ )
		if( character == whitespaces[i] )
			return true;

	return false;
}


CardSpaceIdentitySelector::CardSpaceIdentitySelector()
{
	m_currentErrorNumber = 0;
	m_currentErrorString = NULL;
}

CardSpaceIdentitySelector::~CardSpaceIdentitySelector()
{
  /* destructor code */
}

/* void About (); */
NS_IMETHODIMP CardSpaceIdentitySelector::About()
{
	MessageBox(NULL,L"\n\nThe CardSpace Identity Selector implements \nthe interface to support getting\na security token via the browser.\n\n\n (c) 2006 Kevin Miller. \nReleased under the Mozilla/GPL/LGPL Licenses.",L"About",MB_ICONASTERISK);
    return NS_OK;
}

/* string GetBrowserToken (in string issuer, in string requiredClaims, in string optionalClaims, in string tokenType); */
NS_IMETHODIMP CardSpaceIdentitySelector::GetBrowserToken(const PRUnichar *issuerUri, const PRUnichar *recipientUrl, const PRUnichar *requiredClaims, const PRUnichar *optionalClaims, const PRUnichar *tokenType, const PRUnichar *privacyPolicy, PRInt32 privacyPolicyVersion ,nsIX509Cert *certificate, char **_retval)
{
	/* result */
	nsresult	rc			= NS_OK;
	HRESULT		hresult;
	
	/* certificate store */
	BYTE*			_pbElement	= NULL;
	DWORD			cbElement	= 0;

	/* Result */
	DWORD			sz			= 0 ;
	PBYTE			token		= NULL;

	/* CardSpace Reciipent Policy */
	RECIPIENTPOLICY rp;
	
	/* useful locals */
	const wchar_t**		_requiredClaims = NULL;
	const wchar_t**		_optionalClaims= NULL;

	/* validate incoming values */
	if( !requiredClaims )
		RETURN_ERROR( REQUIRED_CLAIMS_NULL );

	if( !tokenType )
		RETURN_ERROR( TOKEN_TYPE_NULL );

	if( !recipientUrl)
		RETURN_ERROR( RECIPIENT_URL_NULL );

	if( issuerUri && wcslen( issuerUri) > MAX_SAFE_STRING_LENGTH )
		RETURN_ERROR( ISSUER_URI_TOO_LONG );

	if( requiredClaims && wcslen( requiredClaims ) > MAX_SAFE_STRING_LENGTH )
		RETURN_ERROR( REQUIRED_CLAIMS_TOO_LONG );

	if( optionalClaims && wcslen( optionalClaims ) > MAX_SAFE_STRING_LENGTH )
		RETURN_ERROR( OPTIONAL_CLAIMS_TOO_LONG );

	if( tokenType && wcslen( tokenType ) > MAX_SAFE_STRING_LENGTH )
		RETURN_ERROR( TOKEN_TYPE_TOO_LONG );
 
	if( privacyPolicy &&  wcslen( privacyPolicy ) > MAX_SAFE_STRING_LENGTH )
		RETURN_ERROR( PRIVACY_POLICY_URL_TOO_LONG );

	/* IP Identity */
	rp.issuer.policyUrl = NULL ; 
	rp.issuer.rawCertificate.cbData = 0;
	rp.issuer.rawCertificate.pbData = NULL;
	rp.issuer.serviceUrl = issuerUri;

	PRUint32 szCertSize = 0;
	certificate->GetRawDER( &szCertSize, &_pbElement );
	cbElement = szCertSize;

	rp.recipient.policyUrl =  NULL ; 
	rp.recipient.rawCertificate.cbData = cbElement;
	rp.recipient.rawCertificate.pbData = _pbElement;
	rp.recipient.serviceUrl = recipientUrl;

	/* Required Claims */
	rp.requiredClaims.count = GetClaims( requiredClaims,  &_requiredClaims);
	if( rp.requiredClaims.count == 0 )
		RETURN_ERROR( REQUIRED_CLAIMS_EMPTY );

	rp.requiredClaims.claims = _requiredClaims;

	/* Optional Claims */
	rp.optionalClaims.count = GetClaims( optionalClaims,  &_optionalClaims);
	rp.optionalClaims.claims =  _optionalClaims;

	/* RP privacy policy */
	
	if( privacyPolicy)
	{
		rp.privacyUrl = privacyPolicy;
		rp.privacyVersion = privacyPolicyVersion ;
	}
	else
	{
		rp.privacyUrl = NULL;
		rp.privacyVersion = privacyPolicyVersion ;
	}
	
	/* RP Requested Token Type */
	rp.tokenType = tokenType; 

	hresult = ::GetBrowserToken( RECIPIENTPOLICYV1 , &rp , &sz , &token );

	nsMemory::Free( _pbElement );
	
	if( hresult == S_OK )
	{
		m_currentErrorNumber  = 0;
		m_currentErrorString  = NULL;

		rc = ReturnSizedString( _retval , (const char*)token, sz );
	}
	else
	{
		rc = ReturnString( _retval , "" );
		m_currentErrorNumber = hresult; 
		m_currentErrorString = CARDSPACE_ERROR_STRING; 
	}

	/* cleanup */
cleanup:
	// delete[] _pbElement;
	if( _requiredClaims )
	{
		// delete the null separated list
		delete _requiredClaims[0];
		delete _requiredClaims;
	}
	
	if( _optionalClaims )
	{
		// delete the null separated list
		delete _optionalClaims[0];
		delete _optionalClaims;
	}

    return rc;
}

/* string GetVersion (); */
NS_IMETHODIMP CardSpaceIdentitySelector::GetVersion(char **_retval)
{
	return ReturnString( _retval , "CardSpace Identity Selector V 0.1" );
}

/* readonly attribute wstring errorstring; */
NS_IMETHODIMP CardSpaceIdentitySelector::GetErrorstring(PRUnichar * *aErrorstring)
{
	if (m_currentErrorString)
	    return ReturnString( aErrorstring , m_currentErrorString);
	else
		return ReturnString( aErrorstring , L"");
}

/* readonly attribute long errornumber; */
NS_IMETHODIMP CardSpaceIdentitySelector::GetErrornumber(PRInt32 *aErrornumber)
{
	*aErrornumber = m_currentErrorNumber;
    return NS_OK;
}


int CardSpaceIdentitySelector::GetClaims( const PRUnichar* claims,const wchar_t*** result )
{
	/* locals */
	size_t		claimsLength;
	const wchar_t**	_claimList;
	bool		inwhitespace;
	int			claimcount	= 0;
	wchar_t*	pWrite		= NULL;
	
	wchar_t*	_scrap;
	// target buffer should not exist.
	assert(! *result );

	// ensure that there are claims to process; 
	if(!claims)
		return 0;

	claimsLength = wcslen(claims);
	_scrap = new wchar_t[claimsLength+2];


	// start off skipping any upfront whitespace
	inwhitespace = true;

	// change from whitespace delimited to null delimited, 
	for( const wchar_t* pRead = claims; *pRead ; pRead++ )
	{
		if( IsWhitespace(*pRead) )
		{
			inwhitespace = true;
		}
		else 
			if( inwhitespace )
			{
				claimcount++;
				inwhitespace = false;
				// coming out of whitespace
				// start of a new claim URI
				if( !pWrite )
				{
					// first one actually...
					pWrite = _scrap;
					*pWrite = *pRead;
					continue;
				}

				// null me baby one more time...
				*++pWrite = 0;
				*(++pWrite) = *pRead;
			}
			else
			{
				*(++pWrite) = *pRead;
			}
	}

	// and tack on a couple of nulls
	*(++pWrite) = 0;
	*(++pWrite) = 0;


	if( claimcount == 0 )
	{
		// didn't find any claims, clean up all this mess.
		delete _scrap;
		_claimList = NULL;
	}
	else
	{
		// create the claims list with the null separated values
		// these two pointers get cleaned up by the caller.
		wchar_t* pRead = _scrap;

		_claimList = new const wchar_t*[claimcount];
		for( int i = 0; i< claimcount; i++ )
		{
			_claimList[i] = pRead;
			pRead+=wcslen(pRead)+1;
		}
	}
	*result = _claimList;
	return claimcount;
}