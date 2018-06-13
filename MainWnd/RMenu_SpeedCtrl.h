//----------------------------------------------------------------------------
// RMenu_SpeedCtrl.h : �Đ����x�R���g���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_SpeedCtrlH
#define RMenu_SpeedCtrlH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �Đ����x�R���g���[���p�E�N���b�N���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_SpeedCtrl : public CMenu
{
public: // �֐�

	CRMenu_SpeedCtrl(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_SpeedCtrl() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);

private: // �����o�ϐ�

	CMainWnd & m_rParent;
	CMenu m_setSpeedMenu;
	CMenu m_speedDecimalMenu;
};
//----------------------------------------------------------------------------

#endif