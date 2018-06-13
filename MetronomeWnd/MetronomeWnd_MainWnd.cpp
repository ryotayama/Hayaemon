//----------------------------------------------------------------------------
// MetronomeWnd_MainWnd.cpp : ���g���m�[���p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "MetronomeWnd_MainWnd.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CMetronomeWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("MetronomeWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("MetronomeWndCls"),
#if JP
							_T("���g���m�[���@�\"),
#else // JP
							_T("Metronome"),
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
void CMetronomeWnd_MainWnd::SetNextFocus()
{
	switch(nFocus)
	{
		case 0:
			SetFocus((HWND)m_bpmEdit);
			nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_OkButton);
			nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_CancelButton);
			nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_bpmEdit);
			nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// �O�̃R���g���[���Ƀt�H�[�J�X
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::SetPreviousFocus()
{
	switch(nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			nFocus = 3;
			break;
		case 1:
			SetFocus((HWND)m_CancelButton);
			nFocus = 3;
			break;
		case 2:
			SetFocus((HWND)m_bpmEdit);
			nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_OkButton);
			nFocus = 2;
			break;
	}
}
//----------------------------------------------------------------------------
// �R�}���h������ꂽ
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(hwndCtl == m_bpmEdit) {
		CEditExt * rEdit;
		CUpDownCtrl * rUd;
		int nMin;
		int nMax;
		int nNewFocus;
		if(hwndCtl == m_bpmEdit) {
			rEdit = &m_bpmEdit;
			rUd = &m_bpmUd;
			nMin = 10;
			nMax = 600;
			nNewFocus = 1;
		}

		if(codeNotify == EN_SETFOCUS) {
			PostMessage(hwndCtl, WM_LBUTTONUP, 0, 0);
			PostMessage(hwndCtl, EM_SETSEL, 0, -1);
			nFocus = nNewFocus;
			return;
		}
		else if(codeNotify == EN_CHANGE) {
			int n = (int)_ttoi(rEdit->GetText().c_str());
			if(nMin <= n && n <= nMax)
				SendMessage(*rUd, UDM_SETPOS32, 0, n);
		}
		else if(codeNotify == EN_KILLFOCUS) {
			int n = 0;
			TCHAR buf[255];
			if(hwndCtl == m_bpmEdit) {
				n = (int)_ttoi(rEdit->GetText().c_str());
				if(n < nMin) n = nMin;
				else if(n > nMax) n = nMax;
				_stprintf_s(buf, _T("%d"), n);
			}
			rEdit->SetText(buf);
			SendMessage(*rUd, UDM_SETPOS32, 0, n);
		}
	}

	switch(id)
	{
	case ID_OK:
		OnOkButtonClicked();
		break;
	case ID_CANCEL:
		OnCancelButtonClicked();
		break;
	}
	CFrameWnd::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// OK �{�^���������ꂽ
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnOkButtonClicked()
{
	int nBpm = (int)_ttoi(m_bpmEdit.GetText().c_str());
	if(nBpm < 10) nBpm = 10;
	else if(nBpm > 600) nBpm = 600;
	m_rMainWnd.SetMetronome(nBpm);
	Close();
}
//----------------------------------------------------------------------------
// �L�����Z���{�^���������ꂽ
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.StopMetronome();
	Close();
}
//----------------------------------------------------------------------------
// �G���^�[�L�[�������ꂽ
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnReturnKeyPressed()
{
	switch(nFocus)
	{
		case 0:
		case 1:
		case 2:
			OnOkButtonClicked();
			break;
		case 3:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// �X�y�[�X�L�[�������ꂽ
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnSpaceKeyPressed()
{
	switch(nFocus)
	{
		case 0:
			OnOkButtonClicked();
			break;
		case 2:
			OnOkButtonClicked();
			break;
		case 3:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// �G�X�P�[�v�L�[�������ꂽ
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnEscKeyPressed()
{
	m_rMainWnd.StopMetronome();
	Close();
}
//----------------------------------------------------------------------------
// �쐬���ꂽ
//----------------------------------------------------------------------------
LRESULT CMetronomeWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nButtonWidth = 90;
	int nButtonHeight = 20;
	int nBpm = m_rMainWnd.GetBpm();
	TCHAR chBpm[255];
	_stprintf_s(chBpm, _T("%d"), nBpm);

	// �s�v�ȃV�X�e�����j���[���폜
	HMENU hMenu = GetSystemMenu(m_hWnd, FALSE); // �V�X�e�����j���[���擾
	RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND); // ���̃T�C�Y�ɖ߂�
	RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND); // �T�C�Y�ύX
	RemoveMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND); // �ŏ���
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND); // �ő剻
	RemoveMenu(hMenu, 1, MF_BYPOSITION); // �Z�p���[�^

	EnableWindow(m_rMainWnd, FALSE);

	// ��ʂ̃v���p�e�B�Őݒ肳��Ă��郁�b�Z�[�W�{�b�N�X��
	// �����V�X�e���t�H���g�ɐݒ�
	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	// �e���|���x���̍쐬
	if(!m_bpmLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("���x���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_bpmLabel.SetParent(m_hWnd);
	m_bpmLabel.SetFont(m_font, TRUE);
#if JP
	m_bpmLabel.SetText(_T("�e���| : "));
#else // JP
	m_bpmLabel.SetText(_T("Tempo : "));
#endif // JP
	m_bpmLabel.SetSizeToTextSize();
	m_bpmLabel.Show(SW_SHOW);

	// BPM�G�f�B�b�g�{�b�N�X�̍쐬
	if(!m_bpmEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("�G�f�B�b�g�R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_bpmEdit, EM_SETLIMITTEXT, 3, 0);
	m_bpmEdit.SetStyle(m_bpmEdit.GetStyle() | ES_RIGHT | ES_NUMBER);
	m_bpmEdit.SetFont(m_font, TRUE);
	m_bpmEdit.SetText(_T("999"));
	m_bpmEdit.SetSizeToTextSize();
	m_bpmEdit.SetText(chBpm);
	m_bpmEdit.Show(SW_SHOW);

	// BPM�A�b�v�_�E���R���g���[���̍쐬
	if(!m_bpmUd.Create(m_hWnd, m_bpmEdit)) {
#if JP
		m_rApp.ShowError(_T("�A�b�v�_�E���R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_bpmUd, UDM_SETRANGE32, 10, 600);
	SendMessage(m_bpmUd, UDM_SETPOS32, 0, nBpm);
	m_bpmUd.Show(SW_SHOW);
	m_bpmEdit.SetSize(m_bpmEdit.GetWidth() + m_bpmUd.GetWidth(),
					  m_bpmEdit.GetHeight());

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
	m_CancelButton.SetSize(nButtonWidth, nButtonHeight);

	// OK�{�^���̍쐬
	if(!m_OkButton.Create(_T("OK"), m_hWnd, ID_OK, TRUE)) {
#if JP
		m_rApp.ShowError(_T("OK �{�^���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create OK button."));
#endif // JP
		return FALSE;
	}
	m_OkButton.SetSize(nButtonWidth, nButtonHeight);

	// �R���g���[���̈ʒu�ݒ�
	int nBpmLeft = m_rMainWnd.GetControlOffset() * 2;
	int nBpmTop = m_rMainWnd.GetControlOffset() * 4;
	m_bpmLabel.SetPos(nBpmLeft, nBpmTop);
	nBpmLeft += m_bpmLabel.GetWidth();
	m_bpmEdit.SetPos(nBpmLeft, nBpmTop);
	nBpmLeft += m_bpmEdit.GetWidth();
	m_bpmUd.SetPos(nBpmLeft, nBpmTop);

	// �uOK�v�u�L�����Z���v�{�^���̈ʒu�ݒ�
	int nOkButtonLeft = m_rMainWnd.GetControlOffset() * 2;
	int nOkButtonTop = nBpmTop + m_bpmEdit.GetHeight()
						   + m_rMainWnd.GetControlOffset() * 4;
	m_OkButton.SetPos(nOkButtonLeft, nOkButtonTop);
	int nCancelButtonLeft = nOkButtonLeft + m_OkButton.GetWidth()
							+ m_rMainWnd.GetControlOffset();
	int nCancelButtonTop = nOkButtonTop;
	m_CancelButton.SetPos(nCancelButtonLeft, nCancelButtonTop);

	// �E�B���h�E�T�C�Y�̐ݒ�
	int nWidth = nCancelButtonLeft + m_CancelButton.GetWidth()
				 + m_rMainWnd.GetControlOffset() * 2;
	int nHeight = nCancelButtonTop + m_CancelButton.GetHeight()
				  + m_rMainWnd.GetControlOffset() * 2;
	SetClientSize(nWidth, nHeight, FALSE);

	nFocus = 0;
	SetNextFocus();

	Show(SW_SHOW);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// �j��
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnVScroll(HWND hwndCtl, UINT code, int pos)
{
	if(hwndCtl == (HWND)m_bpmUd)
	{
		TCHAR text[18];
		_stprintf_s(text, _T("%d"), pos);
		m_bpmEdit.SetText(text);
		PostMessage(m_bpmEdit, WM_LBUTTONUP, 0, 0);
		PostMessage(m_bpmEdit, EM_SETSEL, 0, -1);
	}

	CFrameWnd::OnVScroll(hwndCtl, code, pos);
}
//----------------------------------------------------------------------------
// �L�[�{�[�h�������ꂽ
//----------------------------------------------------------------------------
void CMetronomeWnd_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
