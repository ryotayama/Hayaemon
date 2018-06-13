//----------------------------------------------------------------------------
// RMenu_ListView.cpp : �Đ����X�g�p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "../App.h"
#include "MainWnd.h"
#include "PlayListView_MainWnd.h"
#include "RMenu_ListView.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_ListView::Create(BOOL bOnItem)
{
	CMenu::CreatePopup();
	if(bOnItem) {
		m_copyMenu.CreatePopup();
		m_copyMenu.Append(MFS_ENABLED, ID_COPY,
#if JP
						  _T("�V�����v���C���X�g(&N)"));
#else // JP
						  _T("New Playlist(&N)"));
#endif // JP
		int nTabCount = m_rParent.GetMainWnd().GetTab().GetItemCount();
		if(nTabCount >= 2) m_copyMenu.AppendSeparator();
		for(int i = 0; i < nTabCount; i++) {
			if((HWND)m_rParent.GetMainWnd().GetPlayList(i) != (HWND)m_rParent)
				m_copyMenu.Append(MFS_ENABLED, ID_COPY + i + 1,
					m_rParent.GetMainWnd().GetTab().GetItemText(i).c_str());
		}
#if JP
		Append(MFS_ENABLED, ID_PLAY, _T("�Đ�(&P)"));
		Append(MFS_ENABLED, ID_DELETE, _T("�폜(&D)"));
#else // JP
		Append(MFS_ENABLED, ID_PLAY, _T("Play(&P)"));
		Append(MFS_ENABLED, ID_DELETE, _T("Delete(&D)"));
#endif // JP
		AppendSeparator();
		Append(MF_POPUP, (UINT_PTR)(HMENU)m_copyMenu,
#if JP
			_T("�I���t�@�C�����R�s�[(&C)"));
#else // JP
			_T("Copy Selected Files(&C)"));
#endif // JP

		BOOL bAdd = FALSE;
		std::vector<tstring> arArtists;
		int nItem = -1;
		while((nItem = m_rParent.GetMainWnd().GetPlayList().GetNextItem(nItem,
			LVNI_SELECTED)) >= 0) {
			TCHAR chArtist[255];
			m_rParent.GetMainWnd().GetPlayList().GetItemText(nItem, 3, chArtist,
				255);
			if(lstrcmp(chArtist, _T("")) != 0) {
				if(!bAdd) bAdd = TRUE, AppendSeparator();
				BOOL bExists = FALSE;
				for(int i = 0; i < (int)arArtists.size(); i++) {
					if(arArtists[i] == chArtist) {
						bExists = TRUE;
						break;
					}
				}
				if(!bExists) {
					arArtists.push_back(chArtist);
#if JP
					Append(MFS_ENABLED, ID_SEARCHITUNES + nItem,
						((tstring)chArtist +
						_T("��iTunes Store�ŃT�[�`(&I)")).c_str());
#else // JP
					Append(MFS_ENABLED, ID_SEARCHITUNES + nItem,
						((tstring)_T("Search ") + chArtist +
						_T(" by iTunes Store(&I)")).c_str());
#endif // JP
				}
			}
		}

		bAdd = FALSE;
		arArtists.clear();
		nItem = -1;
		while((nItem = m_rParent.GetMainWnd().GetPlayList().GetNextItem(nItem,
			LVNI_SELECTED)) >= 0) {
			TCHAR chArtist[255];
			m_rParent.GetMainWnd().GetPlayList().GetItemText(nItem, 3, chArtist,
				255);
			if(lstrcmp(chArtist, _T("")) != 0) {
				if(!bAdd) bAdd = TRUE, AppendSeparator();
				BOOL bExists = FALSE;
				for(int i = 0; i < (int)arArtists.size(); i++) {
					if(arArtists[i] == chArtist) {
						bExists = TRUE;
						break;
					}
				}
				if(!bExists) {
					arArtists.push_back(chArtist);
#if JP
					Append(MFS_ENABLED, ID_SEARCHAMAZON + nItem,
						((tstring)chArtist +
						_T("��Amazon�ŃT�[�`(&S)")).c_str());
#else // JP
					Append(MFS_ENABLED, ID_SEARCHAMAZON + nItem,
						((tstring)_T("Search ") + chArtist +
						_T(" by Amazon(&S)")).c_str());
#endif // JP
				}
			}
		}

		bAdd = FALSE;
		nItem = -1;
		while((nItem = m_rParent.GetMainWnd().GetPlayList().GetNextItem(nItem,
			LVNI_SELECTED)) >= 0) {
			TCHAR chTitle[255];
			m_rParent.GetMainWnd().GetPlayList().GetItemText(nItem, 2, chTitle,
				255);
			if(!bAdd) bAdd = TRUE, AppendSeparator();
#if JP
			Append(MFS_ENABLED, ID_SEARCHLYRICS + nItem, ((tstring)chTitle +
				_T("�̉̎����C���^�[�l�b�g�Ō���(&L)")).c_str());
#else // JP
			Append(MFS_ENABLED, ID_SEARCHLYRICS + nItem,
				((tstring)_T("Search Lyrics of ") + chTitle +
				_T(" by Internet(&S)")).c_str());
#endif // JP
		}

		bAdd = FALSE;
		nItem = -1;
		while((nItem = m_rParent.GetMainWnd().GetPlayList().GetNextItem(nItem,
			LVNI_SELECTED)) >= 0) {
			TCHAR chTitle[255];
			m_rParent.GetMainWnd().GetPlayList().GetItemText(nItem, 2, chTitle,
				255);
			if(!bAdd) bAdd = TRUE, AppendSeparator();
#if JP
			Append(MFS_ENABLED, ID_SEARCHLYRICSMASTER + nItem,
				((tstring)chTitle +
				_T("�̉̎���Lyrics Master�Ō���(&L)")).c_str());
#else // JP
			Append(MFS_ENABLED, ID_SEARCHLYRICSMASTER + nItem,
				((tstring)_T("Search Lyrics of ") + chTitle
				+ _T(" by Lyrics Master(&L)")).c_str());
#endif // JP
		}

		AppendSeparator();
		m_editTagMenu.CreatePopup();
