// $Id: MainDialog.cpp,v 1.5 2006/01/30 10:47:51 gerrit-albrecht Exp $
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
#include "AboutDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDialog::IDD, pParent)
{
  EnableActiveAccessibility();

  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainDialog, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMainDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
  if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
    CAboutDialog dialog;
    dialog.DoModal();
  } else {
    CDialog::OnSysCommand(nID, lParam);
  }
}

// If you add a minimize button to your dialog, you will need the code below
// to draw the icon. For MFC applications using the document/view model,
// this is automatically done for you by the framework.

void CMainDialog::OnPaint()
{
  if (IsIconic()) {
    CPaintDC dc(this);                                               // Device context for painting.

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    int cxIcon = GetSystemMetrics(SM_CXICON);                        // Center icon in client rectangle.
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    dc.DrawIcon(x, y, m_hIcon);                                      // Draw the icon.
  } else {
    CDialog::OnPaint();
  }
}

// The system calls this function to obtain the cursor to display while the user drags  the minimized window.

HCURSOR CMainDialog::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}
