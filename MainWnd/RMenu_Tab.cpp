//----------------------------------------------------------------------------
// RMenu_Tab.cpp : �^�u�p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "Tab_MainWnd.h"
#include "RMenu_Tab.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_Tab::Create()
{
	CreatePopup();
#if JP
	Append(MFS_ENABLED, ID_CLOSE, _T("����(&C)"));
	Append(MFS_ENABLED, ID_RENAME, _T("���O�̕ύX(&R)"));
#else // JP
	Append(MFS_ENABLED, ID_CLOSE, _T("Close(&C)"));
	Append(MFS_ENABLED, ID_RENAME, _T("Rename(&R)"));
#endif // JP
	AppendSeparator();
#if JP
	Append(MFS_ENABLED, ID_NEWTAB, _T("�V�����^�u(&N)"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_VISIBLE, _T("�^�u�̕\��(&V)"));
#else // JP
	Append(MFS_ENABLED, ID_NEWTAB, _T("New tab(&N)"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_VISIBLE, _T("Show Tab(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	else return TRUE;
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Tab::OnCommand(int id, HWND/* hwndCtl*/, UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_CLOSE:
		OnCloseMenuSelected();
		break;
	case ID_RENAME:
		OnRenameMenuSelected();
		break;
	case ID_NEWTAB:
		OnNewTabMenuSelected();
		break;
	case ID_VISIBLE:
		OnVisibleMenuSelected();
		break;
	}
}
//----------------------------------------------------------------------------
// ���郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Tab::OnCloseMenuSelected()
{
	m_rParent.CloseTab();
}
//----------------------------------------------------------------------------
// ���O�̕ύX���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Tab::OnRenameMenuSelected()
{
	m_rParent.ShowEdit();
}
//----------------------------------------------------------------------------
// �V�����^�u���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Tab::OnNewTabMenuSelected()
{
	m_rParent.GetMainWnd().CreateNewList();
}
//----------------------------------------------------------------------------
// �^�u�̕\�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_Tab::OnVisibleMenuSelected()
{
	m_rParent.GetMainWnd().GetMenu().OnTabMenuSelected();
}
//----------------------------------------------------------------------------
