//----------------------------------------------------------------------------
// OutKeyInputWnd.cpp : �O���[�o���z�b�g�L�[���͗p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../KeySettingWnd/KeySettingWnd_MainWnd.h"
#include "OutKeyInputWnd.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL COutKeyInputWnd::Create(BOOL bAdd)
{
	this->bAdd = bAdd;

	Destroy();

	RegisterClass(_T("OutKeyInputWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("OutKeyInputWndCls"),
#if JP
							_T("�O���[�o���z�b�g�L�[����"),
#else // JP
							_T("Global hot key input"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rParentWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// �R�}���h������ꂽ
//----------------------------------------------------------------------------
void COutKeyInputWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_OK:
	{
		WORD wHotKey = (WORD)SendMessage(m_hot, HKM_GETHOTKEY, 0, 0);
		if(bAdd)
			m_rParentWnd.AddList(LOBYTE(wHotKey), HIBYTE(wHotKey), m_combo.GetSelectText());
		else
			m_rParentWnd.ChangeList(LOBYTE(wHotKey), HIBYTE(wHotKey), m_combo.GetSelectText());
		Close();
		break;
	}
	case ID_CANCEL:
		Close();
		break;
	}
}
//----------------------------------------------------------------------------
// �쐬���ꂽ
//----------------------------------------------------------------------------
LRESULT COutKeyInputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// �s�v�ȃV�X�e�����j���[���폜
	HMENU hMenu = GetSystemMenu(m_hWnd, FALSE);
	RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, 1, MF_BYPOSITION); // �Z�p���[�^

	EnableWindow(m_rParentWnd, FALSE);

	if(!m_hot.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("�z�b�g�L�[�R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create hot key control."));
#endif // JP
		return FALSE;
	}
	m_hot.SetPos(10, 10);
	m_hot.SetCaption(_T("Ctrl + Alt + Shift + Scroll Lock"));
	m_hot.SetSize(m_hot.GetTextWidth() + 30, m_hot.GetTextHeight() + 5);
	m_hot.Show(SW_SHOW);
	SetFocus(m_hot);

	if(!m_combo.Create(0, 0, 100, 90, m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("�R���{�{�b�N�X�̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create combobox."));
#endif // JP
		return FALSE;
	}
	POINT pt;
	pt.y = m_hot.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_combo.SetPos(10, pt.y + 10);
	m_combo.SetSize(m_hot.GetWidth(), m_hot.GetHeight() * 10);
	for (int i = 0; m_rParentWnd.m_CmdList[i].div != DIV_TERMINAL; i++) {
		if (m_rParentWnd.m_CmdList[i].use & CMD_HOTKEY)
			m_combo.Add(m_rParentWnd.m_CmdList[i].pszText);
	}
	m_combo.Select(m_rParentWnd.m_CmdList.GetCommandName(ID_OPENFILE).c_str());

	// �L�����Z���{�^���̍쐬
	if(!m_CancelButton.Create(
#if JP
							  _T("�L�����Z��"),
#else // JP
							  _T("Cancel"),
#endif // JP
							  m_hWnd, ID_CANCEL)) {
#if JP
		m_rApp.ShowError(_T("�L�����Z���{�^���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create cancel button."));
#endif // JP
		return FALSE;
	}
	pt.y = m_combo.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_CancelButton.SetSize(90, 20);
	m_CancelButton.SetPos(m_hot.GetWidth() + 10 - m_CancelButton.GetWidth(), pt.y + 10);

	// OK�{�^���̍쐬
	if(!m_OkButton.Create(_T("OK"), m_hWnd, ID_OK)) {
#if JP
		m_rApp.ShowError(_T("OK �{�^���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
		return FALSE;
	}
	m_OkButton.SetSize(90, 20);
	m_OkButton.SetPos(m_CancelButton.GetLeft() - 5 - m_OkButton.GetWidth(), m_CancelButton.GetTop());

	SetClientSize(m_hot.GetWidth() + 20, m_OkButton.GetTop() + m_OkButton.GetHeight() + 10, FALSE);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// �j��
//----------------------------------------------------------------------------
void COutKeyInputWnd::OnDestroy()
{
	EnableWindow(m_rParentWnd, TRUE);
	SetForegroundWindow(m_rParentWnd);
}
//----------------------------------------------------------------------------
