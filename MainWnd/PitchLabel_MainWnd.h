//----------------------------------------------------------------------------
// PitchLabel_MainWnd.h : �����\���p���x���̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef PitchLabel_MainWndH
#define PitchLabel_MainWndH

class CApp;
class CMainWnd;
#include "../Common/Static.h"
#include "../Common/Font.h"
#include "../Common/Edit.h"
#include "../Common/UpDownCtrl.h"
#include "RMenu_PitchCtrl.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �����\���p���x���p�G�f�B�b�g�{�b�N�X�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CEdit_PitchLabel : public CEdit
{
public: // �֐�

	CEdit_PitchLabel(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd) { }
	virtual ~CEdit_PitchLabel() { }

	virtual void OnChar(TCHAR ch, int cRepeat) {
		DWORD dwSel;
		SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&dwSel, (LPARAM)NULL);
		tstring strText = GetText();
		if(dwSel != 0 && ch == '.' && strText.find(_T(".")) == -1)
			CEdit::OnChar(ch, cRepeat);
		else if(dwSel == 0 && ch == '-' && strText.find(_T("-")) == -1)
			CEdit::OnChar(ch, cRepeat);
		else if(IsCharAlphaNumeric(ch) && !IsCharAlpha(ch))
			CEdit::OnChar(ch, cRepeat);
		else if(ch == _T('\b'))
			CEdit::OnChar(ch, cRepeat);
		else if(ch == _T('\t'))
			return;
		else
			MessageBeep(MB_OK);
	}
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
};
//----------------------------------------------------------------------------
// �����\���p���x���̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CPitchLabel_MainWnd : public CStatic
{
public: // �֐�

	CPitchLabel_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd),
		  m_edit(app, mainWnd), m_nDecimalDigit(1) { }
	virtual ~CPitchLabel_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void SetDecimalDigit(int nDecimalDigit);
	virtual void SetPitch(double nPitch);
	virtual void SetLimit(double dMinPitch, double dMaxPitch);

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual LRESULT OnContextMenu(HWND hwnd, int xPos, int yPos);
	virtual LRESULT OnNotify(int idFrom, NMHDR* pnmhdr);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CFont m_font;
	CEdit_PitchLabel m_edit;
	CUpDownCtrl m_ud;
	int m_nDecimalDigit; // �����_����
	CRMenu_PitchCtrl m_rClickMenu; // �E�N���b�N���j���[

public: // �����o�ϐ��̎擾�E�ݒ�

	const CEdit_PitchLabel & GetEdit() const { return m_edit; }
	const CUpDownCtrl & GetUpDownCtrl() const { return m_ud; }
	int GetDecimalDigit() const { return m_nDecimalDigit; }
};
//----------------------------------------------------------------------------

#endif