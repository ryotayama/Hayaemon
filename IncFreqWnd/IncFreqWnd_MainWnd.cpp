//----------------------------------------------------------------------------
// IncFreqWnd_MainWnd.cpp : ���񂾂񑬂�����E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "../MainWnd/MainWnd.h"
#include "IncFreqWnd_MainWnd.h"
//----------------------------------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------------------------------
CIncFreqWnd_MainWnd::CIncFreqWnd_MainWnd(CApp & app,
												   CMainWnd & mainWnd)
	: CIncSpeedWnd_MainWnd(app, mainWnd)
{
#if JP
	strLabel = _T("�Đ����g����");
#else // JP
	strLabel = _T("Turn up frequency");
#endif // JP
}
//----------------------------------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------------------------------
CIncFreqWnd_MainWnd::~CIncFreqWnd_MainWnd()
{
}
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CIncFreqWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("IncFreqWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("IncFreqWndCls"),
#if JP
							_T("���񂾂񑬂�����"),
#else // JP
							_T("Increase frequency"),
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
void CIncFreqWnd_MainWnd::OnOkButtonClicked()
{
	if(SendMessage(m_secondRadioButton, BM_GETCHECK, 0, 0)) {
		double nSecond = _ttof(m_edit.GetText().c_str());
		double nIncFreq = _ttof(m_edit2.GetText().c_str());
		m_rMainWnd.SetIncFreq(nSecond, nIncFreq);
	}
	else {
		double nIncFreq = _ttof(m_edit3.GetText().c_str());
		m_rMainWnd.SetIncFreq(nIncFreq);
	}
	Close();
}
//----------------------------------------------------------------------------
// �L�����Z���{�^���������ꂽ
//----------------------------------------------------------------------------
void CIncFreqWnd_MainWnd::OnCancelButtonClicked()
{
	m_rMainWnd.SetIncFreq(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
// �G�X�P�[�v�L�[�������ꂽ
//----------------------------------------------------------------------------
void CIncFreqWnd_MainWnd::OnEscKeyPressed()
{
	m_rMainWnd.SetIncFreq(FALSE, 0);
	Close();
}
//----------------------------------------------------------------------------
