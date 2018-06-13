//----------------------------------------------------------------------------
// RMenu_EQCtrl.h : EQ�R���g���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_EQCtrlH
#define RMenu_EQCtrlH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// EQ�R���g���[���p�E�N���b�N���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_EQCtrl : public CMenu
{
public: // �֐�

	CRMenu_EQCtrl(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_EQCtrl() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnVisibleMenuSelected();

private: // �����o�ϐ�

	CMainWnd & m_rParent;

public: // �萔

	// �R�}���h ID
	enum {
		ID_VISIBLE = 11,
	};
};
//----------------------------------------------------------------------------

#endif