//----------------------------------------------------------------------------
// EditExt.cpp : �G�f�B�b�g�R���g���[���i�g���Łj�̍쐬�E�Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "Wnd.h"
#include "EditExt.h"
//----------------------------------------------------------------------------
// �L�[�������ꂽ
//----------------------------------------------------------------------------
void CEditExt::OnKeyDown(UINT vk, int cRepeat, UINT flags)
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
	CEdit::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// �L�[�������ꂽ
//----------------------------------------------------------------------------
void CEditExt::OnKeyUp(UINT vk, UINT lKeyData)
{
	switch(vk)
	{
	case VK_SPACE:
		m_rParent.OnSpaceKeyPressed();
		break;
	}
	CEdit::OnKeyUp(vk, lKeyData);
}
//----------------------------------------------------------------------------
