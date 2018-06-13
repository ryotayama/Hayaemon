//----------------------------------------------------------------------------
// OutKeyInputWnd.h : �O���[�o���z�b�g�L�[���͗p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef OutKeyInputWndH
#define OutKeyInputWndH

class CApp;
class CMainWnd;
class COutKeySettingWnd_MainWnd;
#include "../Common/FrameWnd.h"
#include "../Common/ComboBox.h"
#include "../Common/HotKeyCtrl.h"
#include "../Common/Button.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �L�[���͗p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class COutKeyInputWnd : public CFrameWnd
{
public: // �֐�

	COutKeyInputWnd(CApp & app, CMainWnd & mainWnd, COutKeySettingWnd_MainWnd & parentWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rParentWnd(parentWnd), bAdd(FALSE) { }
	virtual ~COutKeyInputWnd() { }

	virtual BOOL Create(BOOL bAdd);

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
	COutKeySettingWnd_MainWnd & m_rParentWnd;

	CComboBox m_combo;
	CHotKeyCtrl m_hot;
	CButton m_OkButton;
	CButton m_CancelButton;

	BOOL bAdd; // ���X�g�ɒǉ����邩�ǂ���

public: // �����o�ϐ��̎擾�E�ݒ�

	CHotKeyCtrl & GetHotKeyCtrl() { return m_hot; }
	CComboBox & GetComboBox() { return m_combo; }

public: // �萔
	enum {
		ID_COMBO = 100,
		ID_HOT,
		ID_OK,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif