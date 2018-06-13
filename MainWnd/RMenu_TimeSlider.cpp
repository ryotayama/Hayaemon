//----------------------------------------------------------------------------
// RMenu_MainWnd.cpp : �Đ����Ԑݒ�p�X���C�_�p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "TimeSlider_MainWnd.h"
#include "RMenu_TimeSlider.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_TimeSlider::Create(BOOL bOnMarker)
{
	CMenu::CreatePopup();
	if(bOnMarker) {
#if JP
		Append(MFS_ENABLED, ID_DELETE, _T("�폜(&D)"));
#else // JP
		Append(MFS_ENABLED, ID_DELETE, _T("Delete(&D)"));
#endif // JP
		AppendSeparator();
	}
#if JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("�Đ��ʒu�X���C�_�̕\��(&V)"));
#else // JP
	Append(MFS_CHECKED, ID_VISIBLE, _T("Show Position Slider(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_TimeSlider::OnCommand(int id, HWND/* hwndCtl*/,
								  UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_DELETE:
		OnDeleteMenuSelected();
		break;
	case ID_VISIBLE:
		OnVisibleMenuSelected();
		break;
	}
}
//----------------------------------------------------------------------------
// �폜���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_TimeSlider::OnDeleteMenuSelected()
{
	m_rParent.DeleteMarker();
}
//----------------------------------------------------------------------------
// �Đ��ʒu�X���C�_�̕\�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_TimeSlider::OnVisibleMenuSelected()
{
	m_rParent.GetMainWnd().GetMenu().OnTimeSliderMenuSelected();
}
//----------------------------------------------------------------------------
