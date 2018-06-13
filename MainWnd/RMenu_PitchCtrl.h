//----------------------------------------------------------------------------
// RMenu_PitchCtrl.h : �����R���g���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_PitchCtrlH
#define RMenu_PitchCtrlH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �����R���g���[���p�E�N���b�N���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_PitchCtrl : public CMenu
{
public: // �֐�

	CRMenu_PitchCtrl(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_PitchCtrl() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);

private: // �����o�ϐ�

	CMainWnd & m_rParent;
	CMenu m_setPitchMenu;
	CMenu m_pitchDecimalMenu;
};
//----------------------------------------------------------------------------

#endif