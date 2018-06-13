//----------------------------------------------------------------------------
// 3DReverbCustomizeWnd.h : �R�c���o�[�u�̃J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef Reverb3DCustomizeWndH
#define Reverb3DCustomizeWndH

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
// �R�c���o�[�u�̃J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class C3DReverbCustomizeWnd : public CFrameWnd
{
public: // �֐�

	C3DReverbCustomizeWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~C3DReverbCustomizeWnd();

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

	CStatic m_roomLabel; // �uROOM:�v�\���p���x��
	CEditExt m_roomEdit;
	CUpDownCtrl m_roomUd;

	CStatic m_roomHFLabel; // �uROOM HF:�v�\���p���x��
	CEditExt m_roomHFEdit;
	CUpDownCtrl m_roomHFUd;

	CStatic m_roomRolloffFactorLabel; // �uROOM ROLLOFF FACTOR:�v�\���p���x��
	CEditExt m_roomRolloffFactorEdit;
	CUpDownCtrl m_roomRolloffFactorUd;

	CStatic m_decayTimeLabel; // �uDECAY TIME:�v�\���p���x��
	CEditExt m_decayTimeEdit;
	CUpDownCtrl m_decayTimeUd;

	CStatic m_decayHFRatioLabel; // �uDECAY HF RATIO:�v�\���p���x��
	CEditExt m_decayHFRatioEdit;
	CUpDownCtrl m_decayHFRatioUd;

	CStatic m_reflectionsLabel; // �uREFLECTIONS:�v�\���p���x��
	CEditExt m_reflectionsEdit;
	CUpDownCtrl m_reflectionsUd;

	CStatic m_reflectionsDelayLabel; // �uREFLECTIONS DELAY:�v�\���p���x��
	CEditExt m_reflectionsDelayEdit;
	CUpDownCtrl m_reflectionsDelayUd;

	CStatic m_reverbLabel; // �uREVERB:�v�\���p���x��
	CEditExt m_reverbEdit;
	CUpDownCtrl m_reverbUd;

	CStatic m_reverbDelayLabel; // �uREVERB DELAY:�v�\���p���x��
	CEditExt m_reverbDelayEdit;
	CUpDownCtrl m_reverbDelayUd;

	CStatic m_diffusionLabel; // �uDIFFUSION:�v�\���p���x��
	CEditExt m_diffusionEdit;
	CUpDownCtrl m_diffusionUd;

	CStatic m_densityLabel; // �uDENSITY:�v�\���p���x��
	CEditExt m_densityEdit;
	CUpDownCtrl m_densityUd;

	CStatic m_hfReferenceLabel; // �uHF REFERENCE:�v�\���p���x��
	CEditExt m_hfReferenceEdit;
	CUpDownCtrl m_hfReferenceUd;

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

#endif // Reverb3DCustomizeWndH