//----------------------------------------------------------------------------
// ChorusCustomizeWnd.h : �R�[���X�̃J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef ChorusCustomizeWndH
#define ChorusCustomizeWndH

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
// �R�[���X�̃J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CChorusCustomizeWnd : public CFrameWnd
{
public: // �֐�

	CChorusCustomizeWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CChorusCustomizeWnd();

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
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CFont m_font;

	CStatic m_wetDryMixLabel; // �uWET DRY MIX:�v�\���p���x��
	CEditExt m_wetDryMixEdit;
	CUpDownCtrl m_wetDryMixUd;

	CStatic m_depthLabel; // �uDEPTH:�v�\���p���x��
	CEditExt m_depthEdit;
	CUpDownCtrl m_depthUd;

	CStatic m_feedbackLabel; // �uFEEDBACK:�v�\���p���x��
	CEditExt m_feedbackEdit;
	CUpDownCtrl m_feedbackUd;

	CStatic m_frequencyLabel; // �uFREQUENCY:�v�\���p���x��
	CEditExt m_frequencyEdit;
	CUpDownCtrl m_frequencyUd;

	CStatic m_waveformLabel; // �uWAVEFORM:�v�\���p���x��
	CEditExt m_waveformEdit;
	CUpDownCtrl m_waveformUd;

	CStatic m_delayLabel; // �uDELAY:�v�\���p���x��
	CEditExt m_delayEdit;
	CUpDownCtrl m_delayUd;

	CButtonExt m_OkButton;
	CButtonExt m_CancelButton;

	int m_nFocus;

public: // �萔
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif // ChorusCustomizeWndH