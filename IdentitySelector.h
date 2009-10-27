/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IdentitySelector.idl
 */

#ifndef __gen_IdentitySelector_h__
#define __gen_IdentitySelector_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIX509Cert_h__
#include "nsIX509Cert.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IIdentitySelector */
#define IIDENTITYSELECTOR_IID_STR "ddd9bc02-c964-4bd5-b5bc-943e483c6c57"

#define IIDENTITYSELECTOR_IID \
  {0xddd9bc02, 0xc964, 0x4bd5, \
    { 0xb5, 0xbc, 0x94, 0x3e, 0x48, 0x3c, 0x6c, 0x57 }}

class NS_NO_VTABLE IIdentitySelector : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(IIDENTITYSELECTOR_IID)

  /* void About (); */
  NS_IMETHOD About(void) = 0;

  /* string GetBrowserToken (in wstring issuerUri, in wstring recipientUrl, in wstring requiredClaims, in wstring optionalClaims, in wstring tokenType, in wstring privacyPolicy, in long privacyPolicyVersion, in nsIX509Cert certificate); */
  NS_IMETHOD GetBrowserToken(const PRUnichar *issuerUri, const PRUnichar *recipientUrl, const PRUnichar *requiredClaims, const PRUnichar *optionalClaims, const PRUnichar *tokenType, const PRUnichar *privacyPolicy, PRInt32 privacyPolicyVersion, nsIX509Cert *certificate, char **_retval) = 0;

  /* string GetVersion (); */
  NS_IMETHOD GetVersion(char **_retval) = 0;

  /* readonly attribute wstring errorstring; */
  NS_IMETHOD GetErrorstring(PRUnichar * *aErrorstring) = 0;

  /* readonly attribute long errornumber; */
  NS_IMETHOD GetErrornumber(PRInt32 *aErrornumber) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IIDENTITYSELECTOR \
  NS_IMETHOD About(void); \
  NS_IMETHOD GetBrowserToken(const PRUnichar *issuerUri, const PRUnichar *recipientUrl, const PRUnichar *requiredClaims, const PRUnichar *optionalClaims, const PRUnichar *tokenType, const PRUnichar *privacyPolicy, PRInt32 privacyPolicyVersion, nsIX509Cert *certificate, char **_retval); \
  NS_IMETHOD GetVersion(char **_retval); \
  NS_IMETHOD GetErrorstring(PRUnichar * *aErrorstring); \
  NS_IMETHOD GetErrornumber(PRInt32 *aErrornumber); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IIDENTITYSELECTOR(_to) \
  NS_IMETHOD About(void) { return _to About(); } \
  NS_IMETHOD GetBrowserToken(const PRUnichar *issuerUri, const PRUnichar *recipientUrl, const PRUnichar *requiredClaims, const PRUnichar *optionalClaims, const PRUnichar *tokenType, const PRUnichar *privacyPolicy, PRInt32 privacyPolicyVersion, nsIX509Cert *certificate, char **_retval) { return _to GetBrowserToken(issuerUri, recipientUrl, requiredClaims, optionalClaims, tokenType, privacyPolicy, privacyPolicyVersion, certificate, _retval); } \
  NS_IMETHOD GetVersion(char **_retval) { return _to GetVersion(_retval); } \
  NS_IMETHOD GetErrorstring(PRUnichar * *aErrorstring) { return _to GetErrorstring(aErrorstring); } \
  NS_IMETHOD GetErrornumber(PRInt32 *aErrornumber) { return _to GetErrornumber(aErrornumber); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IIDENTITYSELECTOR(_to) \
  NS_IMETHOD About(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->About(); } \
  NS_IMETHOD GetBrowserToken(const PRUnichar *issuerUri, const PRUnichar *recipientUrl, const PRUnichar *requiredClaims, const PRUnichar *optionalClaims, const PRUnichar *tokenType, const PRUnichar *privacyPolicy, PRInt32 privacyPolicyVersion, nsIX509Cert *certificate, char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBrowserToken(issuerUri, recipientUrl, requiredClaims, optionalClaims, tokenType, privacyPolicy, privacyPolicyVersion, certificate, _retval); } \
  NS_IMETHOD GetVersion(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVersion(_retval); } \
  NS_IMETHOD GetErrorstring(PRUnichar * *aErrorstring) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetErrorstring(aErrorstring); } \
  NS_IMETHOD GetErrornumber(PRInt32 *aErrornumber) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetErrornumber(aErrornumber); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IIdentitySelector
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IIDENTITYSELECTOR

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IIdentitySelector)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void About (); */
NS_IMETHODIMP _MYCLASS_::About()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetBrowserToken (in wstring issuerUri, in wstring recipientUrl, in wstring requiredClaims, in wstring optionalClaims, in wstring tokenType, in wstring privacyPolicy, in long privacyPolicyVersion, in nsIX509Cert certificate); */
NS_IMETHODIMP _MYCLASS_::GetBrowserToken(const PRUnichar *issuerUri, const PRUnichar *recipientUrl, const PRUnichar *requiredClaims, const PRUnichar *optionalClaims, const PRUnichar *tokenType, const PRUnichar *privacyPolicy, PRInt32 privacyPolicyVersion, nsIX509Cert *certificate, char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetVersion (); */
NS_IMETHODIMP _MYCLASS_::GetVersion(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute wstring errorstring; */
NS_IMETHODIMP _MYCLASS_::GetErrorstring(PRUnichar * *aErrorstring)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long errornumber; */
NS_IMETHODIMP _MYCLASS_::GetErrornumber(PRInt32 *aErrornumber)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IdentitySelector_h__ */
