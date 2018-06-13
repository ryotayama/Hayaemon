//----------------------------------------------------------------------------
// OutKeySettingWnd_MainWnd.cpp : �O���[�o���z�b�g�L�[�J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "OutKeySettingWnd_MainWnd.h"
#include "../Common/AcceleratorTable.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL COutKeySettingWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("OutKeySettingWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("OutKeySettingWndCls"),
#if JP
							_T("�O���[�o���z�b�g�L�[�ݒ�"),
#else // JP
							_T("Global hot key setting"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
// ���̃R���g���[���Ƀt�H�[�J�X
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::SetNextFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_AddButton);
			m_nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_ChangeButton);
			m_nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_DeleteButton);
			m_nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_List);
			m_nFocus = 0;
			break;
	}
}
//----------------------------------------------------------------------------
// �O�̃R���g���[���Ƀt�H�[�J�X
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::SetPreviousFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 4;
			break;
		case 1:
			SetFocus((HWND)m_List);
			m_nFocus = 0;
			break;
		case 2:
			SetFocus((HWND)m_AddButton);
			m_nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_ChangeButton);
			m_nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_DeleteButton);
			m_nFocus = 3;
			break;
	}
}
//----------------------------------------------------------------------------
// �t�H�[�J�X���̃{�^���@�\�����s
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::ExecCurrentButtonFunc()
{
	switch(m_nFocus)
	{
		case 0:
			OnOkButtonClicked();
			break;
		case 1:
			OnAddButtonClicked();
			break;
		case 2:
			OnChangeButtonClicked();
			break;
		case 3:
			OnDeleteButtonClicked();
			break;
		case 4:
			OnOkButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// �R�}���h������ꂽ
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_ADD:
		OnAddButtonClicked();
		break;
	case ID_CHANGE:
		OnChangeButtonClicked();
		break;
	case ID_DELETE:
		OnDeleteButtonClicked();
		break;
	case ID_OK:
		OnOkButtonClicked();
		break;
	}
}
//----------------------------------------------------------------------------
// �ǉ��{�^���������ꂽ
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnAddButtonClicked()
{
	if(!m_outKeyInputWnd.Create(TRUE)) {
#if JP
		m_rApp.ShowError(_T("�O���[�o���z�b�g�L�[���̓_�C�A���O�̍쐬��")
						 _T("���s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create global hot key input dialog"));
#endif // JP
	}
	m_outKeyInputWnd.Show(SW_SHOW);
	m_outKeyInputWnd.Update();
}
//----------------------------------------------------------------------------
// �ύX�{�^���������ꂽ
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnChangeButtonClicked()
{
	int nItem = -1;
	int nCount = 0;
	while((nItem = m_List.GetNextItem(nItem, LVNI_SELECTED)) >= 0)
		nCount++;
	if(nCount == 1) {
		if(!m_outKeyInputWnd.Create(FALSE)) {
#if JP
			m_rApp.ShowError(_T("�O���[�o���z�b�g�L�[���̓_�C�A���O�̍쐬��")
							 _T("���s���܂����B"));
#else // JP
			m_rApp.ShowError(_T("failed to create global hot key input ")
							 _T("dialog."));
#endif // JP
		}

		TCHAR szShortCut[255];
		m_List.GetItemText(m_List.GetNextItem(-1, LVNI_SELECTED), 0,
						   szShortCut, 255);
		tstring strShortCut = szShortCut;
		UINT bfMods = 0;
		if(strShortCut.find(_T("Ctrl")) != tstring::npos)
			bfMods |= HOTKEYF_CONTROL;
		if(strShortCut.find(_T("Alt")) != tstring::npos)
			bfMods |= HOTKEYF_ALT;
		if(strShortCut.find(_T("Shift")) != tstring::npos)
			bfMods |= HOTKEYF_SHIFT;
		UINT key = 0;
		if(strShortCut.rfind(_T("+"), strShortCut.length() - 2)
			!= tstring::npos)
			key = m_rApp.GetAccelTable().GetKeyFromString(
				strShortCut.substr(strShortCut.rfind(_T("+"),
				strShortCut.length() - 2) + 2));
		else
			key = m_rApp.GetAccelTable().GetKeyFromString(strShortCut.c_str());

		if (IS_EXTKEY(key))
			bfMods |= HOTKEYF_EXT;

		SendMessage((HWND)m_outKeyInputWnd.GetHotKeyCtrl(), HKM_SETHOTKEY,
					MAKEWORD(key, bfMods), 0);

		TCHAR szCommand[255];
		m_List.GetItemText(m_List.GetNextItem(-1, LVNI_SELECTED), 1, szCommand,
						   255);
		m_outKeyInputWnd.GetComboBox().Select(szCommand);

		m_outKeyInputWnd.Show(SW_SHOW);
		m_outKeyInputWnd.Update();
	}
}
//----------------------------------------------------------------------------
// �폜�{�^���������ꂽ
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnDeleteButtonClicked()
{
	int nItem = -1;
	while((nItem = m_List.GetNextItem(-1, LVNI_SELECTED)) >= 0)
		m_List.DeleteItem(nItem);
}
//----------------------------------------------------------------------------
// OK �{�^���������ꂽ
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnOkButtonClicked()
{
	for (int i = 0; m_CmdList[i].div != DIV_TERMINAL; i++) {
		if (m_CmdList[i].use & CMD_HOTKEY)
			UnregisterHotKey(m_rMainWnd, m_CmdList[i].id);
	}
	for(int i = 0; i < m_List.GetItemCount(); i++) {
		TCHAR szShortCut[255];
		m_List.GetItemText(i, 0, szShortCut, 255);
		tstring strShortCut = szShortCut;
		BYTE fVirt = 0;
		if(strShortCut.find(_T("Ctrl")) != tstring::npos)
			fVirt |= MOD_CONTROL;
		if(strShortCut.find(_T("Alt")) != tstring::npos)
			fVirt |= MOD_ALT;
		if(strShortCut.find(_T("Shift")) != tstring::npos)
			fVirt |= MOD_SHIFT;
		UINT key = 0;
		if(strShortCut.rfind(_T("+"), strShortCut.length() - 2)
		   != tstring::npos)
			key = m_rApp.GetAccelTable().GetKeyFromString(
				strShortCut.substr(strShortCut.rfind(_T("+"),
				strShortCut.length() - 2) + 2));
		else
			key = m_rApp.GetAccelTable().GetKeyFromString(strShortCut.c_str());

		TCHAR szCommand[255];
		m_List.GetItemText(i, 1, szCommand, 255);
		WORD cmd = m_CmdList.GetCommandId(szCommand);
		RegisterHotKey(m_rMainWnd, cmd, fVirt, key);
	}
	Close();
}
//----------------------------------------------------------------------------
// ����
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::Close()
{
	Show(SW_HIDE);
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// �쐬���ꂽ
//----------------------------------------------------------------------------
LRESULT COutKeySettingWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(320, 200, FALSE);

	// �s�v�ȃV�X�e�����j���[���폜
	HMENU hMenu = GetSystemMenu(m_hWnd, FALSE);
	RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, 1, MF_BYPOSITION); // �Z�p���[�^

	EnableWindow(m_rMainWnd, FALSE);

	if(!m_List.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("���X�g�r���[�̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create list view."));
