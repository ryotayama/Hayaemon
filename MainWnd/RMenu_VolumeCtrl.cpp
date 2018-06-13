//----------------------------------------------------------------------------
// RMenu_VolumeCtrl.cpp : ���ʃR���g���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "RMenu_VolumeCtrl.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_VolumeCtrl::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_ENABLED, ID_RESETVOLUME, _T("�f�t�H���g�ɖ߂�(&R)"));
	AppendSeparator();
	m_setVolumeMenu.CreatePopup();
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_0, _T("0%(&A)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_10, _T("10%(&B)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_20, _T("20%(&C)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_30, _T("30%(&D)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_40, _T("40%(&E)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_50, _T("50%(&F)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_60, _T("60%(&G)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_70, _T("70%(&H)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_80, _T("80%(&I)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_90, _T("90%(&J)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_100, _T("100%(&K)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_setVolumeMenu, _T("���ʎw��(&V)"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_VOLUME, _T("���ʃR���g���[���̕\��(&V)"));
#else // JP
	Append(MFS_ENABLED, ID_RESETVOLUME, _T("Reset(&R)"));
	AppendSeparator();
	m_setVolumeMenu.CreatePopup();
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_0, _T("0%(&A)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_10, _T("10%(&B)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_20, _T("20%(&C)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_30, _T("30%(&D)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_40, _T("40%(&E)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_50, _T("50%(&F)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_60, _T("60%(&G)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_70, _T("70%(&H)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_80, _T("80%(&I)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_90, _T("90%(&J)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_100, _T("100%(&K)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_setVolumeMenu, _T("Set Volume(&V)"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_VOLUME, _T("Show Volume Control(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_VolumeCtrl::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	m_rParent.GetMenu().OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
