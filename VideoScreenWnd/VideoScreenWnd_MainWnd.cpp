//----------------------------------------------------------------------------
// VideoScreenWnd_MainWnd.cpp : �^�C�}�[�Đ��p�E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "VideoScreenWnd_MainWnd.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CVideoScreenWnd_MainWnd::Create()
{
	Destroy();

	CStatic::Create(SS_NOTIFY | SS_BLACKRECT);
	if(!m_hWnd) return FALSE;
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	SetPos(GetSystemMetrics(SM_XVIRTUALSCREEN),
		   GetSystemMetrics(SM_YVIRTUALSCREEN));
	SetSize(GetSystemMetrics(SM_CXVIRTUALSCREEN),
			GetSystemMetrics(SM_CYVIRTUALSCREEN));
	Show(SW_SHOW);

	return TRUE;
}
//----------------------------------------------------------------------------
// �����悤�Ƃ��Ă���
//----------------------------------------------------------------------------
void CVideoScreenWnd_MainWnd::OnClose()
{
	if(m_rMainWnd.IsFullScreen()) m_rMainWnd.SetFullScreen();
	CStatic::OnClose();
}
//----------------------------------------------------------------------------
// �R�}���h
//----------------------------------------------------------------------------
void CVideoScreenWnd_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CStatic::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// �R���e�L�X�g���j���[
//----------------------------------------------------------------------------
LRESULT CVideoScreenWnd_MainWnd::OnContextMenu(HWND hwnd, int xPos, int yPos)
{
	m_rClickMenu.Create();
	TrackPopupMenu((HMENU)m_rClickMenu, TPM_LEFTALIGN | TPM_TOPALIGN, xPos,
		yPos, 0, m_hWnd, NULL);
	
	return CStatic::OnContextMenu(hwnd, xPos, yPos);
}
//----------------------------------------------------------------------------
// �_�u���N���b�N���ꂽ
//----------------------------------------------------------------------------
void CVideoScreenWnd_MainWnd::OnLButtonDoubleClick(int x, int y, UINT keyFlags)
{
	m_rMainWnd.SetFullScreen();
	CStatic::OnLButtonDoubleClick(x, y, keyFlags);
}
//----------------------------------------------------------------------------
