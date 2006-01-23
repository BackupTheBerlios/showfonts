$Id: ReadMe.txt,v 1.2 2006/01/23 12:53:37 gerrit-albrecht Exp $

ShowFonts

http://showfonts.berlios.de/




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
