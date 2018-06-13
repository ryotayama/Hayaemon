//----------------------------------------------------------------------------
// TwitterAuthorizeWnd.h : �c�C�b�^�[�F�ؗp�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef TwitterAuthorizeWndH
#define TwitterAuthorizeWndH

class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "../Common/Button.h"
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/Edit.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �c�C�b�^�[�F�ؗp�E�B���h�E���G�f�B�b�g�{�b�N�X�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CEdit_TwitterAuthorize : public CEdit
{
public: // �֐�

	CEdit_TwitterAuthorize(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_TwitterAuthorize() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// �c�C�b�^�[�F�ؗp�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CTwitterAuthorizeWnd : public CFrameWnd
{
public: // �֐�

	CTwitterAuthorizeWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(app, mainWnd) { }
	virtual ~CTwitterAuthorizeWnd() { }

	virtual BOOL Create();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual bool ParseReply(const char *reply, std::string *token,
							std::string *secret);
	virtual void SetPin();

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButton m_okButton;
	CFont m_font;
	CEdit_TwitterAuthorize m_edit;
	CStatic m_label; // �u���E�U��Łu������v���N���b�N���Ă��������A
					 // �\�����ꂽ�W����PIN�R�[�h����͂��Ă��������B
	CStatic m_label2; // �u���E�U��Łu������v���N���b�N���Ă��������A
					 // �\�����ꂽ�W����PIN�R�[�h����͂��Ă��������B
	CStatic m_label3; // PIN�R�[�h
	std::string t_key;
	std::string postarg;

public: // �萔
	enum {
		ID_OK = 100,
	};
};
//----------------------------------------------------------------------------

#endif