//----------------------------------------------------------------------------
// RMenu_TimeSlider.h : �Đ����Ԑݒ�p�X���C�_�p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_TimeSliderH
#define RMenu_TimeSliderH

class CTimeSlider_MainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ���C���E�B���h�E�p���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_TimeSlider : public CMenu
{
public: // �֐�

	CRMenu_TimeSlider(CTimeSlider_MainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_TimeSlider() { }

	virtual BOOL Create(BOOL bOnMarker);
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnDeleteMenuSelected();
	void OnVisibleMenuSelected();

private: // �����o�ϐ�

	CTimeSlider_MainWnd & m_rParent;

public: // �萔

	// �R�}���h ID
	enum {
		// �폜���j���[
		ID_DELETE = 11,
		ID_VISIBLE,
	};
};
//----------------------------------------------------------------------------

#endif