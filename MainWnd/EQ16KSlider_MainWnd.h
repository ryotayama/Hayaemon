//----------------------------------------------------------------------------
// EQ16KSlider_MainWnd.h : �C�R���C�U ( 16KHz ) �ݒ�p�X���C�_�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef EQ16KSlider_MainWndH
#define EQ16KSlider_MainWndH

class CApp;
class CMainWnd;
#include "../Common/SliderCtrl.h"
#include "RMenu_EQCtrl.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �C�R���C�U ( 16KHz ) �ݒ�p�X���C�_�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CEQ16KSlider_MainWnd : public CSliderCtrl
{
public: // �֐�

	CEQ16KSlider_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), m_rClickMenu(mainWnd),
		  dwThumbClickTime(0) { }
	virtual ~CEQ16KSlider_MainWnd() { }

	virtual BOOL Create();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void ResetSize();

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnHScroll(HWND hwndCtl, UINT code, int pos);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnLButtonDown(int x, int y, UINT keyFlags);
	virtual void OnRButtonUp(int x, int y, UINT keyFlags);
	virtual BOOL OnMouseWheel(UINT nFlags, int zDelta, POINTS pt);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;
	DWORD dwThumbClickTime;
	CRMenu_EQCtrl m_rClickMenu; // �E�N���b�N���j���[
};
//----------------------------------------------------------------------------

#endif