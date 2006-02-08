// $Id: MainDialog.cpp,v 1.11 2006/02/08 12:31:43 gerrit-albrecht Exp $
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

BEGIN_MESSAGE_MAP(CMainDialog, MDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_LBN_SELCHANGE(IDC_FONTS_LIST, &CMainDialog::OnLbnSelchangeFontsList)
    ON_CBN_SELCHANGE(IDC_COMBO_WEIGHT, &CMainDialog::OnCbnSelchangeComboWeight)
    ON_CBN_SELCHANGE(IDC_COMBO_HEIGHT, &CMainDialog::OnCbnSelchangeComboHeight)
    ON_CBN_EDITCHANGE(IDC_COMBO_HEIGHT, &CMainDialog::OnCbnEditchangeComboHeight)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_WEIGHT, &CMainDialog::OnDeltaposSpinWeight)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HEIGHT, &CMainDialog::OnDeltaposSpinHeight)
    ON_WM_SIZE()
    ON_WM_SIZING()
END_MESSAGE_MAP()

CMainDialog::CMainDialog(CWnd *parent /* =0 */)
 : MDialog(CMainDialog::IDD, parent)
{
  EnableActiveAccessibility();

  m_icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_FONTS_LIST, m_fonts_list);
  DDX_Control(pDX, IDC_EXAMPLE_TEXT, m_example_text);
  DDX_Control(pDX, IDC_COMBO_WEIGHT, m_combo_weight);
  DDX_Control(pDX, IDC_COMBO_HEIGHT, m_combo_height);
  DDX_Control(pDX, IDC_SPIN_WEIGHT, m_spin_weight);
  DDX_Control(pDX, IDC_SPIN_HEIGHT, m_spin_height);
}

BOOL CMainDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  CreateSizeGrip(true);
  CreateToolTip();

  // IDM_ABOUTBOX must be in the system command range.

  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);

  // Add "About..." menu item to system menu.

  CMenu *pSysMenu = GetSystemMenu(FALSE);
  if (pSysMenu != NULL) {
    CString strAboutMenu;

    strAboutMenu.LoadString(IDS_ABOUTBOX);
    if (!strAboutMenu.IsEmpty()) {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }

  // Set the icon for this dialog. The framework does this automatically
  // when the application's main window is not a dialog.

  SetIcon(m_icon, TRUE);                                             // Set big icon.
  SetIcon(m_icon, FALSE);                                            // Set small icon.

  // Tell our Rich-Text field that it shall reflect its messages
  // to this dialog. I'm to lazy to make an extra subclass.

  m_example_text.SetEventMask(ENM_MOUSEEVENTS);

  m_example_text.SetWindowText(_T("Das ist ein schöner Test-Text.\n1234567890"));

  GetFontsList();

  m_height   = 50;
  m_weight   = FW_NORMAL;
  m_facename = _T("");

  m_combo_weight.SelectString(-1, _T("Normal"));
  m_combo_height.SelectString(-1, _T("50"));

  m_spin_weight.SetBuddy(&m_combo_weight);
  m_spin_height.SetBuddy(&m_combo_height);

  if (m_fonts_list.GetCount() > 0) {
    m_fonts_list.SetCurSel(0);                                       // Select first font in list.

    OnLbnSelchangeFontsList();
  }

  AddToolTips();

  m_tooltip.AddTool(this, _T("TEST"));
  m_tooltip.AddTool(GetDlgItem(IDOK), _T("OKAY"));

  return TRUE;                                                       // Return TRUE, unless you set the focus to a control.
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
    int x = (rect.Width()  - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    dc.DrawIcon(x, y, m_icon);                                       // Draw the icon.
  } else {
    MDialog::OnPaint();
  }
}

// The system calls this function to obtain the cursor to display
// while the user drags the minimized window.

HCURSOR CMainDialog::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_icon);
}

void CMainDialog::GetFontsList()
{
  LOGFONT  lf;
  //POSITION pos;
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

  return 1;                                                          // I want to get all fonts.
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
}

void CMainDialog::OnCbnSelchangeComboHeight()
{
}

BOOL CMainDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
  if (wParam == IDC_EXAMPLE_TEXT) {
    MSGFILTER *lpMsgFilter = (MSGFILTER *) lParam;

    if ( (lpMsgFilter->nmhdr.code == EN_MSGFILTER) &&
         (lpMsgFilter->msg == WM_RBUTTONDOWN) ) {
      TRACE("Catched a reflected message.\n");


    }
  }

  return CDialog::OnNotify(wParam, lParam, pResult);
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

      selection = popup->TrackPopupMenu((TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD),
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

// Wird bei jedem Tastendruck aufgerufen.

void CMainDialog::OnCbnEditchangeComboHeight()
{
  CString str;

  m_combo_height.GetWindowText(str);

  m_height = _ttoi(str);

  if (m_height <= 0)
    m_height = 1;

  SetNewFont();
}

// Click on the weight spin control.

void CMainDialog::OnDeltaposSpinWeight(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

  TRACE("CMainDialog::OnDeltaposSpinWeight: code=%d pos=%d delta=%d\n", pNMHDR->code, pNMUpDown->iPos, pNMUpDown->iDelta);

  *pResult = 0;
}

// Click on the height spin control.
// pNMHDR->code is always -722 (IDC_SPIN_HEIGHT is 1005),
// pNMUpDown->iPos (0..x), and
// pNMUpDown->iDelta was 1 (down clicked) and -1 (up clicked).

void CMainDialog::OnDeltaposSpinHeight(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

  TRACE("CMainDialog::OnDeltaposSpinHeight: code=%d pos=%d delta=%d\n", pNMHDR->code, pNMUpDown->iPos, pNMUpDown->iDelta);

  *pResult = 0;
}
