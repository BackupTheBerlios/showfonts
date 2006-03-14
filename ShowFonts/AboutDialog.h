// $Id: AboutDialog.h,v 1.3 2006/03/14 14:42:02 gerrit-albrecht Exp $
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

#include "Resource.h"

#include <Miraledon/HyperLinkCtrl.h>

class CAboutDialog : public CDialog
{
  public:
    CAboutDialog ();

	enum { IDD = IDD_ABOUT };

  protected:
    MHyperlinkCtrl m_homepage_link;

  protected:
    virtual void DoDataExchange (CDataExchange* pDX);

  protected:
    DECLARE_MESSAGE_MAP()
};
