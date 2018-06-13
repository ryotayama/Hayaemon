//----------------------------------------------------------------------------
// KeySettingWnd_MainWnd.h : �L�[�J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef KeySettingWnd_MainWndH
#define KeySettingWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : �x�[�X �����o���������X�g�Ŏg�p����܂����B
class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "./List_KeySettingWnd.h"
#include "../Common/ButtonExt.h"
#include "./KeyInputWnd.h"
#include "../Common/CommandList.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �L�[�J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CKeySettingWnd_MainWnd : public CFrameWnd
{
public: // �֐�

	CKeySettingWnd_MainWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CKeySettingWnd_MainWnd();

	virtual void AddList(UINT bVKHotKey, UINT bfMods, tstring strCommand);
	virtual void ChangeList(UINT bVKHotKey, UINT bfMods, tstring strCommand);
	virtual BOOL Create();
	virtual void Close();
	virtual void OnClose();
	virtual void OnAddButtonClicked();
	virtual void OnChangeButtonClicked();
	virtual void OnDeleteButtonClicked();
	virtual void OnDefaultButtonClicked();
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
	virtual void OnReturnKeyPressed();
	virtual void OnSpaceKeyPressed();
	virtual void OnEscKeyPressed();
	virtual void ExecCurrentButtonFunc();
	virtual void SetNextFocus();
	virtual void SetPreviousFocus();
	virtual void ShowList();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

protected: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CList_KeySettingWnd m_List;
	CButtonExt m_AddButton;
	CButtonExt m_ChangeButton;
	CButtonExt m_DeleteButton;
	CButtonExt m_DefaultButton;
	CButtonExt m_OkButton;
	CButtonExt m_CancelButton;

	CKeyInputWnd m_keyInputWnd;

	int m_nFocus;

public: // �����o�ϐ�

	CCommandList m_CmdList;


public: // �萔
	enum {
		ID_ADD = 100,
		ID_CHANGE,
		ID_DELETE,
		ID_DEFAULT,
		ID_OK,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif