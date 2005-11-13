// $Id: ShowFonts.cpp,v 1.1 2005/11/13 21:44:28 gerrit-albrecht Exp $
//
// ShowFonts
// Copyright (C) 2005 by Gerrit M. Albrecht
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.

#include "StdAfx.h"
#include "ShowFonts.h"
#include "MainDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CShowFonts

BEGIN_MESSAGE_MAP(CShowFonts, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CShowFonts-Erstellung

CShowFonts::CShowFonts()
{
	// TODO: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance positionieren
}

// Das einzige CShowFonts-Objekt

CShowFonts theApp;

BOOL CShowFonts::InitInstance()
{
	// InitCommonControls() ist für Windows XP erforderlich, wenn ein Anwendungsmanifest
	// die Verwendung von ComCtl32.dll Version 6 oder höher zum Aktivieren
	// von visuellen Stilen angibt. Ansonsten treten beim Erstellen von Fenstern Fehler auf.

  InitCommonControls();
  AfxInitRichEdit();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

  SetRegistryKey(_T("G.A.S.I."));

	CMainDialog dlg;
	m_pMainWnd = &dlg;
	(void) dlg.DoModal();

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, so dass wir die
	// Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.

  return FALSE;
}
