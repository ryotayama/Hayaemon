//--------------------------------------------------------------------------
// RadioButton.h : ���W�I�{�^���̍쐬�E�Ǘ����s��
//--------------------------------------------------------------------------
#ifndef RadioButtonH
#define RadioButtonH

#include "Button.h"
#include "Font.h"
#include "ClientDC.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//--------------------------------------------------------------------------
// ���W�I�{�^���̍쐬�E�Ǘ����s���N���X
//--------------------------------------------------------------------------
class CRadioButton : public CButton
{
public: // �֐�

	CRadioButton() { }
	virtual ~CRadioButton() { }

	virtual BOOL Create(LPCTSTR, int, int, int, int, HWND);
	virtual BOOL Create(LPCTSTR, HWND);

private: // �����o�ϐ�

};
//--------------------------------------------------------------------------

#endif
