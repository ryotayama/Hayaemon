//----------------------------------------------------------------------------
// Divider3_MainWnd.cpp : ��؂�����̂R�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "Divider3_MainWnd.h"
//----------------------------------------------------------------------------
// �����𓾂�
//----------------------------------------------------------------------------
int CDivider3_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_VOLUME) || 
		m_rMainWnd.GetMenu().IsItemChecked(ID_PAN))
		return CStatic::GetHeight() + m_rMainWnd.GetControlOffset();
	else return m_rMainWnd.GetPitchSlider().GetHeight();
}
//----------------------------------------------------------------------------
// �c�ʒu�𓾂�
//----------------------------------------------------------------------------
int CDivider3_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_VOLUME) || 
		m_rMainWnd.GetMenu().IsItemChecked(ID_PAN))
		return CStatic::GetTop();
	else return m_rMainWnd.GetPitchSlider().GetTop();
}
//----------------------------------------------------------------------------
// �ʒu���Đݒ�
//----------------------------------------------------------------------------
void CDivider3_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetPitchSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(m_rMainWnd.GetExplorer().GetWidth(),
		pt.y + m_rMainWnd.GetPitchSlider().GetHeight()
		+ m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
