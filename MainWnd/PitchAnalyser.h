//----------------------------------------------------------------------------
// PitchAnalyser.h : �s�b�`�A�i���C�U�@�\�̊Ǘ��N���X
//----------------------------------------------------------------------------
#ifndef PitchAnalyserH
#define PitchAnalyserH

#include <string>
#include <vector>
#include "../Common/AcceleratorTable.h"
class CApp;
class CMainWnd;
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �̎��\���@�\�̊Ǘ��N���X
//----------------------------------------------------------------------------
class CPitchAnalyser
{
public: // �֐�

	CPitchAnalyser(CApp & app, CMainWnd & mainWnd);
	virtual ~CPitchAnalyser();
	virtual void ClearScreen();
	virtual void Update(double dCurrentTime);

private: // �����o�ϐ�

	CApp & m_rApp;
	CMainWnd & m_rMainWnd;

	HBITMAP hBitmap;
	HDC hMemDC;
	HFONT hFont;
	void* pImage;
	int m_nLeft;

public: // �����o�ϐ��̎擾�E�ݒ�

};
//----------------------------------------------------------------------------

#endif