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
 * The Original Code is the JavaScript implementation for the XBL.
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

function __ICardError( number , description ){ this.number = number;this.description = description;}

var InformationCard = {
    /// INITIALIZATION CODE
    onInstall : function() 
    {
        window.removeEventListener("load", InformationCard.onInstall, true);

        // Only use the new stylesheet api
        var sss = Components.classes["@mozilla.org/content/style-sheet-service;1"].getService(Components.interfaces.nsIStyleSheetService);
        var ios = Components.classes["@mozilla.org/network/io-service;1"].getService(Components.interfaces.nsIIOService);
        var u = ios.newURI("chrome://IdentitySelector/content/InformationCard.css", null, null);
        if(!sss.sheetRegistered(u, sss.USER_SHEET)) 
        {
            sss.loadAndRegisterSheet(u, sss.USER_SHEET);
            dump("installing InformationCard\n");
        }
    },

    // HANDLE EVENT
    onCallIdentitySelector: function(event) 
    {
        var target = event.target.wrappedJSObject;
        var data = target.cardspacedata;
        var result;

        try
        {
            // verify incoming data
            if( target.location.href != data.recipientURL )
                throw new __ICardError( -600 , "Recipent URL and Incoming location mismatch." ); // ERRORMARKER 

            if( data.recipientURL == null || data.recipientURL == "" || (""+data.recipientURL).toLowerCase().indexOf("https://") != 0 ) 
                throw new __ICardError( -602 , "Recipent URL must be HTTPS." ); // ERRORMARKER 
            
            if( data.requiredClaims == null || data.requiredClaims == "" )
                throw new __ICardError( -603 , "Required Claims must not be empty" ); // ERRORMARKER 

            if( data.privacyPolicyVersion == null || data.privacyPolicyVersion == "" )
                data.privacyPolicyVersion = 0;
            else
                data.privacyPolicyVersion = 0+data.privacyPolicyVersion;
                
            //if( data.tokenType == null || data.tokenType == "" )
            //    throw new __ICardError( -604 , "Token Type must not be empty" ); // ERRORMARKER 
                
            var obj = null;
            try
            {
                // lookup class id from config.
                var prefs = Components.classes["@mozilla.org/preferences-service;1"].getService(Components.interfaces.nsIPrefBranch);
    		    var pbi = prefs.QueryInterface(Components.interfaces.nsIPrefBranch);
        		
                var cid = pbi.getCharPref("identityselector.contractid");
                obj = Components.classes[cid].createInstance();
                obj = obj.QueryInterface(Components.interfaces.IIdentitySelector);
            }
            catch (err)
            {
                throw new __ICardError( -601 , "Unable to find registered Identity Selector" ); // ERRORMARKER
            }

            var browser = document.getElementById("content");
            var secureUi = browser.securityUI;
            var sslStatusProvider = secureUi.QueryInterface(Components.interfaces.nsISSLStatusProvider);
            var sslStatus = sslStatusProvider.SSLStatus.QueryInterface(Components.interfaces.nsISSLStatus);

            result = obj.GetBrowserToken(data.issuer , data.recipientURL, data.requiredClaims ,data.optionalClaims , data.tokenType ,data.privacyPolicy, data.privacyPolicyVersion ,sslStatus.serverCert );

            if( obj.errornumber != 0 )
            {
                throw new __ICardError( obj.errornumber  , obj.errorstring ); // ERRORMARKER
            }
            target.cardspacedata = result;
        }
        catch (err)
        {
            // bubble the exception up as the return value. 
            target.cardspacedata = err;
        }
    },
// HANDLE EVENT
    onIdentitySelectorAvailable: function(event) 
    {
        var target = event.target.wrappedJSObject;
        target.IdentitySelectorAvailable = true;
    }    
}

window.addEventListener("load", InformationCard.onInstall, true);
addEventListener("CallIdentitySelector",InformationCard.onCallIdentitySelector,false,true);
addEventListener("IdentitySelectorAvailable",InformationCard.onIdentitySelectorAvailable,false,true);

