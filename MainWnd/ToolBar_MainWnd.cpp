//----------------------------------------------------------------------------
// ToolBar_MainWnd.cpp : ���C���E�B���h�E�p�c�[���o�[�̍쐬�E�Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../resource.h"
#include "../App.h"
#include "MainWnd.h"
#include "ToolBar_MainWnd.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CToolBar_MainWnd::Create()
{
	CToolBar::Create(m_rMainWnd);
	if(!m_hWnd) return FALSE;
	SetStyle(GetStyle()| CCS_NORESIZE | CCS_NODIVIDER | CCS_TOP
			 | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT);
	LoadBitmap(MAKEINTRESOURCE(IDR_TOOLBARS));
	UINT id[23] = {
		ID_HEAD,
		ID_PREVMARKER,
		ID_PLAY,
		ID_PAUSE,
		ID_STOP,
		ID_NEXTMARKER,
		ID_NEXT,
		0,
		ID_OPENFILE,
		0,
		ID_SLOOP,
		ID_ALOOP,
		ID_RANDOM,
		0,
		ID_ABLOOP_A,
		ID_ABLOOP_B,
		0,
		ID_MARKERPLAY,
		ID_ADDMARKER,
		ID_DELETEMARKER,
		0,
		ID_EXPLORER,
		ID_PLAYLIST,
	};
	SetButtons(id, 23);
	HideButton(ID_PREVMARKER, TRUE);
	HideButton(ID_NEXTMARKER, TRUE);
	HideButton(ID_PAUSE, TRUE);

	POINT pt;
	pt.y = m_rMainWnd.GetDivider1().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(m_rMainWnd.GetControlOffset(),
		   pt.y + m_rMainWnd.GetDivider1().GetHeight());

	SetSize(400, 22);
	Show(SW_SHOW);
	return TRUE;
}
//----------------------------------------------------------------------------
// �`�a���[�v�̏�Ԃ�ݒ�
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetABLoopState(BOOL bALoop, BOOL bBLoop)
{
	CheckButton(ID_ABLOOP_A, bALoop);
	CheckButton(ID_ABLOOP_B, bBLoop);
	EnableButton(ID_SLOOP, !(bALoop || bBLoop));
	EnableButton(ID_ALOOP, !(bALoop || bBLoop));
	EnableButton(ID_RANDOM, !(bALoop || bBLoop));
	EnableButton(ID_MARKERPLAY, !(bALoop || bBLoop));
	EnableButton(ID_ADDMARKER, !(bALoop || bBLoop));
	EnableButton(ID_DELETEMARKER, !(bALoop || bBLoop));
}
//----------------------------------------------------------------------------
// �}�[�J�[�Đ��̏�Ԃ�ݒ�
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetMarkerPlayState(BOOL bMarkerPlay)
{
	CheckButton(ID_MARKERPLAY, bMarkerPlay);
	EnableButton(ID_SLOOP, !bMarkerPlay);
	EnableButton(ID_ALOOP, !bMarkerPlay);
	EnableButton(ID_RANDOM, !bMarkerPlay);
	EnableButton(ID_ABLOOP_A, !bMarkerPlay);
	EnableButton(ID_ABLOOP_B, !bMarkerPlay);

	HideButton(ID_HEAD, bMarkerPlay);
	HideButton(ID_PREVMARKER, !bMarkerPlay);
	HideButton(ID_NEXT, bMarkerPlay);
	HideButton(ID_NEXTMARKER, !bMarkerPlay);
}
//----------------------------------------------------------------------------
// �Đ���Ԃ�ݒ�
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetPlayingState(BOOL bPlaying)
{
	HideButton(ID_PLAY, bPlaying);
	HideButton(ID_PAUSE, !bPlaying);
	CheckButton(ID_PAUSE, FALSE);
}
//----------------------------------------------------------------------------
// �ꎞ��~��Ԃ�ݒ�
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetPausingState(BOOL bPausing)
{
	CheckButton(ID_PAUSE, bPausing);
}
//----------------------------------------------------------------------------
// �T�C�Y�i���j�ɕύX����
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetSSize()
{
	std::vector<TBBUTTON> arrayButton;
	int nCount = SendMessage(m_hWnd, TB_BUTTONCOUNT, 0, 0);
	for(int i = 0; i < nCount; i++) {
		TBBUTTON btn;
		ZeroMemory(&btn, sizeof(TBBUTTON));
		SendMessage(m_hWnd, TB_GETBUTTON, i, (LPARAM)&btn);
		arrayButton.push_back(btn);
	}

	ResetProc();
	DestroyWindow(m_hWnd);
	m_hWnd = CreateToolbarEx(m_rMainWnd, WS_CHILD | CCS_NORESIZE |
		CCS_NODIVIDER | CCS_TOP | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT, 0,
		0, GetModuleHandle(NULL), NULL, NULL, 0,
		0, 0, 16, 15, 0);
	SetProc();
	SetStyle(GetStyle()| CCS_NORESIZE | CCS_NODIVIDER | CCS_TOP
			 | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT);
	LoadBitmap(MAKEINTRESOURCE(IDR_TOOLBARS));
	UINT id[23] = {
		ID_HEAD,
		ID_PREVMARKER,
		ID_PLAY,
		ID_PAUSE,
		ID_STOP,
		ID_NEXTMARKER,
		ID_NEXT,
		0,
		ID_OPENFILE,
		0,
		ID_SLOOP,
		ID_ALOOP,
		ID_RANDOM,
		0,
		ID_ABLOOP_A,
		ID_ABLOOP_B,
		0,
		ID_MARKERPLAY,
		ID_ADDMARKER,
		ID_DELETEMARKER,
		0,
		ID_EXPLORER,
		ID_PLAYLIST,
	};
	m_arrayButton.clear();
	SetButtons(id, 23);
	HideButton(ID_PREVMARKER, TRUE);
	HideButton(ID_NEXTMARKER, TRUE);
	HideButton(ID_PAUSE, TRUE);

	int b = SendMessage(m_hWnd, TB_BUTTONCOUNT, 0, 0);
	for(int i = 0; i < b; i++)
		SendMessage(m_hWnd, TB_DELETEBUTTON, 0, 0);
	for(int i = 0; i < (int)arrayButton.size(); i++) {
		SendMessage(m_hWnd, TB_ADDBUTTONS, 1,
			(LPARAM)&arrayButton[i]);
	}

	SetPlayingState(!m_rMainWnd.GetSound().ChannelIsStopped());
	SetPausingState(m_rMainWnd.GetSound().ChannelIsPausing());
	CheckButton(ID_ALOOP, m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP));
	CheckButton(ID_RANDOM, m_rMainWnd.GetMenu().IsItemChecked(ID_RANDOM));
	SetSingleLoopState(m_rMainWnd.GetSound().IsLoop());
	SetMarkerPlayState(m_rMainWnd.IsMarkerPlay());
	if(!m_rMainWnd.IsMarkerPlay())
		SetABLoopState(m_rMainWnd.GetSound().IsABLoopA(),
			m_rMainWnd.GetSound().IsABLoopB());
	CheckButton(ID_PLAYLIST,
		m_rMainWnd.GetMenu().IsItemChecked(ID_PLAYLIST));
	CheckButton(ID_EXPLORER,
		m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER));

	POINT pt;
	pt.y = m_rMainWnd.GetDivider1().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(m_rMainWnd.GetControlOffset(),
		   pt.y + m_rMainWnd.GetDivider1().GetHeight());

	SetSize(400, 22);
	Show(SW_SHOW);
}
//----------------------------------------------------------------------------
// �T�C�Y�i���j�ɕύX����
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetMSize()
{
	std::vector<TBBUTTON> arrayButton;
	int nCount = SendMessage(m_hWnd, TB_BUTTONCOUNT, 0, 0);
	for(int i = 0; i < nCount; i++) {
		TBBUTTON btn;
		ZeroMemory(&btn, sizeof(TBBUTTON));
		SendMessage(m_hWnd, TB_GETBUTTON, i, (LPARAM)&btn);
		arrayButton.push_back(btn);
	}

	ResetProc();
	DestroyWindow(m_hWnd);
	m_hWnd = CreateToolbarEx(m_rMainWnd, WS_CHILD | CCS_NORESIZE |
		CCS_NODIVIDER | CCS_TOP | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT, 0,
		0, GetModuleHandle(NULL), NULL, NULL, 0,
		0, 0, 20, 20, 0);
	SetProc();
	SetStyle(GetStyle()| CCS_NORESIZE | CCS_NODIVIDER | CCS_TOP
			 | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT);
	LoadBitmap(MAKEINTRESOURCE(IDR_TOOLBARM));
	UINT id[23] = {
		ID_HEAD,
		ID_PREVMARKER,
		ID_PLAY,
		ID_PAUSE,
		ID_STOP,
		ID_NEXTMARKER,
		ID_NEXT,
		0,
		ID_OPENFILE,
		0,
		ID_SLOOP,
		ID_ALOOP,
		ID_RANDOM,
		0,
		ID_ABLOOP_A,
		ID_ABLOOP_B,
		0,
		ID_MARKERPLAY,
		ID_ADDMARKER,
		ID_DELETEMARKER,
		0,
		ID_EXPLORER,
		ID_PLAYLIST,
	};
	m_arrayButton.clear();
	SetButtons(id, 23);
	HideButton(ID_PREVMARKER, TRUE);
	HideButton(ID_NEXTMARKER, TRUE);
	HideButton(ID_PAUSE, TRUE);

	int b = SendMessage(m_hWnd, TB_BUTTONCOUNT, 0, 0);
	for(int i = 0; i < b; i++)
		SendMessage(m_hWnd, TB_DELETEBUTTON, 0, 0);
	for(int i = 0; i < (int)arrayButton.size(); i++) {
		SendMessage(m_hWnd, TB_ADDBUTTONS, 1,
			(LPARAM)&arrayButton[i]);
	}

	SetPlayingState(!m_rMainWnd.GetSound().ChannelIsStopped());
	SetPausingState(m_rMainWnd.GetSound().ChannelIsPausing());
	CheckButton(ID_ALOOP, m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP));
	CheckButton(ID_RANDOM, m_rMainWnd.GetMenu().IsItemChecked(ID_RANDOM));
	SetSingleLoopState(m_rMainWnd.GetSound().IsLoop());
	SetMarkerPlayState(m_rMainWnd.IsMarkerPlay());
	if(!m_rMainWnd.IsMarkerPlay())
		SetABLoopState(m_rMainWnd.GetSound().IsABLoopA(),
			m_rMainWnd.GetSound().IsABLoopB());
	CheckButton(ID_PLAYLIST,
		m_rMainWnd.GetMenu().IsItemChecked(ID_PLAYLIST));
	CheckButton(ID_EXPLORER,
		m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER));

	POINT pt;
	pt.y = m_rMainWnd.GetDivider1().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(m_rMainWnd.GetControlOffset(),
		   pt.y + m_rMainWnd.GetDivider1().GetHeight());

	SetSize(460, 26);
	Show(SW_SHOW);
}
//----------------------------------------------------------------------------
// �T�C�Y�i��j�ɕύX����
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetLSize()
{
	std::vector<TBBUTTON> arrayButton;
	int nCount = SendMessage(m_hWnd, TB_BUTTONCOUNT, 0, 0);
	for(int i = 0; i < nCount; i++) {
		TBBUTTON btn;
		ZeroMemory(&btn, sizeof(TBBUTTON));
		SendMessage(m_hWnd, TB_GETBUTTON, i, (LPARAM)&btn);
		arrayButton.push_back(btn);
	}

	ResetProc();
	DestroyWindow(m_hWnd);
	m_hWnd = CreateToolbarEx(m_rMainWnd, WS_CHILD | CCS_NORESIZE |
		CCS_NODIVIDER | CCS_TOP | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT, 0,
		0, GetModuleHandle(NULL), NULL, NULL, 0,
		0, 0, 24, 24, 0);
	SetProc();
	SetStyle(GetStyle()| CCS_NORESIZE | CCS_NODIVIDER | CCS_TOP
			 | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT);
	LoadBitmap(MAKEINTRESOURCE(IDR_TOOLBARL));
	UINT id[23] = {
		ID_HEAD,
		ID_PREVMARKER,
		ID_PLAY,
		ID_PAUSE,
		ID_STOP,
		ID_NEXTMARKER,
		ID_NEXT,
		0,
		ID_OPENFILE,
		0,
		ID_SLOOP,
		ID_ALOOP,
		ID_RANDOM,
		0,
		ID_ABLOOP_A,
		ID_ABLOOP_B,
		0,
		ID_MARKERPLAY,
		ID_ADDMARKER,
		ID_DELETEMARKER,
		0,
		ID_EXPLORER,
		ID_PLAYLIST,
	};
	m_arrayButton.clear();
	SetButtons(id, 23);
	HideButton(ID_PREVMARKER, TRUE);
	HideButton(ID_NEXTMARKER, TRUE);
	HideButton(ID_PAUSE, TRUE);

	int b = SendMessage(m_hWnd, TB_BUTTONCOUNT, 0, 0);
	for(int i = 0; i < b; i++)
		SendMessage(m_hWnd, TB_DELETEBUTTON, 0, 0);
	for(int i = 0; i < (int)arrayButton.size(); i++) {
		SendMessage(m_hWnd, TB_ADDBUTTONS, 1,
			(LPARAM)&arrayButton[i]);
	}

	SetPlayingState(!m_rMainWnd.GetSound().ChannelIsStopped());
	SetPausingState(m_rMainWnd.GetSound().ChannelIsPausing());
	CheckButton(ID_ALOOP, m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP));
	CheckButton(ID_RANDOM, m_rMainWnd.GetMenu().IsItemChecked(ID_RANDOM));
	SetSingleLoopState(m_rMainWnd.GetSound().IsLoop());
	SetMarkerPlayState(m_rMainWnd.IsMarkerPlay());
	if(!m_rMainWnd.IsMarkerPlay())
		SetABLoopState(m_rMainWnd.GetSound().IsABLoopA(),
			m_rMainWnd.GetSound().IsABLoopB());
	CheckButton(ID_PLAYLIST,
		m_rMainWnd.GetMenu().IsItemChecked(ID_PLAYLIST));
	CheckButton(ID_EXPLORER,
		m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER));

	POINT pt;
	pt.y = m_rMainWnd.GetDivider1().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(m_rMainWnd.GetControlOffset(),
		   pt.y + m_rMainWnd.GetDivider1().GetHeight());
	SetWindowPos(m_hWnd, m_rMainWnd.GetTimeLabel(), 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE);

	SetSize(518, 30);
	Show(SW_SHOW);
}
//----------------------------------------------------------------------------
// �P�ȃ��[�v�̏�Ԃ�ݒ�
//----------------------------------------------------------------------------
void CToolBar_MainWnd::SetSingleLoopState(BOOL bSLoop)
{
	CheckButton(ID_SLOOP, bSLoop);
	EnableButton(ID_ALOOP, !bSLoop);
	EnableButton(ID_RANDOM, !bSLoop);
}
//----------------------------------------------------------------------------
// ���o���{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnHeadButtonSelected()
{
	if(GetTickCount() - dwRewindClickTime < 500) {
		if((!m_rMainWnd.GetMenu().IsItemChecked(ID_REVERSE)
			&& m_rMainWnd.GetSound().ChannelGetSecondsPosition() < 1.0f)
			|| (m_rMainWnd.GetMenu().IsItemChecked(ID_REVERSE)
			&& m_rMainWnd.GetSound().ChannelGetSecondsPosition()
			> m_rMainWnd.GetSound().ChannelGetSecondsLength() - 1.0f)) {
			if(m_rMainWnd.GetMenu().IsItemChecked(ID_RANDOM)) {
				if(!(!m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
				   && m_rMainWnd.GetPlayList().GetMaxPlayOrder() == 1))
					m_rMainWnd.PlayPrevious();
			}
			else if(m_rMainWnd.GetSound().GetNSFCount() > 0)
				m_rMainWnd.PlayPrevious();
			else {
				if(!(!m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
				   && m_rMainWnd.GetSound().GetCurFileNum() == 1))
					m_rMainWnd.PlayPrevious();
			}
		}
		else m_rMainWnd.Head();
	}
}
//----------------------------------------------------------------------------
// �O�̃}�[�J�[�փ{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnPrevMarkerButtonSelected()
{
	if(GetTickCount() - dwRewindClickTime < 500) {
		if((!m_rMainWnd.GetMenu().IsItemChecked(ID_REVERSE)
		   && m_rMainWnd.GetSound().ChannelGetSecondsPosition()
		   < m_rMainWnd.GetSound().GetLoopPosA_sec() + 1.0f)
		   || (m_rMainWnd.GetMenu().IsItemChecked(ID_REVERSE)
		   && m_rMainWnd.GetSound().ChannelGetSecondsPosition()
		   > m_rMainWnd.GetSound().GetLoopPosB_sec() - 1.0f)) {
			m_rMainWnd.SetPrevMarker();
		}
		else m_rMainWnd.Head();
	}
}
//----------------------------------------------------------------------------
// �t�@�C�����J���{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnOpenFileButtonSelected()
{
	m_rMainWnd.ShowOpenFileDialog(TRUE);
}
//----------------------------------------------------------------------------
// �Đ��{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnPlayButtonSelected()
{
	m_rMainWnd.Play();
}
//----------------------------------------------------------------------------
// �ꎞ��~�{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnPauseButtonSelected()
{
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// ��~�{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnStopButtonSelected()
{
	m_rMainWnd.Stop(FALSE);
}
//----------------------------------------------------------------------------
// ���̃}�[�J�[�փ{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnNextMarkerButtonSelected()
{
	if(GetTickCount() - dwRewindClickTime < 500) m_rMainWnd.SetNextMarker();
}
//----------------------------------------------------------------------------
// ���փ{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnNextButtonSelected()
{
	if(GetTickCount() - dwRewindClickTime < 500) {
		if(m_rMainWnd.GetMenu().IsItemChecked(ID_RANDOM)) {
			if(!(!m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
			   && m_rMainWnd.GetPlayList().GetMaxPlayOrder()
			   == m_rMainWnd.GetPlayList().GetItemCount()))
				m_rMainWnd.PlayNext(FALSE, FALSE);
		}
		else {
			if(!(!m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
			   && m_rMainWnd.GetSound().GetCurFileNum()
			   == m_rMainWnd.GetPlayList().GetItemCount()))
				m_rMainWnd.PlayNext(FALSE, FALSE);
			else if(m_rMainWnd.GetSound().GetNSFCount() > 0)
				m_rMainWnd.PlayNext(FALSE, FALSE);
		}
	}
}
//----------------------------------------------------------------------------
// �P�ȃ��[�v�{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnSingleLoopButtonSelected()
{
	m_rMainWnd.SetSingleLoop();
}
//----------------------------------------------------------------------------
// �S�ȃ��[�v�{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnAllLoopButtonSelected()
{
	m_rMainWnd.SetAllLoop();
}
//----------------------------------------------------------------------------
// �����_���Đ��{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnRandomButtonSelected()
{
	m_rMainWnd.SetRandom();
}
//----------------------------------------------------------------------------
// �`�a���[�v�i�`�j�{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnABLoopAButtonSelected()
{
	m_rMainWnd.SetABLoopA();
}
//----------------------------------------------------------------------------
// �`�a���[�v�i�a�j�{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnABLoopBButtonSelected()
{
	m_rMainWnd.SetABLoopB();
}
//----------------------------------------------------------------------------
// �}�[�J�[�Đ��{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnMarkerPlayButtonSelected()
{
	m_rMainWnd.SetMarkerPlay();
}
//----------------------------------------------------------------------------
// �}�[�J�[�ǉ��{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnAddMarkerButtonSelected()
{
	m_rMainWnd.AddMarker();
}
//----------------------------------------------------------------------------
// �}�[�J�[�폜�{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnDeleteMarkerButtonSelected()
{
	m_rMainWnd.DeleteMarker();
}
//----------------------------------------------------------------------------
// �G�N�X�v���[���{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnExplorerButtonSelected()
{
	m_rMainWnd.SetExplorerVisible();
}
//----------------------------------------------------------------------------
// �Đ����X�g�{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnPlayListButtonSelected()
{
	m_rMainWnd.SetPlayListVisible();
}
//----------------------------------------------------------------------------
// �{�^�����I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnCommand(int id, HWND/* hwndCtl*/, UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_HEAD:
		OnHeadButtonSelected();
		break;
	case ID_PREVMARKER:
		OnPrevMarkerButtonSelected();
		break;
	case ID_OPENFILE:
		OnOpenFileButtonSelected();
		break;
	case ID_PLAY:
		OnPlayButtonSelected();
		break;
	case ID_PAUSE:
		OnPauseButtonSelected();
		break;
	case ID_STOP:
		OnStopButtonSelected();
		break;
	case ID_NEXTMARKER:
		OnNextMarkerButtonSelected();
		break;
	case ID_NEXT:
		OnNextButtonSelected();
		break;
	case ID_SLOOP:
		OnSingleLoopButtonSelected();
		break;
	case ID_ALOOP:
		OnAllLoopButtonSelected();
		break;
	case ID_RANDOM:
		OnRandomButtonSelected();
		break;
	case ID_ABLOOP_A:
		OnABLoopAButtonSelected();
		break;
	case ID_ABLOOP_B:
		OnABLoopBButtonSelected();
		break;
	case ID_MARKERPLAY:
		OnMarkerPlayButtonSelected();
		break;
	case ID_ADDMARKER:
		OnAddMarkerButtonSelected();
		break;
	case ID_DELETEMARKER:
		OnDeleteMarkerButtonSelected();
		break;
	case ID_EXPLORER:
		OnExplorerButtonSelected();
		break;
	case ID_PLAYLIST:
		OnPlayListButtonSelected();
		break;
	}
}
//----------------------------------------------------------------------------
// �R�����R���g���[������̃��b�Z�[�W
//----------------------------------------------------------------------------
LRESULT CToolBar_MainWnd::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	switch(pnmhdr->code)
	{
	case TTN_NEEDTEXT:
		OnNeed_Text(idFrom, (TOOLTIPTEXT*)pnmhdr);
		break;
	}
	return CToolBar::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
// �c�[���`�b�v���K�v
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnNeed_Text(int idFrom, TOOLTIPTEXT* pttt)
{
	switch(idFrom)
	{
	case ID_HEAD:
		if(m_rMainWnd.GetMenu().IsItemChecked(ID_RANDOM)) {
			if(!m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
			   && m_rMainWnd.GetPlayList().GetMaxPlayOrder() == 1)
#if JP
				pttt->lpszText = _T("�����߂�\n")
								 _T("���o��");
#else // JP
				pttt->lpszText = _T("Rewind\n")
								 _T("Head");
#endif // JP
			else
#if JP
				pttt->lpszText = _T("�N���b�N : ���o��/�O��\n")
								 _T("������ : �����߂�");
#else // JP
				pttt->lpszText = _T("Click : Head/Previous\n")
								 _T("Long press : Rewind");
#endif // JP
		}
		else
		{
			if(!m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
			   && m_rMainWnd.GetSound().GetCurFileNum() == 1)
#if JP
				pttt->lpszText = _T("�����߂�\n")
								 _T("���o��");
#else // JP
				pttt->lpszText = _T("Rewind\n")
								 _T("Head");
#endif // JP
			else
#if JP
				pttt->lpszText = _T("�N���b�N : ���o��/�O��\n")
								 _T("������ : �����߂�");
#else // JP
				pttt->lpszText = _T("Click : Head/Previous\n")
								 _T("Long press : Rewind");
#endif // JP
		}
		break;
	case ID_PREVMARKER:
#if JP
		pttt->lpszText = _T("�N���b�N : ���o��/�O�̃}�[�J�[��\n")
						 _T("������ : �����߂�");
#else // JP
		pttt->lpszText = _T("Click : Head/Previous marker\n")
						 _T("Long press : Rewind");
#endif // JP
		break;
	case ID_PLAY:
#if JP
		pttt->lpszText = _T("�Đ�");
#else // JP
		pttt->lpszText = _T("Play");
#endif // JP
		break;
	case ID_PAUSE:
#if JP
		pttt->lpszText = _T("�ꎞ��~");
#else // JP
		pttt->lpszText = _T("Pause");
#endif // JP
		break;
	case ID_STOP:
#if JP
		pttt->lpszText = _T("��~");
#else // JP
		pttt->lpszText = _T("Stop");
#endif // JP
		break;
	case ID_NEXTMARKER:
#if JP
		pttt->lpszText = _T("�N���b�N : ���̃}�[�J�[��\n")
						 _T("������ : ������");
#else // JP
		pttt->lpszText = _T("Click : Next marker\n")
						 _T("Long press : Forward");
#endif // JP
		break;
	case ID_NEXT:
		if(m_rMainWnd.GetMenu().IsItemChecked(ID_RANDOM)) {
			if(m_rMainWnd.GetSound().GetCurFileNum() > 0
			   && !m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
			   && m_rMainWnd.GetPlayList().GetMaxPlayOrder()
			       == m_rMainWnd.GetPlayList().GetItemCount())
#if JP
				pttt->lpszText = _T("������");
#else // JP
				pttt->lpszText = _T("Forward");
#endif // JP
			else
#if JP
				pttt->lpszText = _T("�N���b�N : ����\n")
								 _T("������ : ������");
#else // JP
				pttt->lpszText = _T("Click : Next\n")
								 _T("Long press : Forward");
#endif // JP
		}
		else {
			if(m_rMainWnd.GetSound().GetCurFileNum() > 0
			   && !m_rMainWnd.GetMenu().IsItemChecked(ID_ALOOP)
			   && m_rMainWnd.GetSound().GetCurFileNum()
			       == m_rMainWnd.GetPlayList().GetItemCount())
#if JP
				pttt->lpszText = _T("������");
#else // JP
				pttt->lpszText = _T("Forward");
#endif // JP
			else
#if JP
				pttt->lpszText = _T("�N���b�N : ����\n")
								 _T("������ : ������");
#else // JP
				pttt->lpszText = _T("Click : Next\n")
								 _T("Long press : Forward");
#endif // JP
		}
		break;
	case ID_OPENFILE:
#if JP
		pttt->lpszText = _T("�t�@�C�����J��");
#else // JP
		pttt->lpszText = _T("Open file");
#endif // JP
		break;
	case ID_SLOOP:
#if JP
		pttt->lpszText = _T("�P�ȃ��[�v");
#else // JP
		pttt->lpszText = _T("Single loop");
#endif // JP
		break;
	case ID_ALOOP:
#if JP
		pttt->lpszText = _T("�S�ȃ��[�v");
#else // JP
		pttt->lpszText = _T("All loop");
#endif // JP
		break;
	case ID_RANDOM:
#if JP
		pttt->lpszText = _T("�����_���Đ�");
#else // JP
		pttt->lpszText = _T("Random play");
#endif // JP
		break;
	case ID_ABLOOP_A:
#if JP
		pttt->lpszText = _T("�`�a���[�v�i�`�j");
#else // JP
		pttt->lpszText = _T("AB loop(A)");
#endif // JP
		break;
	case ID_ABLOOP_B:
#if JP
		pttt->lpszText = _T("�`�a���[�v�i�a�j");
#else // JP
		pttt->lpszText = _T("AB loop(B)");
#endif // JP
		break;
	case ID_MARKERPLAY:
#if JP
		pttt->lpszText = _T("�}�[�J�[�Đ�");
#else // JP
		pttt->lpszText = _T("Marker play");
#endif // JP
		break;
	case ID_ADDMARKER:
#if JP
		pttt->lpszText = _T("�}�[�J�[�ǉ�");
#else // JP
		pttt->lpszText = _T("Add a marker");
#endif // JP
		break;
	case ID_DELETEMARKER:
#if JP
		pttt->lpszText = _T("�}�[�J�[�폜");
#else // JP
		pttt->lpszText = _T("Delete a marker");
#endif // JP
		break;
	case ID_EXPLORER:
#if JP
		pttt->lpszText = _T("�G�N�X�v���[���̕\�����");
#else // JP
		pttt->lpszText = _T("Switch visibility of explorer");
#endif // JP
		break;
	case ID_PLAYLIST:
#if JP
		pttt->lpszText = _T("�Đ����X�g�̕\�����");
#else // JP
		pttt->lpszText = _T("Switch visibility of playlist");
#endif // JP
		break;
	}
}
//----------------------------------------------------------------------------
// �h���b�O���J�n���ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnBeginDrag(NMTOOLBAR* pnmtb)
{
	switch(pnmtb->iItem)
	{
	case ID_HEAD:
	case ID_PREVMARKER:
		if(!m_rMainWnd.GetMenu().IsItemChecked(ID_REWIND)) {
			dwRewindClickTime = GetTickCount();
			m_rMainWnd.StartRewind();
		}
		break;
	case ID_NEXT:
	case ID_NEXTMARKER:
		if(!m_rMainWnd.GetMenu().IsItemChecked(ID_FORWARD)) {
			dwRewindClickTime = GetTickCount();
			m_rMainWnd.StartForward();
		}
		break;
	}
}
//----------------------------------------------------------------------------
// �h���b�O���I�����ꂽ
//----------------------------------------------------------------------------
void CToolBar_MainWnd::OnEndDrag(NMTOOLBAR* pnmtb)
{
	switch(pnmtb->iItem)
	{
	case ID_HEAD:
	case ID_PREVMARKER:
		m_rMainWnd.StopRewind();
		break;
	case ID_NEXT:
	case ID_NEXTMARKER:
		m_rMainWnd.StopForward();
		break;
	}
}
//----------------------------------------------------------------------------
