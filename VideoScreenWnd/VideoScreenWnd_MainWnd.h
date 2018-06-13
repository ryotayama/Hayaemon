//----------------------------------------------------------------------------
// VideoScreenWnd_MainWnd.h : �r�f�I�S��ʍĐ��p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef VideoScreenWnd_MainWndH
#define VideoScreenWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : �x�[�X �����o���������X�g�Ŏg�p����܂����B
class CApp;
class CMainWnd;
#include "RMenu_VideoScreenWnd.h"
#include "../Common/Static.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �^�C�}�[�Đ��p�E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CVideoScreenWnd_MainWnd : public CStatic
{
public: // �֐�

	CVideoScreenWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(*this) { }
	virtual ~CVideoScreenWnd_MainWnd() { }

	virtual BOOL Create();

	virtual void OnClose();
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnLButtonDoubleClick(int x, int y, UINT keyFlags);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CRMenu_VideoScreenWnd m_rClickMenu; // �E�N���b�N���j���[

public: // �����o�ϐ��̎擾�E�ݒ�

	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif