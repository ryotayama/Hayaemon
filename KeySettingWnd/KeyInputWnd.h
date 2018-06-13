//----------------------------------------------------------------------------
// KeyInputWnd.h : �L�[���͗p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef KeyInputWndH
#define KeyInputWndH

class CApp;
class CMainWnd;
class CKeySettingWnd_MainWnd;
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
// �z�b�g�L�[�R���g���[���̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CHotKeyCtrl_KeyInputWnd : public CHotKeyCtrl
{
public: // �֐�

	CHotKeyCtrl_KeyInputWnd() { }
	virtual ~CHotKeyCtrl_KeyInputWnd() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
};
//----------------------------------------------------------------------------
// �L�[���͗p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CKeyInputWnd : public CFrameWnd
{
public: // �֐�

	CKeyInputWnd(CApp & app, CMainWnd & mainWnd,
				 CKeySettingWnd_MainWnd & parentWnd);
	virtual ~CKeyInputWnd();

	virtual BOOL Create(BOOL bAdd);

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
	CKeySettingWnd_MainWnd & m_rParentWnd;

	CComboBox m_combo;
	CHotKeyCtrl_KeyInputWnd m_hot;
	CButton m_OkButton;
	CButton m_CancelButton;

	LPACCEL m_pAccel; // �A�N�Z�����[�^�e�[�u���ޔ�p
	int m_nAccel; // �A�N�Z�����[�^�e�[�u���ޔ�p
	BOOL m_bAdd; // ���X�g�ɒǉ����邩�ǂ���

public: // �����o�ϐ��̎擾�E�ݒ�

	CHotKeyCtrl_KeyInputWnd & GetHotKeyCtrl() { return m_hot; }
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