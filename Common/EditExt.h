//----------------------------------------------------------------------------
// EditExt.h : �G�f�B�b�g�R���g���[���i�g���Łj�̍쐬�E�Ǘ����s��
//----------------------------------------------------------------------------
#ifndef EditExtH
#define EditExtH

#include "Wnd.h"
#include "Edit.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �G�f�B�b�g�R���g���[���i�g���Łj�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CEditExt : public CEdit
{
public: // �֐�

	CEditExt(CWnd & parent)
		: m_rParent(parent) { }
	virtual ~CEditExt() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnKeyUp(UINT vk, UINT lKeyData);

protected: // �����o�ϐ�

	CWnd & m_rParent;
};
//----------------------------------------------------------------------------

#endif