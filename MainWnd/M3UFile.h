//--------------------------------------------------------------------------
// M3UFile.h : M3U�t�@�C���̊Ǘ����s��
//--------------------------------------------------------------------------
#ifndef M3UFileH
#define M3UFileH

#include <tchar.h>
#include <vector>
#include <string>

using namespace std;
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//--------------------------------------------------------------------------
//	M3U�t�@�C���̊Ǘ����s���N���X
//--------------------------------------------------------------------------
class CM3UFile
{
public: // �֐�

	CM3UFile(); // �R���X�g���N�^
	~CM3UFile(); // �f�X�g���N�^

	tstring GetFilePath(int num);
	void Init();
	void Read(const PCTSTR & pFilePath, BOOL bUtf8);
	void Save(const PCTSTR & pFilePath, tstring str, BOOL bUtf8);

private: // �����o�ϐ�

	vector<tstring> buffer;
	bool isLoaded;

public: // �����o�ϐ��̎擾�E�ݒ�

	bool GetIsLoaded() { return isLoaded; }
	int GetLinesCount() { return (int)buffer.size(); }
	void PushBack(tstring str) { buffer.push_back(str); }
};
//--------------------------------------------------------------------------

#endif