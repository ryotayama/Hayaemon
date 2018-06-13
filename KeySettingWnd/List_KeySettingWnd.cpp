//----------------------------------------------------------------------------
// List_KeySettingWnd.cpp : �L�[�J�X�^�}�C�Y�p�E�B���h�E���̃��X�g�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "KeySettingWnd_MainWnd.h"
#include "List_KeySettingWnd.h"
//----------------------------------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------------------------------
CList_KeySettingWnd::CList_KeySettingWnd(CKeySettingWnd_MainWnd & parent)
	: m_rParent(parent)
{
}
//----------------------------------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------------------------------
CList_KeySettingWnd::~CList_KeySettingWnd()
{
}
//----------------------------------------------------------------------------
// �L�[�������ꂽ
//----------------------------------------------------------------------------
void CList_KeySettingWnd::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	switch(vk)
	{
	case VK_TAB:
		if(GetKeyState(VK_SHIFT) < 0)
			m_rParent.SetPreviousFocus();
		else
			m_rParent.SetNextFocus();
		break;
	case VK_RETURN:
		m_rParent.OnReturnKeyPressed();
		break;
	case VK_ESCAPE:
		m_rParent.OnEscKeyPressed();
		break;
	}
	CListView::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
