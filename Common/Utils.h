//--------------------------------------------------------------------------
// Utils.h : ���[�e�B���e�B�֐�
//--------------------------------------------------------------------------
#ifndef UtilsH
#define UtilsH

#include <string>
#include "Define.h"

using namespace std;
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//--------------------------------------------------------------------------
// ���[�e�B���e�B�֐��N���X
//--------------------------------------------------------------------------
class CUtils
{
public: // �֐�

	static tstring GetFilePath(const tstring &);
	static tstring GetFileName(const tstring &);
	static tstring GetFileNameWithoutExt(const tstring &);
	static tstring GetFileSize_KB(const tstring &);
	static tstring Replace(tstring str, tstring srcStr, tstring dstStr);
	static int GetRandom(int nMin, int nMax);
};
//--------------------------------------------------------------------------
#endif
