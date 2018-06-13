//----------------------------------------------------------------------------
// RMenu_Taskbar.h : �^�X�N�o�[�p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_TaskbarH
#define RMenu_TaskbarH

class CMainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �^�X�N�o�[�p�E�N���b�N���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_Taskbar : public CMenu
{
public: // �֐�

	CRMenu_Taskbar(CMainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_Taskbar() { }

	virtual BOOL Create();
	virtual UINT GetItemFlags(UINT_PTR uID);

private: // �����o�ϐ�

	CMainWnd & m_rParent;
	CMenu m_returnMenu;
	CMenu m_forwardMenu;
	CMenu m_speedMenu;
	CMenu m_freqMenu;
	CMenu m_pitchMenu;
	CMenu m_systemMenu;
	CMenu m_effectMenu;
	CMenu m_reverbMenu;
	CMenu m_delayMenu;
	CMenu m_chorusMenu;
	CMenu m_compressorMenu;
	CMenu m_flangerMenu;
	CMenu m_gargleMenu;
	CMenu m_distortionMenu;
	CMenu m_eqPresetMenu;
	CMenu m_recoveryMenu;
	CMenu m_recoverVisibleMenu;
	CMenu m_recoverPlayModeMenu;

public: // �萔

};
//----------------------------------------------------------------------------

#endif