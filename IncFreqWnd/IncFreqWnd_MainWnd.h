//----------------------------------------------------------------------------
// IncFreqWnd_MainWnd.h : ���񂾂񑬂�����E�B���h�E�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef IncFreqWnd_MainWndH
#define IncFreqWnd_MainWndH

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
// ���񂾂񑬂�����E�B���h�E�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CIncFreqWnd_MainWnd : public CIncSpeedWnd_MainWnd
{
public: // �֐�

	CIncFreqWnd_MainWnd(CApp & app, CMainWnd & mainWnd);
	virtual ~CIncFreqWnd_MainWnd();

	virtual BOOL Create();
	virtual void OnOkButtonClicked();
	virtual void OnCancelButtonClicked();
	virtual void OnEscKeyPressed();
};
//----------------------------------------------------------------------------

#endif