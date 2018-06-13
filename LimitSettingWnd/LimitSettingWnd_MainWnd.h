//----------------------------------------------------------------------------
// LimitSettingWnd_MainWnd.h : �ő�l�^�ŏ��l�̐ݒ�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef LimitSettingWnd_MainWndH
#define LimitSettingWnd_MainWndH

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
// �ő�l�^�ŏ��l�̐ݒ�p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CLimitSettingWnd_MainWnd : public CFrameWnd
{
public: // �֐�

	CLimitSettingWnd_MainWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CLimitSettingWnd_MainWnd();

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

	CStatic m_speedLabel; // �u�Đ����x�F�v�\���p���x��
	CStatic m_speedLabel2; // �u% �`�v�\���p���x��
	CStatic m_speedLabel3; // �u%�v�\���p���x��
	CEditExt m_minSpeedEdit;
	CEditExt m_maxSpeedEdit;
	CUpDownCtrl m_minSpeedUd;
	CUpDownCtrl m_maxSpeedUd;

	CStatic m_freqLabel; // �u�Đ����g���F�v�\���p���x��
	CStatic m_freqLabel2; // �u% �`�v�\���p���x��
	CStatic m_freqLabel3; // �u%�v�\���p���x��
	CEditExt m_minFreqEdit;
	CEditExt m_maxFreqEdit;
	CUpDownCtrl m_minFreqUd;
	CUpDownCtrl m_maxFreqUd;

	CStatic m_pitchLabel; // �u�����F�v�\���p���x��
	CStatic m_pitchLabel2; // �u�`�v�\���p���x��
	CEditExt m_minPitchEdit;
	CEditExt m_maxPitchEdit;
	CUpDownCtrl m_minPitchUd;
	CUpDownCtrl m_maxPitchUd;

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

#endif // LimitSettingWnd_MainWndH