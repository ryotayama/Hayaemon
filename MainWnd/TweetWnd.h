//----------------------------------------------------------------------------
// TweetWnd.h : �Đ��ʒu�ݒ�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef TweetWndH
#define TweetWndH

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
// �Đ��ʒu�ݒ�p�G�f�B�b�g�{�b�N�X�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CEdit_Tweet : public CEdit
{
public: // �֐�

	CEdit_Tweet(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_Tweet() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// �Đ��ʒu�ݒ�p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CTweetWnd : public CFrameWnd
{
public: // �֐�

	CTweetWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(app, mainWnd),
		  m_pAccel(NULL) { }
	virtual ~CTweetWnd() { }

	virtual BOOL Create();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual void Tweet();

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButton m_tweetButton;
	CFont m_font;
	CEdit_Tweet m_edit;

	int m_nAccel;
	ACCEL* m_pAccel;

public: // �萔
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif