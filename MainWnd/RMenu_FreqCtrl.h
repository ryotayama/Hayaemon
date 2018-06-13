//----------------------------------------------------------------------------
// RMenu_FreqCtrl.h : �Đ����g���R���g���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_FreqCtrlH
#define RMenu_FreqCtrlH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �Đ����g���R���g���[���p�E�N���b�N���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_FreqCtrl : public CMenu
{
public: // �֐�

	CRMenu_FreqCtrl(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_FreqCtrl() { }

	virtual BOOL Create();
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);

private: // �����o�ϐ�

	CMainWnd & m_rParent;
	CMenu m_setFreqMenu;
	CMenu m_freqDecimalMenu;
};
//----------------------------------------------------------------------------

#endif