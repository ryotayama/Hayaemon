//----------------------------------------------------------------------------
// EQ50Label_MainWnd.h : �C�R���C�U ( 50Hz ) �\���p���x���̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef EQ50Label_MainWndH
#define EQ50Label_MainWndH

class CApp;
class CMainWnd;
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/UpDownCtrl.h"
#include "RMenu_EQCtrl.h"
#include "Edit_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �C�R���C�U ( 50Hz ) �\���p���x���̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CEQ50Label_MainWnd : public CStatic
{
public: // �֐�

	CEQ50Label_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd),
		  m_edit(app, mainWnd, _T('-')) { }
	virtual ~CEQ50Label_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void SetEQ50(int nEQ50);
	virtual void ResetPos();

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnVScroll(HWND hwndCtl, UINT code, int pos);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CFont m_font;
	CEdit_MainWnd m_edit;
	CUpDownCtrl m_ud;
	CRMenu_EQCtrl m_rClickMenu; // �E�N���b�N���j���[

public: // �����o�ϐ��̎擾�E�ݒ�

	const CEdit_MainWnd & GetEdit() const { return m_edit; }
};
//----------------------------------------------------------------------------

#endif