//----------------------------------------------------------------------------
// ProgressWnd_MainWnd.h : �v���O���X�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef ProgressWnd_MainWndH
#define ProgressWnd_MainWndH

class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "../Common/ProgressCtrl.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �v���O���X�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CProgressWnd_MainWnd : public CFrameWnd
{
public: // �֐�

	CProgressWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CProgressWnd_MainWnd() {
		EnableWindow(m_rMainWnd, TRUE);
	}

	virtual BOOL Create();
	virtual void SetProgressPos(int nPos) {
		m_progress.SetProgressPos(nPos);
	}
	virtual void SetProgressRange(int nLower, int nUpper) {
		m_progress.SetProgressRange(nLower, nUpper);
	}

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CProgressCtrl m_progress;
};
//----------------------------------------------------------------------------

#endif