//----------------------------------------------------------------------------
// DecSpeedWnd_MainWnd.h : ���񂾂�x������E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef DecSpeedWnd_MainWndH
#define DecSpeedWnd_MainWndH

#pragma warning(disable: 4355)
	// 'this' : �x�[�X �����o���������X�g�Ŏg�p����܂����B
#include "../IncSpeedWnd/IncSpeedWnd_MainWnd.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// ���񂾂�x������E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CDecSpeedWnd_MainWnd : public CIncSpeedWnd_MainWnd
{
public: // �֐�

	CDecSpeedWnd_MainWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CDecSpeedWnd_MainWnd();

	virtual BOOL Create();
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
	virtual void OnEscKeyPressed();
};
//----------------------------------------------------------------------------

#endif