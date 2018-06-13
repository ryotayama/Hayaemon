//----------------------------------------------------------------------------
// Divider5_MainWnd.cpp : ��؂�����̂T�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "Divider5_MainWnd.h"
//----------------------------------------------------------------------------
// �����𓾂�
//----------------------------------------------------------------------------
int CDivider5_MainWnd::GetHeight() const
{
	return CStatic::GetHeight() + m_rMainWnd.GetControlOffset();
}
//----------------------------------------------------------------------------
// �c�ʒu�𓾂�
//----------------------------------------------------------------------------
int CDivider5_MainWnd::GetTop() const
{
	return CStatic::GetTop();
}
//----------------------------------------------------------------------------
// �ʒu���Đݒ�
//----------------------------------------------------------------------------
void CDivider5_MainWnd::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetEQ20KLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nEQ20KLabelBottom = pt.y + m_rMainWnd.GetEQ20KLabel().GetHeight();
	pt.y = m_rMainWnd.GetEQ20KSlider().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nEQ20KSliderBottom = pt.y + m_rMainWnd.GetEQ20KSlider().GetHeight();
	int nBigger = nEQ20KLabelBottom > nEQ20KSliderBottom ? nEQ20KLabelBottom
		: nEQ20KSliderBottom;
	SetPos(m_rMainWnd.GetExplorer().GetWidth(), nBigger +
		m_rMainWnd.GetControlOffset());
}
//----------------------------------------------------------------------------
