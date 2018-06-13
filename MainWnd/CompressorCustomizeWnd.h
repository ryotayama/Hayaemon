//----------------------------------------------------------------------------
// CompressorCustomizeWnd.h : �R���v���b�T�̃J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef CompressorCustomizeWndH
#define CompressorCustomizeWndH

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
// �R���v���b�T�[�̃J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CCompressorCustomizeWnd : public CFrameWnd
{
public: // �֐�

	CCompressorCustomizeWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CCompressorCustomizeWnd();

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

	CStatic m_gainLabel; // �uGAIN:�v�\���p���x��
	CEditExt m_gainEdit;
	CUpDownCtrl m_gainUd;

	CStatic m_attackLabel; // �uATTACK:�v�\���p���x��
	CEditExt m_attackEdit;
	CUpDownCtrl m_attackUd;

	CStatic m_releaseLabel; // �uRELEASE:�v�\���p���x��
	CEditExt m_releaseEdit;
	CUpDownCtrl m_releaseUd;

	CStatic m_thresholdLabel; // �uTHRESHOLD:�v�\���p���x��
	CEditExt m_thresholdEdit;
	CUpDownCtrl m_thresholdUd;

	CStatic m_ratioLabel; // �uRATIO:�v�\���p���x��
	CEditExt m_ratioEdit;
	CUpDownCtrl m_ratioUd;

	CStatic m_predelayLabel; // �uPREDELAY:�v�\���p���x��
	CEditExt m_predelayEdit;
	CUpDownCtrl m_predelayUd;

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

#endif // CompressorCustomizeWndH