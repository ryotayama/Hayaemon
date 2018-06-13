//----------------------------------------------------------------------------
// ToolBar.cpp : �c�[���o�[�̍쐬�E�Ǘ��E�j�����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include <commctrl.h>
#include "ToolBar.h"
//----------------------------------------------------------------------------
// �`�F�b�N��Ԃ̐ݒ�
//----------------------------------------------------------------------------
void CToolBar::CheckButton(int nID, BOOL fCheck)
{
	SendMessage(m_hWnd, TB_CHECKBUTTON, (WPARAM)nID, (LPARAM)fCheck);
}
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CToolBar::Create(HWND hParentWnd)
{
	INITCOMMONCONTROLSEX icc;
	ZeroMemory(&icc, sizeof(INITCOMMONCONTROLSEX));
	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icc.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&icc);

	m_hWnd = CreateToolbarEx(hParentWnd, WS_CHILD | CCS_NORESIZE |
		CCS_NODIVIDER | CCS_TOP | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT, 0,
		0, GetModuleHandle(NULL), NULL, NULL, 0,
		0, 0, 16, 15, 0);
	if(!m_hWnd) return FALSE;
	SetProc();
	return TRUE;
}
//----------------------------------------------------------------------------
// �L����Ԃ̐ݒ�
//----------------------------------------------------------------------------
void CToolBar::EnableButton(int nID, BOOL fEnable)
{
	SendMessage(m_hWnd, TB_ENABLEBUTTON, (WPARAM)nID, (LPARAM)fEnable);
}
//----------------------------------------------------------------------------
// �\����Ԃ̐ݒ�
//----------------------------------------------------------------------------
void CToolBar::HideButton(int nID, BOOL fHide)
{
	SendMessage(m_hWnd, TB_HIDEBUTTON, (WPARAM)nID, (LPARAM)fHide);
}
//----------------------------------------------------------------------------
// �r�b�g�}�b�v�̓ǂݍ���
//----------------------------------------------------------------------------
void CToolBar::LoadBitmap(LPCTSTR lpszResourceName)
{
	m_bitmap.Load(lpszResourceName, LR_LOADMAP3DCOLORS);

	SendMessage(m_hWnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

	BITMAP bitmap;
	GetObject((HBITMAP)m_bitmap, sizeof(BITMAP), &bitmap);
	TBADDBITMAP tbab;
	ZeroMemory(&tbab, sizeof(TBADDBITMAP));
	tbab.nID = (UINT_PTR)(HBITMAP)m_bitmap;
	SendMessage(m_hWnd, TB_ADDBITMAP, bitmap.bmWidth / bitmap.bmHeight,
				(LPARAM)&tbab);
}
//----------------------------------------------------------------------------
// �{�^���̐ݒ�
//----------------------------------------------------------------------------
void CToolBar::SetButtons(const UINT* lpIDArray, int nIDCount)
{
	if(nIDCount < 1) return; // �P�����̏ꍇ�͂��̂܂ܕԂ�
	SendMessage(m_hWnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

	// �{�^���̒ǉ�
	TBBUTTON btn;
	ZeroMemory(&btn, sizeof(TBBUTTON));
	btn.fsState = TBSTATE_ENABLED;
	btn.fsStyle = TBSTYLE_BUTTON;
	if(lpIDArray) // ���ʂ̃{�^������؂��
	{
		// �{�^���������ǉ����Ă���
		for(int i = 0, iBitmap = 0; i < nIDCount; i++, lpIDArray++)
		{
			btn.idCommand = *lpIDArray;
			if(btn.idCommand == 0) // ��؂��
				btn.fsStyle = TBSTYLE_SEP;
			else // ���ʂ̃{�^��
			{
				btn.fsStyle = TBSTYLE_BUTTON;
				btn.iBitmap = iBitmap;
				iBitmap++;
			}
			SendMessage(m_hWnd, TB_ADDBUTTONS, 1, (LPARAM)&btn);
			m_arrayButton.push_back(btn);
		}
	}
	else // �󔒂̃{�^��
	{
		// �{�^���������ǉ����Ă���
		for(int i = 0; i < nIDCount; i++)
			SendMessage(m_hWnd, TB_ADDBUTTONS, 0, (LPARAM)&btn);
	}

	SendMessage(m_hWnd, TB_AUTOSIZE, 0, 0);
}
//----------------------------------------------------------------------------
// �{�^���̏�Ԃ�ݒ�
//----------------------------------------------------------------------------
void CToolBar::SetState(int nID, UINT nState)
{
	SendMessage(m_hWnd, TB_SETSTATE, (WPARAM)nID, (LPARAM)nState);
}
//----------------------------------------------------------------------------
