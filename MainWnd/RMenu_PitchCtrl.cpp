//----------------------------------------------------------------------------
// RMenu_PitchCtrl.cpp : �����R���g���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "RMenu_PitchCtrl.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_PitchCtrl::Create()
{
	CMenu::CreatePopup();
#if JP
	Append(MFS_ENABLED, ID_RESETPITCH, _T("�f�t�H���g�ɖ߂�(&R)"));
	AppendSeparator();
	m_setPitchMenu.CreatePopup();
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F12, _T("��12(&A)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F11, _T("��11(&B)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F10, _T("��10(&C)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F9, _T("��9(&D)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F8, _T("��8(&E)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F7, _T("��7(&F)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F6, _T("��6(&G)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F5, _T("��5(&H)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F4, _T("��4(&I)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F3, _T("��3(&J)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F2, _T("��2(&K)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F1, _T("��1(&L)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_0, _T("0(&M)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S1, _T("��1(&N)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S2, _T("��2(&O)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S3, _T("��3(&P)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S4, _T("��4(&Q)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S5, _T("��5(&R)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S6, _T("��6(&S)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S7, _T("��7(&T)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S8, _T("��8(&U)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S9, _T("��9(&V)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S10, _T("��10(&W)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S11, _T("��11(&X)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S12, _T("��12(&Y)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_setPitchMenu, _T("�����w��(&F)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_DOWN1PITCH, _T("����������(&1)"));
	Append(MFS_ENABLED, ID_DOWN2PITCH, _T("�S��������(&2)"));
	Append(MFS_ENABLED, ID_DOWN1OCTPITCH, _T("�P�I�N�^�[�u������(&3)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_UP1PITCH, _T("�����グ��(&A)"));
	Append(MFS_ENABLED, ID_UP2PITCH, _T("�S���グ��(&B)"));
	Append(MFS_ENABLED, ID_UP1OCTPITCH, _T("�P�I�N�^�[�u�グ��(&C)"));
	AppendSeparator();
	m_pitchDecimalMenu.CreatePopup();
	m_pitchDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_PITCHDEC_0) ?
		MF_CHECKED : MF_ENABLED, ID_PITCHDEC_0, _T("0��(&0)"));
	m_pitchDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_PITCHDEC_1) ?
		MF_CHECKED : MF_ENABLED, ID_PITCHDEC_1, _T("1��(&1)"));
	m_pitchDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_PITCHDEC_2) ?
		MF_CHECKED : MF_ENABLED, ID_PITCHDEC_2, _T("2��(&2)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchDecimalMenu, _T("�����_����"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_PITCH, _T("�����R���g���[���̕\��(&V)"));
#else // JP
	Append(MFS_ENABLED, ID_RESETPITCH, _T("Reset(&R)"));
	AppendSeparator();
	m_setPitchMenu.CreatePopup();
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F12, _T("��12(&A)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F11, _T("��11(&B)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F10, _T("��10(&C)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F9, _T("��9(&D)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F8, _T("��8(&E)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F7, _T("��7(&F)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F6, _T("��6(&G)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F5, _T("��5(&H)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F4, _T("��4(&I)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F3, _T("��3(&J)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F2, _T("��2(&K)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F1, _T("��1(&L)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_0, _T("0(&M)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S1, _T("��1(&N)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S2, _T("��2(&O)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S3, _T("��3(&P)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S4, _T("��4(&Q)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S5, _T("��5(&R)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S6, _T("��6(&S)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S7, _T("��7(&T)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S8, _T("��8(&U)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S9, _T("��9(&V)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S10, _T("��10(&W)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S11, _T("��11(&X)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S12, _T("��12(&Y)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_setPitchMenu, _T("Set Pitch(&F)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_DOWN1PITCH, _T("Flat(&1)"));
	Append(MFS_ENABLED, ID_DOWN2PITCH, _T("Double flat(&2)"));
	Append(MFS_ENABLED, ID_DOWN1OCTPITCH, _T("Down 1 Octave(&3)"));
	AppendSeparator();
	Append(MFS_ENABLED, ID_UP1PITCH, _T("Sharp(&A)"));
	Append(MFS_ENABLED, ID_UP2PITCH, _T("Double sharp(&B)"));
	Append(MFS_ENABLED, ID_UP1OCTPITCH, _T("Up 1 Octave(&C)"));
	AppendSeparator();
	m_pitchDecimalMenu.CreatePopup();
	m_pitchDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_PITCHDEC_0) ?
		MF_CHECKED : MF_ENABLED, ID_PITCHDEC_0, _T("0 digit(&0)"));
	m_pitchDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_PITCHDEC_1) ?
		MF_CHECKED : MF_ENABLED, ID_PITCHDEC_1, _T("1 digit(&1)"));
	m_pitchDecimalMenu.Append(m_rParent.GetMenu().IsItemChecked(ID_PITCHDEC_2) ?
		MF_CHECKED : MF_ENABLED, ID_PITCHDEC_2, _T("2 digit(&2)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchDecimalMenu, _T("Decimal digit"));
	AppendSeparator();
	Append(MFS_CHECKED, ID_PITCH, _T("Show Pitch Control(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_PitchCtrl::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	m_rParent.GetMenu().OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
