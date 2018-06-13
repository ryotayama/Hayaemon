//----------------------------------------------------------------------------
// Tab_MainWnd.h : �^�u�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef Tab_MainWndH
#define Tab_MainWndH

class CApp;
class CMainWnd;
#include "RMenu_Tab.h"
#include "../Common/Tab.h"
#include "../Common/EditExt.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �^�u�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CTab_MainWnd : public CTab
{
public: // �֐�

	CTab_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(*this), m_edit(*this)
	{ }
	virtual ~CTab_MainWnd() { }

	virtual void AddNewTab(BOOL bChangeFocus = TRUE);
	virtual void CloseTab();
	virtual BOOL Create();
	virtual int GetItemHeight() {
		RECT rc;
		TabCtrl_GetItemRect(m_hWnd, 1, &rc);
		return rc.bottom - rc.top;
	}
	virtual void ResetPos();
	virtual void ResetSize();
	virtual void ResetWidth();
	virtual void ShowEdit();
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnLButtonDoubleClick(int x, int y, UINT keyFlags);
	virtual void OnLButtonDown(int x, int y, UINT keyFlags);
	virtual void OnLButtonUp(int x, int y, UINT keyFlags);
	virtual void OnMouseMove(int x, int y, UINT keyFlags);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);
	virtual void OnReturnKeyPressed();

	CRMenu_Tab m_rClickMenu; // �E�N���b�N���j���[
	int m_nTab;
	CFont m_font;
	CEditExt m_edit;
	RECT rcLast;

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

public: // �����o�ϐ��̎擾�E�ݒ�

	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif