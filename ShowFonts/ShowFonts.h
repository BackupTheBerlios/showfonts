// $Id: ShowFonts.h,v 1.3 2006/01/30 10:47:51 gerrit-albrecht Exp $
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

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "Resource.h"

class CShowFonts : public CWinApp
{
  public:
    CShowFonts();

  public:
    virtual BOOL InitInstance();

  DECLARE_MESSAGE_MAP()
};

extern CShowFonts theApp;
