//----------------------------------------------------------------------------
// OutKeySettingWnd_MainWnd.h : �O���[�o���z�b�g�L�[�J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef OutKeySettingWnd_MainWndH
#define OutKeySettingWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : �x�[�X �����o���������X�g�Ŏg�p����܂����B
class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "./OutKeyInputWnd.h"
#include "../KeySettingWnd/KeySettingWnd_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �O���[�o���z�b�g�L�[�J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class COutKeySettingWnd_MainWnd : public CKeySettingWnd_MainWnd
{
public: // �֐�

	COutKeySettingWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: CKeySettingWnd_MainWnd(app,mainWnd),
		  m_outKeyInputWnd(app, mainWnd, *this) {}
	virtual ~COutKeySettingWnd_MainWnd() { }

	virtual BOOL Create();
	virtual void Close();
	virtual void OnAddButtonClicked();
	virtual void OnChangeButtonClicked();
	virtual void OnDeleteButtonClicked();
	virtual void OnOkButtonClicked();
	virtual void ExecCurrentButtonFunc();
	virtual void SetNextFocus();
	virtual void SetPreviousFocus();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);


private: // �����o�ϐ�

	COutKeyInputWnd m_outKeyInputWnd;

public: // �����o�ϐ��̎擾�E�ݒ�

	CListView & GetList() { return m_List; }

};
//----------------------------------------------------------------------------

#endif