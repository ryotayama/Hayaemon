//----------------------------------------------------------------------------
// FreqLabel_MainWnd.h : �Đ����g���\���p���x���̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef FreqLabel_MainWndH
#define FreqLabel_MainWndH

class CApp;
class CMainWnd;
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/Edit.h"
#include "../Common/UpDownCtrl.h"
#include "RMenu_FreqCtrl.h"
#include "Edit_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �Đ����g���\���p���x���̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CFreqLabel_MainWnd : public CStatic
{
public: // �֐�

	CFreqLabel_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd),
		  m_edit(app, mainWnd, _T('.')), m_nDecimalDigit(1) { }
	virtual ~CFreqLabel_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void SetDecimalDigit(int nDecimalDigit);
	virtual void SetFreq(double nFreq);
	virtual void SetLimit(double dMinFreq, double dMaxFreq);

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CStatic m_percentLabel; // �u%�v�\���p���x��
	CFont m_font;
	CEdit_MainWnd m_edit;
	CUpDownCtrl m_ud;
	int m_nDecimalDigit; // �����_����
	CRMenu_FreqCtrl m_rClickMenu; // �E�N���b�N���j���[

public: // �����o�ϐ��̎擾�E�ݒ�

	const CEdit_MainWnd & GetEdit() const { return m_edit; }
	const CUpDownCtrl & GetUpDownCtrl() const { return m_ud; }
	int GetDecimalDigit() const { return m_nDecimalDigit; }
};
//----------------------------------------------------------------------------

#endif