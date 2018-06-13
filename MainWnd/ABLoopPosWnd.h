//----------------------------------------------------------------------------
// ABLoopPosWnd.h : AB���[�v�ʒu�ݒ�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef ABLoopPosWndH
#define ABLoopPosWndH

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
// AB���[�v�ʒu�ݒ�p�G�f�B�b�g�{�b�N�X�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CEdit_ABLoopPos : public CEdit
{
public: // �֐�

	CEdit_ABLoopPos(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_ABLoopPos() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// AB���[�v�ʒu�ݒ�p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CABLoopPosWnd : public CFrameWnd
{
public: // �֐�

	CABLoopPosWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(app, mainWnd),
		  m_bLoopA(FALSE) { }
	virtual ~CABLoopPosWnd() { }

	virtual BOOL Create(BOOL bLoopA);

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual void SetPos();

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButton m_OkButton;
	CFont m_font;
	CEdit_ABLoopPos m_edit;

	BOOL m_bLoopA; // AB���[�v(A)���ǂ����iFALSE�̏ꍇ�AB�j

public: // �萔
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif