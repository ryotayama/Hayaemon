//----------------------------------------------------------------------------
// Divider5_MainWnd.h : ��؂�����̂T�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef Divider5_MainWndH
#define Divider5_MainWndH

class CApp;
class CMainWnd;
#include "Divider2_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ��؂�����̂T�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CDivider5_MainWnd : public CDivider2_MainWnd
{
public: // �֐�

	CDivider5_MainWnd(CApp & app, CMainWnd & mainWnd)
		: CDivider2_MainWnd(app, mainWnd) { }
	virtual ~CDivider5_MainWnd() { }

	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
};
//----------------------------------------------------------------------------

#endif