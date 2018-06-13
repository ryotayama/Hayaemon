//----------------------------------------------------------------------------
// ButtonExt.h : �{�^���i�g���Łj�̍쐬�E�Ǘ����s��
//----------------------------------------------------------------------------
#ifndef ButtonExtH
#define ButtonExtH

#include "Wnd.h"
#include "Button.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �{�^���i�g���Łj�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CButtonExt : public CButton
{
public: // �֐�

	CButtonExt(CWnd & parent)
		: m_rParent(parent) { }
	virtual ~CButtonExt() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnKeyUp(UINT vk, UINT lKeyData);

private: // �����o�ϐ�

	CWnd & m_rParent;
};
//----------------------------------------------------------------------------

#endif