//----------------------------------------------------------------------------
// GargleCustomizeWnd.h : �K�[�O���̃J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef GargleCustomizeWndH
#define GargleCustomizeWndH

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
// �K�[�O���̃J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CGargleCustomizeWnd : public CFrameWnd
{
public: // �֐�

	CGargleCustomizeWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CGargleCustomizeWnd();

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

	CStatic m_rateHzLabel; // �uRATE HZ:�v�\���p���x��
	CEditExt m_rateHzEdit;
	CUpDownCtrl m_rateHzUd;

	CStatic m_waveShapeLabel; // �uWAVE SHAPE:�v�\���p���x��
	CEditExt m_waveShapeEdit;
	CUpDownCtrl m_waveShapeUd;

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

#endif // GargleCustomizeWndH