#if JP
		m_editTagMenu.Append(MFS_ENABLED, ID_EDITTITLE, _T("�^�C�g��(&T)"));
		m_editTagMenu.Append(MFS_ENABLED, ID_EDITARTIST,
			_T("�A�[�e�B�X�g(&A)"));
		m_editTagMenu.Append(MFS_ENABLED, ID_EDITYEAR, _T("�N(&Y)"));
		Append(MF_POPUP, (UINT_PTR)(HMENU)m_editTagMenu, _T("�^�O�̕ҏW(&T)"));
		Append(MFS_ENABLED, ID_OPENFOLDER, _T("�t�H���_���J��(&O)"));
		Append(MFS_ENABLED, ID_PROPERTIES, _T("�v���p�e�B(&R)"));
#else // JP
		m_editTagMenu.Append(MFS_ENABLED, ID_EDITTITLE, _T("Title(&T)"));
		m_editTagMenu.Append(MFS_ENABLED, ID_EDITARTIST,
			_T("Artist(&A)"));
		m_editTagMenu.Append(MFS_ENABLED, ID_EDITYEAR, _T("Year(&Y)"));
		Append(MF_POPUP, (UINT_PTR)(HMENU)m_editTagMenu,
			_T("Edit the Tag(&T)"));
		Append(MFS_ENABLED, ID_OPENFOLDER, _T("Open Folder(&O)"));
		Append(MFS_ENABLED, ID_PROPERTIES, _T("Properties(&R)"));
#endif // JP
		AppendSeparator();
	}

#if JP
	Append(MF_CHECKED, ID_VISIBLE, _T("�Đ����X�g�̕\��(&V)"));
#else // JP
	Append(MF_CHECKED, ID_VISIBLE, _T("Show Play List(&S)"));
