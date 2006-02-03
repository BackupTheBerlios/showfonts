$Id: ReadMe.txt,v 1.2 2006/02/03 13:23:09 gerrit-albrecht Exp $

ShowFonts

http://showfonts.berlios.de/





Help Support:

hlp\ShowFonts.hhp
    This file is a help project file. It contains the data needed to
    compile the help files into a .chm file.

hlp\ShowFonts.hhc
    This file lists the contents of the help project.

hlp\ShowFonts.hhk
    This file contains an index of the help topics.

hlp\afxcore.htm
    This file contains the standard help topics for standard MFC
    commands and screen objects. Add your own help topics to this file.

makehtmlhelp.bat
    This file is used by the build system to compile the help files.

hlp\Images\*.gif
    These are bitmap files required by the standard help file topics for
    Microsoft Foundation Class Library standard commands.


Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

ShowFonts.manifest
	Application manifest files are used by Windows XP to describe an applications 
	dependency on specific versions of Side-by-Side assemblies. The loader uses this 
	information to load the appropriate assembly from the assembly cache or private 
	from the application. The Application manifest  maybe included for redistribution 
	as an external .manifest file that is installed in the same folder as the application 
	executable or it may be included in the executable in the form of a resource. 

If your application uses MFC in a shared DLL, you will need 
to redistribute the MFC DLLs. If your application is in a language 
other than the operating system's locale, you will also have to 
redistribute the corresponding localized resources MFC80XXX.DLL. 
For more information on both of these topics, please see the section on 
redistributing Visual C++ applications in MSDN documentation. 


Hinweis zu lokalisierten MFC-DLLs

Wenn Ihre Anwendung die MFC in einer gemeinsam genutzten DLL
verwendet und eine andere als die aktuell auf dem Betriebssystem
eingestellte Sprache verwendet, muss die entsprechend lokalisierte
Ressource MFC70XXX.DLL von der Microsoft Visual C++ CD-ROM in das
Verzeichnis system oder system32 kopiert und in MFCLOC.DLL
umbenannt werden. "XXX" steht dabei für die Abkürzung der Sprache.
So enthält beispielsweise MFC70DEU.DLL die ins Deutsche übersetzten
Ressourcen. Anderenfalls werden einige Oberflächenelemente der
Anwendung in der Sprache des Betriebssystems angezeigt.
