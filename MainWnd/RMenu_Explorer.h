//----------------------------------------------------------------------------
// RMenu_Explorer.h : �G�N�X�v���[���p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_ExplorerH
#define RMenu_ExplorerH

class CExplorer;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �G�N�X�v���[���p�E�N���b�N���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_Explorer : public CMenu
{
public: // �֐�

	CRMenu_Explorer(CExplorer & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_Explorer() { }

	virtual BOOL Create(BOOL bOnItem);
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnOpenFilesMenuSelected();
	void OnAddFilesMenuSelected();
	void OnOpenFolderMenuSelected();
	void OnPropertiesMenuSelected();
	void OnVisibleMenuSelected();

private: // �����o�ϐ�

	CExplorer & m_rParent;

public: // �萔

	// �R�}���h ID
	enum {
		ID_OPEN = 11,
		ID_ADD,
		ID_OPENFOLDER,
		ID_PROPERTIES,
		ID_VISIBLE,
	};
};
//----------------------------------------------------------------------------

#endif