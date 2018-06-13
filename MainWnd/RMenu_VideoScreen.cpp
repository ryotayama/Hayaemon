//----------------------------------------------------------------------------
// RMenu_VideoScreen.cpp : �r�f�I��ʗp�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "VideoScreen_MainWnd.h"
#include "RMenu_VideoScreen.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_VideoScreen::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_ENABLED, ID_FULLSCREEN, _T("�S��ʕ\��(&F)"));
	AppendSeparator();
	Append(m_rParent.GetMenu().IsItemChecked(ID_LYRICS) ?
		MF_CHECKED : MF_ENABLED, ID_LYRICS, _T("�̎�(&L)"));
	Append(m_rParent.GetMenu().IsItemChecked(ID_PITCHANALYSER) ?
		MF_CHECKED : MF_ENABLED, ID_PITCHANALYSER, _T("�s�b�`�A�i���C�U(&P)"));
	AppendSeparator();
	Append(MF_CHECKED, ID_VIDEOSCREEN, _T("�r�f�I��ʂ̕\��(&V)"));
#else // JP
	Append(MFS_ENABLED, ID_FULLSCREEN, _T("FullScreen(&F)"));
	AppendSeparator();
	Append(m_rParent.GetMenu().IsItemChecked(ID_LYRICS) ?
		MF_CHECKED : MF_ENABLED, ID_LYRICS, _T("Lyrics(&L)"));
	Append(m_rParent.GetMenu().IsItemChecked(ID_PITCHANALYSER) ?
		MF_CHECKED : MF_ENABLED, ID_PITCHANALYSER, _T("Pitch Analyser(&P)"));
	AppendSeparator();
	Append(MF_CHECKED, ID_VIDEOSCREEN, _T("Show Video Screen(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_VideoScreen::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case ID_FULLSCREEN:
		OnFullScreenMenuSelected();
		return;
	}
	m_rParent.GetMenu().OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// �S��ʕ\�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_VideoScreen::OnFullScreenMenuSelected()
{
	m_rParent.SetFullScreen();
}
//----------------------------------------------------------------------------
