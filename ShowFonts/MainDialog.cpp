// $Id: MainDialog.cpp,v 1.1 2005/11/13 21:44:28 gerrit-albrecht Exp $
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
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_FONTS_LIST, m_fonts_list);
  DDX_Control(pDX, IDC_EXAMPLE_TEXT, m_example_text);
}

BEGIN_MESSAGE_MAP(CMainDialog, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_LBN_SELCHANGE(IDC_FONTS_LIST, OnLbnSelchangeFontsList)
  ON_CBN_SELCHANGE(IDC_COMBO_WEIGHT, OnCbnSelchangeComboWeight)
END_MESSAGE_MAP()


// CMainDialog Meldungshandler

BOOL CMainDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUT_DIALOG & 0xFFF0) == IDM_ABOUT_DIALOG);
	ASSERT(IDM_ABOUT_DIALOG < 0xF000);

	CMenu *pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
		CString strAboutMenu;

    strAboutMenu.LoadString(IDS_ABOUT_DIALOG);

    if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUT_DIALOG, strAboutMenu);
		}
	}

  // Tell our Rich-Text field that it shall reflect its messages
  // to this dialog. I'm to lazy to make a subclass.

  m_example_text.SetEventMask(ENM_MOUSEEVENTS);

  // Symbol für dieses Dialogfeld festlegen. Wird sonst automatisch
  // erledigt wenn das Hauptfenster der Anwendung kein Dialogfeld ist.

  SetIcon(m_hIcon, TRUE);                        // Großes Symbol verwenden.
  SetIcon(m_hIcon, FALSE);                       // Kleines Symbol verwenden.

  m_example_text.SetWindowText("Das ist ein schöner Test-Text. 1234567890");

  GetFontsList();

  m_height   = 50;
  m_weight   = FW_NORMAL;
  m_facename = "";

  // TODO: Select default popup values in the top right area ...

  if (m_fonts_list.GetCount() > 0) {
    m_fonts_list.SetCurSel(0);                   // Select first font in list.

    OnLbnSelchangeFontsList();
  }

  return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten.
}

void CMainDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUT_DIALOG) {
		CAboutDialog dialog;
		dialog.DoModal();
	}
	else {
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CMainDialog::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);

  CDialog::OnDestroy();
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
// den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
// Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CMainDialog::OnPaint()
{
  if (IsIconic()) {
    CPaintDC dc(this);                           // Gerätekontext zum Zeichnen.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);    // Symbol in Clientrechteck zentrieren.
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width()  - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

    dc.DrawIcon(x, y, m_hIcon);                  // Symbol zeichnen.
	}
	else {
		CDialog::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen,
// der angezeigt wird, während der Benutzer das minimierte Fenster
// mit der Maus zieht.

HCURSOR CMainDialog::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}

void CMainDialog::GetFontsList()
{
  LOGFONT  lf;
  POSITION pos;
  HDC      dc = ::GetDC(NULL);  // GetDC()->m_hDC

  memset(&lf, 0, sizeof(LOGFONT));        // Just to be sure: zero out structure.

  //m_fonts_list Clearing ...

  lf.lfCharSet = ANSI_CHARSET;
  lf.lfFaceName[0] = '\0';
  //*lf.lfFaceName = 0;
  //lf.lfPitchAndFamily = 0;

  ::EnumFontFamiliesEx(dc, &lf, (FONTENUMPROC) CMainDialog::EnumFontFamExProc, 
                       (LPARAM) &m_fonts_list, 0);

  ::ReleaseDC(NULL, dc);

  //for (pos = fontlist.GetHeadPosition(); pos != NULL;)
  //  this->AddString(fontlist.GetNext(pos));
}

int CALLBACK CMainDialog::EnumFontFamExProc(ENUMLOGFONTEX *lpelfe,
                                            NEWTEXTMETRICEX *lpntme,
                                            int FontType, LPARAM lParam)
{
  //CStringList* m_temp = (CStringList*) lParam;
  //m_temp->AddTail((char*)lpelfe->elfFullName);

  CListBox *fonts_list = reinterpret_cast<CListBox *>(lParam);

  fonts_list->AddString((LPCTSTR) (lpelfe->elfFullName));

  return 1;                                      // I want to get all fonts.
}

void CMainDialog::SetNewFont()
{
  CFont font;

  font.CreateFont(m_height, 0, 0, 0, m_weight, FALSE, FALSE, FALSE, DEFAULT_CHARSET /*ANSI_CHARSET*/,
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
    DEFAULT_PITCH | FF_SWISS /*FF_DONTCARE*/, m_facename.GetBuffer(0));

  m_example_text.SetFont(&font, TRUE);

  #ifdef _DEBUG
  {
    LOGFONT lf;
    font.GetLogFont(&lf);
    TRACE("  Typeface = %s\n", lf.lfFaceName);
    TRACE("  Charset = %d\n", lf.lfCharSet);
  }
  #endif

  font.DeleteObject();
}

void CMainDialog::OnLbnSelchangeFontsList()
{
  CString str;
  int sel, len;

  sel = m_fonts_list.GetCurSel();
  len = m_fonts_list.GetTextLen(sel);

  m_fonts_list.GetText(sel, str.GetBuffer(len));
  str.ReleaseBuffer();

  m_facename = str;

  SetNewFont();

  #ifdef _DEBUG
  {
    CString s;
    s.Format(_T("item %d: %s\n"), sel, str.GetBuffer());
    afxDump << s;
  }
  #endif
}

void CMainDialog::OnCbnSelchangeComboWeight()
{
  CString str;
  CComboBox *cb;
  int item;
  int len;

  cb = (CComboBox *) GetDlgItem(IDC_COMBO_WEIGHT);
  item = cb->GetCurSel();
  len = cb->GetLBTextLen(item);
  cb->GetLBText(item, str.GetBuffer(len));
  str.ReleaseBuffer();

  //AfxMessageBox(str, MB_OK);

  if (str == "")
    m_weight = FW_DONTCARE;
  else if (str == "Normal")
    m_weight = FW_NORMAL;
  else if (str == "Ordentlich")
    m_weight = FW_REGULAR;
  else if (str == "Fett")
    m_weight = FW_BOLD;
  else
    m_weight = FW_NORMAL;

  SetNewFont();
}

BOOL CMainDialog::PreTranslateMessage(MSG* pMsg)
{
  if (pMsg->message == WM_RBUTTONDOWN) {
    CWnd *win = (CWnd *) GetDlgItem(IDC_FONTS_LIST);

    CRect rect;
    win->GetWindowRect(rect);

    #ifdef _DEBUG
      afxDump << pMsg->pt.x << " " << pMsg->pt.y << "\n";
      afxDump << rect.left << " " << rect.top << " " << rect.right << " " << rect.bottom << "\n";
    #endif

    if (rect.PtInRect(pMsg->pt)) {
      CMenu menu;
      DWORD selection;

      VERIFY(menu.LoadMenu(IDR_MENU_FONT_LIST));

      CMenu *popup = menu.GetSubMenu(0);
      ASSERT(popup != NULL);

      selection = popup->TrackPopupMenu((TPM_LEFTALIGN | TPM_LEFTBUTTON |
                                         TPM_NONOTIFY | TPM_RETURNCMD),
                                        pMsg->pt.x, pMsg->pt.y, this);
      popup->DestroyMenu();

      switch (selection) {
        case 0:
          break;

        case ID_CUSTOM_FONT_DIR:
          break;

        case ID_SYSTEM_FONT_DIR:
          break;
      }

      return TRUE;
    }
  }

  return CDialog::PreTranslateMessage(pMsg);
}

BOOL CMainDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
  if (wParam == IDC_EXAMPLE_TEXT) {
    MSGFILTER *lpMsgFilter = (MSGFILTER *) lParam;

    if ( (lpMsgFilter->nmhdr.code == EN_MSGFILTER) &&
         (lpMsgFilter->msg == WM_RBUTTONDOWN) )
    {
      afxDump << "Catched a reflected message.\n";


    }
  }

  return CDialog::OnNotify(wParam, lParam, pResult);
}
