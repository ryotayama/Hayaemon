//--------------------------------------------------------------------------
// Button.cpp : �{�^���̍쐬�E�Ǘ����s��
//--------------------------------------------------------------------------
#include <windows.h>
#include "Button.h"
//--------------------------------------------------------------------------
// �쐬
//--------------------------------------------------------------------------
BOOL CButton::Create(LPCTSTR lpWindowName, int x, int y, int cx, int cy, HWND hwnd, UINT id, BOOL bDef)
{
	Destroy();
	UINT style = WS_CHILD | WS_VISIBLE;
	if(bDef) style |= BS_DEFPUSHBUTTON;
	m_hWnd = CreateWindow(_T("BUTTON"), lpWindowName, style, x, y, cx, cy, hwnd, (HMENU)id, GetModuleHandle(NULL), NULL);
	if(!m_hWnd) return FALSE;

	// ��ʂ̃v���p�e�B�Őݒ肳��Ă��郁�b�Z�[�W�{�b�N�X�Ɠ����V�X�e���t�H���g�ɐݒ�
	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	SetProc();

	return TRUE;
}
//--------------------------------------------------------------------------
// �쐬
//--------------------------------------------------------------------------
BOOL CButton::Create(LPCTSTR lpWindowName, HWND hwnd, UINT id, BOOL bDef)
{
	Destroy();
	UINT style = WS_CHILD | WS_VISIBLE;
	if(bDef) style |= BS_DEFPUSHBUTTON;
	m_hWnd = CreateWindow(_T("BUTTON"), lpWindowName, style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)id, GetModuleHandle(NULL), NULL);
	if(!m_hWnd) return FALSE;

	// ��ʂ̃v���p�e�B�Őݒ肳��Ă��郁�b�Z�[�W�{�b�N�X�Ɠ����V�X�e���t�H���g�ɐݒ�
	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
	m_font.CreateIndirect(&ncm.lfMessageFont);
	SetFont(m_font, TRUE);

	SetProc();

	return TRUE;
}
//--------------------------------------------------------------------------
// ���ʒu�𓾂�
//--------------------------------------------------------------------------
int CButton::GetLeft() const
{
	if(!m_hWnd) return -1;

	POINT pt;
	pt.x = CWnd::GetLeft();
	pt.y = CWnd::GetTop();
	ScreenToClient(GetParent(m_hWnd), &pt);
	return pt.x;
}
//--------------------------------------------------------------------------
// ��ʒu�𓾂�
//--------------------------------------------------------------------------
int CButton::GetTop() const
{
	if(!m_hWnd) return -1;

	POINT pt;
	pt.x = CWnd::GetLeft();
	pt.y = CWnd::GetTop();
	ScreenToClient(GetParent(m_hWnd), &pt);
	return pt.y;
}
//--------------------------------------------------------------------------
// �E�ʒu�𓾂�
//--------------------------------------------------------------------------
int CButton::GetRight() const
{
	if(!m_hWnd) return -1;

	POINT pt;
	pt.x = CWnd::GetRight();
	pt.y = CWnd::GetBottom();
	ScreenToClient(GetParent(m_hWnd), &pt);
	return pt.x;
}
//--------------------------------------------------------------------------
// ���ʒu�𓾂�
//--------------------------------------------------------------------------
int CButton::GetBottom() const
{
	if(!m_hWnd) return -1;

	POINT pt;
	pt.x = CWnd::GetRight();
	pt.y = CWnd::GetBottom();
	ScreenToClient(GetParent(m_hWnd), &pt);
	return pt.y;
}
//--------------------------------------------------------------------------
// �e�L�X�g�̍����𓾂�
//--------------------------------------------------------------------------
int CButton::GetTextHeight() const
{
	if(!m_hWnd) return -1;

	CClientDC dc(m_hWnd);
	HFONT hFont = GetFont();
	HFONT hOrgFont = 0;
	if(hFont)
		hOrgFont = dc.SelectFont(hFont);
	TEXTMETRIC tm;
	GetTextMetrics(dc, &tm);
	int height = tm.tmHeight + tm.tmExternalLeading + 9;
	if(hOrgFont)
		dc.SelectFont(hOrgFont);
	return height;
}
//--------------------------------------------------------------------------
// �e�L�X�g�̕��𓾂�
//--------------------------------------------------------------------------
int CButton::GetTextWidth() const
{
	if(!m_hWnd) return -1;

	CClientDC dc(m_hWnd);
	HFONT hFont = GetFont();
	HFONT hOrgFont = 0;
	if(hFont)
		hOrgFont = dc.SelectFont(hFont);
	int width = dc.GetTextWidth(GetCaption()) + 16;
	if(hOrgFont)
		dc.SelectFont(hOrgFont);
	return width;
}
//--------------------------------------------------------------------------
// �g�p�E�s�̐ݒ�
//--------------------------------------------------------------------------
void CButton::SetEnable(BOOL bEnable)
{
	UINT style = GetWindowLong(m_hWnd, GWL_STYLE);
	if(bEnable)
		style &= ~WS_DISABLED;
	else
		style |= WS_DISABLED;
	SetWindowLong(m_hWnd, GWL_STYLE, style);
}
//--------------------------------------------------------------------------
// �T�C�Y���e�L�X�g�ɍ��킹��
//--------------------------------------------------------------------------
void CButton::SetSizeToTextSize()
{
	SetClientSize(GetTextWidth(), GetTextHeight(), FALSE);
}
//--------------------------------------------------------------------------
