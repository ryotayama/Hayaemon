//----------------------------------------------------------------------------
// UpDownCtrl.h : �A�b�v�_�E���R���g���[���̍쐬�E�Ǘ����s��
//----------------------------------------------------------------------------
#ifndef UpDownCtrlH
#define UpDownCtrlH

#include <commctrl.h>
#include "Wnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �A�b�v�_�E���R���g���[���̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CUpDownCtrl : public CWnd
{
public: // �֐�

	CUpDownCtrl() { }
	virtual ~CUpDownCtrl() { }
	virtual BOOL Create(HWND hParentWnd, HWND hBuddy)
	{
		Destroy();

		INITCOMMONCONTROLSEX ic;
		ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
		ic.dwICC = ICC_UPDOWN_CLASS;
		InitCommonControlsEx(&ic);

		m_hWnd = CreateUpDownControl(
			WS_CHILD | WS_BORDER | UDS_ALIGNRIGHT | UDS_ARROWKEYS,
			0, 0, 0, 0,
			hParentWnd,
			0,
			GetModuleHandle(NULL),
			hBuddy,
			2048,
			0,
			0
		);
		if(!m_hWnd) return FALSE;
		SetProc();
		return TRUE;
	}
};
//----------------------------------------------------------------------------

#endif