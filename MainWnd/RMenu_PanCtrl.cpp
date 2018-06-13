//----------------------------------------------------------------------------
// RMenu_PanCtrl.cpp : �p���R���g���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "RMenu_PanCtrl.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_PanCtrl::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("�p���̕\��(&V)"));
#else // JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("Show Pan Control(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_PanCtrl::OnCommand(int id, HWND/* hwndCtl*/,
								  UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_VISIBLE:
		OnVisibleMenuSelected();
		break;
	}
}
//----------------------------------------------------------------------------
// �p���̕\�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_PanCtrl::OnVisibleMenuSelected()
{
	m_rParent.GetMenu().OnPanMenuSelected();
}
//----------------------------------------------------------------------------
