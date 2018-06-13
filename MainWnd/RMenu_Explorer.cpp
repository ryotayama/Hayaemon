//----------------------------------------------------------------------------
// RMenu_Explorer.cpp : �G�N�X�v���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "Explorer.h"
#include "RMenu_Explorer.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_Explorer::Create(BOOL bOnItem)
{
	CMenu::CreatePopup();

	if(bOnItem) {
#if JP
		Append(MFS_ENABLED, ID_OPEN, _T("�J��(&O)"));
		Append(MFS_ENABLED, ID_ADD, _T("�ǉ�(&A)"));
#else // JP
		Append(MFS_ENABLED, ID_OPEN, _T("Open(&O)"));
		Append(MFS_ENABLED, ID_ADD, _T("Add(&A)"));
#endif // JP

		AppendSeparator();
#if JP
		Append(MFS_ENABLED, ID_OPENFOLDER, _T("�t�H���_���J��(&O)"));
		Append(MFS_ENABLED, ID_PROPERTIES, _T("�v���p�e�B(&R)"));
#else // JP
		Append(MFS_ENABLED, ID_OPENFOLDER, _T("Open Folder(&O)"));
		Append(MFS_ENABLED, ID_PROPERTIES, _T("Properties(&R)"));
#endif // JP
		AppendSeparator();
	}
#if JP
	Append(MF_CHECKED, ID_VISIBLE, _T("�G�N�X�v���[���̕\��(&V)"));
#else // JP
	Append(MF_CHECKED, ID_VISIBLE, _T("Show Exploler(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnCommand(int id, HWND/* hwndCtl*/, UINT/* codeNotify*/)
{
	if(id == ID_OPEN) OnOpenFilesMenuSelected();
	else if(id == ID_ADD) OnAddFilesMenuSelected();
	else if(id == ID_OPENFOLDER) OnOpenFolderMenuSelected();
	else if(id == ID_PROPERTIES) OnPropertiesMenuSelected();
	else if(id == ID_VISIBLE) OnVisibleMenuSelected();
}
//----------------------------------------------------------------------------
// �J�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnOpenFilesMenuSelected()
{
	m_rParent.OpenFiles(TRUE);
}
//----------------------------------------------------------------------------
// �ǉ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnAddFilesMenuSelected()
{
	m_rParent.OpenFiles(FALSE);
}
//----------------------------------------------------------------------------
// �t�H���_���J�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnOpenFolderMenuSelected()
{
	m_rParent.OpenFolder();
}
//----------------------------------------------------------------------------
// �v���p�e�B���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnPropertiesMenuSelected()
{
	m_rParent.ShowProperties();
}
//----------------------------------------------------------------------------
// �G�N�X�v���[���̕\�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Explorer::OnVisibleMenuSelected()
{
	m_rParent.GetMainWnd().GetMenu().OnExplorerMenuSelected();
}
//----------------------------------------------------------------------------
