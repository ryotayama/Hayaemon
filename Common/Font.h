//----------------------------------------------------------------------------
// Font.h : �t�H���g�̍쐬�E�Ǘ��E�j�����s��
//----------------------------------------------------------------------------
#ifndef FontH
#define FontH
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �t�H���g�̍쐬�E�Ǘ��E�j�����s���N���X
//----------------------------------------------------------------------------
class CFont
{
public: // �֐�

	CFont(): m_hFont(0) { }
	virtual ~CFont() { Destroy(); }

	virtual BOOL Create(int nHeight, int nWidth, int nEscapement,
						int nOrientation, int nWeight, BYTE bItalic,
						BYTE bUnderline, BYTE cStrikeOut, BYTE nCharSet,
						BYTE nOutPrecision, BYTE nClipPrecision, BYTE nQuality,
						BYTE nPitchAndFamily, LPCTSTR lpszFacename) {
		m_hFont = CreateFont(nHeight, nWidth, nEscapement, nOrientation,
								nWeight, bItalic, bUnderline, cStrikeOut,
								nCharSet, nOutPrecision, nClipPrecision,
								nQuality, nPitchAndFamily, lpszFacename);
		return (m_hFont ? TRUE : FALSE);
	}
	virtual BOOL CreateIndirect(const LOGFONT* pLogFont) {
		m_hFont = CreateFontIndirect(pLogFont);
		return (m_hFont ? TRUE : FALSE);
	}
	virtual void Destroy() {
		if(m_hFont) DeleteObject(m_hFont), m_hFont = 0;
	}

protected: // �����o�ϐ�

	HFONT m_hFont;

public: // �����o�ϐ��̎擾�E�ݒ�

	operator HFONT() const { return m_hFont; }
};
//----------------------------------------------------------------------------

#endif