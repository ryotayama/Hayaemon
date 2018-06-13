//----------------------------------------------------------------------------
// Bitmap.h : �r�b�g�}�b�v�̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef BitmapH
#define BitmapH
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �r�b�g�}�b�v�̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CBitmap
{
public: // �֐�

	CBitmap(): m_hBitmap(0) { }
	virtual ~CBitmap() { Destroy(); }

	virtual void Destroy() {
		if(m_hBitmap) DeleteObject(m_hBitmap), m_hBitmap = 0;
	}
	virtual void Load(LPCTSTR lpszName, UINT fuLoad) {
		Destroy();
		m_hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), lpszName, IMAGE_BITMAP, 0, 0, fuLoad);
	}

protected: // �����o�ϐ�

	HBITMAP m_hBitmap;

public: // �����o�ϐ��̎擾�E�ݒ�

	operator HBITMAP() const { return m_hBitmap; }
};
//----------------------------------------------------------------------------

#endif