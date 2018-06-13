//----------------------------------------------------------------------------
// ClientDC.h : �E�B���h�E�̃N���C�A���g�̈�p�f�o�C�X�R���e�L�X�g�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef ClientDCH
#define ClientDCH

#include "DC.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �E�B���h�E�̃N���C�A���g�̈�p�f�o�C�X�R���e�L�X�g�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CClientDC : public CDC
{
public: // �֐�

	CClientDC(HWND hWnd) {
		m_hWnd = hWnd;
		m_hDC = GetDC(m_hWnd);
	}
	virtual ~CClientDC() { }

	virtual void Destroy() {
		if(m_hDC) ReleaseDC(m_hWnd, m_hDC), m_hWnd = 0, m_hDC = 0;
	}

protected: // �����o�ϐ�

	HWND m_hWnd;
};
//----------------------------------------------------------------------------

#endif