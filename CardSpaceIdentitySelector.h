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
 * The Original Code is the header file for the Identity Selector extension.
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


#ifndef __CardSpaceIdentitySelector_h__
#define __CardSpaceIdentitySelector_h__

#include "IdentitySelector.h"

#define CARDSPACE_IDENTITY_SELECTOR_CONTRACTID "@perpetual-motion.com/IdentitySelector/CardSpaceIdentitySelector;1"
#define CARDSPACE_IDENTITY_SELECTOR_CLASSNAME "CardSpace Identity Selector"
#define CARDSPACE_IDENTITY_SELECTOR_CID { 0x765d1d98, 0x414c, 0x4eb4, { 0xb0, 0x2c, 0xa6, 0xb, 0x89, 0x18, 0x6c, 0x82 } }
/* 
	Arbitrary max string length  
	The claims list from the browser should be under this. 
	I'm making it 32k for no good reason.
*/
#define MAX_SAFE_STRING_LENGTH 32768
#define stringer( x ) L#x 


#define ISSUER_URI_TOO_LONG				500
#define REQUIRED_CLAIMS_NULL			501
#define REQUIRED_CLAIMS_TOO_LONG		502
#define OPTIONAL_CLAIMS_TOO_LONG		503
#define TOKEN_TYPE_TOO_LONG				504
#define RP_CERTIFICATE_MISSING			505
#define REQUIRED_CLAIMS_EMPTY			506
#define PRIVACY_POLICY_URL_TOO_LONG     507
#define TOKEN_TYPE_NULL					508
#define RECIPIENT_URL_NULL				510

#define ISSUER_URI_TOO_LONG_STRING		L"Issuer URI is exceeds maximum length"
#define REQUIRED_CLAIMS_NULL_STRING		L"Required Claims is not permitted to be null"
#define REQUIRED_CLAIMS_TOO_LONG_STRING L"Required Claims list exceeds maximum length"
#define OPTIONAL_CLAIMS_TOO_LONG_STRING L"Option Claims list exceeds maximum length"
#define TOKEN_TYPE_TOO_LONG_STRING		L"Token Type exceeds maximum length"
#define RP_CERTIFICATE_MISSING_STRING	L"Relying Party Certificate Missing"
#define REQUIRED_CLAIMS_EMPTY_STRING	L"Required Claims List is empty"
#define PRIVACY_POLICY_URL_TOO_LONG_STRING L"Privacy Policy URL exceeds maximum length"

#define TOKEN_TYPE_NULL_STRING			L"Token Type is not permitted to be null"				
#define RECIPIENT_URL_NULL_STRING		L"Recipient URL is not permitted to be null"

#define CARDSPACE_ERROR_STRING			L"CardSpace Returned Error value"

/* Header file */
class CardSpaceIdentitySelector : public IIdentitySelector
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IIDENTITYSELECTOR

  CardSpaceIdentitySelector();

private:
  ~CardSpaceIdentitySelector();

protected:
  /* additional members */
	const wchar_t* m_currentErrorString;
	long m_currentErrorNumber;

	int GetClaims( const PRUnichar* claims, const wchar_t*** result );
};


#endif
