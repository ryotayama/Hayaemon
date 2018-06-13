//----------------------------------------------------------------------------
// DelayCustomizeWnd.cpp : �f�B���C�̃J�X�^�}�C�Y�p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "DelayCustomizeWnd.h"
//----------------------------------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------------------------------
CDelayCustomizeWnd::CDelayCustomizeWnd(CApp & app, CMainWnd & mainWnd)
	: m_rApp(app), m_rMainWnd(mainWnd), m_wetDryMixEdit(*this),
	  m_feedbackEdit(*this), m_leftDelayEdit(*this),
	  m_rightDelayEdit(*this), m_panDelayEdit(*this), m_OkButton(*this),
	  m_CancelButton(*this), m_nFocus(0)
{
}
//----------------------------------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------------------------------
CDelayCustomizeWnd::~CDelayCustomizeWnd()
{
}
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CDelayCustomizeWnd::Create()
{
	Destroy();

	RegisterClass(_T("DelayCustomizeWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("DelayCustomizeWndCls"),
#if JP
							_T("�f�B���C�̃J�X�^�}�C�Y"),
#else // JP
							_T("Customize Delay"),
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
void CDelayCustomizeWnd::SetNextFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_wetDryMixEdit);
			m_nFocus = 1;
			break;
		case 1:
			SetFocus((HWND)m_feedbackEdit);
			m_nFocus = 2;
			break;
		case 2:
			SetFocus((HWND)m_leftDelayEdit);
			m_nFocus = 3;
			break;
		case 3:
			SetFocus((HWND)m_rightDelayEdit);
			m_nFocus = 4;
			break;
		case 4:
			SetFocus((HWND)m_panDelayEdit);
			m_nFocus = 5;
			break;
		case 5:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 6;
			break;
		case 6:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 7;
			break;
		case 7:
			SetFocus((HWND)m_wetDryMixEdit);
			m_nFocus = 1;
			break;
	}
}
//----------------------------------------------------------------------------
// �O�̃R���g���[���Ƀt�H�[�J�X
//----------------------------------------------------------------------------
void CDelayCustomizeWnd::SetPreviousFocus()
{
	switch(m_nFocus)
	{
		case 0:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 7;
			break;
		case 1:
			SetFocus((HWND)m_CancelButton);
			m_nFocus = 7;
			break;
		case 2:
			SetFocus((HWND)m_wetDryMixEdit);
			m_nFocus = 1;
			break;
		case 3:
			SetFocus((HWND)m_feedbackEdit);
			m_nFocus = 2;
			break;
		case 4:
			SetFocus((HWND)m_leftDelayEdit);
			m_nFocus = 3;
			break;
		case 5:
			SetFocus((HWND)m_rightDelayEdit);
			m_nFocus = 4;
			break;
		case 6:
			SetFocus((HWND)m_panDelayEdit);
			m_nFocus = 5;
			break;
		case 7:
			SetFocus((HWND)m_OkButton);
			m_nFocus = 6;
			break;
	}
}
//----------------------------------------------------------------------------
// �R�}���h������ꂽ
//----------------------------------------------------------------------------
void CDelayCustomizeWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if( hwndCtl == m_wetDryMixEdit || hwndCtl == m_feedbackEdit ||
		hwndCtl == m_leftDelayEdit || hwndCtl == m_rightDelayEdit ||
		hwndCtl == m_panDelayEdit)
	{
		CEditExt * rEdit;
		CUpDownCtrl * rUd;
		double dMin;
		double dMax;
		int nNewFocus;
		if(hwndCtl == m_wetDryMixEdit) {
			rEdit = &m_wetDryMixEdit;
			rUd = &m_wetDryMixUd;
			dMin = 0.0;
			dMax = 100.0;
			nNewFocus = 1;
		}
		else if(hwndCtl == m_feedbackEdit) {
			rEdit = &m_feedbackEdit;
			rUd = &m_feedbackUd;
			dMin = 0.0;
			dMax = 100.0;
			nNewFocus = 2;
		}
		else if(hwndCtl == m_leftDelayEdit) {
			rEdit = &m_leftDelayEdit;
			rUd = &m_leftDelayUd;
			dMin = 1.0;
			dMax = 2000.0;
			nNewFocus = 3;
		}
		else if(hwndCtl == m_rightDelayEdit) {
			rEdit = &m_rightDelayEdit;
			rUd = &m_rightDelayUd;
			dMin = 1.0;
			dMax = 2000.0;
			nNewFocus = 4;
		}
		else if(hwndCtl == m_panDelayEdit) {
			rEdit = &m_panDelayEdit;
			rUd = &m_panDelayUd;
			dMin = 0.0;
			dMax = 1.0;
			nNewFocus = 5;
		}

		if(codeNotify == EN_SETFOCUS) {
			PostMessage(hwndCtl, WM_LBUTTONUP, 0, 0);
			PostMessage(hwndCtl, EM_SETSEL, 0, -1);
			m_nFocus = nNewFocus;
			return;
		}
		else if(codeNotify == EN_CHANGE) {
			double n = (double)_tstof(rEdit->GetText().c_str());
			if(dMin <= n && n <= dMax) {
				if( hwndCtl == m_panDelayEdit)
					SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)n);
				else SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)(n * 1000));
			}
		}
		else if(codeNotify == EN_KILLFOCUS) {
			double n = (double)_tstof(rEdit->GetText().c_str());
			TCHAR buf[255];
			if(n < dMin) n = dMin;
			else if(n > dMax) n = dMax;
			if( hwndCtl == m_panDelayEdit)
				_stprintf_s(buf, _T("%d"), (int)n);
			else _stprintf_s(buf, _T("%4.3f"), n);
			rEdit->SetText(buf);
			if( hwndCtl == m_panDelayEdit)
				SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)n);
			else SendMessage(*rUd, UDM_SETPOS32, 0, (LONG)(n * 1000));
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
void CDelayCustomizeWnd::OnOkButtonClicked()
{
	float flWetDryMix = (float)_tstof(m_wetDryMixEdit.GetText().c_str());
	float flFeedback = (float)_tstof(m_feedbackEdit.GetText().c_str());
	float flLeftDelay = (float)_tstof(m_leftDelayEdit.GetText().c_str());
	float flRightDelay = (float)_tstof(m_rightDelayEdit.GetText().c_str());
	int lPanDelay = _tstoi(m_panDelayEdit.GetText().c_str());

	m_rMainWnd.GetMenu().SetDelay(flWetDryMix, flFeedback, flLeftDelay,
		flRightDelay, (BOOL)lPanDelay, ID_DELAY_CUSTOMIZE);
	Close();
}
//----------------------------------------------------------------------------
// �L�����Z���{�^���������ꂽ
//----------------------------------------------------------------------------
void CDelayCustomizeWnd::OnCancelButtonClicked()
{
	Close();
}
//----------------------------------------------------------------------------
// �G���^�[�L�[�������ꂽ
//----------------------------------------------------------------------------
void CDelayCustomizeWnd::OnReturnKeyPressed()
{
	switch(m_nFocus)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			OnOkButtonClicked();
			break;
		case 7:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// �X�y�[�X�L�[�������ꂽ
//----------------------------------------------------------------------------
void CDelayCustomizeWnd::OnSpaceKeyPressed()
{
	switch(m_nFocus)
	{
		case 0:
			OnOkButtonClicked();
			break;
		case 6:
			OnOkButtonClicked();
			break;
		case 7:
			OnCancelButtonClicked();
			break;
	}
}
//----------------------------------------------------------------------------
// �G�X�P�[�v�L�[�������ꂽ
//----------------------------------------------------------------------------
void CDelayCustomizeWnd::OnEscKeyPressed()
{
	Close();
}
//----------------------------------------------------------------------------
// �쐬���ꂽ
//----------------------------------------------------------------------------
LRESULT CDelayCustomizeWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int nButtonWidth = 90;
	int nButtonHeight = 20;
	BASS_DX8_ECHO bde;
	BOOL bDelay = m_rMainWnd.GetSound().GetDelay(&bde);
	float fWetDryMix = bDelay ? bde.fWetDryMix : 8.0f;
	float fFeedback = bDelay ? bde.fFeedback : 50.0f;
	float fLeftDelay = bDelay ? bde.fLeftDelay : 600.0f;
	float fRightDelay = bDelay ? bde.fRightDelay : 300.0f;
	int lPanDelay = bDelay ? bde.lPanDelay : 1;

	TCHAR chWetDryMix[255], chFeedback[255], chLeftDelay[255],
		  chRightDelay[255], chPanDelay[255];
	_stprintf_s(chWetDryMix, _T("%4.3f"), fWetDryMix);
	_stprintf_s(chFeedback, _T("%4.3f"), fFeedback);
	_stprintf_s(chLeftDelay, _T("%4.3f"), fLeftDelay);
	_stprintf_s(chRightDelay, _T("%4.3f"), fRightDelay);
	_stprintf_s(chPanDelay, _T("%d"), lPanDelay);

	// �s�v�ȃV�X�e�����j���[���폜
	HMENU hMenu = GetSystemMenu(m_hWnd, FALSE);
	RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, 1, MF_BYPOSITION); // �Z�p���[�^

	EnableWindow(m_rMainWnd, FALSE);

	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	if(!m_wetDryMixLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("���x���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_wetDryMixLabel.SetParent(m_hWnd);
	m_wetDryMixLabel.SetFont(m_font, TRUE);
	m_wetDryMixLabel.SetText(_T("WET DRY MIX: "));
	m_wetDryMixLabel.SetSizeToTextSize();
	m_wetDryMixLabel.Show(SW_SHOW);

	if(!m_wetDryMixEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("�G�f�B�b�g�R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_wetDryMixEdit, EM_SETLIMITTEXT, 7, 0);
	m_wetDryMixEdit.SetStyle(m_wetDryMixEdit.GetStyle() | ES_RIGHT);
	m_wetDryMixEdit.SetFont(m_font, TRUE);
	m_wetDryMixEdit.SetText(_T("2000.000"));
	m_wetDryMixEdit.SetSizeToTextSize();
	m_wetDryMixEdit.SetText(chWetDryMix);
	m_wetDryMixEdit.Show(SW_SHOW);

	if(!m_wetDryMixUd.Create(m_hWnd, m_wetDryMixEdit)) {
#if JP
		m_rApp.ShowError(_T("�A�b�v�_�E���R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_wetDryMixUd, UDM_SETRANGE32, 0, 100000);
	SendMessage(m_wetDryMixUd, UDM_SETPOS32, 0, (LONG)(fWetDryMix * 1000));
	m_wetDryMixUd.Show(SW_SHOW);
	m_wetDryMixEdit.SetSize(m_wetDryMixEdit.GetWidth()
		+ m_wetDryMixUd.GetWidth(), m_wetDryMixEdit.GetHeight());

	if(!m_feedbackLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("���x���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_feedbackLabel.SetParent(m_hWnd);
	m_feedbackLabel.SetFont(m_font, TRUE);
	m_feedbackLabel.SetText(_T("FEEDBACK:"));
	m_feedbackLabel.SetSizeToTextSize();
	m_feedbackLabel.Show(SW_SHOW);

	if(!m_feedbackEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("�G�f�B�b�g�R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_feedbackEdit, EM_SETLIMITTEXT, 7, 0);
	m_feedbackEdit.SetStyle(m_feedbackEdit.GetStyle() | ES_RIGHT);
	m_feedbackEdit.SetFont(m_font, TRUE);
	m_feedbackEdit.SetText(_T("2000.000"));
	m_feedbackEdit.SetSizeToTextSize();
	m_feedbackEdit.SetText(chFeedback);
	m_feedbackEdit.Show(SW_SHOW);

	if(!m_feedbackUd.Create(m_hWnd, m_feedbackEdit)) {
#if JP
		m_rApp.ShowError(_T("�A�b�v�_�E���R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_feedbackUd, UDM_SETRANGE32, 0, 100000);
	SendMessage(m_feedbackUd, UDM_SETPOS32, 0, (LONG)(fFeedback * 1000));
	m_feedbackUd.Show(SW_SHOW);
	m_feedbackEdit.SetSize(m_feedbackEdit.GetWidth()
		+ m_feedbackUd.GetWidth(), m_feedbackEdit.GetHeight());

	if(!m_leftDelayLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("���x���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_leftDelayLabel.SetParent(m_hWnd);
	m_leftDelayLabel.SetFont(m_font, TRUE);
	m_leftDelayLabel.SetText(_T("LEFT DELAY:"));
	m_leftDelayLabel.SetSizeToTextSize();
	m_leftDelayLabel.Show(SW_SHOW);

	if(!m_leftDelayEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("�G�f�B�b�g�R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_leftDelayEdit, EM_SETLIMITTEXT, 8, 0);
	m_leftDelayEdit.SetStyle(m_leftDelayEdit.GetStyle() | ES_RIGHT);
	m_leftDelayEdit.SetFont(m_font, TRUE);
	m_leftDelayEdit.SetText(_T("2000.000"));
	m_leftDelayEdit.SetSizeToTextSize();
	m_leftDelayEdit.SetText(chLeftDelay);
	m_leftDelayEdit.Show(SW_SHOW);

	if(!m_leftDelayUd.Create(m_hWnd, m_leftDelayEdit)) {
#if JP
		m_rApp.ShowError(_T("�A�b�v�_�E���R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_leftDelayUd, UDM_SETRANGE32, 1000, 2000000);
	SendMessage(m_leftDelayUd, UDM_SETPOS32, 0, (LONG)(fLeftDelay * 1000));
	m_leftDelayUd.Show(SW_SHOW);
	m_leftDelayEdit.SetSize(m_leftDelayEdit.GetWidth()
		+ m_leftDelayUd.GetWidth(), m_leftDelayEdit.GetHeight());

	if(!m_rightDelayLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("���x���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_rightDelayLabel.SetParent(m_hWnd);
	m_rightDelayLabel.SetFont(m_font, TRUE);
	m_rightDelayLabel.SetText(_T("RIGHT DELAY: "));
	m_rightDelayLabel.SetSizeToTextSize();
	m_rightDelayLabel.Show(SW_SHOW);

	if(!m_rightDelayEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("�G�f�B�b�g�R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_rightDelayEdit, EM_SETLIMITTEXT, 8, 0);
	m_rightDelayEdit.SetStyle(m_rightDelayEdit.GetStyle() | ES_RIGHT);
	m_rightDelayEdit.SetFont(m_font, TRUE);
	m_rightDelayEdit.SetText(_T("2000.000"));
	m_rightDelayEdit.SetSizeToTextSize();
	m_rightDelayEdit.SetText(chRightDelay);
	m_rightDelayEdit.Show(SW_SHOW);

	if(!m_rightDelayUd.Create(m_hWnd, m_rightDelayEdit)) {
#if JP
		m_rApp.ShowError(_T("�A�b�v�_�E���R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_rightDelayUd, UDM_SETRANGE32, 1000, 2000000);
	SendMessage(m_rightDelayUd, UDM_SETPOS32, 0, (LONG)(fRightDelay * 1000));
	m_rightDelayUd.Show(SW_SHOW);
	m_rightDelayEdit.SetSize(m_rightDelayEdit.GetWidth()
		+ m_rightDelayUd.GetWidth(), m_rightDelayEdit.GetHeight());

	if(!m_panDelayLabel.Create()) {
#if JP
		m_rApp.ShowError(_T("���x���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create label."));
#endif // JP
		return FALSE;
	}
	m_panDelayLabel.SetParent(m_hWnd);
	m_panDelayLabel.SetFont(m_font, TRUE);
	m_panDelayLabel.SetText(_T("PAN DELAY: "));
	m_panDelayLabel.SetSizeToTextSize();
	m_panDelayLabel.Show(SW_SHOW);

	if(!m_panDelayEdit.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("�G�f�B�b�g�R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create edit control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_panDelayEdit, EM_SETLIMITTEXT, 1, 0);
	m_panDelayEdit.SetStyle(m_panDelayEdit.GetStyle() | ES_RIGHT);
	m_panDelayEdit.SetFont(m_font, TRUE);
	m_panDelayEdit.SetText(_T("2000.000"));
	m_panDelayEdit.SetSizeToTextSize();
	m_panDelayEdit.SetText(chPanDelay);
	m_panDelayEdit.Show(SW_SHOW);

	if(!m_panDelayUd.Create(m_hWnd, m_panDelayEdit)) {
#if JP
		m_rApp.ShowError(_T("�A�b�v�_�E���R���g���[���̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create up down control."));
#endif // JP
		return FALSE;
	}
	SendMessage(m_panDelayUd, UDM_SETRANGE32, 0, 1);
	SendMessage(m_panDelayUd, UDM_SETPOS32, 0, lPanDelay);
	m_panDelayUd.Show(SW_SHOW);
	m_panDelayEdit.SetSize(m_panDelayEdit.GetWidth()
		+ m_panDelayUd.GetWidth(), m_panDelayEdit.GetHeight());

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

	int nLeft = m_rMainWnd.GetControlOffset() * 2;
	int nTop = m_rMainWnd.GetControlOffset() * 4;
	m_wetDryMixLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_wetDryMixEdit.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixEdit.GetWidth();
	m_wetDryMixUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_wetDryMixEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_feedbackLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_feedbackEdit.SetPos(nLeft, nTop);
	nLeft += m_feedbackEdit.GetWidth();
	m_feedbackUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_feedbackEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_leftDelayLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_leftDelayEdit.SetPos(nLeft, nTop);
	nLeft += m_leftDelayEdit.GetWidth();
	m_leftDelayUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_leftDelayEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_rightDelayLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_rightDelayEdit.SetPos(nLeft, nTop);
	nLeft += m_rightDelayEdit.GetWidth();
	m_rightDelayUd.SetPos(nLeft, nTop);

	nLeft = m_rMainWnd.GetControlOffset() * 2;
	nTop += m_rightDelayEdit.GetHeight() + m_rMainWnd.GetControlOffset();
	m_panDelayLabel.SetPos(nLeft, nTop);
	nLeft += m_wetDryMixLabel.GetWidth();
	m_panDelayEdit.SetPos(nLeft, nTop);
	nLeft += m_panDelayEdit.GetWidth();
	m_panDelayUd.SetPos(nLeft, nTop);

	// �uOK�v�u�L�����Z���v�{�^���̈ʒu�ݒ�
	int nCancelButtonLeft = nLeft;
	int nCancelButtonTop = nTop + m_panDelayEdit.GetHeight()
						   + m_rMainWnd.GetControlOffset() * 4;
	m_CancelButton.SetPos(nCancelButtonLeft, nCancelButtonTop);
	int nOkButtonLeft = nCancelButtonLeft - m_rMainWnd.GetControlOffset()
						- m_OkButton.GetWidth();
	int nOkButtonTop = nCancelButtonTop;
	m_OkButton.SetPos(nOkButtonLeft, nOkButtonTop);

	// �E�B���h�E�T�C�Y�̐ݒ�
	int nWidth = nCancelButtonLeft + m_CancelButton.GetWidth()
				 + m_rMainWnd.GetControlOffset() * 2;
	int nHeight = nCancelButtonTop + m_CancelButton.GetHeight()
				  + m_rMainWnd.GetControlOffset() * 2;
	SetClientSize(nWidth, nHeight, FALSE);

	m_nFocus = 0;
	SetNextFocus();

	Show(SW_SHOW);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
// �j��
//----------------------------------------------------------------------------
void CDelayCustomizeWnd::OnDestroy()
{
	EnableWindow(m_rMainWnd, TRUE);
	SetForegroundWindow(m_rMainWnd);
}
//----------------------------------------------------------------------------
// �L�[�{�[�h�������ꂽ
//----------------------------------------------------------------------------
void CDelayCustomizeWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
// �ʒm������
//----------------------------------------------------------------------------
LRESULT CDelayCustomizeWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	if(pnmhdr->code == UDN_DELTAPOS) {
		if( pnmhdr->hwndFrom == m_wetDryMixUd ||
			pnmhdr->hwndFrom == m_feedbackUd ||
			pnmhdr->hwndFrom == m_leftDelayUd ||
			pnmhdr->hwndFrom == m_rightDelayUd ||
			pnmhdr->hwndFrom == m_panDelayUd)
		{
			CEditExt * rEdit;
			CUpDownCtrl * rUd;
			double dMin;
			double dMax;
			if(pnmhdr->hwndFrom == m_wetDryMixUd) {
				rEdit = &m_wetDryMixEdit;
				rUd = &m_wetDryMixUd;
				dMin = 0.0;
				dMax = 100.0;
			}
			else if(pnmhdr->hwndFrom == m_feedbackUd) {
				rEdit = &m_feedbackEdit;
				rUd = &m_feedbackUd;
				dMin = 0.0;
				dMax = 100.0;
			}
			else if(pnmhdr->hwndFrom == m_leftDelayUd) {
				rEdit = &m_leftDelayEdit;
				rUd = &m_leftDelayUd;
				dMin = 1.0;
				dMax = 2000.0;
			}
			else if(pnmhdr->hwndFrom == m_rightDelayUd) {
				rEdit = &m_rightDelayEdit;
				rUd = &m_rightDelayUd;
				dMin = 1.0;
				dMax = 2000.0;
			}
			else if(pnmhdr->hwndFrom == m_panDelayUd) {
				rEdit = &m_panDelayEdit;
				rUd = &m_panDelayUd;
				dMin = 0.0;
				dMax = 1.0;
			}

			tstring str = rEdit->GetText();
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)pnmhdr;
			double d = _ttof(str.c_str());
			BOOL bInt = FALSE;
			if(pnmhdr->hwndFrom == m_panDelayUd)
				bInt = TRUE;
			if(bInt) {
				if(lpnmud->iDelta > 0) d += 1.0;
				else d -= 1.0;
			}
			else {
				if(lpnmud->iDelta > 0) d += 0.001;
				else d -= 0.001;
			}
			if(dMin <= d && d <= dMax) {
				TCHAR buf[255];
				if(bInt) _stprintf_s(buf, _T("%d"), (int)d);
				else _stprintf_s(buf, _T("%4.3f"), d);
				rEdit->SetText(buf);
			}
			PostMessage(*rEdit, WM_LBUTTONUP, 0, 0);
			PostMessage(*rEdit, EM_SETSEL, 0, -1);
			return TRUE;
		}
	}

	return CFrameWnd::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
