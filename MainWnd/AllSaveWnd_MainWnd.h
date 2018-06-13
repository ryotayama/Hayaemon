//----------------------------------------------------------------------------
// AllSaveWnd_MainWnd.h : �ꊇ�ϊ��E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef AllSaveWnd_MainWndH
#define AllSaveWnd_MainWndH

class CApp;
class CMainWnd;
#include "../Common/FrameWnd.h"
#include "../Common/ComboBox.h"
#include "../Common/Button.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �ꊇ�ϊ��E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CAllSaveWnd_MainWnd : public CFrameWnd
{
public: // �֐�

	CAllSaveWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), bOk(FALSE) { }
	virtual ~CAllSaveWnd_MainWnd() {
		EnableWindow(m_rMainWnd, TRUE);
	}

	virtual BOOL Create();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CComboBox m_Combo;
	CButton m_OkButton;
	CButton m_CancelButton;

	BOOL bOk;

public: // �萔
	enum {
		ID_FORMAT = 100,
		ID_OK,
		ID_CANCEL,
	};

	BOOL IsOk() { return bOk; }
	int GetFormat()
	{
		// 0 : WAVE
		// 1 : MP3
		// 2 : OGG

		return (int)SendMessage(m_Combo, CB_GETCURSEL, 0, 0);
	}
};
//----------------------------------------------------------------------------

#endif