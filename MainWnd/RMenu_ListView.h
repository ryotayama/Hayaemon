//----------------------------------------------------------------------------
// RMenu_ListView.h : �Đ����X�g�p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef RMenu_ListViewH
#define RMenu_ListViewH

class CPlayListView_MainWnd;
#include "../Common/Menu.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �Đ����X�g�p�E�N���b�N���j���[�̍쐬�E�Ǘ����s���N���X
//----------------------------------------------------------------------------
class CRMenu_ListView : public CMenu
{
public: // �֐�

	CRMenu_ListView(CPlayListView_MainWnd & parent)
		: m_rParent(parent) { }
	virtual ~CRMenu_ListView() { }

	virtual BOOL Create(BOOL bOnItem);
	void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	void OnCopyNewListMenuSelected(int id);
	void OnDeleteMenuSelected();
	void OnPlayMenuSelected();
	void OnSearchAmazonMenuSelected(int id);
	void OnSearchLyricsMenuSelected(int id);
	void OnSearchLyricsMasterMenuSelected(int id);
	void OnEditTitleMenuSelected();
	void OnEditArtistMenuSelected();
	void OnEditYearMenuSelected();
	void OnOpenFolderMenuSelected();
	void OnPropertiesMenuSelected();
	void OnVisibleMenuSelected();

private: // �����o�ϐ�

	CPlayListView_MainWnd & m_rParent;
	CMenu m_copyMenu;
	CMenu m_editTagMenu;

public: // �萔

	// �R�}���h ID
	enum {
		ID_PLAY = 11,
		ID_DELETE,
		ID_EDITTITLE,
		ID_EDITARTIST,
		ID_EDITYEAR,
		ID_OPENFOLDER,
		ID_PROPERTIES,
		ID_VISIBLE,
		ID_COPY,
		ID_SEARCHAMAZON = 10000,
		ID_SEARCHLYRICS = 20000,
		ID_SEARCHLYRICSMASTER = 30000,
	};
};
//----------------------------------------------------------------------------

#endif