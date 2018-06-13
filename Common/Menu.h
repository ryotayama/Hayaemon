//----------------------------------------------------------------------------
// Menu.h : ���j���[�̍쐬�E�Ǘ��E�j�����s��
//----------------------------------------------------------------------------
#ifndef MenuH
#define MenuH
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ���j���[�̍쐬�E�Ǘ��E�j�����s���N���X
//----------------------------------------------------------------------------
class CMenu
{
public: // �֐�

	CMenu(): m_hMenu(0) { }
	virtual ~CMenu() { Destroy(); }

	// ���j���[�̖����ɐV�������ڂ�ǉ�
	virtual BOOL Append(UINT uFlags, UINT_PTR uIDNewItem, LPCTSTR lpNewItem);

	// ���j���[�̖����ɋ�؂����ǉ�
	virtual BOOL AppendSeparator();

	virtual BOOL Create();
	virtual void CheckItem(UINT uIDCheckItem, UINT uCheck) {
		CheckMenuItem(m_hMenu, uIDCheckItem, uCheck);
	}
	virtual BOOL CreatePopup();
	virtual void Destroy();
	virtual void EnableItem(UINT uIDEnableItem, UINT uEnable) {
		EnableMenuItem(m_hMenu, uIDEnableItem, uEnable);
	}
	virtual UINT GetState(UINT uID) {
		return GetMenuState(m_hMenu, uID, MF_BYCOMMAND);
	}
	virtual BOOL Insert(UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem,
						LPCTSTR lpNewItem);
	virtual BOOL IsItemChecked(UINT uID) {
		UINT uRet = GetMenuState(m_hMenu, uID, MF_BYCOMMAND);
		return (BOOL)(uRet & MF_CHECKED);
	}

protected: // �����o�ϐ�

	HMENU m_hMenu;

public: // �����o�ϐ��̎擾�E�ݒ�

	operator HMENU() const { return m_hMenu; }
};
//----------------------------------------------------------------------------

#endif