#endif // JP

	if(!m_hMenu) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnCommand(int id, HWND/* hwndCtl*/, UINT/* codeNotify*/)
{
	int nTabCount = m_rParent.GetMainWnd().GetTab().GetItemCount();
	if(ID_COPY <= id && id <= ID_COPY + nTabCount)
		OnCopyNewListMenuSelected(id);
	else if(id == ID_DELETE) OnDeleteMenuSelected();
	else if(id == ID_PLAY) OnPlayMenuSelected();
	else if(id == ID_EDITTITLE) OnEditTitleMenuSelected();
	else if(id == ID_EDITARTIST) OnEditArtistMenuSelected();
	else if(id == ID_EDITYEAR) OnEditYearMenuSelected();
	else if(id == ID_OPENFOLDER) OnOpenFolderMenuSelected();
	else if(id == ID_PROPERTIES) OnPropertiesMenuSelected();
	else if(id == ID_VISIBLE) OnVisibleMenuSelected();
	else if(ID_SEARCHITUNES <= id && id < ID_SEARCHAMAZON)
		OnSearchITunesMenuSelected(id);
	else if(ID_SEARCHAMAZON <= id && id < ID_SEARCHLYRICS)
		OnSearchAmazonMenuSelected(id);
	else if(ID_SEARCHLYRICS <= id && id < ID_SEARCHLYRICSMASTER)
		OnSearchLyricsMenuSelected(id);
	else if(ID_SEARCHLYRICSMASTER <= id)
		OnSearchLyricsMasterMenuSelected(id);
}
//----------------------------------------------------------------------------
// �I���t�@�C�����R�s�[���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnCopyNewListMenuSelected(int id)
{
	if(id == ID_COPY) m_rParent.CreateNewList();
	else {
		int nList = id - ID_COPY - 1;
		m_rParent.CopySelectedItem(nList);
	}
}
//----------------------------------------------------------------------------
// �폜���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnDeleteMenuSelected()
{
	m_rParent.GetMainWnd().GetPlayList().DeleteSelectedItems();
}
//----------------------------------------------------------------------------
// �Đ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnPlayMenuSelected()
{
	m_rParent.GetMainWnd().GetPlayList().PlaySelectedItem();
}
//----------------------------------------------------------------------------
// ���̃A�[�e�B�X�g��iTunes�ŃT�[�`���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnSearchITunesMenuSelected(int id)
{
	int nItem = id - ID_SEARCHITUNES;
	TCHAR chArtist[255];
	m_rParent.GetMainWnd().GetPlayList().GetItemText(nItem, 3, chArtist, 255);
#if JP
	ShellExecute(m_rParent.GetMainWnd(), _T("open"), ((tstring)_T("http://soft.edolfzoku.com/hayaemon2/itunes/") + chArtist).c_str(), NULL, NULL, SW_SHOWDEFAULT);
#else // JP
	ShellExecute(m_rParent.GetMainWnd(), _T("open"), ((tstring)_T("http://en.edolfzoku.com/hayaemon2/itunes/") + chArtist).c_str(), NULL, NULL, SW_SHOWDEFAULT);
#endif // JP
}
//----------------------------------------------------------------------------
// ���̃A�[�e�B�X�g��Amazon�ŃT�[�`���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnSearchAmazonMenuSelected(int id)
{
	int nItem = id - ID_SEARCHAMAZON;
	TCHAR chArtist[255];
	m_rParent.GetMainWnd().GetPlayList().GetItemText(nItem, 3, chArtist, 255);
#if JP
	ShellExecute(m_rParent.GetMainWnd(), _T("open"), ((tstring)_T("http://www.amazon.co.jp/gp/search?ie=UTF8&camp=247&creative=1211&index=aps&keywords=") + chArtist + _T("&linkCode=ur2&tag=edolfzoku-22")).c_str(), NULL, NULL, SW_SHOWDEFAULT);
#else // JP
	ShellExecute(m_rParent.GetMainWnd(), _T("open"), ((tstring)_T("http://www.amazon.com/gp/search?ie=UTF8&camp=247&creative=1211&index=aps&keywords=") + chArtist + _T("&linkCode=ur2&tag=edolfzoku-22")).c_str(), NULL, NULL, SW_SHOWDEFAULT);
#endif // JP
}
//----------------------------------------------------------------------------
// �̎����C���^�[�l�b�g�Ō������j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnSearchLyricsMenuSelected(int id)
{
	int nItem = id - ID_SEARCHLYRICS;
	TCHAR chTitle[255];
	TCHAR chArtist[255];
	m_rParent.GetMainWnd().GetPlayList().GetItemText(nItem, 2, chTitle, 255);
	m_rParent.GetMainWnd().GetPlayList().GetItemText(nItem, 3, chArtist, 255);
#if JP
	ShellExecute(m_rParent.GetMainWnd(), _T("open"), ((tstring)_T("https://www.google.co.jp/search?q=") + chArtist + _T("+") + chTitle + _T("+�̎�")).c_str(), NULL, NULL, SW_SHOWDEFAULT);
#else // JP
	ShellExecute(m_rParent.GetMainWnd(), _T("open"), ((tstring)_T("https://www.google.com/search?q=") + chArtist + _T("+") + chTitle + _T("+�̎�")).c_str(), NULL, NULL, SW_SHOWDEFAULT);
#endif // JP
}
//----------------------------------------------------------------------------
// �̎���Lyrics Master�Ō������j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnSearchLyricsMasterMenuSelected(int id)
{
	tstring initFilePath = m_rParent.GetApp().GetFilePath() + _T("Setting.ini");

	TCHAR chPath[MAX_PATH];
	GetPrivateProfileString(_T("Option"), _T("LyricsMasterPath"), _T(""),
		chPath, MAX_PATH, initFilePath.c_str());
	if(_tcsicmp(chPath, _T("")) == 0) {
		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hInstance = GetModuleHandle(NULL);
		ofn.hwndOwner = m_rParent.GetMainWnd();
#if JP
		ofn.lpstrTitle = _T("ExtSupport.js��I�����ĉ������B");
		ofn.lpstrFilter = _T("JScript �t�@�C��(*.js)\0*.js\0\0");
#else // JP
		ofn.lpstrTitle = _T("Select ExtSupport.js");
		ofn.lpstrFilter = _T("JScript file(*.js)\0*.js\0\0");
#endif // JP
		ofn.lpstrFile = chPath;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER;

		if(GetOpenFileName(&ofn))
			WritePrivateProfileString(_T("Option"), _T("LyricsMasterPath"),
				chPath, initFilePath.c_str());
	}

	int nItem = id - ID_SEARCHLYRICSMASTER;
	TCHAR chTitle[255];
	TCHAR chArtist[255];
	m_rParent.GetMainWnd().GetPlayList().GetItemText(nItem, 2, chTitle, 255);
	m_rParent.GetMainWnd().GetPlayList().GetItemText(nItem, 3, chArtist, 255);
	tstring strFile = _T("C:\\Windows\\System32\\wscript.exe");
	tstring strParam = (tstring)_T("\"") + chPath + _T("\" multi \"") +
		chTitle + _T("\" \"") + chArtist + _T("\"");
	ShellExecute(m_rParent.GetMainWnd(), _T("open"),
		strFile.c_str(), strParam.c_str(), NULL, SW_SHOWDEFAULT);
}
//----------------------------------------------------------------------------
// �^�C�g���^�O�̕ҏW���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnEditTitleMenuSelected()
{
	int nItem = m_rParent.GetMainWnd().GetPlayList().GetNextItem(-1,
		LVNI_SELECTED);
	m_rParent.GetMainWnd().GetPlayList().SetItemNum(nItem);
	m_rParent.GetMainWnd().GetPlayList().SetSubItemNum(2);
	m_rParent.GetMainWnd().GetPlayList().StartTagEdit();
}
//----------------------------------------------------------------------------
// �A�[�e�B�X�g�^�O�̕ҏW���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnEditArtistMenuSelected()
{
	int nItem = m_rParent.GetMainWnd().GetPlayList().GetNextItem(-1,
		LVNI_SELECTED);
	m_rParent.GetMainWnd().GetPlayList().SetItemNum(nItem);
	m_rParent.GetMainWnd().GetPlayList().SetSubItemNum(3);
	m_rParent.GetMainWnd().GetPlayList().StartTagEdit();
}
//----------------------------------------------------------------------------
// �N�^�O�̕ҏW���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnEditYearMenuSelected()
{
	int nItem = m_rParent.GetMainWnd().GetPlayList().GetNextItem(-1,
		LVNI_SELECTED);
	m_rParent.GetMainWnd().GetPlayList().SetItemNum(nItem);
	m_rParent.GetMainWnd().GetPlayList().SetSubItemNum(4);
	m_rParent.GetMainWnd().GetPlayList().StartTagEdit();
}
//----------------------------------------------------------------------------
// �t�H���_���J�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnOpenFolderMenuSelected()
{
	m_rParent.GetMainWnd().GetPlayList().OpenFolder();
}
//----------------------------------------------------------------------------
// �v���p�e�B���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnPropertiesMenuSelected()
{
	m_rParent.GetMainWnd().GetPlayList().ShowProperties();
}
//----------------------------------------------------------------------------
// �Đ����X�g�̕\�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CRMenu_ListView::OnVisibleMenuSelected()
{
	m_rParent.GetMainWnd().GetMenu().OnPlayListMenuSelected();
}
//----------------------------------------------------------------------------
