There are three projects in this solution.
1 - IdentitySelector.  This is the main project.  This is the one you want to build.  
It is the XPCOM code.

2 - SupportingFiles.  This is the project filled with things that you do not need to compile, or at 
least not with VC++.  This includes the files necessary for the XPI install and the IdentitySelector.IDL.
This is an XPCOM IDL file, not a VC++ IDL file.  It must be parsed by XPIDL, not by MIDL.  
MIDL thinks it is unfunny.  All of these files would normally not be n the solution file, but I needed 
to add them in order to get them into CodePlex.  I have excluded this the build in the configuration manager.

Note that IdentitySelector actually lives in the IdentitySelector folder, but I had to put it in an excluded
project to keep VC++ from complaining.

3 - ReadThisFirst.  This is a project containing instructions (this file).  I'm hoping to make this a bit
simpler in the future by including a VBScript file to download and setup the CardSpace API and Gecko SDK.
However, for now you'll have to settle with the instructions below.


INITIAL SETUP INSTRUCTIONS
1.  Download and install .Net 3.0.
	
	You can find it at http://www.netfx3.com, and click on the "Download the .Net Framework 3.0" link.
	
2.  Download and install the CardSpace API.    I believe that you must download the complete 
	Windows SDK, which is a bit overkill for this project.  Ah, well.  At least you only have to do 
	this once.  
	
	You can find it at via a quick search on the MSDN site.  The current link is 
	http://www.microsoft.com/downloads/details.aspx?FamilyId=C2B1E300-F358-4523-B479-F53D234CDCCF&displaylang=en
	although I hold no hopes that it won't move tomorrow.
	
3.  Download and extract the Gecko SDK.  The Gecko SDK includes the XPIDL compiler, which we will use
	instead of MIDL.

	You can find it at http://developer.mozilla.org/en/docs/Gecko_SDK.
	
4.  Check the IdentitySelector project settings.  Specifically, setup the include and library directories.
	"C/C++"/General/Additional Include Directories - ensure the directories containing infocard.h and
		the gecko-sdk\include directories are correct
	Linker/Additional Library Directories - ensure that the directories containing infocardapi.lib
		and the gecko-sdk\lib directories are correct
	I have also added a Pre-Build and Post-Build step.  You may wish to check the paths in those scripts.
	
5.  If you are having any difficulty building, you may wish to check dependencies.  This project relies
	on a few header files and libraries.
	 - CardSpaceIdentitySelector.h (in this project)
	 - IdentitySelector.h (in this project)
	 - sdafx.h (in this project)
	 - nsMemory.h (in the Gecko SDK)
	 - infocard.h (in the Windows SDK)
	 - xpcomglue_s.lib (in the Gecko SDK)
	 - xpcom.lib (in the Gecko SDK)
	 - infocardapi.lib (in the Windows SDK)
	 - nspr4.lib (in the Gecko SDK)
	 - crypt32.lib (in the Windows SDK)
	 
6.  Download Info-ZIP (unless you already have PKZip or compatible command-line alternative installed).
	Make sure that it is in your path, or alter the Post-Build step to ensure it is in the path.

	You can find it at http://www.info-zip.org
	
7.  I recommend downloading a static version of XPIDL.exe.  This will save you some setup woes.  

	You can find a copy at http://developer.mozilla.org/en/docs/User:Andywang:xpidl
	
	Once you have downloaded it, extract it over the regular xpidl.exe in the gecko-sdk\bin directory.
	 
BUILDING INSTRUCTIONS

1.  Build the code.  That's all, nothing fancy.  The only project that VS 2005 will compile is 
	IdentitySelector.  It invokes a Pre-Build (to call XPIDL to create all the necessary .h files)
	and a Post-Build (to create the XPI file from the build results)
	
A tip of the hat to Garrett Serack for the code snippet to detect the gecko-sdk path.  Much easier than
relying on environment variables, as long as your path is one of the ones it attempts to guess.  If your 
path isn't found, either move the Gecko SDK to a sibling directory to this project (and preferably named
gecko-sdk), or edit the Pre and Post Build steps accordingly.
