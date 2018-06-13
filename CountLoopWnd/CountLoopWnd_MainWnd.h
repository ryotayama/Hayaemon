//----------------------------------------------------------------------------
// CountLoopWnd_MainWnd.h : �񐔃��[�v�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef CountLoopWnd_MainWndH
#define CountLoopWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : �x�[�X �����o���������X�g�Ŏg�p����܂����B
class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "../Common/ButtonExt.h"
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/EditExt.h"
#include "../Common/UpDownCtrl.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �񐔃��[�v�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CCountLoopWnd_MainWnd : public CFrameWnd
{
public: // �֐�

	CCountLoopWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(*this),
		  m_OkButton(*this), m_CancelButton(*this), nFocus(0) { }
	virtual ~CCountLoopWnd_MainWnd() { }

	virtual BOOL Create();
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
	virtual void OnReturnKeyPressed();
	virtual void OnSpaceKeyPressed();
	virtual void OnEscKeyPressed();
	virtual void SetNextFocus();
	virtual void SetPreviousFocus();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual void OnVScroll(HWND hwndCtl, UINT code, int pos);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButtonExt m_OkButton;
	CButtonExt m_CancelButton;
	CStatic m_label; // �u�}�[�J�[�Ԃ��v�\���p���x��
	CStatic m_label2; // �u�񂸂��[�v������v�\���p���x��
	CFont m_font;
	CEditExt m_edit;
	CUpDownCtrl m_ud;

	int nFocus;

public: // �萔
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif