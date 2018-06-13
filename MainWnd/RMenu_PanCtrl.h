//----------------------------------------------------------------------------
// RMenu_PanCtrl.h : �p���R���g���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_PanCtrlH
#define RMenu_PanCtrlH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �p���R���g���[���p�E�N���b�N���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_PanCtrl : public CMenu
{
public: // �֐�

	CRMenu_PanCtrl(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_PanCtrl() { }

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