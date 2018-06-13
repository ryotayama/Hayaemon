//----------------------------------------------------------------------------
// PlayRangeWnd.h : �Đ��͈͐ݒ�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef PlayRangeWndH
#define PlayRangeWndH

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
// �Đ��͈͐ݒ�p�G�f�B�b�g�{�b�N�X�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CEdit_PlayRange : public CEdit
{
public: // �֐�

	CEdit_PlayRange(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_PlayRange() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// �Đ��͈͐ݒ�p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CPlayRangeWnd : public CFrameWnd
{
public: // �֐�

	CPlayRangeWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_editStart(app, mainWnd),
		  m_editEnd(app, mainWnd) { }
	virtual ~CPlayRangeWnd() { }

	virtual BOOL Create();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual void SetNextFocus();
	virtual void SetRange();

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButton m_OkButton;
	CFont m_font;
	CEdit_PlayRange m_editStart;
	CEdit_PlayRange m_editEnd;
	CStatic m_label; // �u�`�v�\���p���x��

public: // �萔
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif