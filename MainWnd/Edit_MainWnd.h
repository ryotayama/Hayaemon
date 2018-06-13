//----------------------------------------------------------------------------
// Edit_MainWnd.h : ���C���E�B���h�E�p�G�f�B�b�g�{�b�N�X�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef Edit_MainWndH
#define Edit_MainWndH

class CApp;
class CMainWnd;
#include "../Common/Define.h"
#include "../Common/Edit.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ���C���E�B���h�E�p�G�f�B�b�g�{�b�N�X�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CEdit_MainWnd : public CEdit
{
public: // �֐�

	CEdit_MainWnd(CApp & app, CMainWnd & mainWnd, TCHAR ch)
		: m_rApp(app), m_rMainWnd(mainWnd), chAllow(ch), m_nDecimalDigit(1)
	{ }
	virtual ~CEdit_MainWnd() { }

	virtual void OnChar(TCHAR ch, int cRepeat) {
		DWORD dwSel;
		SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&dwSel, (LPARAM)NULL);
		tstring strText = GetText();
		if(chAllow == _T('-') && dwSel == 0 && ch == chAllow
		   && strText.find(_T('-')) == -1)
			CEdit::OnChar(ch, cRepeat);
		else if(chAllow == _T('.') && dwSel != 0 && ch == chAllow
		   && strText.find(_T('.')) == -1)
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
	TCHAR chAllow;
	int m_nDecimalDigit;

public: // �����o�ϐ��̎擾�E�ݒ�
	void SetDecimalDigit(int n) { m_nDecimalDigit = n; }
};
//----------------------------------------------------------------------------

#endif