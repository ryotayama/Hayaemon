//----------------------------------------------------------------------------
// Explorer.cpp : �G�N�X�v���[���̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include <shobjidl.h>
#include <shlwapi.h>
#include <TCHAR.H>
#include <vector>
#include "../Common/Utils.h"
#include "../resource.h"
#include "../App.h"
#include "MainWnd.h"
#include "Explorer.h"

typedef struct _tagSORTDATA{
    HWND hwndList; // ���X�g�r���[��hwnd
	int isortSubItem; // �\�[�g����T�u�A�C�e���C���f�b�N�X
    int iUPDOWN; // �������~����
} SORTDATA;
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CExplorer::Create()
{
	CListView::Create(m_rMainWnd);
	if(!m_hWnd) return FALSE;
	SetStyle(GetStyle() | LVS_SHAREIMAGELISTS | LVS_AUTOARRANGE);
	SetExtendedStyle(GetExtendedStyle() & ~LVS_EX_GRIDLINES
		| WS_EX_ACCEPTFILES);

	ResetPos();

	POINT pt;
	pt.y = GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nHeight = m_rMainWnd.GetClientHeight() - pt.y;
	SetSize(240, nHeight);

#if JP
	InsertColumn(0, _T("���O"), LVCFMT_LEFT, 100, 0);
	InsertColumn(1, _T("�X�V����"), LVCFMT_LEFT, 80, 1);
	InsertColumn(2, _T("���"), LVCFMT_LEFT, 80, 2);
	InsertColumn(3, _T("�T�C�Y"), LVCFMT_RIGHT, 80, 3);
#else // JP
	InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100, 0);
	InsertColumn(1, _T("Date Modified"), LVCFMT_LEFT, 80, 1);
	InsertColumn(2, _T("Type"), LVCFMT_LEFT, 80, 2);
	InsertColumn(3, _T("Size"), LVCFMT_RIGHT, 80, 3);
