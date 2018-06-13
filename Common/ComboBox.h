//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// ComboBox.h : �R���{�{�b�N�X�E�R���g���[���̍쐬�E�Ǘ����s��
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#ifndef ComboBoxH
#define ComboBoxH

#include "Wnd.h"
#include "Font.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//--------------------------------------------------------------------------
//	�R���{�{�b�N�X�E�R���g���[���̍쐬�E�Ǘ����s���N���X
//--------------------------------------------------------------------------
class CComboBox : public CWnd
{
public: // �֐�

	CComboBox() { }
	virtual ~CComboBox() { }

	virtual void Add(LPCTSTR);
	virtual BOOL Create(int, int, int, int, HWND);
	virtual void Select(LPCTSTR);
	virtual tstring GetSelectText();

private: // �����o�ϐ�

	CFont m_font;
};
//--------------------------------------------------------------------------

#endif