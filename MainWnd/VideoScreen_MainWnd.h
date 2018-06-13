//----------------------------------------------------------------------------
// VideoScreen_MainWnd.h : �r�f�I��ʂ̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef VideoScreen_MainWndH
#define VideoScreen_MainWndH

#pragma warning(disable: 4355)
	// 'this' : �x�[�X �����o���������X�g�Ŏg�p����܂����B
class CApp;
class CMainWnd;
#include "RMenu_VideoScreen.h"
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/Edit.h"
#include "../Common/UpDownCtrl.h"
#include "Edit_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �r�f�I��ʂ̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CVideoScreen_MainWnd : public CStatic
{
public: // �֐�

	CVideoScreen_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd) { }
	virtual ~CVideoScreen_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void ResetSize();
	virtual void ResetWidth();

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnLButtonDoubleClick(int x, int y, UINT keyFlags);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CRMenu_VideoScreen m_rClickMenu; // �E�N���b�N���j���[
	CFont m_font;

public: // �����o�ϐ��̎擾�E�ݒ�

	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif