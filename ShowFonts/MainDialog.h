// $Id: MainDialog.h,v 1.8 2006/02/03 12:18:15 gerrit-albrecht Exp $
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
#include "MiraDialog.h"
#include "TrayIcon.h"

class CMainDialog : public CMiraDialog
{
  public:
    CMainDialog(CWnd *parent = 0);

    enum { IDD = IDD_SHOWFONTS_DIALOG };

  public:
    CFont           m_font;                      ///< The font object with the currently selected font.
    CListBox        m_fonts_list;                ///< The fonts list on the left side of our dialog.
    CRichEditCtrl   m_example_text;              ///< The example text area.
    CComboBox       m_combo_weight;              ///< Contains predefined values for the font weight.
    CComboBox       m_combo_height;              ///< Contains predefined values for the font height. 
    CSpinButtonCtrl m_spin_weight;               ///< Changes the font's weight.
    CSpinButtonCtrl m_spin_height;               ///< Sets the font's height with the mouse.

  protected:
    HICON           m_icon;
    CTrayIcon       m_tray_icon;
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
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

  public:
    afx_msg void OnLbnSelchangeFontsList();
    afx_msg void OnCbnSelchangeComboWeight();
    afx_msg void OnCbnSelchangeComboHeight();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnCbnEditchangeComboHeight();
    afx_msg void OnDeltaposSpinWeight(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeltaposSpinHeight(NMHDR *pNMHDR, LRESULT *pResult);
};
