//----------------------------------------------------------------------------
// RMenu_VolumeCtrl.h : ���ʃR���g���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_VolumeCtrlH
#define RMenu_VolumeCtrlH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ���ʃR���g���[���p�E�N���b�N���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_VolumeCtrl : public CMenu
{
public: // �֐�

	CRMenu_VolumeCtrl(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_VolumeCtrl() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);

private: // �����o�ϐ�

	CMainWnd & m_rParent;
	CMenu m_setVolumeMenu;
};
//----------------------------------------------------------------------------

#endif