#endif // JP

	HIMAGELIST hImgS, hImgN;
	SHFILEINFO sfi;
	hImgS = (HIMAGELIST)SHGetFileInfo(_T("C:\\"), 0, &sfi,
		sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	hImgN = (HIMAGELIST)SHGetFileInfo(_T("C:\\"), 0, &sfi,
		sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_LARGEICON);

	if(hImgS && hImgN) {
		SetImageList(hImgS, LVSIL_SMALL);
		SetImageList(hImgN, LVSIL_NORMAL);
	}

	InsertItem(0);
	RECT rc;
	GetItemRect(0, &rc, LVIR_BOUNDS);
	m_nHeaderHeight = rc.top;
	DeleteItem(0);

	ShowFiles();

	return TRUE;
}
//----------------------------------------------------------------------------
// ���𓾂�
//----------------------------------------------------------------------------
int CExplorer::GetWidth() const
{
	if(m_rMainWnd.GetMenu().IsItemChecked(ID_EXPLORER))
		return CListView::GetWidth();
	else return 0;
}
//----------------------------------------------------------------------------
// �I�𒆂̃t�@�C�����J��
//----------------------------------------------------------------------------
void CExplorer::OpenFiles(BOOL bClear)
{
	int nItem = -1;
	BOOL bAdd = FALSE;
	while((nItem = GetNextItem(nItem, LVNI_SELECTED)) >= 0) {
		if(!bAdd) {
			if(bClear) {
				m_rMainWnd.ChangeCurPlayTab();
				m_rMainWnd.GetPlayList().DeleteAllItems();
			}
			m_rMainWnd.AddFile(filePaths[nItem].c_str());
		}
		else m_rMainWnd.AddFile(filePaths[nItem].c_str());
		bAdd = TRUE;
	}
	if(bAdd && bClear) {
		m_rMainWnd.GetSound().SetCurFileNum(0);
		m_rMainWnd.PlayNext(TRUE, FALSE);
		m_rMainWnd.SetPreviousNextMenuState();
	}
	m_rMainWnd.StartUpdateInfo();
}
//----------------------------------------------------------------------------
// �t�H���_���J��
//----------------------------------------------------------------------------
void CExplorer::OpenFolder()
{
	int nItem = -1;
	while((nItem = GetNextItem(nItem, LVNI_SELECTED)) >= 0) {
		TCHAR chPath[_MAX_PATH];
		lstrcpy(chPath, filePaths[nItem].c_str());
		PathRemoveFileSpec(chPath);
		SHELLEXECUTEINFO sei;
		ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));
		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		sei.lpFile = chPath;
		sei.nShow = SW_SHOW;
		sei.fMask = NULL;
		sei.lpVerb = _T("open");
		ShellExecuteEx(&sei);
	}
}
//----------------------------------------------------------------------------
// �I�𒆂̃f�B���N�g�����J��
//----------------------------------------------------------------------------
BOOL CExplorer::OpenDirectory()
{
	int itemNum = GetNextItem(-1, LVNI_SELECTED);
	if(itemNum < 0) return FALSE;

	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(filePaths[itemNum].c_str(), &wfd);
	if(hFind == INVALID_HANDLE_VALUE) return FALSE;
	FindClose(hFind);
	if(!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) return FALSE;

	// �J�`�b�Ƃ�������炷
	HKEY hKey;
	RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("AppEvents\\Schemes\\Apps\\Explorer\\Navigating\\.Current"), 0, KEY_QUERY_VALUE, &hKey);
	TCHAR filePath[MAX_PATH];
	DWORD size = MAX_PATH;
	RegQueryValueEx(hKey, _T(""), NULL, NULL, (LPBYTE)filePath, &size);
	RegCloseKey(hKey);
	PlaySound(filePath, NULL, SND_ALIAS | SND_ASYNC);

	SetCurrentDirectory(filePaths[itemNum].c_str());
	ShowFiles();
	return TRUE;
}
//----------------------------------------------------------------------------
// �ʒu�̍Đݒ�
//----------------------------------------------------------------------------
void CExplorer::ResetPos()
{
	POINT pt;
	pt.y = m_rMainWnd.GetExplorerBar().GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	SetPos(0, pt.y + m_rMainWnd.GetExplorerBar().GetHeight());
}
//----------------------------------------------------------------------------
// �T�C�Y�̍Đݒ�
//----------------------------------------------------------------------------
void CExplorer::ResetSize()
{
	POINT pt;
	pt.y = GetTop();
	ScreenToClient(m_rMainWnd, &pt);
	int nHeight = m_rMainWnd.GetClientHeight() - pt.y;
	SetSize(IsWindowVisible(m_hWnd) ? GetWidth() : 240, nHeight);
}
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �A�C�R���̐ݒ�
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void CExplorer::SetIcon(NMLVDISPINFO * pnmlvdi)
{
	// �t�@�C���ւ̐�΃p�X
	TCHAR filePath[MAX_PATH + _MAX_FNAME];
	lstrcpy(filePath, filePaths[pnmlvdi->item.iItem].c_str());

	// �A�C�R���̐ݒ�
	SHFILEINFO shFileInfo;
	SHGetFileInfo(filePath, 0, &shFileInfo, sizeof(shFileInfo),
		SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_ATTRIBUTES);
	pnmlvdi->item.iImage = shFileInfo.iIcon;

	// ����t�@�C���̐ݒ�
	pnmlvdi->item.stateMask = pnmlvdi->item.state = 0;
	if(shFileInfo.dwAttributes & SFGAO_LINK) {
		// �V���[�g�J�b�g�t�@�C��
		pnmlvdi->item.mask |= LVIF_STATE;
		pnmlvdi->item.stateMask |= LVIS_OVERLAYMASK;
		pnmlvdi->item.state |= INDEXTOOVERLAYMASK(2);
	}
	if(shFileInfo.dwAttributes & SFGAO_SHARE) {
		// ���L�t�@�C��
		pnmlvdi->item.mask |= LVIF_STATE;
		pnmlvdi->item.stateMask |= LVIS_OVERLAYMASK;
		pnmlvdi->item.state |= INDEXTOOVERLAYMASK(1);
	}
	if(shFileInfo.dwAttributes & SFGAO_GHOSTED) {
		// �B���t�@�C��
		pnmlvdi->item.mask |= LVIF_STATE;
		pnmlvdi->item.stateMask |= LVIS_CUT;
		pnmlvdi->item.state |= LVIS_CUT;
	}
}
//----------------------------------------------------------------------------
// �t�@�C���̕\��
//----------------------------------------------------------------------------
BOOL CExplorer::ShowFiles()
{
	m_rMainWnd.GetExplorerBar().GetEdit().SetText(_T(""));
	DeleteAllItems();

	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(TEXT("*.*"), &wfd);
	if(hFind == INVALID_HANDLE_VALUE) return FALSE;

	TCHAR chPath[255];
	GetCurrentDirectory(255, chPath);
	m_rMainWnd.GetExplorerBar().GetEdit().SetText(chPath);

	// �t�@�C���̗񋓃��[�v
	int i = 0;
	filePaths.clear();
	do {
		if(_tcscmp(wfd.cFileName, _T(".")) == 0
			|| _tcscmp(wfd.cFileName, _T("..")) == 0)
			continue;

		// �t�@�C���̃p�X��ێ����Ă���
		TCHAR filePath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, filePath);
		tstring str = filePath;
		if(str.substr(str.size()-1,1) != _T("\\"))
			lstrcat(filePath, TEXT("\\"));
		lstrcat(filePath, wfd.cFileName);

		TCHAR ext[_MAX_EXT];
		_tsplitpath_s(filePath, NULL, 0, NULL, 0, NULL, 0, ext, _MAX_EXT);

		if(!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			lstrcmpi(ext, _T(".wav")) != 0 && lstrcmpi(ext, _T(".cda")) != 0 &&
			lstrcmpi(ext, _T(".mp3")) != 0 && lstrcmpi(ext, _T(".mp2")) != 0 &&
			lstrcmpi(ext, _T(".mp1")) != 0 && lstrcmpi(ext, _T(".ogg")) != 0 &&
			lstrcmpi(ext, _T(".wma")) != 0 && lstrcmpi(ext, _T(".aiff")) != 0 &&
			lstrcmpi(ext, _T(".aif")) != 0 && lstrcmpi(ext, _T(".ape")) != 0 &&
			lstrcmpi(ext, _T(".flac")) != 0 && lstrcmpi(ext, _T(".m4a")) != 0 &&
			lstrcmpi(ext, _T(".m4b")) != 0 &&
			lstrcmpi(ext, _T(".mp4")) != 0 && lstrcmpi(ext, _T(".aac")) != 0 &&
			lstrcmpi(ext, _T(".avi")) != 0 && lstrcmpi(ext, _T(".wmv")) != 0 &&
			lstrcmpi(ext, _T(".mkv")) != 0 && lstrcmpi(ext, _T(".flv")) != 0 &&
			lstrcmpi(ext, _T(".ini")) != 0 && lstrcmpi(ext, _T(".m3u")) != 0 &&
			lstrcmpi(ext, _T(".m3u8")) != 0)
			continue;

		// ���������t�@�C���p�ɐV�A�C�e����ǉ�
		InsertItem(i, I_IMAGECALLBACK, LPSTR_TEXTCALLBACK);

		filePaths.push_back(filePath);

		i++;
	}
	while(FindNextFile(hFind, &wfd));
	FindClose(hFind);
	return TRUE;
}
//----------------------------------------------------------------------------
// �I�𒆂̃A�C�e���̃v���p�e�B��\��
//----------------------------------------------------------------------------
void CExplorer::ShowProperties()
{
	int nItem = -1;
	while((nItem = GetNextItem(nItem, LVNI_SELECTED)) >= 0) {
		SHELLEXECUTEINFO sei;
		ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));
		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		sei.lpFile = filePaths[nItem].c_str();
		sei.nShow = SW_SHOW;
		sei.fMask = SEE_MASK_INVOKEIDLIST;
		sei.lpVerb = _T("properties");
		ShellExecuteEx(&sei);
	}
}
//----------------------------------------------------------------------------
// �\�[�g
//----------------------------------------------------------------------------
void CExplorer::Sort(NMLISTVIEW* pnmlv)
{
	if(pnmlv->iSubItem == 0 || pnmlv->iSubItem == 1) return;
	SORTDATA sortData;
	sortData.hwndList = m_hWnd;
	sortData.isortSubItem = pnmlv->iSubItem;
	if(lastSort == pnmlv->iSubItem && isLastSortUp) {
		// �~��
		sortData.iUPDOWN = 2;
		isLastSortUp = FALSE;
	}
	else {
		// ����
		sortData.iUPDOWN = 1;
		isLastSortUp = TRUE;
	}
	lastSort = pnmlv->iSubItem;
	ListView_SortItemsEx(m_hWnd, CExplorer::SortProc, &sortData);
}
//----------------------------------------------------------------------------
// �\�[�g�p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
int CALLBACK CExplorer::SortProc(LPARAM lp1, LPARAM lp2, LPARAM lp3)
{
	TCHAR szItemText1[_MAX_PATH];
	TCHAR szItemText2[_MAX_PATH];

	SORTDATA* sortData = (SORTDATA *)lp3;
	HWND hCtlLView = (HWND)sortData->hwndList;

	ListView_GetItemText(hCtlLView, lp1, sortData->isortSubItem, szItemText1,
		sizeof(szItemText1));
	ListView_GetItemText(hCtlLView, lp2, sortData->isortSubItem, szItemText2, 
		sizeof(szItemText2));

	return lstrcmpi(szItemText1, szItemText2) * (sortData->iUPDOWN == 2 ? -1 : 1);
}
//----------------------------------------------------------------------------
// �h���b�O���J�n���ꂽ
//----------------------------------------------------------------------------
void CExplorer::OnBeginDrag(NM_LISTVIEW *pnmlv)
{
	SetCursor(LoadCursor(GetModuleHandle(NULL), (LPCTSTR)IDC_DRAG_MOVE));
	SetCapture(m_hWnd);
}
//----------------------------------------------------------------------------
// �R�}���h
//----------------------------------------------------------------------------
void CExplorer::OnCommand(int id, HWND hwndCtl, UINT codeNotify)
{
	if(!hwndCtl) m_rClickMenu.OnCommand(id, hwndCtl, codeNotify);
	CListView::OnCommand(id, hwndCtl, codeNotify);
}
//----------------------------------------------------------------------------
// �R���e�L�X�g���j���[
//----------------------------------------------------------------------------
LRESULT CExplorer::OnContextMenu(HWND hwnd, int xPos, int yPos)
{
	POINT pt;
	pt.x = xPos;
	pt.y = yPos;
	LV_HITTESTINFO lvhtst;
	lvhtst.pt = pt;
	ScreenToClient(m_hWnd, &lvhtst.pt);
	ListView_HitTest(m_hWnd, &lvhtst);
	if(lvhtst.flags & LVHT_ONITEM && lvhtst.pt.y > m_nHeaderHeight)
		m_rClickMenu.Create(TRUE);
	else m_rClickMenu.Create(FALSE);
	SetForegroundWindow(m_hWnd);
	TrackPopupMenu((HMENU)m_rClickMenu,
					TPM_LEFTALIGN | TPM_TOPALIGN, xPos, yPos, 0,
					m_hWnd, NULL);
	return CListView::OnContextMenu(hwnd, xPos, yPos);
}
//----------------------------------------------------------------------------
// �t�@�C�����h���b�v���ꂽ
//----------------------------------------------------------------------------
void CExplorer::OnDropFiles(HDROP hdrop)
{
	CListView::OnDropFiles(hdrop);
}
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �\���̗v��
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void CExplorer::OnGetDispInfo(NMHDR* pnmhdr)
{
	NMLVDISPINFO * pnmlvdi = (NMLVDISPINFO*)pnmhdr;

	if(pnmlvdi->item.mask & LVIF_TEXT) {
		TCHAR filePath[MAX_PATH + _MAX_FNAME];
		lstrcpy(filePath, filePaths[pnmlvdi->item.iItem].c_str());
		switch(pnmlvdi->item.iSubItem)
		{
		case 0: // �t�@�C���̖��O��ݒ�
		{
			TCHAR fileName[_MAX_FNAME];
			GetFileTitle(filePath, fileName, _MAX_FNAME);
			lstrcpy(pnmlvdi->item.pszText, fileName);
			break;
		}
		case 1: // �t�@�C���̍X�V������ݒ�
		{
			tstring strTime = _T("");
			WIN32_FIND_DATA wfd;
			HANDLE hFind = FindFirstFile(filePath, &wfd);
			if(hFind != INVALID_HANDLE_VALUE) {
				SYSTEMTIME systemTime;
				FILETIME fileTime;
				FileTimeToLocalFileTime(&wfd.ftLastWriteTime, &fileTime);
				FindClose(hFind);
				FileTimeToSystemTime(&fileTime, &systemTime);
				TCHAR ch[MAX_PATH];
				wsprintf(ch, _T("%02d/%02d/%02d %02d:%02d"),
					systemTime.wYear, systemTime.wMonth, systemTime.wDay,
					systemTime.wHour, systemTime.wMinute);
				strTime = ch;
			}

			lstrcpy(pnmlvdi->item.pszText, strTime.c_str());
			break;
		}
		case 2: // �t�@�C���̎�ނ�ݒ�
		{
			SHFILEINFO shFileInfo;
			SHGetFileInfo(filePath, 0, &shFileInfo, sizeof(shFileInfo),
				SHGFI_TYPENAME);
			lstrcpy(pnmlvdi->item.pszText, shFileInfo.szTypeName);
			break;
		}
		case 3: // �t�@�C���̃T�C�Y��ݒ�
		{
			tstring fileSize = CUtils::GetFileSize_KB(filePath);
			lstrcpy(pnmlvdi->item.pszText, fileSize.c_str());
			break;
		}
		}
	}

	if(pnmlvdi->item.mask & LVIF_IMAGE)
		SetIcon(pnmlvdi);
}
//----------------------------------------------------------------------------
// �L�[�{�[�h�������ꂽ
//----------------------------------------------------------------------------
void CExplorer::OnKeyDown(UINT vk, int cRepeat, UINT flags)
{
	if(vk == VK_RETURN) {
		if(!OpenDirectory()) OpenFiles(GetKeyState(VK_CONTROL) >= 0);
	}
	else if(vk == VK_BACK) {
		TCHAR chPath[255];
		GetCurrentDirectory(255, chPath);
		tstring str = chPath;
		if(str.substr(str.size()-1,1) == _T("\\"))
			str = str.substr(0, str.size()-1);
		lstrcpy(chPath, str.c_str());
		PathRemoveFileSpec(chPath);
		SetCurrentDirectory(chPath);
		ShowFiles();
	}
	CListView::OnKeyDown(vk, cRepeat, flags);
}
//----------------------------------------------------------------------------
// �_�u���N���b�N���ꂽ
//----------------------------------------------------------------------------
void CExplorer::OnLButtonDoubleClick(int x, int y, UINT keyFlags)
{
	if(!OpenDirectory()) OpenFiles(GetKeyState(VK_CONTROL) >= 0);

	CListView::OnLButtonDoubleClick(x, y, keyFlags);
}
//----------------------------------------------------------------------------
// ���N���b�N�������ꂽ
//----------------------------------------------------------------------------
void CExplorer::OnLButtonUp(int x, int y, UINT keyFlags)
{
	if(GetCapture() == m_hWnd) {
		ReleaseCapture();
		if(x > GetWidth()) {
			POINT pt;
			pt.y = m_rMainWnd.GetPlayList().GetTop();
			ScreenToClient(m_rMainWnd, &pt);
			OpenFiles(y < pt.y);
		}
	}
}
//----------------------------------------------------------------------------
// �R�����R���g���[������̒ʒm������
//----------------------------------------------------------------------------
LRESULT CExplorer::OnNotify(int idFrom, NMHDR* pnmhdr)
{
	return CListView::OnNotify(idFrom, pnmhdr);
}
//----------------------------------------------------------------------------
