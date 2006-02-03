// $Id: OptionsDialog.cpp,v 1.1 2006/02/03 15:00:18 gerrit-albrecht Exp $
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
#include "OptionsDialog.h"

IMPLEMENT_DYNAMIC(COptionsDialog, CDialog)

BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
END_MESSAGE_MAP()

COptionsDialog::COptionsDialog(CWnd* pParent /*=NULL*/)
 : CDialog(COptionsDialog::IDD, pParent)
{
#ifndef _WIN32_WCE
  EnableActiveAccessibility();
#endif
}

COptionsDialog::~COptionsDialog()
{
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}
