//----------------------------------------------------------------------------
// ExplorerBar.h : �G�N�X�v���[���p�c�[���o�[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef ExplorerBarH
#define ExplorerBarH

class CApp;
class CMainWnd;
#include "../Common/Font.h"
#include "../Common/EditExt.h"
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �G�N�X�v���[���p�c�[���o�[�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CExplorerBar : public CStatic
{
public: // �֐�

	CExplorerBar(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(*this) { }
	virtual ~CExplorerBar() { }

	virtual BOOL Create();
	virtual void ResetPos();
	virtual void SetSize(int cx, int cy);

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnLButtonDown(int x, int y, UINT keyFlags);
	virtual void OnReturnKeyPressed();

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
	CEditExt m_edit;
	CFont m_font;

public: // �����o�ϐ��̎擾�E�ݒ�

	CEditExt & GetEdit() { return m_edit; }
};
//----------------------------------------------------------------------------

#endif