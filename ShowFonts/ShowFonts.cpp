// $Id: ShowFonts.cpp,v 1.4 2006/01/30 14:19:59 gerrit-albrecht Exp $
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

BEGIN_MESSAGE_MAP(CShowFonts, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CShowFonts theApp;                                                   // The one and only CShowFonts object.

CShowFonts::CShowFonts()
{
  EnableHtmlHelp();

  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

// CShowFonts initialization.

BOOL CShowFonts::InitInstance()
{
  // InitCommonControlsEx() is required on Windows XP if an application
  // manifest specifies use of ComCtl32.dll version 6 or later to enable
  // visual styles.  Otherwise, any window creation will fail.

  INITCOMMONCONTROLSEX InitCtrls;
  InitCtrls.dwSize = sizeof(InitCtrls);

  // Set this to include all the common control classes you want to use
  // in your application.

  InitCtrls.dwICC = ICC_WIN95_CLASSES;
  InitCommonControlsEx(&InitCtrls);                                  // Oder nur: InitCommonControls();

  AfxInitRichEdit();

  CWinApp::InitInstance();

  if (! AfxSocketInit()) {
    AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
    return FALSE;
  }

  if (! AfxOleInit()) {                                              // Initialize OLE libraries.
    AfxMessageBox(IDP_OLE_INIT_FAILED);
    return FALSE;
  }

  AfxEnableControlContainer();

  // Standard initialization
  // If you are not using these features and wish to reduce the size
  // of your final executable, you should remove from the following
  // the specific initialization routines you do not need
  // Change the registry key under which our settings are stored
  // TODO: You should modify this string to be something appropriate
  // such as the name of your company or organization

  SetRegistryKey(_T("G.A.S.I."));

  CMainDialog dlg;
  m_pMainWnd = &dlg;

  (void) dlg.DoModal();

  // Since the dialog has been closed, return FALSE so that we exit the
  // application, rather than start the application's message pump.

  return FALSE;
}
