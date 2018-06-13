//----------------------------------------------------------------------------
// HotKeyCtrl.h : �z�b�g�L�[�R���g���[���̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef HotKeyCtrlH
#define HotKeyCtrlH

#include <commctrl.h>
#include "Wnd.h"
#include "Font.h"
#include "AcceleratorTable.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �z�b�g�L�[�R���g���[���̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CHotKeyCtrl : public CWnd
{
public: // �֐�

	CHotKeyCtrl() { }
	virtual ~CHotKeyCtrl() { }

	virtual BOOL Create(HWND hParentWnd)
	{
		Destroy();
	
		INITCOMMONCONTROLSEX ic;
		ic.dwSize = sizeof(INITCOMMONCONTROLSEX);
		ic.dwICC = ICC_HOTKEY_CLASS;
		InitCommonControlsEx(&ic);

		m_hWnd = CreateWindow(HOTKEY_CLASS, _T(""), WS_CHILD, CW_USEDEFAULT,
								CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
								hParentWnd, 0, GetModuleHandle(NULL), NULL);
		if(!m_hWnd) return FALSE;

		// ��ʂ̃v���p�e�B�Őݒ肳��Ă��郁�b�Z�[�W�{�b�N�X�Ɠ����V�X�e���t�H���g�ɐݒ�
		NONCLIENTMETRICS ncm;
		ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
		ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(int);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
		m_font.CreateIndirect(&ncm.lfMessageFont);
		SetFont(m_font, TRUE);

		SetProc();

		return TRUE;
	}
	virtual int GetTextHeight() const {
		if(!m_hWnd) return -1;

		CClientDC dc(m_hWnd);
		HFONT hFont = GetFont();
		HFONT hOrgFont = 0;
		if(hFont)
			hOrgFont = dc.SelectFont(hFont);
		TEXTMETRIC tm;
		GetTextMetrics(dc, &tm);
		int height = tm.tmHeight + tm.tmExternalLeading + 4;
		if(hOrgFont)
			dc.SelectFont(hOrgFont);
		return height;
	}
	virtual int GetTextWidth() const {
		if(!m_hWnd) return -1;

		CClientDC dc(m_hWnd);
		HFONT hFont = GetFont();
		HFONT hOrgFont = 0;
		if(hFont)
			hOrgFont = dc.SelectFont(hFont);
		LRESULT lMargin = SendMessage(m_hWnd, EM_GETMARGINS, 0L, 0L);
		int width = dc.GetTextWidth(GetCaption()) + LOWORD(lMargin) + HIWORD(lMargin) + 8;
		if(hOrgFont)
			dc.SelectFont(hOrgFont);
		return width;
	}
	virtual void SetSizeToTextSize() {
		SetClientSize(GetTextWidth(), GetTextHeight(), FALSE);
	}
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags)
	{
		if (IS_EXTKEY(vk))
			flags |= KF_EXTENDED; // �g���L�[�t���O��ǉ�

		if (vk == VK_CLEAR)
			vk = 0x00; // Numlock�������� "Num 5" ��o�^�����Ȃ�

		CWnd::OnKeyDown(vk, cRepeat, flags);
	}

private: // �����o�ϐ�

	CFont m_font;
};
//----------------------------------------------------------------------------

#endif