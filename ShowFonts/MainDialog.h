// $Id: MainDialog.h,v 1.5 2006/01/30 14:19:59 gerrit-albrecht Exp $
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

#pragma once

#include "afxwin.h"
#include "afxcmn.h"

class CMainDialog : public CDialog
{
  public:
    CMainDialog(CWnd* pParent = NULL);

    enum { IDD = IDD_SHOWFONTS_DIALOG };

  public:
    CFont           m_font;
    CListBox        m_fonts_list;
    CRichEditCtrl   m_example_text;
    CComboBox       m_combo_weight;
    CComboBox       m_combo_height;
    CSpinButtonCtrl m_spin_weight;
    CSpinButtonCtrl m_spin_height;

  protected:
    HICON           m_icon;
    int             m_height;
    int             m_weight;
    CString         m_facename;

  protected:
    void GetFontsList();
    static int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, int FontType, LPARAM lParam);
    void SetNewFont();
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

  public:
    afx_msg void OnLbnSelchangeFontsList();
};
