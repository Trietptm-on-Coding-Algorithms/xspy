/* 
 *
 * This file is part of xspy
 * By lynnux <lynnux@qq.com>
 * Copyright 2013 lynnux
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlframe.h>
//#include "ui_mfc.h"
//#include "ui_atl.h"
#include "ui_capture.h"
#include <boost/shared_ptr.hpp>
#include "AboutDlg.h"

class CMainDlg 
    : public CDialogImpl<CMainDlg>
    , public CMessageFilter
    , public CIdleHandler
    , public CDialogResize<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnIdle();

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		//NOTIFY_HANDLER(IDC_TAB1, TCN_SELCHANGE, OnTcnSelchangeTab1)
        MESSAGE_HANDLER(WM_SPY, OnSpy)
        MESSAGE_HANDLER(WM_SPY_START, OnSpyStart)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        COMMAND_HANDLER(IDC_CHECK1, BN_CLICKED, OnBnClickedCheck1)
        COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
        CHAIN_MSG_MAP(CDialogResize<CMainDlg>)
    END_MSG_MAP()

    BEGIN_DLGRESIZE_MAP(CMainDlg)
        DLGRESIZE_CONTROL(IDC_EDIT1, DLSZ_SIZE_X)
        DLGRESIZE_CONTROL(IDC_STATIC1, DLSZ_MOVE_X)
        DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X)
        DLGRESIZE_CONTROL(IDC_EDIT_MSG, DLSZ_SIZE_X | DLSZ_SIZE_Y)

        //BEGIN_DLGRESIZE_GROUP()
            DLGRESIZE_CONTROL(IDC_STATIC_OPTIONS, DLSZ_MOVE_Y | DLSZ_SIZE_X) // set transparent=true in property
            DLGRESIZE_CONTROL(IDC_CHECK1, DLSZ_MOVE_Y)
            DLGRESIZE_CONTROL(IDC_EDIT2, DLSZ_MOVE_Y)
            DLGRESIZE_CONTROL(IDC_CHECK2, DLSZ_MOVE_Y)
            DLGRESIZE_CONTROL(ID_APP_ABOUT, DLSZ_MOVE_X | DLSZ_MOVE_Y)
            //END_DLGRESIZE_GROUP()
    END_DLGRESIZE_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    LRESULT OnSpy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnSpyStart(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	//LRESULT OnTcnSelchangeTab1(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
    void CloseDialog(int nVal);
	//int CalcTabHeight();

    void ShowChange(int index);
    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CAboutDlg dlg;
        dlg.DoModal();
        return 0;
    }
private:

	//CTabCtrl m_tab;
	//ui_mfc ui_mfc_;
	//ui_atl ui_atl_;
	ui_capture ui_capture_;
    bool hideXspyWhenCapture_;
    //boost::shared_ptr<CAboutDlg> ui_about_;
public:
    LRESULT OnBnClickedCheck1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedButton1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
