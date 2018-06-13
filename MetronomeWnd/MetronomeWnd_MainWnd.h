//----------------------------------------------------------------------------
// MetronomeWnd_MainWnd.h : ���g���m�[���p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef MetronomeWnd_MainWndH
#define MetronomeWnd_MainWndH

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
// ���g���m�[���p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CMetronomeWnd_MainWnd : public CFrameWnd
{
public: // �֐�

	CMetronomeWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_bpmEdit(*this),
		  m_OkButton(*this), m_CancelButton(*this), nFocus(0) { }
	virtual ~CMetronomeWnd_MainWnd() { }

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

	CFont m_font;

	CStatic m_bpmLabel; // �u�e���|�F�v�\���p���x��
	CEditExt m_bpmEdit;
	CUpDownCtrl m_bpmUd;

	CButtonExt m_OkButton;
	CButtonExt m_CancelButton;

	int nFocus;

public: // �萔
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif