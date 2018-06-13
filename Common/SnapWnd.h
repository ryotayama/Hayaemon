//----------------------------------------------------------------------------
// SnapWnd.h : �X�i�b�v�E�B���h�E�N���X
//----------------------------------------------------------------------------
#ifndef SnapWndH
#define SnapWndH

#include "FrameWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �t���[���E�B���h�E�N���X
//----------------------------------------------------------------------------
class CSnapWnd : public CFrameWnd
{
public: // �֐�

	CSnapWnd(): m_nSnapRange(24) { }
	virtual ~CSnapWnd() { }

	virtual void OnEnterSizeMove()
	{
		POINT pt;
		GetCursorPos(&pt);
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		m_nCsrLeftToLeft = rc.left - pt.x;
		m_nCsrLeftToRight = rc.right - pt.x;
		m_nCsrTopToTop = rc.top - pt.y;
		m_nCsrTopToBottom = rc.bottom - pt.y;

		CFrameWnd::OnEnterSizeMove();
	}

	virtual LRESULT OnMoving(UINT nSide, LPRECT lpRect)
	{
		// �}�E�X�J�[�\���̈ʒu�𓾂�
		POINT pt;
		GetCursorPos(&pt);

		// �E�B���h�E�̈ʒu
		int left = pt.x + m_nCsrLeftToLeft;
		int top = pt.y + m_nCsrTopToTop;
		int right = pt.x + m_nCsrLeftToRight;
		int bottom = pt.y + m_nCsrTopToBottom;

		RECT rc;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);

		int width = right - left;
		int height = bottom - top;

		// ���ʒu
		if(top <= rc.bottom && bottom >= rc.top)
		{
			// �E�ʒu
			if(rc.right - m_nSnapRange < right && right < rc.right + m_nSnapRange)
			{
				right = rc.right;
				left = right - width;
			}

			// ���ʒu
			if(rc.left - m_nSnapRange < left && left < rc.left + m_nSnapRange)
			{
				left = rc.left;
				right = left + width;
			}
		}

		// �c�ʒu
		if(left <= rc.right && right >= rc.left)
		{
			// ���ʒu
			bottom = top + height;
			if(rc.bottom - m_nSnapRange < bottom && bottom < rc.bottom + m_nSnapRange)
			{
				bottom = rc.bottom;
				top = bottom - height;
			}

			// ��ʒu
			if(rc.top - m_nSnapRange < top && top < rc.top + m_nSnapRange)
			{
				top = rc.top;
				bottom = top + height;
			}
		}

		// �ʒu�̐ݒ�
		lpRect->left = left;
		lpRect->right = right;
		lpRect->top = top;
		lpRect->bottom = bottom;

		return TRUE;
	}

	virtual LRESULT OnSizing(UINT nSide, LPRECT lpRect)
	{
		// �}�E�X�J�[�\���̈ʒu�𓾂�
		POINT pt;
		GetCursorPos(&pt);

		// �E�B���h�E�̈ʒu
		int left = lpRect->left;
		int right = lpRect->right;
		int top = lpRect->top;
		int bottom = lpRect->bottom;

		RECT rc;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);

		// ���ʒu
		if(nSide == WMSZ_LEFT || nSide == WMSZ_TOPLEFT || nSide == WMSZ_BOTTOMLEFT)
		{
			if(rc.left - m_nSnapRange < pt.x && pt.x < rc.left + m_nSnapRange)
				left = rc.left;
		}

		// �E�ʒu
		if(nSide == WMSZ_RIGHT || nSide == WMSZ_TOPRIGHT || nSide == WMSZ_BOTTOMRIGHT)
		{
			if(rc.right - m_nSnapRange < pt.x && pt.x < rc.right + m_nSnapRange)
				right = rc.right;
		}

		// ��ʒu
		if(nSide == WMSZ_TOP || nSide == WMSZ_TOPLEFT || nSide == WMSZ_TOPRIGHT)
		{
			if(rc.top - m_nSnapRange < pt.y && pt.y < rc.top + m_nSnapRange)
				top = rc.top;
		}

		// ���ʒu
		if(nSide == WMSZ_BOTTOM || nSide == WMSZ_BOTTOMLEFT || nSide == WMSZ_BOTTOMRIGHT)
		{
			if(rc.bottom - m_nSnapRange < pt.y && pt.y < rc.bottom + m_nSnapRange)
				bottom = rc.bottom;
		}

		// �ʒu�̐ݒ�
		lpRect->left = left;
		lpRect->right = right;
		lpRect->top = top;
		lpRect->bottom = bottom;

		return TRUE;
	}

protected: // �����o�ϐ�

	int m_nCsrLeftToLeft; // �J�[�\������E�B���h�E�̍��[�܂ł̈ʒu
	int m_nCsrLeftToRight; // �J�[�\������E�B���h�E�̉E�[�܂ł̈ʒu
	int m_nCsrTopToTop; // �J�[�\������E�B���h�E�̏�[�܂ł̈ʒu
	int m_nCsrTopToBottom; // �J�[�\������E�B���h�E�̉��[�܂ł̈ʒu
	int m_nSnapRange;

public: // �����o�ϐ��̎擾�E�ݒ�

};
//----------------------------------------------------------------------------

#endif