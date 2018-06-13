//----------------------------------------------------------------------------
// PanSlider_MainWnd.cpp : �{�����[���\���p���x���̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../Common/Utils.h"
#include "../App.h"
#include "MainWnd.h"
#include "PanSlider_MainWnd.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CPanSlider_MainWnd::Create()
{
	CSliderCtrl::Create(m_rMainWnd);
	if(!m_hWnd) return FALSE;

	SetStyle(GetStyle() | WS_TABSTOP | TBS_AUTOTICKS | TBS_HORZ | TBS_NOTICKS);

	SetRangeMin(-100);
	SetRangeMax(100);
	SetLineSize(1);
	SetPageSize(5);
	SetThumbPos(0);

	ResetPos();

	return TRUE;
}
//----------------------------------------------------------------------------
// �����𓾂�
//----------------------------------------------------------------------------
int CPanSlider_MainWnd::GetHeight() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_PAN))
		return CSliderCtrl::GetHeight();
	else return m_rMainWnd.GetVolumeSlider().GetHeight();
}
//----------------------------------------------------------------------------
// �c�ʒu�𓾂�
//----------------------------------------------------------------------------
int CPanSlider_MainWnd::GetTop() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_PAN))
		return CSliderCtrl::GetTop();
	else return m_rMainWnd.GetVolumeSlider().GetTop();
}
//----------------------------------------------------------------------------
// �ʒu�̍Đݒ�
//----------------------------------------------------------------------------
void CPanSlider_MainWnd::ResetPos()
{
	POINT pt;
	pt.x = m_rMainWnd.GetPanLabel().GetLeft();
	pt.y = m_rMainWnd.GetPanLabel().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nLeft = pt.x + m_rMainWnd.GetPanLabel().GetWidth() +
				m_rMainWnd.GetControlOffset();
	SetPos(nLeft, pt.y);
}
//----------------------------------------------------------------------------
// �T�C�Y�̍Đݒ�
//----------------------------------------------------------------------------
void CPanSlider_MainWnd::ResetSize()
{
	POINT pt;
	pt.x = GetLeft();
	ScreenToClient(m_rMainWnd, &pt);
	int nWidth = m_rMainWnd.GetClientWidth() - pt.x;
	SetSize(nWidth, (int)(GetSystemMetrics(SM_CYHSCROLL) * 1.5));
}
//----------------------------------------------------------------------------
// �R�}���h
//----------------------------------------------------------------------------
void CPanSlider_MainWnd::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CSliderCtrl::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// �X�N���[�����ꂽ
//----------------------------------------------------------------------------
void CPanSlider_MainWnd::OnHScroll(HWND hwndCtl, UINT code, int pos)
{
	LONG trackpos = GetThumbPos();
	m_rMainWnd.SetPan((int)trackpos);
	m_rMainWnd.GetPanLabel().SetPan(trackpos);
}
//----------------------------------------------------------------------------
// �L�[�{�[�h�������ꂽ
//----------------------------------------------------------------------------
void CPanSlider_MainWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_TAB) {
		if(GetKeyState(VK_CONTROL) < 0) m_rMainWnd.SetFocusNextTab();
		else m_rMainWnd.SetFocusNextControl();
	}
	else if(vk == VK_HOME) {
		SetThumbPos(0);
		m_rMainWnd.SetPan(0);
		m_rMainWnd.GetPanLabel().SetPan(0);
		return;
	}
	else if(vk == VK_UP) vk = VK_DOWN;
	else if(vk == VK_DOWN) vk = VK_UP;
	else if(vk == VK_PRIOR) vk = VK_NEXT;
	else if(vk == VK_NEXT) vk = VK_PRIOR;
	CSliderCtrl::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// �N���b�N���ꂽ
//----------------------------------------------------------------------------
void CPanSlider_MainWnd::OnLButtonDown(int x, int y, UINT keyFlags)
{
	RECT rc;
	SendMessage(m_hWnd, TBM_GETTHUMBRECT, 0, (LPARAM)&rc);
	if(rc.left < x && x < rc.right &&
		rc.top < y && y < rc.bottom) {
		if(GetTickCount() - dwThumbClickTime <= GetDoubleClickTime()) {
			SetThumbPos(0);
			m_rMainWnd.GetPanLabel().SetPan(0);
			m_rMainWnd.SetPan(0);
			return;
		}
		else dwThumbClickTime = GetTickCount();
	}
	CSliderCtrl::OnLButtonDown(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// �}�E�X�z�C�[�����X�N���[�����ꂽ
//----------------------------------------------------------------------------
BOOL CPanSlider_MainWnd::OnMouseWheel(UINT nFlags, int zDelta, POINTS pt)
{
	tstring strPan = m_rMainWnd.GetPanLabel().GetEdit().GetText();
	int n = _ttoi(strPan.c_str());
	if(zDelta >= 0) n++;
	else n--;
	int nMin = GetRangeMin(), nMax = GetRangeMax();
	if(n < nMin) n = nMin;
	if(n > nMax) n = nMax;
	m_rMainWnd.SetPan(n);
	m_rMainWnd.GetPanLabel().SetPan(n);
	return FALSE;
}
//----------------------------------------------------------------------------
// �E�N���b�N�������ꂽ
//----------------------------------------------------------------------------
void CPanSlider_MainWnd::OnRButtonUp(int x, int y, UINT keyFlags)
{
	m_rClickMenu.Create();
	POINT pt;
	GetCursorPos(&pt);
	SetForegroundWindow(m_hWnd);
	TrackPopupMenu((HMENU)m_rClickMenu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x,
		pt.y, 0, m_hWnd, NULL);

	CSliderCtrl::OnRButtonUp(x, y, keyFlags);
}
//----------------------------------------------------------------------------
