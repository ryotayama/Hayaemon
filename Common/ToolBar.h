//----------------------------------------------------------------------------
// ToolBar.h :�c�[���o�[�̍쐬�E�Ǘ��E�j�����s��
//----------------------------------------------------------------------------
#ifndef ToolBarH
#define ToolBarH

#include "Wnd.h"
#include "Bitmap.h"
#include <vector>
#include <commctrl.h>
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �c�[���o�[�̍쐬�E�Ǘ��E�j�����s���N���X
//----------------------------------------------------------------------------
class CToolBar : public CWnd
{
public: // �֐�

	CToolBar() { }
	virtual ~CToolBar() { }

	virtual void CheckButton(int nID, BOOL fCheck);
	virtual BOOL Create(HWND hParentWnd);
	virtual void EnableButton(int nID, BOOL fEnable);
	virtual void HideButton(int nID, BOOL fHide);
	virtual void LoadBitmap(LPCTSTR lpszResourceName);
	virtual void SetButtons(const UINT* lpIDArray, int nIDCount);
	virtual void SetState(int nID, UINT nState);

protected: // �����o�ϐ�

	CBitmap m_bitmap;
	std::vector<TBBUTTON> m_arrayButton;

public: // �����o�ϐ��̎擾�E�ݒ�

	virtual std::vector<TBBUTTON> GetArrayButton() const
	{
		return m_arrayButton;
	}
};
//----------------------------------------------------------------------------

#endif