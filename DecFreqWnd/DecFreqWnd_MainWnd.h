//----------------------------------------------------------------------------
// DecFreqWnd_MainWnd.h : ���񂾂�x������E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef DecFreqWnd_MainWndH
#define DecFreqWnd_MainWndH

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
class CDecFreqWnd_MainWnd : public CIncSpeedWnd_MainWnd
{
public: // �֐�

	CDecFreqWnd_MainWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CDecFreqWnd_MainWnd();

	virtual BOOL Create();
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
	virtual void OnEscKeyPressed();
};
//----------------------------------------------------------------------------

#endif