//----------------------------------------------------------------------------
// VolumeLabel_MainWnd.h : ���ʕ\���p���x���̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef VolumeLabel_MainWndH
#define VolumeLabel_MainWndH

class CApp;
class CMainWnd;
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/Edit.h"
#include "../Common/UpDownCtrl.h"
#include "RMenu_VolumeCtrl.h"
#include "Edit_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ���ʕ\���p���x���̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CVolumeLabel_MainWnd : public CStatic
{
public: // �֐�

	CVolumeLabel_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd),
		  m_edit(app, mainWnd, _T('.')) { }
	virtual ~CVolumeLabel_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void SetVolume(double nVolume);
	virtual void ResetPos();

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual void OnVScroll(HWND hwndCtl, UINT code, int pos);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CStatic m_percentLabel; // �u%�v�\���p���x��
	CFont m_font;
	CEdit_MainWnd m_edit;
	CUpDownCtrl m_ud;
	CRMenu_VolumeCtrl m_rClickMenu; // �E�N���b�N���j���[

public: // �����o�ϐ��̎擾�E�ݒ�

	const CEdit_MainWnd & GetEdit() const { return m_edit; }
};
//----------------------------------------------------------------------------

#endif