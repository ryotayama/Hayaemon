//----------------------------------------------------------------------------
// PlayListView_MainWnd.h : �v���C���X�g�p���X�g�r���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef PlayListView_MainWndH
#define PlayListView_MainWndH

#pragma warning(disable: 4355)
	// 'this' : �x�[�X �����o���������X�g�Ŏg�p����܂����B
#include <vector>
class CApp;
class CMainWnd;
#include "RMenu_ListView.h"
#include "../Common/ListView.h"
#include "../Common/mp3infp_ExportFunc.h"
#include "../Common/EditExt.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �^�O�ҏW�p�G�f�B�b�g�{�b�N�X�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CTagEdit : public CEditExt
{
public: // �֐�
	CTagEdit(CWnd & parent):CEditExt(parent) { }
	virtual ~CTagEdit() { }

	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
};
//----------------------------------------------------------------------------
// �v���C���X�g�p���X�g�r���[�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CPlayListView_MainWnd : public CListView
{
public: // �֐�

	CPlayListView_MainWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CPlayListView_MainWnd() {
		FreeLibrary(hMp3infpDll);
	}

	virtual void AddDirectory(LPCTSTR lpszDirectoryPath);
	virtual void AddFile(LPCTSTR lpszFilePath, int nPos = -1);
	virtual void AddFile(LPCTSTR lpszFilePath, int nPos, LPCTSTR lpszTitle,
						 LPCTSTR lpszArtist, LPCTSTR lpszYear,
						 LPCTSTR lpszLength);
	virtual void AddURL(LPCTSTR lpszFilePath, int nPos = -1);
	virtual void CopySelectedItem(int nDst);
	virtual BOOL Create();
	virtual void CreateNewList();
	virtual BOOL DeleteAllItems();
	virtual void DeleteSelectedItems();
	virtual void Delete(int nItem);
	virtual void EndTagEdit();
	virtual int GetMaxPlayOrder() const;
	virtual void PlaySelectedItem();
	virtual void SetPlaying(int iItem);
	virtual void SetPausing(int iItem);
	virtual void SetPlayOrder(int iItem);
	virtual void SetPlayOrder(int iItem, int nOrder);
	virtual void ClearPlayOrder();
	virtual void FixPlayOrder(int iItem);
	virtual int GetClosestItem(int x, int y);
	virtual int GetMinSize();
	virtual void InitSize();
	virtual void OpenFolder();
	virtual void ResetPos();
	virtual void ResetSize();
	virtual void ResetWidth();
	virtual void ResetNumber();
	virtual void ScrollToItem(int nItem);
	virtual void SaveTag();
	virtual void ShowProperties();
	virtual void SelectAll();
	virtual void Sort(NMLISTVIEW* pnmlv);
	virtual void StartTagEdit();
	virtual void UpdateItemInfo(int nItem);

	static int CALLBACK SortProc(LPARAM lp1, LPARAM lp2, LPARAM lp3);

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnCustomDraw(NMLVCUSTOMDRAW *pnmlvcd);
	virtual void OnBeginDrag(NM_LISTVIEW *pnmlv);
	virtual LRESULT OnBeginLabelEdit(NM_LISTVIEW *pnmlv);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnDropFiles(HDROP hdrop);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnLButtonDoubleClick(int x, int y, UINT keyFlags);
	virtual void OnLButtonUp(int x, int y, UINT keyFlags);
	virtual void OnMouseMove(int x, int y, UINT keyFlags);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);
	virtual void OnEscKeyPressed();
	virtual void OnReturnKeyPressed();
	virtual void OnUpKeyPressed();
	virtual void OnDownKeyPressed();
	virtual void OnLeftKeyPressed();
	virtual void OnRightKeyPressed();

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	int m_nHeaderHeight;
	int lastSort; // �O��\�[�g�����C���f�b�N�X
	BOOL isLastSortUp; // �O��̃\�[�g��������������
	std::vector<int> orders; // �Đ���
	HIMAGELIST hSmall;
	int m_nLastItem;
	int m_nItem;
	int m_nSubItem;
	tstring m_strTag;
	int m_nAccel;
	ACCEL* m_pAccel;

	CRMenu_ListView m_rClickMenu; // �E�N���b�N���j���[
	CFont m_font;
	CTagEdit m_edit;

	HMODULE hMp3infpDll;
	LPMP3INFP_LOAD lpmp3infp_Load;
	LPMP3INFP_SETCONF lpmp3infp_SetConf;
	LPMP3INFP_GETTYPE lpmp3infp_GetType;
	LPMP3INFP_GETVALUE lpmp3infp_GetValue;
	LPMP3INFP_MP3_GETTAGTYPE lpmp3infp_mp3_GetTagType;
	LPMP3INFP_SETVALUE lpmp3infp_SetValue;
	LPMP3INFP_SAVE lpmp3infp_Save;
	LPMP3INFP_MP3_MAKEID3V1 lpmp3infp_mp3_MakeId3v1;
	LPMP3INFP_MP3_MAKEID3V2 lpmp3infp_mp3_MakeId3v2;
	LPMP3INFP_MP3_MAKERMP lpmp3infp_mp3_MakeRMP;
	LPMP3INFP_MP3_MAKEAPETAG lpmp3infp_mp3_MakeApeTag;

public: // �����o�ϐ��̎擾�E�ݒ�

	virtual std::vector<int> GetOrders() const
	{
		return orders;
	}
	CApp & GetApp() { return m_rApp; }
	CMainWnd & GetMainWnd() { return m_rMainWnd; }
	void SetItemNum(int nItem) { m_nItem = nItem; }
	void SetSubItemNum(int nItem) { m_nSubItem = nItem; }
};
//----------------------------------------------------------------------------

#endif