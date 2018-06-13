//----------------------------------------------------------------------------
// PresetNameInputWnd.h : �v���Z�b�g�����̓E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef PresetNameInputWndH
#define PresetNameInputWndH

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
// �v���Z�b�g�����̓G�f�B�b�g�{�b�N�X�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CEdit_PresetNameInput : public CEdit
{
public: // �֐�

	CEdit_PresetNameInput(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_PresetNameInput() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// �v���Z�b�g�����̓E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CPresetNameInputWnd : public CFrameWnd
{
public: // �֐�

	CPresetNameInputWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_edit(app, mainWnd) { }
	virtual ~CPresetNameInputWnd() { }

	virtual BOOL Create();

	virtual LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnDestroy();
	virtual void SetPreset();

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CButton m_OkButton;
	CStatic m_label;
	CFont m_font;
	CEdit_PresetNameInput m_edit;

public: // �萔
	enum {
		ID_OK = 100,
		ID_CANCEL,
	};
};
//----------------------------------------------------------------------------

#endif