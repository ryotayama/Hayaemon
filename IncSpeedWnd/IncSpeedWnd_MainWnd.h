//----------------------------------------------------------------------------
// IncSpeedWnd_MainWnd.h : ���񂾂񑬂�����E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef IncSpeedWnd_MainWndH
#define IncSpeedWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : �x�[�X �����o���������X�g�Ŏg�p����܂����B
class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "../Common/ButtonExt.h"
#include "../Common/RadioButton.h"
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
// ���񂾂񑬂�����E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CIncSpeedWnd_MainWnd : public CFrameWnd
{
public: // �֐�

	CIncSpeedWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(*this), m_edit2(*this),
		  m_edit3(*this), m_OkButton(*this), m_CancelButton(*this),
		  nFocus(0), strLabel(_T("�Đ����x��")), strLabel2(_T("�グ��")) { }
	virtual ~CIncSpeedWnd_MainWnd() { }

	virtual BOOL Create();
	virtual void EnableControl(BOOL bSecondEnable, BOOL bLoopEnable);
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

protected: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CRadioButton m_secondRadioButton;
	CButtonExt m_OkButton;
	CButtonExt m_CancelButton;
	CStatic m_label; // �u�Đ����x���v�\���p���x��
	CStatic m_label2; // �u�b�ԂɁv�\���p���x��
	CStatic m_label3; // �u%�グ��v�\���p���x��
	CFont m_font;
	CEditExt m_edit;
	CEditExt m_edit2;
	CUpDownCtrl m_ud;
	CUpDownCtrl m_ud2;

	CRadioButton m_loopRadioButton;
	CStatic m_label4; // �u�Đ����x���v�\���p���x��
	CStatic m_label5; // �u���[�v���Ɂv�\���p���x��
	CStatic m_label6; // �u%�グ��v�\���p���x��
	CEditExt m_edit3;
	CUpDownCtrl m_ud3;

	int nFocus;

	tstring strLabel;
	tstring strLabel2;

public: // �萔
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif