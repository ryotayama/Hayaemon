//----------------------------------------------------------------------------
// DecSpeedWnd_MainWnd.cpp : ���񂾂�x������E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "DecSpeedWnd_MainWnd.h"
//----------------------------------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------------------------------
CDecSpeedWnd_MainWnd::CDecSpeedWnd_MainWnd(CApp & app, CMainWnd & mainWnd)
	: CIncSpeedWnd_MainWnd(app, mainWnd)
{
#if JP
	strLabel2 = _T("������");
#else // JP
	strLabel = _T("Turn down speed");
#endif // JP
}
//----------------------------------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------------------------------
CDecSpeedWnd_MainWnd::~CDecSpeedWnd_MainWnd()
{
}
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CDecSpeedWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("DecSpeedWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("DecSpeedWndCls"),
#if JP
							_T("���񂾂�x������"),
#else // JP
							_T("Decrease speed"),
#endif // JP
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	nFocus = 0;

	return TRUE;
}
//----------------------------------------------------------------------------
// OK �{�^���������ꂽ
//----------------------------------------------------------------------------
void CDecSpeedWnd_MainWnd::OnOkButtonClicked()
{
	if(SendMessage(m_secondRadioButton, BM_GETCHECK, 0, 0)) {
		double nSecond = _ttof(m_edit.GetText().c_str());
		double nDecSpeed = _ttof(m_edit2.GetText().c_str());
		m_rMainWnd.SetDecSpeed(nSecond, nDecSpeed);
	}
	else {
		double nDecSpeed = _ttof(m_edit3.GetText().c_str());
		m_rMainWnd.SetDecSpeed(nDecSpeed);
	}
	Close();
}
//----------------------------------------------------------------------------
// �L�����Z���{�^���������ꂽ
//----------------------------------------------------------------------------
void CDecSpeedWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetDecSpeed(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
// �G�X�P�[�v�L�[�������ꂽ
//----------------------------------------------------------------------------
void CDecSpeedWnd_MainWnd::OnEscKeyPressed()
{
	m_rMainWnd.SetDecSpeed(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
