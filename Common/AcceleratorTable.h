//----------------------------------------------------------------------------
// AcceleratorTable.h : �A�N�Z�����[�^�e�[�u���̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef AcceleratorTableH
#define AcceleratorTableH

#include <windows.h>
#include "Define.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//--------------------------------------------------------------------------
// STRUCT
//--------------------------------------------------------------------------
typedef struct ST_ACCEL {
	BYTE    virt;
	WORD    key;
	WORD    cmd;
} *PST_ACCEL;

typedef struct ST_LYRICS {
	double dStartTime;
	double dEndTime;
	tstring strLyrics;
	BOOL bReline;
} *PST_LYRICS;

//--------------------------------------------------------------------------
// MACRO
//--------------------------------------------------------------------------
#define IS_EXTKEY(k_) ((k_) == VK_APPS  || (k_) == VK_PRIOR  || (k_) == VK_NEXT   || (k_) == VK_END     || \
                       (k_) == VK_HOME  || (k_) == VK_LEFT   || (k_) == VK_UP     || (k_) == VK_RIGHT   || \
                       (k_) == VK_DOWN  || (k_) == VK_INSERT || (k_) == VK_DELETE || (k_) == VK_NUMLOCK || \
                       (k_) == VK_DIVIDE|| (k_) == VK_CANCEL)

//----------------------------------------------------------------------------
// �A�N�Z�����[�^�e�[�u���̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CAcceleratorTable
{
public: // �֐�

	CAcceleratorTable() : m_hAccel(0) { }
	~CAcceleratorTable() { Destroy(); }

	BOOL Add(BYTE fVirt, WORD key, WORD cmd);
	int Copy(LPACCEL lpAccelDst, int cAccelEntries);
	BOOL Create(LPACCEL pAccel, int nAccel);
	BOOL Delete(BYTE fVirt, WORD key, WORD cmd);
	BOOL Destroy();
	WORD GetCommandId(int i);
	tstring GetShortCut(int i);
	tstring GetShortCut(BYTE fVirt, UINT key);
	tstring GetStringFromKey(UINT key);
	UINT GetKeyFromString(tstring str);
	void SetDefault();
	ST_ACCEL GetDefault(int idx);

	// �G���g�����𓾂�
	int GetNum() { return Copy(NULL, 0); }

private: // �����o�ϐ�

	HACCEL m_hAccel;

public: // �����o�ϐ��̎擾

	operator HACCEL() const { return m_hAccel; }
};
//----------------------------------------------------------------------------

#endif