//--------------------------------------------------------------------------
// Button.h : �{�^���̍쐬�E�Ǘ����s��
//--------------------------------------------------------------------------
#ifndef ButtonH
#define ButtonH

#include "Wnd.h"
#include "Font.h"
#include "ClientDC.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//--------------------------------------------------------------------------
//	�{�^���̍쐬�E�Ǘ����s���N���X
//--------------------------------------------------------------------------
class CButton : public CWnd
{
public: // �֐�

	CButton() { }
	virtual ~CButton() { }

	virtual BOOL Create(LPCTSTR, int, int, int, int, HWND, UINT, BOOL bDef = FALSE);
	virtual BOOL Create(LPCTSTR, HWND, UINT, BOOL bDef = FALSE);
	virtual void SetEnable(BOOL);
	virtual int GetLeft() const;
	virtual int GetTop() const;
	virtual int GetRight() const;
	virtual int GetBottom() const;
	virtual int GetTextHeight() const;
	virtual int GetTextWidth() const;
	virtual void SetSizeToTextSize();

private: // �����o�ϐ�

	CFont m_font;
};
//--------------------------------------------------------------------------

#endif