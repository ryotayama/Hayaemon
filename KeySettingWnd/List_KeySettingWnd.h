//----------------------------------------------------------------------------
// List_KeySettingWnd.h : �L�[�J�X�^�}�C�Y�p�E�B���h�E���̃��X�g�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef List_KeySettingWndH
#define List_KeySettingWndH

class CKeySettingWnd_MainWnd;
#include "../Common/ListView.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �L�[�J�X�^�}�C�Y�p�E�B���h�E���̃��X�g�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CList_KeySettingWnd : public CListView
{
public: // �֐�

	CList_KeySettingWnd(CKeySettingWnd_MainWnd & parent);
	virtual ~CList_KeySettingWnd();

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // �����o�ϐ�

	CKeySettingWnd_MainWnd & m_rParent;
};
//----------------------------------------------------------------------------

#endif