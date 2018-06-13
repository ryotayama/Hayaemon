//----------------------------------------------------------------------------
// RMenu_EQCtrl.cpp : EQ�R���g���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "RMenu_EQCtrl.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_EQCtrl::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("�O���t�B�b�N�C�R���C�U�̕\��(&V)"));
#else // JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("Show EQ Control(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_EQCtrl::OnCommand(int id, HWND/* hwndCtl*/,
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
// EQ�̕\�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_EQCtrl::OnVisibleMenuSelected()
{
	m_rParent.GetMenu().OnEQMenuSelected();
}
//----------------------------------------------------------------------------
