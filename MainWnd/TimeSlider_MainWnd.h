//----------------------------------------------------------------------------
// TimeSlider_MainWnd.h : �Đ����Ԑݒ�p�X���C�_�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef TimeSlider_MainWndH
#define TimeSlider_MainWndH

#pragma warning(disable: 4355)
	// 'this' : �x�[�X �����o���������X�g�Ŏg�p����܂����B
class CApp;
class CMainWnd;
#include "../Common/bassinc.h"
#include "../Common/SliderCtrl.h"
#include "RMenu_TimeSlider.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �Đ����Ԑݒ�p�X���C�_�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CTimeSlider_MainWnd : public CSliderCtrl
{
public: // �֐�

	CTimeSlider_MainWnd(CApp & app, CMainWnd & mainWnd)
		: m_rApp(app), m_rMainWnd(mainWnd), bABLoopADrag(FALSE),
		  bABLoopBDrag(FALSE), m_rClickMenu(*this), bDrag(FALSE),
		  nDraggingMarker(0), bControl(FALSE), qwFirstPos(0), nDeleteMarker(0) 
	{ }
	virtual ~CTimeSlider_MainWnd() { }

	virtual BOOL Create();
	virtual void DeleteMarker();
	virtual int GetHeight() const;
	virtual int GetTop() const;
	virtual void ResetPos();
	virtual void ResetSize();
	virtual void SetTime(QWORD time, QWORD totalTime);

	virtual void OnCommand(int id, HWND hwndCtl, UINT codeNotify);
	virtual void OnHScroll(HWND hwndCtl, UINT code, int pos);
	virtual void OnKeyDown(UINT vk, int cRepeat, UINT flags);
	virtual void OnKeyUp(UINT vk, UINT lKeyData);
	virtual void OnLButtonDown(int x, int y, UINT keyFlags);
	virtual void OnLButtonUp(int x, int y, UINT keyFlags);
	virtual void OnRButtonUp(int x, int y, UINT keyFlags);
	virtual void OnMouseMove(int x, int y, UINT keyFlags);
	virtual BOOL OnSetCursor(HWND hwndCursor, UINT codeHitTest, UINT msg);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	CRMenu_TimeSlider m_rClickMenu; // �E�N���b�N���j���[

	BOOL bABLoopADrag;
	BOOL bABLoopBDrag;
	BOOL bDrag; // �}�[�J�[�ʒu���h���b�O�����ǂ���
	int nDraggingMarker; // ���Ԗڂ̃}�[�J�[���h���b�O����
	BOOL bControl; // Ctrl �L�[�ɂ������������ǂ���
	QWORD qwFirstPos; // �h���b�O�J�n���̃}�[�J�[�ʒu
	int nDeleteMarker; // ���Ԗڂ̃}�[�J�[���폜�\�肩

public: // �����o�ϐ��̎擾�E�ݒ�

	CMainWnd & GetMainWnd() { return m_rMainWnd; }
};
//----------------------------------------------------------------------------

#endif