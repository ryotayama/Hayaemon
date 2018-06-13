//----------------------------------------------------------------------------
// KeySettingWnd_MainWnd.cpp : �L�[�J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "KeySettingWnd_MainWnd.h"
#include "../Common/AcceleratorTable.h"
//----------------------------------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------------------------------
CKeySettingWnd_MainWnd::CKeySettingWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_keyInputWnd(app, mainWnd, *this),
	  m_AddButton(*this), m_ChangeButton(*this), m_DeleteButton(*this),
	  m_DefaultButton(*this), m_OkButton(*this), m_CancelButton(*this),
	  m_List(*this), m_nFocus(0), m_CmdList()
{
}
//----------------------------------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------------------------------
CKeySettingWnd_MainWnd::~CKeySettingWnd_MainWnd()
{
}
//----------------------------------------------------------------------------
// ���X�g�ɒǉ�����
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::AddList(UINT bVKHotKey, UINT bfMods, tstring strCommand)
{
	BYTE fVirt = FVIRTKEY;
	if(bfMods & HOTKEYF_CONTROL)
		fVirt |= FCONTROL;
	if(bfMods & HOTKEYF_ALT)
		fVirt |= FALT;
	if(bfMods & HOTKEYF_SHIFT)
		fVirt |= FSHIFT;
	tstring strAddShortCut = m_rApp.GetAccelTable().GetShortCut(fVirt,
																bVKHotKey);
	if(strAddShortCut == _T("")) return;

	for(int i = 0; i < m_List.GetItemCount(); i++) {
		TCHAR szShortCut[255];
		m_List.GetItemText(i, 0, szShortCut, 255);
		tstring strShortCut = szShortCut;
		if(strAddShortCut == szShortCut) {
			tstring strMessage = strAddShortCut +
#if JP
				_T("�͊��ɓo�^����Ă��܂��B\n\n�����̓��e��u�������܂����H");
#else // JP
				_T("already exists.\n\nOverride?");
#endif // JP
			int nRet = MessageBox(m_hWnd, strMessage.c_str(),
#if JP
								  _T("�m�F"),
#else // JP
								  _T("Question"),
#endif // JP
								  MB_YESNO | MB_ICONQUESTION);
			if(nRet == IDYES) m_List.SetItem(i, 1, strCommand.c_str());
			return;
		}
	}

	int n = m_List.GetItemCount();
	m_List.InsertItem(n);
	m_List.SetItem(n, 0, strAddShortCut.c_str());
	m_List.SetItem(n, 1, strCommand.c_str());
}
//----------------------------------------------------------------------------
// ���X�g��ύX����
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::ChangeList(UINT bVKHotKey, UINT bfMods, tstring strCommand)
{
	int nItem = -1;
	int nCount = 0;
	while((nItem = m_List.GetNextItem(nItem, LVNI_SELECTED)) >= 0)
		nCount++;
	if(nCount == 1) {
		int n = m_List.GetNextItem(-1, LVNI_SELECTED);
		BYTE fVirt = FVIRTKEY;
		if(bfMods & HOTKEYF_CONTROL) fVirt |= FCONTROL;
		if(bfMods & HOTKEYF_ALT) fVirt |= FALT;
		if(bfMods & HOTKEYF_SHIFT) fVirt |= FSHIFT;
		tstring strAddShortCut = m_rApp.GetAccelTable().GetShortCut(fVirt,
																	bVKHotKey);
		if(strAddShortCut == _T("")) return;

		for(int i = 0; i < m_List.GetItemCount(); i++) {
			TCHAR szShortCut[255];
			m_List.GetItemText(i, 0, szShortCut, 255);
			tstring strShortCut = szShortCut;
			if(strAddShortCut == szShortCut) {
				if(i == n) continue;
				tstring strMessage = strAddShortCut +
#if JP
				_T("�͊��ɓo�^����Ă��܂��B\n\n�����̓��e��u�������܂����H");
#else // JP
				_T("already exists.\n\nOverride?");
#endif // JP
				int nRet = MessageBox(m_hWnd, strMessage.c_str(),
#if JP
									  _T("�m�F"),
#else // JP
									  _T("Question"),
#endif // JP
									  MB_YESNO | MB_ICONQUESTION);
				if(nRet == IDNO) return;
				m_List.DeleteItem(i);
			}
		}
		m_List.SetItem(n, 0, strAddShortCut.c_str());
		m_List.SetItem(n, 1, strCommand.c_str());
	}
}
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CKeySettingWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("KeySettingWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("KeySettingWndCls"),
#if JP
							_T("�V���[�g�J�b�g�L�[�ݒ�"),
#else // JP
							_T("Shortcut key setting"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	m_nFocus = 0;

	return TRUE;
}
//----------------------------------------------------------------------------
// ����
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::Close()
{
	Show(SW_HIDE);
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// ����ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnClose()
{
	Close();
}
//----------------------------------------------------------------------------
// ���̃R���g���[���Ƀt�H�[�J�X
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::SetNextFocus()
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
			SetFocus((HWND)m_DefaultButton);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 5;
			break;
		case 5:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 6;
			break;
		case 6:
			SetFocus((HWND)m_List);
			m_nFocus = 0;
			break;
	}
}
//----------------------------------------------------------------------------
// �O�̃R���g���[���Ƀt�H�[�J�X
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::SetPreviousFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 6;
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
		case 5:
			SetFocus((HWND)m_DefaultButton);
			m_nFocus = 4;
			break;
		case 6:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 5;
			break;
	}
}
//----------------------------------------------------------------------------
// ���X�g�r���[�̕\��
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::ShowList()
{
	m_List.DeleteAllItems();
	CAcceleratorTable & accelTable = m_rApp.GetAccelTable();
	int nAccel = accelTable.GetNum();
	ACCEL * pAccel = new ACCEL[nAccel];
	accelTable.Copy(pAccel, nAccel);
	for(int i = 0; i < nAccel; i++) {
		m_List.InsertItem(i);
		m_List.SetItem(i, 0, m_rApp.GetAccelTable().GetShortCut(
			pAccel[i].fVirt, pAccel[i].key).c_str());
		m_List.SetItem(i, 1, m_CmdList.GetCommandName(pAccel[i].cmd).c_str());
	}
	delete [] pAccel;
}
//----------------------------------------------------------------------------
// �R�}���h������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
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
	case ID_DEFAULT:
		OnDefaultButtonClicked();
		break;
	case ID_OK:
		OnOkButtonClicked();
		break;
	case ID_CANCEL:
		OnCancelButtonClicked();
		break;
	}
}
//----------------------------------------------------------------------------
// �ǉ��{�^���������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnAddButtonClicked()
{
	if(!m_keyInputWnd.Create(TRUE)) {
#if JP
		m_rApp.ShowError(_T("�V���[�g�J�b�g�L�[���̓_�C�A���O�̍쐬�Ɏ��s")
						 _T("���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create shortcut key setting dialog"));
#endif // JP
	}
	m_keyInputWnd.Show(SW_SHOW);
	m_keyInputWnd.Update();
}
//----------------------------------------------------------------------------
// �ύX�{�^���������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnChangeButtonClicked()
{
	int nItem = -1;
	int nCount = 0;
	while((nItem = m_List.GetNextItem(nItem, LVNI_SELECTED)) >= 0)
		nCount++;
	if(nCount != 1) return;
	if(!m_keyInputWnd.Create(FALSE)) {
#if JP
		m_rApp.ShowError(_T("�V���[�g�J�b�g�L�[���̓_�C�A���O�̍쐬�Ɏ��s")
							_T("���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create shortcut key setting dialog"));
#endif // JP
	}

	TCHAR szShortCut[255];
	m_List.GetItemText(m_List.GetNextItem(-1, LVNI_SELECTED), 0, szShortCut,
					   255);
	tstring strShortCut = szShortCut;
	UINT bfMods = 0;
	if(strShortCut.find(_T("Ctrl")) != tstring::npos)
		bfMods |= HOTKEYF_CONTROL;
	if(strShortCut.find(_T("Alt")) != tstring::npos) bfMods |= HOTKEYF_ALT;
	if(strShortCut.find(_T("Shift")) != tstring::npos) bfMods |= HOTKEYF_SHIFT;
	UINT key = 0;
	if(strShortCut.rfind(_T("+"), strShortCut.length() - 2) != tstring::npos)
		key = m_rApp.GetAccelTable().GetKeyFromString(
				strShortCut.substr(strShortCut.rfind(_T("+"),
				strShortCut.length() - 2) + 2));
	else
		key = m_rApp.GetAccelTable().GetKeyFromString(strShortCut.c_str());

	if (IS_EXTKEY(key)) bfMods |= HOTKEYF_EXT;

	SendMessage((HWND)m_keyInputWnd.GetHotKeyCtrl(), HKM_SETHOTKEY,
				MAKEWORD(key, bfMods), 0);

	TCHAR szCommand[255];
	m_List.GetItemText(m_List.GetNextItem(-1, LVNI_SELECTED), 1, szCommand,
										  255);
	m_keyInputWnd.GetComboBox().Select(szCommand);

	m_keyInputWnd.Show(SW_SHOW);
	m_keyInputWnd.Update();
}
//----------------------------------------------------------------------------
// �폜�{�^���������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnDeleteButtonClicked()
{
	int nItem = -1;
	while((nItem = m_List.GetNextItem(-1, LVNI_SELECTED)) >= 0)
		m_List.DeleteItem(nItem);
}
//----------------------------------------------------------------------------
// �f�t�H���g�{�^���������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnDefaultButtonClicked()
{
	ST_ACCEL tmp;

	m_List.DeleteAllItems();

	for(int i = 0; (tmp = m_rApp.GetAccelTable().GetDefault(i)).key != NULL;
		i++) {
		m_List.InsertItem(i);
		m_List.SetItem(i, 0, m_rApp.GetAccelTable().GetShortCut(tmp.virt,
					   tmp.key).c_str());
		m_List.SetItem(i, 1, m_CmdList.GetCommandName(tmp.cmd).c_str());
	}
}
//----------------------------------------------------------------------------
// OK �{�^���������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnOkButtonClicked()
{
	m_rApp.GetAccelTable().Destroy();
	for(int i = 0; i < m_List.GetItemCount(); i++) {
		TCHAR szShortCut[255];
		m_List.GetItemText(i, 0, szShortCut, 255);
		tstring strShortCut = szShortCut;
		BYTE fVirt = FVIRTKEY;
		if(strShortCut.find(_T("Ctrl")) != tstring::npos) fVirt |= FCONTROL;
		if(strShortCut.find(_T("Alt")) != tstring::npos) fVirt |= FALT;
		if(strShortCut.find(_T("Shift")) != tstring::npos) fVirt |= FSHIFT;
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
		m_rApp.GetAccelTable().Add(fVirt, key, cmd);
	}
	Close();
}
//----------------------------------------------------------------------------
// �L�����Z���{�^���������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnCancelButtonClicked()
{
	Close();
}
//----------------------------------------------------------------------------
// �t�H�[�J�X���̃{�^���@�\�����s
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::ExecCurrentButtonFunc()
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
			OnDefaultButtonClicked();
			break;
		case 5:
			OnOkButtonClicked();
			break;
		case 6:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// �G���^�[�L�[�������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnReturnKeyPressed()
{
	ExecCurrentButtonFunc();
}
//----------------------------------------------------------------------------
// �X�y�[�X�L�[�������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnSpaceKeyPressed()
{
	ExecCurrentButtonFunc();
}
//----------------------------------------------------------------------------
// �G�X�P�[�v�L�[�������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnEscKeyPressed()
{
	Close();
}
//----------------------------------------------------------------------------
// �쐬���ꂽ
//----------------------------------------------------------------------------
LRESULT CKeySettingWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize(350, 200, FALSE);

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
	m_List.InsertColumn(0,
#if JP
						_T("�V���[�g�J�b�g�L�["),
#else // JP
						_T("Shortcut key"),
#endif // JP
						LVCFMT_LEFT, 125, 0);
	m_List.InsertColumn(1,
#if JP
						_T("�A�N�V����"),
#else // JP
						_T("Action"),
#endif // JP
						LVCFMT_LEFT, 150, 0);
	ShowList();
	m_List.Show(SW_SHOW);

	// �f�t�H���g�̕����{�^���̍쐬
	if(!m_DefaultButton.Create(
#if JP
							   _T("�f�t�H���g�̕���"),
#else // JP
							   _T("Default"),
#endif // JP
							   m_hWnd, ID_DEFAULT)) {
#if JP
		m_rApp.ShowError(_T("�f�t�H���g�̕����{�^���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create recover default button."));
#endif // JP
		return FALSE;
	}
	m_DefaultButton.SetSizeToTextSize();
	POINT pt;
	pt.y = m_List.GetBottom();
	ScreenToClient(m_hWnd, &pt);
	m_DefaultButton.SetPos(GetClientWidth() - 10 - m_DefaultButton.GetWidth(),
						   pt.y + 10);

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
	m_DeleteButton.SetPos(m_DefaultButton.GetLeft() - 5 - 
						  m_DeleteButton.GetWidth(), m_DefaultButton.GetTop());

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
						  m_ChangeButton.GetWidth(), m_DefaultButton.GetTop());

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
					   m_DefaultButton.GetTop());

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
	m_CancelButton.SetSize(90, 20);
	m_CancelButton.SetPos(GetClientWidth() - 10 - m_CancelButton.GetWidth(),
						  m_AddButton.GetBottom() + 20);

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
	m_OkButton.SetPos(m_CancelButton.GetLeft() - 5 - m_OkButton.GetWidth(),
					  m_CancelButton.GetTop());

	SetClientSize(GetClientWidth(), m_OkButton.GetTop() +
				  m_OkButton.GetHeight() + 10, FALSE);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// �L�[�{�[�h�������ꂽ
//----------------------------------------------------------------------------
void CKeySettingWnd_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	switch(vk)
	{
	case VK_TAB:
		if(GetKeyState(VK_SHIFT) < 0) SetPreviousFocus();
		else SetNextFocus();
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