#endif // JP
		return FALSE;
	}
	m_List.SetPos(10, 10);
	m_List.SetSize(GetClientWidth() - 20, 140);
#if JP
	m_List.InsertColumn(0, _T("�V���[�g�J�b�g�L�["), LVCFMT_LEFT, 125, 0);
	m_List.InsertColumn(1, _T("�A�N�V����"), LVCFMT_LEFT, 150, 0);
#else // JP
	m_List.InsertColumn(0, _T("Shortcut key"), LVCFMT_LEFT, 125, 0);
	m_List.InsertColumn(1, _T("Action"), LVCFMT_LEFT, 150, 0);
#endif // JP
	m_List.Show(SW_SHOW);

	// �폜�{�^���̍쐬
	if(!m_DeleteButton.Create(
#if JP
							  _T("�폜"),
#else // JP
							  _T("Delete"),
#endif // JP
							  m_hWnd, ID_DELETE)) {
#if JP
		m_rApp.ShowError(_T("�폜�{�^���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create delete button."));
#endif // JP
		return FALSE;
	}
	m_DeleteButton.SetSizeToTextSize();
	POINT pt;
	pt.y = m_List.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_DeleteButton.SetPos(GetClientWidth() - 10 - m_DeleteButton.GetWidth(),
						  pt.y + 10);

	// �ύX�{�^���̍쐬
	if(!m_ChangeButton.Create(
#if JP
							  _T("�ύX"),
#else // JP
							  _T("Change"),
#endif // JP
							  m_hWnd, ID_CHANGE)) {
#if JP
		m_rApp.ShowError(_T("�ύX�{�^���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create change button."));
#endif // JP
		return FALSE;
	}
	m_ChangeButton.SetSizeToTextSize();
	m_ChangeButton.SetPos(m_DeleteButton.GetLeft() - 5 -
						  m_ChangeButton.GetWidth(), m_DeleteButton.GetTop());

	// �ǉ��{�^���̍쐬
	if(!m_AddButton.Create(
#if JP
						   _T("�ǉ�"),
#else // JP
						   _T("Add"),
#endif // JP
						   m_hWnd, ID_ADD)) {
#if JP
		m_rApp.ShowError(_T("�ǉ��{�^���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create add button."));
#endif // JP
		return FALSE;
	}
	m_AddButton.SetSizeToTextSize();
	m_AddButton.SetPos(m_ChangeButton.GetLeft() - 5 - m_AddButton.GetWidth(),
					   m_DeleteButton.GetTop());

	// OK�{�^���̍쐬
	if(!m_OkButton.Create(_T("OK"), m_hWnd, ID_OK, TRUE)) {
#if JP
		m_rApp.ShowError(_T("OK �{�^���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
		return FALSE;
	}
	m_OkButton.SetSize(90, 20);
	m_OkButton.SetPos(GetClientWidth() - 10 - m_OkButton.GetWidth(),
					  m_AddButton.GetBottom() + 20);

	SetClientSize(GetClientWidth(), m_OkButton.GetTop() +
				  m_OkButton.GetHeight() + 10, FALSE);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// �L�[�{�[�h�������ꂽ
//----------------------------------------------------------------------------
void COutKeySettingWnd_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	switch(vk)
	{
	case VK_TAB:
		if(GetKeyState(VK_SHIFT) < 0)
			SetPreviousFocus();
		else
			SetNextFocus();
		break;
	case VK_RETURN:
		OnReturnKeyPressed();
		break;
	case VK_SPACE:
		OnSpaceKeyPressed();
		break;
	case VK_ESCAPE:
		OnEscKeyPressed();
		break;
	}
	CFrameWnd::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
