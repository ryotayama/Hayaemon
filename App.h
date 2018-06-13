//----------------------------------------------------------------------------
// App.h : �A�v���P�[�V�����̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef AppH
#define AppH

#pragma warning(disable: 4355)
	// 'this' : �x�[�X �����o���������X�g�Ŏg�p����܂����B
#include <TCHAR.H>
#include "./MainWnd/MainWnd.h"
#include "./Common/AcceleratorTable.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// �A�v���P�[�V�����̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CApp
{
public: // �֐�

	CApp(const int & nCmdShow);
	~CApp();

	BOOL CheckDoubleRun(); // ���d�N���̃`�F�b�N
	int Run(); // ���s
	void ShowError(tstring strError); // �G���[���o�͂��ďI��

private: // �����o�ϐ�

	const int m_nCmdShow; // �����\�����
	const tstring m_cstrName; // �A�v���P�[�V�����̖��O
	const tstring m_cstrVersionInfo; // �o�[�W�������
	const tstring m_cstrAuthorName; // ��Җ�
	const tstring m_cstrAuthorEMail; // ��҂̃��[���A�h���X
	const tstring m_cstrAuthorWebSiteName; // ��҂̃T�C�g��
	const tstring m_cstrAuthorURL; // ��҂̃T�C�g�̃A�h���X
	tstring m_strPath;
	std::string m_strPathA;

	CMainWnd m_wnd;
	CAcceleratorTable m_accelTable;

public: // �����o�ϐ��̎擾�E�ݒ�

	int GetNCmdShow() const { return m_nCmdShow; }
	tstring GetName() const { return m_cstrName; }
	tstring GetVersionInfo() const { return m_cstrVersionInfo; }
	tstring GetAuthorName() const { return m_cstrAuthorName; }
	tstring GetAuthorEMail() const { return m_cstrAuthorEMail; }
	tstring GetAuthorWebSiteName() const { return m_cstrAuthorWebSiteName; }
	tstring GetAuthorURL() const { return m_cstrAuthorURL; }
	tstring GetFilePath() const { return m_strPath; }
	std::string GetFilePathA() const { return m_strPathA; }
	CAcceleratorTable & GetAccelTable() { return m_accelTable; }
};
//----------------------------------------------------------------------------

#endif // AppH