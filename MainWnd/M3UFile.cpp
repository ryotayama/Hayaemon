//--------------------------------------------------------------------------
// M3UFile.cpp : M3U�t�@�C���̊Ǘ����s��
//--------------------------------------------------------------------------
#include <windows.h>
#include "..\Common\Utils.h"
#include "M3UFile.h"
//--------------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------------
CM3UFile::CM3UFile()
	:isLoaded(false)
{
}
//--------------------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------------------
CM3UFile::~CM3UFile()
{
}
//--------------------------------------------------------------------------
// �t�@�C���p�X�𓾂�
//--------------------------------------------------------------------------
tstring CM3UFile::GetFilePath(int num)
{
	if(!isLoaded || !buffer.size()) return _T("");
	return buffer[num];
}
//--------------------------------------------------------------------------
// ������
//--------------------------------------------------------------------------
void CM3UFile::Init()
{
	isLoaded = false;
	buffer.clear();
}
//--------------------------------------------------------------------------
// �ǂݍ���
//--------------------------------------------------------------------------
void CM3UFile::Read(const PCTSTR & pFilePath, BOOL bUtf8)
{
	FILE *fp = NULL;

	if(bUtf8) _tfopen_s(&fp, pFilePath, _T("r, ccs=UTF-8"));
	else _tfopen_s(&fp, pFilePath, _T("r"));
	if(!fp) return;

	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, FILE_SHARE_READ
		| FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE) return;

	Init();
	DWORD fileSize = GetFileSize(hFile, NULL) + 1;
	if((int)fileSize <= 1) {
		isLoaded = true;
		CloseHandle(hFile);
		fclose(fp);
		return;
	}

	tstring strPath = CUtils::GetFilePath(pFilePath);

	wchar_t * buf = new wchar_t[fileSize];
	while(fgetws(buf, fileSize, fp) != NULL) {
#ifdef UNICODE
		tstring strName = buf;
#else
		int cbMB = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
		char *szBuf = new char[cbMB];

		memset(szBuf, 0, cbMB);
		WideCharToMultiByte(CP_ACP, 0, buf, -1, szBuf, cbMB, NULL, NULL);
		tstring strName = szBuf;

		delete[] szBuf;
#endif // UNICODE
		strName = CUtils::Replace(strName, _T("\r\n"), _T(""));
		strName = CUtils::Replace(strName, _T("\n"), _T(""));
		tstring strPathName = strPath + strName;
		if(GetFileAttributes(strPathName.c_str()) != 0xFFFFFFFF)
			// ���΃p�X
			buffer.push_back(strPathName.c_str());
		else if(GetFileAttributes(strName.c_str()) != 0xFFFFFFFF)
			// ��΃p�X
			buffer.push_back(strName.c_str());
	}

	delete[] buf;
	CloseHandle(hFile);
	fclose(fp);

	isLoaded = true;
}
//--------------------------------------------------------------------------
// �ۑ�
//--------------------------------------------------------------------------
void CM3UFile::Save(const PCTSTR & pFilePath, tstring str, BOOL bUtf8)
{
	FILE *fp = NULL;

	if(bUtf8) _tfopen_s(&fp, pFilePath, _T("w, ccs=UTF-8"));
	else _tfopen_s(&fp, pFilePath, _T("w"));
		
	if(!fp) return;

#ifdef UNICODE
	_fputts(str.c_str(), fp);
#else
	int cchWC = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str.c_str(), -1, NULL, 0);
	wchar_t *wszTmp = new wchar_t[cchWC];

	memset(wszTmp, 0, cchWC * sizeof(wchar_t));
	if(MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str.c_str(), -1,
		wszTmp, cchWC))
		fputws(wszTmp, fp);

	delete[] wszTmp;
#endif // UNICODE

	fclose(fp);
}
//--------------------------------------------------------------------------
