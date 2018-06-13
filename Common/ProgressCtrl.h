//----------------------------------------------------------------------------
// ProgressCtrl.h : �X���C�_�R���g���[���̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef ProgressCtrlH
#define ProgressCtrlH

#include <commctrl.h>
#include "Wnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �X���C�_�R���g���[���̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CProgressCtrl : public CWnd
{
public: // �֐�

	CProgressCtrl() { }
	virtual ~CProgressCtrl() { }

	virtual BOOL Create(HWND hParentWnd) {
		Destroy();
	
		INITCOMMONCONTROLSEX ic;
		ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
		ic.dwICC = ICC_PROGRESS_CLASS;
		InitCommonControlsEx(&ic);

		m_hWnd = CreateWindow(PROGRESS_CLASS, _T(""), PBS_SMOOTH | WS_CHILD, CW_USEDEFAULT,
								CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								hParentWnd, 0, GetModuleHandle(NULL), NULL);
		if(!m_hWnd) return FALSE;
		SetProc();
		return TRUE;
	}
	virtual void SetProgressPos(int nPos) {
		SendMessage(m_hWnd, PBM_SETPOS, (WPARAM)nPos, 0L);
	}
	virtual void SetProgressRange(int nLower, int nUpper) {
		SendMessage(m_hWnd, PBM_SETRANGE32, (WPARAM)nLower, (LPARAM)nUpper);
	}
};
//----------------------------------------------------------------------------

#endif