//--------------------------------------------------------------------------
// RadioButton.cpp : ���W�I�{�^���̍쐬�E�Ǘ����s��
//--------------------------------------------------------------------------
#include <windows.h>
#include "RadioButton.h"
//--------------------------------------------------------------------------
// �쐬
//--------------------------------------------------------------------------
BOOL CRadioButton::Create(LPCTSTR lpWindowName, int x, int y, int cx, int cy,
	HWND hwnd)
{
	Destroy();
	UINT style = WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON;
	m_hWnd = CreateWindow(_T("BUTTON"), lpWindowName, style, x, y, cx, cy, hwnd, NULL, GetModuleHandle(NULL), NULL);
	if(!m_hWnd) return FALSE;

	SetProc();

	return TRUE;
}
//--------------------------------------------------------------------------
// �쐬
//--------------------------------------------------------------------------
BOOL CRadioButton::Create(LPCTSTR lpWindowName, HWND hwnd)
{
	Destroy();
	UINT style = WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON;
	m_hWnd = CreateWindow(_T("BUTTON"), lpWindowName, style, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							hwnd, NULL, GetModuleHandle(NULL), NULL);
	if(!m_hWnd) return FALSE;

	SetProc();

	return TRUE;
}
//--------------------------------------------------------------------------
