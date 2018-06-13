//----------------------------------------------------------------------------
// Divider2_MainWnd.cpp : ��؂�����̂Q�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "Divider2_MainWnd.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CDivider2_MainWnd::Create()
{
	CStatic::Create(SS_SUNKEN);
	if(!m_hWnd) return FALSE;
	SetParent(m_rMainWnd);
	ResetPos();
	ResetSize();

	return TRUE;
}
//----------------------------------------------------------------------------
// �����𓾂�
//----------------------------------------------------------------------------
int CDivider2_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_SPEED) || 
		m_rMainWnd.GetMenu().IsItemChecked(ID_FREQ) ||
		m_rMainWnd.GetMenu().IsItemChecked(ID_PITCH))
		return CStatic::GetHeight() + m_rMainWnd.GetControlOffset();
	else return m_rMainWnd.GetTimeSlider().GetHeight();
}
//----------------------------------------------------------------------------
// �c�ʒu�𓾂�
//----------------------------------------------------------------------------
int CDivider2_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_SPEED) || 
		m_rMainWnd.GetMenu().IsItemChecked(ID_FREQ) ||
		m_rMainWnd.GetMenu().IsItemChecked(ID_PITCH))
		return CStatic::GetTop();
	else return m_rMainWnd.GetTimeSlider().GetTop();
}
//----------------------------------------------------------------------------
// �ʒu���Đݒ�
//----------------------------------------------------------------------------
void CDivider2_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetTimeSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(0, pt.y + m_rMainWnd.GetTimeSlider().GetHeight()
			+ m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
