//----------------------------------------------------------------------------
// RMenu_VideoScreen.h : �Đ����Ԑݒ�p�X���C�_�p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_VideoScreenH
#define RMenu_VideoScreenH

class CVideoScreen_MainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ���C���E�B���h�E�p���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_VideoScreen : public CMenu
{
public: // �֐�

	CRMenu_VideoScreen(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_VideoScreen() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnFullScreenMenuSelected();

private: // �����o�ϐ�

	CMainWnd & m_rParent;

public: // �萔

	// �R�}���h ID
	enum {
		ID_FULLSCREEN = 11,
	};
};
//----------------------------------------------------------------------------

#endif