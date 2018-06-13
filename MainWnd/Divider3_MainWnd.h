//----------------------------------------------------------------------------
// Divider3_MainWnd.h : ��؂�����̂R�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef Divider3_MainWndH
#define Divider3_MainWndH

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
// ��؂�����̂R�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CDivider3_MainWnd : public CDivider2_MainWnd
{
public: // �֐�

	CDivider3_MainWnd(CApp & app, CMainWnd & mainWnd)
		: CDivider2_MainWnd(app, mainWnd) { }
	virtual ~CDivider3_MainWnd() { }

	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
};
//----------------------------------------------------------------------------

#endif