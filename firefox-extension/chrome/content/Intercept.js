//------------------------------------------------------------------------------
// Desc:
// Tabs: 3
//
// Copyright (c) 2007-2008 Novell, Inc. All Rights Reserved.
//
// This program and the accompanying materials are made available
// under, alternatively, the terms of:   a) the Eclipse Public License v1.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v10.html; or, b) the Apache License,
// Version 2.0 which accompanies this distribution as is available at
// www.opensource.org/licenses/apache2.0.php.
//
// To contact Novell about this file by physical or electronic mail,
// you may find current contact information at www.novell.com.
//
// Author: Andrew Hodgkinson <ahodgkinson@novell.com>
//------------------------------------------------------------------------------

var cardspace;

// ***********************************************************************
// Function: interceptOnDOMChanged
// ***********************************************************************
function interceptOnDOMChanged( event)
{
        var target = event ? event.target : this;
        var doc;

        if( target.wrappedJSObject)
        {
                target = target.wrappedJSObject;
        }

        try
        {
                if( (doc = target.ownerDocument) == undefined)
                {
                        return;
                }

                var evnt = doc.createEvent( "Event");
                evnt.initEvent( "ICDOMChanged", true, true);
                target.dispatchEvent( evnt);
        }
        catch( e)
        {
        }
}
       
// **************************************************************************
// Desc: Configure the identity selector context object
// **************************************************************************
try
{
        if( document.__identityselector__ == undefined)
        {
                document.__identityselector__ = new Object();
                document.__identityselector__.data = new Object();
                document.__identityselector__.submitIntercepted = false;
       
                // Insert ourselves into the submit handler chain
               
                document.__identityselector__.chainSubmit =
                        HTMLFormElement.prototype.submit;
       
                HTMLFormElement.prototype.submit = function()
                {
                        var event = document.createEvent( "Event");
                        event.initEvent( "ICFormSubmit", true, true);
                        this.dispatchEvent( event);
                        document.__identityselector__.chainSubmit.apply( this);
                };
               
                // Define a value getter
               
                document.__identityselector__.valueGetter = function()
                {
                        try
                        {
                                var event = document.createEvent( "Event");
                                event.initEvent( "ICGetTokenValue", true, true);
                                this.dispatchEvent( event);
                                return( this.__value);
                        }
                        catch( e)
                        {
                                alert( e);
                                throw e;
                        }
                };
               
                // Special case for Microsoft sites (such as live.com) that
                // expect a cardspace object to be available
               
                cardspace = new Object();
                cardspace.__defineGetter__( "value", function()
                {
                        try
                        {
                                if( document.__identityselector__.targetElem == undefined)
                                {
                                        var event = document.createEvent( "Event");
                                        event.initEvent( "ICProcessItems", true, true);
                                        document.dispatchEvent( event);
                                }
       
                                return( document.__identityselector__.targetElem.value);
                        }
                        catch( e)
                        {
                                alert( e);
                                throw e;
                        }
                });
               
                // Add DOM listeners to watch for changes to the document
                // that could result in new information card objects being
                // added
               
                document.addEventListener(
                        "DOMNodeInserted",
                        interceptOnDOMChanged,
                        false, false);
               
                document.addEventListener(
                        "DOMAttrModified",
                        interceptOnDOMChanged,
                        false, false);
               
                document.addEventListener(
                        "DOMSubtreeModified",
                        interceptOnDOMChanged,
                        false, false);
               
                document.addEventListener(
                        "DOMNodeInsertedIntoDocument",
                        interceptOnDOMChanged,
                        false, false);
        }
}
catch( e)
{
}

