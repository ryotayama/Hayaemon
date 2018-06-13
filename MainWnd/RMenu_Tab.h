//----------------------------------------------------------------------------
// RMenu_Tab.h : �^�u�p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_TabH
#define RMenu_TabH

class CTab_MainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �^�u�p�E�N���b�N���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_Tab : public CMenu
{
public: // �֐�

	CRMenu_Tab(CTab_MainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_Tab() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnCloseMenuSelected();
	void OnRenameMenuSelected();
	void OnNewTabMenuSelected();
	void OnVisibleMenuSelected();

private: // �����o�ϐ�

	CTab_MainWnd & m_rParent;

public: // �萔

	// �R�}���h ID
	enum {
		ID_CLOSE = 11,
		ID_RENAME,
		ID_NEWTAB,
		ID_VISIBLE,
	};
};
//----------------------------------------------------------------------------

#endif