//----------------------------------------------------------------------------
// ProgressWnd_MainWnd.cpp : ���x�\���p���x���̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "ProgressWnd_MainWnd.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CProgressWnd_MainWnd::Create()
{
	Destroy();

	RegisterClass(_T("ProgressWndCls"));
	m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, _T("ProgressWndCls"), _T(""),
							WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT, m_rMainWnd, 0,
							GetModuleHandle(NULL), this);
	if(!m_hWnd) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
LRESULT CProgressWnd_MainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetClientSize((int)(m_rMainWnd.GetWidth() / 1.2),
				  (int)(GetSystemMetrics(SM_CYHSCROLL) / 1.5), FALSE);
	SetPos(m_rMainWnd.GetLeft() + m_rMainWnd.GetWidth() / 2 - GetWidth() / 2,
		   m_rMainWnd.GetTop() + m_rMainWnd.GetHeight() / 2 - GetHeight() / 2);

	// �s�v�ȃV�X�e�����j���[���폜
	HMENU hMenu = GetSystemMenu(m_hWnd, FALSE);
	RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	RemoveMenu(hMenu, 1, MF_BYPOSITION); // �Z�p���[�^

	EnableWindow(m_rMainWnd, FALSE);

	if(!m_progress.Create(m_hWnd)) {
#if JP
		m_rApp.ShowError(_T("�v���O���X�o�[�̍쐬�Ɏ��s���܂����B"));
#else // JP
		m_rApp.ShowError(_T("failed to create progress bar."));
#endif // JP
		return FALSE;
	}
	m_progress.SetPos(0, 0);
	m_progress.SetSize(GetClientWidth(), GetClientHeight());
	m_progress.Show(SW_SHOW);

	return CFrameWnd::OnCreate(lpCreateStruct);
}
//----------------------------------------------------------------------------
