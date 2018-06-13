//----------------------------------------------------------------------------
// RMenu_VideoScreenWnd.cpp : �r�f�I��ʗp�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../MainWnd/MainWnd.h"
#include "VideoScreenWnd_MainWnd.h"
#include "RMenu_VideoScreenWnd.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_VideoScreenWnd::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_CHECKED, ID_FULLSCREEN, _T("�S��ʕ\��(&F)"));
#else // JP
	Append(MFS_CHECKED, ID_FULLSCREEN, _T("FullScreen(&F)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_VideoScreenWnd::OnCommand(int id, HWND/* hwndCtl*/,
								  UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_FULLSCREEN:
		OnFullScreenMenuSelected();
		break;
	}
}
//----------------------------------------------------------------------------
// �S��ʕ\�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_VideoScreenWnd::OnFullScreenMenuSelected()
{
	m_rParent.GetMainWnd().SetFullScreen();
}
//----------------------------------------------------------------------------
