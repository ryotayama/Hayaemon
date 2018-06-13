//----------------------------------------------------------------------------
// Menu_MainWnd.cpp : ���C���E�B���h�E�p���j���[�̍쐬�E�Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include <WinInet.h>
#include "../Common/Utils.h"
#include "../App.h"
#include "MainWnd.h"
#include "Menu_MainWnd.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CMenu_MainWnd::Create()
{
	CMenu::Create();
#if JP
	// �t�@�C�����j���[
	m_fileMenu.CreatePopup();
	m_fileMenu.Append(MFS_ENABLED, ID_OPENFILE, _T("�J��(&O)...\tCtrl+O"));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDFILE, _T("�ǉ�(&P)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_OPENFOLDER, _T("�t�H���_���J��(&F)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDFOLDER, _T("�t�H���_��ǉ�(&G)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_OPENURL, _T("URL���J��(&O)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDURL, _T("URL��ǉ�(&A)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_DISABLED, ID_SAVEFILE, _T("�ۑ�(&S)...\tCtrl+E"));
	m_fileMenu.Append(MFS_DISABLED, ID_SAVEALLFILE, _T("�ꊇ�ϊ�(&A)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_ENABLED, ID_LAMECOMMANDLINE,
		_T("LAME�R�}���h���C���I�v�V����(&L)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_ENABLED, ID_EXIT, _T("�I��(&X)\tAlt+F4"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_fileMenu, _T("�t�@�C��(&F)"));

	// �ҏW���j���[
	m_editMenu.CreatePopup();
	m_editMenu.Append(MFS_ENABLED, ID_DELETE, _T("�폜(&D)"));
	m_editMenu.Append(MFS_ENABLED, ID_SELECTALL, _T("���ׂđI��(&A)\tCtrl+A"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_editMenu, _T("�ҏW(&E)"));

	// �\�����j���[
	m_viewMenu.CreatePopup();
	m_videoScreenMenu.CreatePopup();
	m_videoScreenMenu.Append(MFS_ENABLED, ID_VIDEOSCREEN, _T("�\��(&V)"));
	m_videoScreenMenu.AppendSeparator();
	m_videoScreenMenu.Append(MFS_CHECKED, ID_LYRICS, _T("�̎�(&L)"));
	m_videoScreenMenu.Append(MFS_ENABLED, ID_PITCHANALYSER,
		_T("�s�b�`�A�i���C�U(&P)"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_videoScreenMenu,
		_T("�r�f�I���(&V)"));
	m_viewMenu.Append(MFS_ENABLED, ID_TIMESLIDER, _T("�Đ��ʒu�X���C�_(&T)"));
	m_viewMenu.Append(MFS_ENABLED, ID_EXPLORER, _T("�G�N�X�v���[��(&E)"));
	m_viewMenu.Append(MFS_ENABLED, ID_SPEED, _T("�Đ����x(&S)"));
	m_viewMenu.Append(MFS_ENABLED, ID_FREQ, _T("�Đ����g��(&F)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PITCH, _T("����(&P)"));
	m_viewMenu.Append(MFS_ENABLED, ID_VOLUME, _T("����(&V)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PAN, _T("�p��(&P)"));
	m_eqMenu.CreatePopup();
	m_eqMenu.Append(MFS_ENABLED, ID_EQ, _T("�\��(&V)"));
	m_eqMenu.AppendSeparator();
	m_eqMenu.Append(MFS_ENABLED, ID_EQ20, _T("20 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ25, _T("25 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ31_5, _T("31.5 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ40, _T("40 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ50, _T("50 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ63, _T("63 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ80, _T("80 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ100, _T("100 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ125, _T("125 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ160, _T("160 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ200, _T("200 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ250, _T("250 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ315, _T("315 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ400, _T("400 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ500, _T("500 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ630, _T("630 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ800, _T("800 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1K, _T("1 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1_25K, _T("1.25 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1_6K, _T("1.6 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ2K, _T("2 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ2_5K, _T("2.5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ3_15K, _T("3.15 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ4K, _T("4 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ5K, _T("5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ6_3K, _T("6.3 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ8K, _T("8 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ10K, _T("10 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ12_5K, _T("12.5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ16K, _T("16 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ20K, _T("20 KHz"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqMenu,
		_T("�O���t�B�b�N�C�R���C�U(&G)"));
	m_viewMenu.Append(MFS_CHECKED, ID_TAB, _T("�^�u(&T)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PLAYLIST, _T("�Đ����X�g(&P)"));
	m_viewMenu.AppendSeparator();
	m_viewMenu.Append(MFS_ENABLED, ID_CLOSEALL, _T("�S�ẴR���g���[�������(&C)"));
	m_viewMenu.AppendSeparator();
	m_toolbarMenu.CreatePopup();
	m_toolbarMenu.Append(MFS_CHECKED, ID_TOOLBAR_SIZES, _T("�T�C�Y�i���j(&S)"));
	m_toolbarMenu.Append(MFS_ENABLED, ID_TOOLBAR_SIZEM, _T("�T�C�Y�i���j(&M)"));
	m_toolbarMenu.Append(MFS_ENABLED, ID_TOOLBAR_SIZEL, _T("�T�C�Y�i��j(&L)"));
	m_toolbarMenu.AppendSeparator();
	m_toolbarMenu.Append(MFS_ENABLED, ID_CUSTOMIZETOOLBAR,
		_T("�J�X�^�}�C�Y(&T)"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_toolbarMenu, _T("�c�[���o�["));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_viewMenu, _T("�\��(&V)"));

	// �Đ����j���[
	m_playMenu.CreatePopup();
	m_playMenu.Append(MFS_ENABLED, ID_PAUSE, _T("�Đ�/�ꎞ��~(&P)\tCtrl+P"));
	m_playMenu.Append(MFS_ENABLED, ID_STOP, _T("��~(&S)\tCtrl+S"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_HEAD, _T("���o��(&T)\tCtrl+0"));
	m_playMenu.Append(MFS_ENABLED, ID_PREV, _T("�O��(&V)\tCtrl+B"));
	m_playMenu.Append(MFS_ENABLED, ID_NEXT, _T("����(&N)\tCtrl+F"));
	m_playMenu.Append(MFS_ENABLED, ID_REWIND, _T("�����߂�(&R)\tCtrl+Shift+B"));
	m_playMenu.Append(MFS_ENABLED, ID_FORWARD, _T("������(&A)\tCtrl+Shift+F"));
	m_playMenu.AppendSeparator();
	m_returnMenu.CreatePopup();
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN1SEC, _T("1�b�߂�(&1)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN2SEC, _T("2�b�߂�(&2)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN3SEC, _T("3�b�߂�(&3)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN5SEC, _T("5�b�߂�(&5)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN10SEC, _T("10�b�߂�(&T)"));
	m_playMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_returnMenu, _T("�߂�(&R)"));
	m_forwardMenu.CreatePopup();
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD1SEC, _T("1�b�i��(&1)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD2SEC, _T("2�b�i��(&2)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD3SEC, _T("3�b�i��(&3)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD5SEC, _T("5�b�i��(&5)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD10SEC, _T("10�b�i��(&T)"));
	m_playMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_forwardMenu, _T("�i��(&F)"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_SLOOP, _T("�P�ȃ��[�v(&1)\tCtrl+1"));
	m_playMenu.Append(MF_ENABLED, ID_ALOOP, _T("�S�ȃ��[�v(&T)\tCtrl+T"));
	m_playMenu.Append(MFS_ENABLED, ID_RANDOM, _T("�����_���Đ�(&H)\tCtrl+H"));
	m_playMenu.Append(MFS_ENABLED, ID_CONTINUE, _T("�A���Đ�(&C)"));
	m_playMenu.Append(MFS_ENABLED, ID_SAMEARTIST, _T("�����A�[�e�B�X�g�̋Ȃ��Đ�(&S)"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_ABLOOP_A,
		_T("���݈ʒu��AB���[�v(A)�ɐݒ�(&A)"));
	m_playMenu.Append(MFS_ENABLED, ID_ABLOOP_B,
		_T("���݈ʒu��AB���[�v(B)�ɐݒ�(&B)"));
	m_playMenu.Append(MFS_DISABLED, ID_ABLOOP_A_SETTING,
		_T("AB���[�v(A)�̈ʒu�ݒ�(&C)..."));
	m_playMenu.Append(MFS_DISABLED, ID_ABLOOP_B_SETTING,
		_T("AB���[�v(B)�̈ʒu�ݒ�(&D)..."));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_MARKERPLAY, _T("�}�[�J�[�Đ�(&M)"));
	m_playMenu.Append(MFS_ENABLED, ID_ADDMARKER, _T("�}�[�J�[�ǉ�(&A)"));
	m_playMenu.Append(MFS_ENABLED, ID_DELETEMARKER, _T("�}�[�J�[�폜(&D)"));
	m_playMenu.Append(MFS_DISABLED, ID_COUNTLOOP, _T("�񐔃��[�v(&C)"));
	m_playMenu.Append(MFS_ENABLED, ID_INSTANTLOOP, _T("�}�[�J�[�ǉ����Ƀ��[�v(&I)"));
	m_playMenu.Append(MFS_ENABLED, ID_SETPOSITIONAUTO,
		_T("�}�[�J�[�������̍Đ��ʒu�A��(&S)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_playMenu, _T("�Đ�(&P)"));

	// �G�t�F�N�g���j���[
	m_effectMenu.CreatePopup();
	m_presetMenu.CreatePopup();
	m_presetMenu.Append(MFS_ENABLED, ID_ADDPRESET, _T("���݂̐ݒ��ǉ�(&A)"));
	m_presetMenu.Append(MFS_DISABLED, ID_DELETEPRESET, _T("�I�𒆂̃v���Z�b�g���폜(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_presetMenu,
		_T("�v���Z�b�g(&P)"));
	m_effectMenu.AppendSeparator();
	m_speedMenu.CreatePopup();
	m_speedMenu.Append(MFS_ENABLED, ID_RESETSPEED, _T("�f�t�H���g�ɖ߂�(&R)"));
	m_speedMenu.AppendSeparator();
	m_setSpeedMenu.CreatePopup();
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_50, _T("50%(&A)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_60, _T("60%(&B)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_70, _T("70%(&C)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_80, _T("80%(&D)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_90, _T("90%(&E)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_100, _T("100%(&F)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_110, _T("110%(&G)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_120, _T("120%(&H)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_130, _T("130%(&I)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_140, _T("140%(&J)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_150, _T("150%(&K)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_160, _T("160%(&L)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_170, _T("170%(&M)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_180, _T("180%(&N)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_190, _T("190%(&O)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_200, _T("200%(&P)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_250, _T("250%(&Q)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_300, _T("300%(&R)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_350, _T("350%(&S)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_400, _T("400%(&T)"));
	m_speedMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setSpeedMenu,
		_T("���x�w��(&S)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN0_1SPEED, _T("0.1%������(&0)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN1SPEED, _T("1%������(&1)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN2SPEED, _T("2%������(&2)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN3SPEED, _T("3%������(&3)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN5SPEED, _T("5%������(&5)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN10SPEED, _T("10%������(&T)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MFS_ENABLED, ID_UP0_1SPEED, _T("0.1%�グ��(&Z)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP1SPEED, _T("1%�グ��(&A)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP2SPEED, _T("2%�グ��(&B)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP3SPEED, _T("3%�グ��(&C)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP5SPEED, _T("5%�グ��(&D)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP10SPEED, _T("10%�グ��(&E)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MF_ENABLED, ID_DECSPEED, _T("���񂾂�x������(&D)..."));
	m_speedMenu.Append(MF_ENABLED, ID_INCSPEED, _T("���񂾂񑬂�����(&D)..."));
	m_speedMenu.AppendSeparator();
	m_speedDecimalMenu.CreatePopup();
	m_speedDecimalMenu.Append(MFS_ENABLED, ID_SPEEDDEC_0, _T("0��(&0)"));
	m_speedDecimalMenu.Append(MFS_CHECKED, ID_SPEEDDEC_1, _T("1��(&1)"));
	m_speedDecimalMenu.Append(MFS_ENABLED, ID_SPEEDDEC_2, _T("2��(&2)"));
	m_speedMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedDecimalMenu, _T("�����_����"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedMenu,
		_T("�Đ����x(&S)"));
	m_freqMenu.CreatePopup();
	m_freqMenu.Append(MFS_ENABLED, ID_RESETFREQ, _T("�f�t�H���g�ɖ߂�(&R)"));
	m_freqMenu.AppendSeparator();
	m_setFreqMenu.CreatePopup();
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_50, _T("50%(&A)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_60, _T("60%(&B)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_70, _T("70%(&C)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_80, _T("80%(&D)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_90, _T("90%(&E)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_100, _T("100%(&F)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_110, _T("110%(&G)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_120, _T("120%(&H)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_130, _T("130%(&I)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_140, _T("140%(&J)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_150, _T("150%(&K)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_160, _T("160%(&L)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_170, _T("170%(&M)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_180, _T("180%(&N)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_190, _T("190%(&O)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_200, _T("200%(&P)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_250, _T("250%(&Q)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_300, _T("300%(&R)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_350, _T("350%(&S)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_400, _T("400%(&T)"));
	m_freqMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setFreqMenu,
		_T("���g���w��(&F)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN0_1FREQ, _T("0.1%������(&0)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN1FREQ, _T("1%������(&1)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN2FREQ, _T("2%������(&2)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN3FREQ, _T("3%������(&3)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN5FREQ, _T("5%������(&5)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN10FREQ, _T("10%������(&T)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MFS_ENABLED, ID_UP0_1FREQ, _T("0.1%�グ��(&Z)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP1FREQ, _T("1%�グ��(&A)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP2FREQ, _T("2%�グ��(&B)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP3FREQ, _T("3%�グ��(&C)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP5FREQ, _T("5%�グ��(&D)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP10FREQ, _T("10%�グ��(&E)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MF_ENABLED, ID_DECFREQ,
		_T("���񂾂�x������(&F)..."));
	m_freqMenu.Append(MF_ENABLED, ID_INCFREQ,
		_T("���񂾂񑬂�����(&F)..."));
	m_freqMenu.AppendSeparator();
	m_freqDecimalMenu.CreatePopup();
	m_freqDecimalMenu.Append(MFS_ENABLED, ID_FREQDEC_0, _T("0��(&0)"));
	m_freqDecimalMenu.Append(MFS_CHECKED, ID_FREQDEC_1, _T("1��(&1)"));
	m_freqDecimalMenu.Append(MFS_ENABLED, ID_FREQDEC_2, _T("2��(&2)"));
	m_freqMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqDecimalMenu, _T("�����_����"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqMenu,
		_T("�Đ����g��(&F)"));
	m_pitchMenu.CreatePopup();
	m_pitchMenu.Append(MFS_ENABLED, ID_RESETPITCH, _T("�f�t�H���g�ɖ߂�(&R)"));
	m_pitchMenu.AppendSeparator();
	m_setPitchMenu.CreatePopup();
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F12, _T("��12(&A)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F11, _T("��11(&B)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F10, _T("��10(&C)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F9, _T("��9(&D)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F8, _T("��8(&E)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F7, _T("��7(&F)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F6, _T("��6(&G)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F5, _T("��5(&H)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F4, _T("��4(&I)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F3, _T("��3(&J)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F2, _T("��2(&K)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F1, _T("��1(&L)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_0, _T("0(&M)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S1, _T("��1(&N)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S2, _T("��2(&O)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S3, _T("��3(&P)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S4, _T("��4(&Q)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S5, _T("��5(&R)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S6, _T("��6(&S)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S7, _T("��7(&T)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S8, _T("��8(&U)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S9, _T("��9(&V)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S10, _T("��10(&W)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S11, _T("��11(&X)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S12, _T("��12(&Y)"));
	m_pitchMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setPitchMenu,
		_T("�����w��(&F)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN1PITCH, _T("����������(&1)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN2PITCH, _T("�S��������(&2)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN1OCTPITCH, _T("�P�I�N�^�[�u������(&3)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(MFS_ENABLED, ID_UP1PITCH, _T("�����グ��(&A)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_UP2PITCH, _T("�S���グ��(&B)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_UP1OCTPITCH, _T("�P�I�N�^�[�u�グ��(&C)"));
	m_pitchMenu.AppendSeparator();
	m_pitchDecimalMenu.CreatePopup();
	m_pitchDecimalMenu.Append(MFS_ENABLED, ID_PITCHDEC_0, _T("0��(&0)"));
	m_pitchDecimalMenu.Append(MFS_CHECKED, ID_PITCHDEC_1, _T("1��(&1)"));
	m_pitchDecimalMenu.Append(MFS_ENABLED, ID_PITCHDEC_2, _T("2��(&2)"));
	m_pitchMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchDecimalMenu, _T("�����_����"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchMenu, _T("����(&P)"));
	m_volumeMenu.CreatePopup();
	m_volumeMenu.Append(MFS_ENABLED, ID_RESETVOLUME, _T("�f�t�H���g�ɖ߂�(&R)"));
	m_volumeMenu.AppendSeparator();
	m_setVolumeMenu.CreatePopup();
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_0, _T("0%(&A)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_10, _T("10%(&B)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_20, _T("20%(&C)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_30, _T("30%(&D)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_40, _T("40%(&E)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_50, _T("50%(&F)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_60, _T("60%(&G)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_70, _T("70%(&H)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_80, _T("80%(&I)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_90, _T("90%(&J)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_100, _T("100%(&K)"));
	m_volumeMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setVolumeMenu,
		_T("���ʎw��(&V)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_volumeMenu, _T("����(&V)"));
	m_eqPresetMenu.CreatePopup();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQFLAT, _T("FLAT(&F)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWSUPER,
		_T("�ቹ�����i���ŋ��j(&A)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWHIGHEST,
		_T("�ቹ�����i�ŋ��j(&B)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWHIGH,
		_T("�ቹ�����i���j(&C)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWMIDDLE,
		_T("�ቹ�����i���j(&D)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWLOW, _T("�ቹ�����i��j(&E)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWLOWEST,
		_T("�ቹ�����i�Ŏ�j(&G)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLESUPER,
		_T("���������i���ŋ��j(&H)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEHIGHEST,
		_T("���������i�ŋ��j(&I)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEHIGH, 
		_T("���������i���j(&J)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEMIDDLE, 
		_T("���������i���j(&K)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLELOW, 
		_T("���������i��j(&L)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLELOWEST, 
		_T("���������i�Ŏ�j(&M)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHSUPER, 
		_T("���������i���ŋ��j(&N)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHHIGHEST, 
		_T("���������i�ŋ��j(&O)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHHIGH, 
		_T("���������i���j(&P)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHMIDDLE, 
		_T("���������i���j(&Q)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHLOW, 
		_T("���������i��j(&R)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHLOWEST, 
		_T("���������i�Ŏ�j(&S)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTSUPER,
		_T("�ቹ�J�b�g�i���ŋ��j(&T)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTHIGHEST,
		_T("�ቹ�J�b�g�i�ŋ��j(&U)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTHIGH,
		_T("�ቹ�J�b�g�i���j(&V)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTMIDDLE,
		_T("�ቹ�J�b�g�i���j(&W)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTLOW,
		_T("�ቹ�J�b�g�i��j(&X)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTLOWEST,
		_T("�ቹ�J�b�g�i�Ŏ�j(&Y)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTSUPER,
		_T("�����J�b�g�i���ŋ��j(&Z)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTHIGHEST,
		_T("�����J�b�g�i�ŋ��j(&0)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTHIGH, 
		_T("�����J�b�g�i���j(&1)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTMIDDLE, 
		_T("�����J�b�g�i���j(&2)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTLOW, 
		_T("�����J�b�g�i��j(&3)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTLOWEST, 
		_T("�����J�b�g�i�Ŏ�j(&4)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTSUPER, 
		_T("�����J�b�g�i���ŋ��j(&5)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTHIGHEST, 
		_T("�����J�b�g�i�ŋ��j(&6)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTHIGH, 
		_T("�����J�b�g�i���j(&7)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTMIDDLE, 
		_T("�����J�b�g�i���j(&8)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTLOW, 
		_T("�����J�b�g�i��j(&9)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTLOWEST, 
		_T("�����J�b�g�i�Ŏ�j(&0)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqPresetMenu, 
		_T("EQ�v���Z�b�g(&E)"));
	m_effectMenu.AppendSeparator();
	m_reverbMenu.CreatePopup();
	m_reverbMenu.Append(MFS_ENABLED, ID_REVERB_DEFAULT, 
		_T("�f�t�H���g(&D)"));
	m_reverbMenu.AppendSeparator();
	m_reverbMenu.Append(MFS_ENABLED, ID_REVERB_CUSTOMIZE, 
		_T("�J�X�^�}�C�Y(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_reverbMenu, 
		_T("���o�[�u(&R)"));
	m_3dreverbMenu.CreatePopup();
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_DEFAULT, 
		_T("�f�t�H���g(&D)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PADDEDCELL, 
		_T("�N�b�V��������̈��S��(&P)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ROOM, _T("����(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_BATHROOM, _T("����(&B)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LIVINGROOM, _T("���r���O(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_STONEROOM, _T("�Ύ�(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_AUDITORIUM, _T("�u��(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CONCERTHALL, 
		_T("�R���T�[�g�z�[��(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CAVE, _T("���A(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ARENA, _T("�A���[�i(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_HANGAR, _T("�[��(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CARPETEDHALLWAY, 
		_T("�J�[�y�b�g��~�����L��(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_HALLWAY, _T("�L��(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_STONECORRIDOR, 
		_T("�΂̘L��(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ALLEY, _T("���ʂ�(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_FOREST, _T("�X��(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CITY, _T("�s�s(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MOUNTAINS, _T("�R(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_QUARRY, _T("�̐Ώ�(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PLAIN, _T("����(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PARKINGLOT, _T("���ԏ�(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_SEWERPIPE, _T("������(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_UNDERWATER, _T("����(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_SMALLROOM, _T("������(&S)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MEDIUMROOM, _T("������(&M)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LARGEROOM, _T("�啔��(&L)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MEDIUMHALL, _T("���z�[��(&M)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LARGEHALL, _T("��z�[��(&L)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PLATE, _T("�v���[�g(&P)"));
	m_3dreverbMenu.AppendSeparator();
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CUSTOMIZE, 
		_T("�J�X�^�}�C�Y(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_3dreverbMenu, 
		_T("�R�c���o�[�u(&R)"));
	m_delayMenu.CreatePopup();
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DEFAULT, _T("�f�t�H���g(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_SHORT, _T("�Z���G�R�[(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_MEDIUM, 
		_T("�����炢�̃G�R�[(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_LONG, _T("�����G�R�[(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOSHORT,
					   _T("�X�e���I�̒Z���G�R�[(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOMEDIUM,
					   _T("�X�e���I�̒����炢�̃G�R�[(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOLONG,
					   _T("�X�e���I�̒����G�R�[(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_MOUNTAIN, _T("�R�т�(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_BIG, _T("�傫���G�R�[(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOBIG,
					   _T("�X�e���I�̑傫���G�R�[(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DOUBLING, _T("�_�u�����O(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DOUBLEKICK, 
		_T("�_�u���L�b�N(&D)"));
	m_delayMenu.AppendSeparator();
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_CUSTOMIZE, 
		_T("�J�X�^�}�C�Y(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_delayMenu, 
		_T("�f�B���C(&D)"));
	m_chorusMenu.CreatePopup();
	m_chorusMenu.Append(MFS_ENABLED, ID_CHORUS_DEFAULT, _T("�f�t�H���g(&D)"));
	m_chorusMenu.AppendSeparator();
	m_chorusMenu.Append(MFS_ENABLED, ID_CHORUS_CUSTOMIZE,
		_T("�J�X�^�}�C�Y(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_chorusMenu,
						_T("�R�[���X(&C)"));
	m_compressorMenu.CreatePopup();
	m_compressorMenu.Append(MFS_ENABLED, ID_COMPRESSOR_DEFAULT,
							_T("�f�t�H���g(&D)"));
	m_compressorMenu.AppendSeparator();
	m_compressorMenu.Append(MFS_ENABLED, ID_COMPRESSOR_CUSTOMIZE,
							_T("�J�X�^�}�C�Y(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_compressorMenu,
						_T("�R���v���b�T�[(&C)"));
	m_flangerMenu.CreatePopup();
	m_flangerMenu.Append(MFS_ENABLED, ID_FLANGER_DEFAULT,
							_T("�f�t�H���g(&D)"));
	m_flangerMenu.AppendSeparator();
	m_flangerMenu.Append(MFS_ENABLED, ID_FLANGER_CUSTOMIZE,
							_T("�J�X�^�}�C�Y(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_flangerMenu,
						_T("�t�����W���[(&F)"));
	m_gargleMenu.CreatePopup();
	m_gargleMenu.Append(MFS_ENABLED, ID_GARGLE_DEFAULT,
							_T("�f�t�H���g(&D)"));
	m_gargleMenu.AppendSeparator();
	m_gargleMenu.Append(MFS_ENABLED, ID_GARGLE_CUSTOMIZE,
							_T("�J�X�^�}�C�Y(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_gargleMenu,
						_T("�K�[�O��(&G)"));
	m_distortionMenu.CreatePopup();
	m_distortionMenu.Append(MFS_ENABLED, ID_DISTORTION_DEFAULT, 
		_T("�f�t�H���g(&D)"));
	m_distortionMenu.AppendSeparator();
	m_distortionMenu.Append(MFS_ENABLED, ID_DISTORTION_CUSTOMIZE, 
		_T("�J�X�^�}�C�Y(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_distortionMenu,
						_T("�f�B�X�g�[�V����(&D)"));
	m_effectMenu.AppendSeparator();
	m_soundEffectMenu.CreatePopup();
	m_soundEffectMenu.Append(MFS_ENABLED, ID_RECORDNOISE,
		_T("���R�[�h�m�C�Y(&R)"));
	m_soundEffectMenu.Append(MFS_ENABLED, ID_WAVE, _T("�g��(&W)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_soundEffectMenu,
		_T("���ʉ�(&S)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_NORMALIZE, _T("�m�[�}���C�Y(&N)"));
	m_effectMenu.Append(MFS_ENABLED, ID_VOCALCANCEL, 
		_T("�{�[�J���L�����Z��(&V)"));
	m_effectMenu.Append(MFS_ENABLED, ID_REVERSE, _T("�t��]�Đ�(&R)"));
	m_effectMenu.Append(MFS_ENABLED, ID_RECORD, _T("�Âт����R�[�h�Đ�(&F)"));
	m_effectMenu.Append(MFS_ENABLED, ID_LOWBATTERY, _T("�d�r�؂�(&L)"));
	m_effectMenu.Append(MFS_ENABLED, ID_NOSENSE, _T("�̂ւ����[�h(&N)"));
	m_effectMenu.Append(MFS_ENABLED, ID_BASSCOPY, _T("�x�[�X�̎��R�s(&B)"));
	m_effectMenu.Append(MFS_ENABLED, ID_CYMBALCOPY,
		_T("�h�����i�n�C�n�b�g�A�V���o���j�̎��R�s(&D)"));
	m_effectMenu.Append(MFS_ENABLED, ID_EARTRAINING,
		_T("���o�g���[�j���O(&E)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_MONORAL, _T("���m����(&M)"));
	m_effectMenu.Append(MFS_ENABLED, ID_ONLYLEFT, _T("���̂ݍĐ�(&L)"));
	m_effectMenu.Append(MFS_ENABLED, ID_ONLYRIGHT, _T("�E�̂ݍĐ�(&R)"));
	m_effectMenu.Append(MFS_ENABLED, ID_CHANGELR, _T("���E����ւ�(&C)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_RESETALL, _T("�S�ăf�t�H���g�ɖ߂�(&D)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_effectMenu, _T("�G�t�F�N�g(&E)"));

	// �V�X�e�����j���[
	m_systemMenu.CreatePopup();
	m_recoveryMenu.CreatePopup();
	m_recoverVisibleMenu.CreatePopup();
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERVIDEOSCREENVISIBLE, 
		_T("�r�f�I���(&V)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERTIMESLIDERVISIBLE, 
		_T("�Đ��ʒu�X���C�_(&T)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERSPEEDVISIBLE, 
		_T("�Đ����x(&S)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERFREQVISIBLE, 
		_T("�Đ����g��(&F)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERPITCHVISIBLE, 
		_T("����(&P)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERVOLUMEVISIBLE, 
		_T("����(&V)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERPANVISIBLE, 
		_T("�p��(&P)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVEREQVISIBLE, 
		_T("�O���t�B�b�N�C�R���C�U(&G)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERLISTVISIBLE, 
		_T("�Đ����X�g(&P)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverVisibleMenu, 
		_T("�\�����(&V)"));
	m_recoverPlayModeMenu.CreatePopup();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERSLOOP, 
		_T("�P�ȃ��[�v(&1)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERALOOP, 
		_T("�S�ȃ��[�v(&T)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERRANDOM, 
		_T("�����_���Đ�(&H)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERCONTINUE,
		_T("�A���Đ�(&C)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERINSTANTLOOP, 
		_T("�}�[�J�[�ǉ����Ƀ��[�v(&I)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERSETPOSITIONAUTO, 
		_T("�}�[�J�[�ʒu�ύX���ɍĐ��ʒu�ύX(&S)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERREVERSE, 
		_T("�t��]�Đ�(&R)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERRECORD, 
		_T("�Âт����R�[�h�Đ�(&F)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverPlayModeMenu, 
		_T("�Đ����[�h(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERWPOS, 
		_T("�E�B���h�E�ʒu(&P)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERWSIZE, 
		_T("�E�B���h�E�T�C�Y(&S)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPLAYPOS, _T("�Đ��ʒu(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERSPEED, _T("�Đ����x(&S)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERFREQ, 
		_T("�Đ����g��(&F)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPITCH, _T("����(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERVOLUME, _T("����(&V)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPAN, _T("�p��(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVEREQ, 
		_T("�O���t�B�b�N�C�R���C�U(&G)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERLIST, _T("�Đ����X�g(&P)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoveryMenu, 
		_T("����(&R)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_KEYSETTING, 
		_T("�V���[�g�J�b�g�L�[�ݒ�(&K)..."));
	m_systemMenu.Append(MF_ENABLED, ID_OUTKEYSETTING, 
		_T("�O���[�o���z�b�g�L�[�ݒ�(&G)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_LIMIT, 
		_T("�ő�l�^�ŏ��l�̐ݒ�(&L)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_TIMERPLAY, _T("�^�C�}�[�ݒ�(&T)..."));
	m_systemMenu.Append(MF_ENABLED, ID_PLAYRANGE, _T("�Đ��͈�(&R)..."));
	m_systemMenu.Append(MF_ENABLED, ID_PLAYPOSITION, _T("�Đ��ʒu(&P)..."));
	m_systemMenu.Append(MF_ENABLED, ID_FADEOUTSTOP,
		_T("�Đ���~���Ƀt�F�[�h�A�E�g(&F)"));
	m_fadeoutMenu.CreatePopup();
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP1SEC, _T("1�b(&1)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP2SEC, _T("2�b(&2)"));
	m_fadeoutMenu.Append(MFS_CHECKED, ID_FADEOUTSTOP3SEC, _T("3�b(&3)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP4SEC, _T("4�b(&4)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP5SEC, _T("5�b(&5)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP6SEC, _T("6�b(&6)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP7SEC, _T("7�b(&7)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP8SEC, _T("8�b(&8)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP9SEC, _T("9�b(&9)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP10SEC, _T("10�b(&A)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_fadeoutMenu,
		_T("��~���t�F�[�h�A�E�g����(&G)"));
	m_systemMenu.Append(MF_ENABLED, ID_FADEOUTNEXT, 
		_T("�Ȃ̐ؑ֎��Ƀt�F�[�h�A�E�g(&F)"));
	m_fadeoutNextMenu.CreatePopup();
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT1SEC, _T("1�b(&1)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT2SEC, _T("2�b(&2)"));
	m_fadeoutNextMenu.Append(MFS_CHECKED, ID_FADEOUTNEXT3SEC, _T("3�b(&3)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT4SEC, _T("4�b(&4)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT5SEC, _T("5�b(&5)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT6SEC, _T("6�b(&6)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT7SEC, _T("7�b(&7)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT8SEC, _T("8�b(&8)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT9SEC, _T("9�b(&9)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT10SEC, _T("10�b(&A)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_fadeoutNextMenu,
		_T("�ؑ֎��t�F�[�h�A�E�g����(&H)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_TWEET, 
		_T("Twitter�łԂ₭(&T)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_METRONOME, 
		_T("���g���m�[���@�\(&M)..."));
	m_systemMenu.AppendSeparator();
	m_qualityMenu.CreatePopup();
	m_qualityMenu.Append(MFS_CHECKED, ID_QUALITY_NORMAL, _T("�m�[�}��(&N)"));
	m_qualityMenu.Append(MF_ENABLED, ID_QUALITY_ASIO, _T("ASIO(&A)"));
	m_qualityMenu.Append(MF_ENABLED, ID_QUALITY_WASAPI, _T("WASAPI(&W)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_qualityMenu,
		_T("����(&Q)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_DOUBLERUN, _T("���d�N��(&D)"));
	m_systemMenu.Append(MF_ENABLED, ID_TOPMOST, _T("�őO�ʕ\��(&S)"));
	m_systemMenu.Append(MF_ENABLED, ID_TASKTRAY, 
		_T("�ŏ������^�X�N�g���C�Ɋi�[(&T)"));
	m_systemMenu.Append(MF_ENABLED, ID_COPYTIME, 
		_T("���݂̍Đ��ʒu���N���b�v�{�[�h�ɃR�s�[(&C)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_systemMenu, _T("�V�X�e��(&S)"));

	CheckItem(ID_CONTINUE, MF_CHECKED);

	// �w���v���j���[
	m_helpMenu.CreatePopup();
	m_helpMenu.Append(MFS_ENABLED, ID_MANUAL,
		_T("�I�����C���}�j���A��(&M)..."));
	m_helpMenu.AppendSeparator();
	m_helpMenu.Append(MFS_ENABLED, ID_UPDATECHECK, 
		_T("�A�b�v�f�[�g�̊m�F(&U)..."));
	m_helpMenu.Append(MFS_ENABLED, ID_VERSIONINFO, 
		_T("�o�[�W�������(&A)..."));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_helpMenu, _T("�w���v(&H)"));
#else // JP
	// �t�@�C�����j���[
	m_fileMenu.CreatePopup();
	m_fileMenu.Append(MFS_ENABLED, ID_OPENFILE, _T("Open(&O)...\tCtrl+O"));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDFILE, _T("Add(&P)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_OPENFOLDER, _T("Open Directory(&F)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDFOLDER, _T("Add Directory(&G)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_OPENURL, _T("Open URL(&O)..."));
	m_fileMenu.Append(MFS_ENABLED, ID_ADDURL, _T("Add URL(&A)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_DISABLED, ID_SAVEFILE, _T("Save(&S)...\tCtrl+E"));
	m_fileMenu.Append(MFS_DISABLED, ID_SAVEALLFILE, _T("Save All(&A)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_ENABLED, ID_LAMECOMMANDLINE,
		_T("LAME Command Line Option(&L)..."));
	m_fileMenu.AppendSeparator();
	m_fileMenu.Append(MFS_ENABLED, ID_EXIT, _T("Exit(&X)\tAlt+F4"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_fileMenu, _T("File(&F)"));

	// �ҏW���j���[
	m_editMenu.CreatePopup();
	m_editMenu.Append(MFS_ENABLED, ID_DELETE, _T("Delete(&D)"));
	m_editMenu.Append(MFS_ENABLED, ID_SELECTALL, _T("Select All(&A)\tCtrl+A"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_editMenu, _T("Edit(&E)"));

	// �\�����j���[
	m_viewMenu.CreatePopup();
	m_videoScreenMenu.CreatePopup();
	m_videoScreenMenu.Append(MFS_ENABLED, ID_VIDEOSCREEN, _T("Visible(&V)"));
	m_videoScreenMenu.AppendSeparator();
	m_videoScreenMenu.Append(MFS_CHECKED, ID_LYRICS, _T("Lyrics(&L)"));
	m_videoScreenMenu.Append(MFS_ENABLED, ID_PITCHANALYSER,
		_T("Pitch Analyser(&P)"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_videoScreenMenu,
		_T("Video Screen(&V)"));
	m_viewMenu.Append(MFS_ENABLED, ID_TIMESLIDER, _T("Position Slider(&T)"));
	m_viewMenu.Append(MFS_ENABLED, ID_EXPLORER, _T("Explorer(&E)"));
	m_viewMenu.Append(MFS_ENABLED, ID_SPEED, _T("Speed(&S)"));
	m_viewMenu.Append(MFS_ENABLED, ID_FREQ, _T("Frequency(&F)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PITCH, _T("Pitch(&P)"));
	m_viewMenu.Append(MFS_ENABLED, ID_VOLUME, _T("Volume(&V)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PAN, _T("Pan(&P)"));
	m_eqMenu.CreatePopup();
	m_eqMenu.Append(MFS_ENABLED, ID_EQ, _T("Visible(&V)"));
	m_eqMenu.AppendSeparator();
	m_eqMenu.Append(MFS_ENABLED, ID_EQ20, _T("20 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ25, _T("25 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ31_5, _T("31.5 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ40, _T("40 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ50, _T("50 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ63, _T("63 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ80, _T("80 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ100, _T("100 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ125, _T("125 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ160, _T("160 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ200, _T("200 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ250, _T("250 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ315, _T("315 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ400, _T("400 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ500, _T("500 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ630, _T("630 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ800, _T("800 Hz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1K, _T("1 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1_25K, _T("1.25 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ1_6K, _T("1.6 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ2K, _T("2 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ2_5K, _T("2.5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ3_15K, _T("3.15 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ4K, _T("4 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ5K, _T("5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ6_3K, _T("6.3 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ8K, _T("8 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ10K, _T("10 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ12_5K, _T("12.5 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ16K, _T("16 KHz"));
	m_eqMenu.Append(MFS_ENABLED, ID_EQ20K, _T("20 KHz"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqMenu,
		_T("EQ(&G)"));
	m_viewMenu.Append(MFS_CHECKED, ID_TAB, _T("Tab(&T)"));
	m_viewMenu.Append(MFS_ENABLED, ID_PLAYLIST, _T("Playlist(&P)"));
	m_viewMenu.AppendSeparator();
	m_viewMenu.Append(MFS_ENABLED, ID_CLOSEALL, _T("Close All(&C)"));
	m_viewMenu.AppendSeparator();
	m_toolbarMenu.CreatePopup();
	m_toolbarMenu.Append(MFS_CHECKED, ID_TOOLBAR_SIZES, _T("S size(&S)"));
	m_toolbarMenu.Append(MFS_ENABLED, ID_TOOLBAR_SIZEM, _T("M size(&M)"));
	m_toolbarMenu.Append(MFS_ENABLED, ID_TOOLBAR_SIZEL, _T("L size(&L)"));
	m_toolbarMenu.AppendSeparator();
	m_toolbarMenu.Append(MFS_ENABLED, ID_CUSTOMIZETOOLBAR,
		_T("Customize(&T)"));
	m_viewMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_toolbarMenu, _T("Toolbar"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_viewMenu, _T("View(&V)"));

	// �Đ����j���[
	m_playMenu.CreatePopup();
	m_playMenu.Append(MFS_ENABLED, ID_PAUSE, _T("Play/Pause(&P)\tCtrl+P"));
	m_playMenu.Append(MFS_ENABLED, ID_STOP, _T("Stop(&S)\tCtrl+S"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_HEAD, _T("Head(&T)\tCtrl+0"));
	m_playMenu.Append(MFS_ENABLED, ID_PREV, _T("Previous(&V)\tCtrl+B"));
	m_playMenu.Append(MFS_ENABLED, ID_NEXT, _T("Next(&N)\tCtrl+F"));
	m_playMenu.Append(MFS_ENABLED, ID_REWIND, _T("Rewind(&R)\tCtrl+Shift+B"));
	m_playMenu.Append(MFS_ENABLED, ID_FORWARD, 
		_T("Forward(&A)\tCtrl+Shift+F"));
	m_playMenu.AppendSeparator();
	m_returnMenu.CreatePopup();
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN1SEC, _T("Rewind 1 sec.(&1)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN2SEC, _T("Rewind 2 sec.(&2)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN3SEC, _T("Rewind 3 sec.(&3)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN5SEC, _T("Rewind 5 sec.(&5)"));
	m_returnMenu.Append(MFS_ENABLED, ID_RETURN10SEC, _T("Rewind 10 sec.(&T)"));
	m_playMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_returnMenu, 
		_T("Rewind(&R)"));
	m_forwardMenu.CreatePopup();
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD1SEC, 
		_T("Forward 1 sec.(&1)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD2SEC, 
		_T("Forward 2 sec.(&2)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD3SEC, 
		_T("Forward 3 sec.(&3)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD5SEC, 
		_T("Forward 5 sec.(&5)"));
	m_forwardMenu.Append(MFS_ENABLED, ID_FORWARD10SEC, 
		_T("Forward 10 sec.(&T)"));
	m_playMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_forwardMenu, 
		_T("Forward(&F)"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_SLOOP, _T("Single Loop(&1)\tCtrl+1"));
	m_playMenu.Append(MF_ENABLED, ID_ALOOP, _T("All Loop(&T)\tCtrl+T"));
	m_playMenu.Append(MFS_ENABLED, ID_RANDOM, _T("Random Play(&H)\tCtrl+H"));
	m_playMenu.Append(MFS_ENABLED, ID_CONTINUE, _T("Continuous Play(&C)"));
	m_playMenu.Append(MFS_ENABLED, ID_SAMEARTIST, _T("Same Artist(&S)"));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_ABLOOP_A,
		_T("Set AB Loop(A) To Current Position(&A)"));
	m_playMenu.Append(MFS_ENABLED, ID_ABLOOP_B,
		_T("Set AB Loop(B) To Current Position(&B)"));
	m_playMenu.Append(MFS_DISABLED, ID_ABLOOP_A_SETTING,
		_T("AB Loop(A) Pos Setting(&C)..."));
	m_playMenu.Append(MFS_DISABLED, ID_ABLOOP_B_SETTING,
		_T("AB Loop(B) Pos Setting(&D)..."));
	m_playMenu.AppendSeparator();
	m_playMenu.Append(MFS_ENABLED, ID_MARKERPLAY, _T("Marker Play(&M)"));
	m_playMenu.Append(MFS_ENABLED, ID_ADDMARKER, _T("Add a Marker(&A)"));
	m_playMenu.Append(MFS_ENABLED, ID_DELETEMARKER, _T("Delete a Marker(&D)"));
	m_playMenu.Append(MFS_DISABLED, ID_COUNTLOOP, _T("Count Loop(&C)"));
	m_playMenu.Append(MFS_ENABLED, ID_INSTANTLOOP, 
		_T("Loop when adding a marker(&I)"));
	m_playMenu.Append(MFS_ENABLED, ID_SETPOSITIONAUTO, 
		_T("Set position automatic when adjusting marker position(&S)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_playMenu, _T("Play(&P)"));

	// �G�t�F�N�g���j���[
	m_effectMenu.CreatePopup();
	m_presetMenu.CreatePopup();
	m_presetMenu.Append(MFS_ENABLED, ID_ADDPRESET, _T("Add Current Settings(&A)"));
	m_presetMenu.Append(MFS_DISABLED, ID_DELETEPRESET, _T("Delete Selected Preset(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_presetMenu,
		_T("Preset(&P)"));
	m_effectMenu.AppendSeparator();
	m_speedMenu.CreatePopup();
	m_speedMenu.Append(MFS_ENABLED, ID_RESETSPEED, _T("Reset Speed(&R)"));
	m_speedMenu.AppendSeparator();
	m_setSpeedMenu.CreatePopup();
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_50, _T("50%(&A)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_60, _T("60%(&B)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_70, _T("70%(&C)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_80, _T("80%(&D)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_90, _T("90%(&E)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_100, _T("100%(&F)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_110, _T("110%(&G)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_120, _T("120%(&H)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_130, _T("130%(&I)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_140, _T("140%(&J)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_150, _T("150%(&K)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_160, _T("160%(&L)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_170, _T("170%(&M)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_180, _T("180%(&N)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_190, _T("190%(&O)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_200, _T("200%(&P)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_250, _T("250%(&Q)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_300, _T("300%(&R)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_350, _T("350%(&S)"));
	m_setSpeedMenu.Append(MFS_ENABLED, ID_SPEED_400, _T("400%(&T)"));
	m_speedMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setSpeedMenu,
		_T("Set Speed(&S)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN0_1SPEED, _T("Turn Down 0.1%(&0)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN1SPEED, _T("Turn Down 1%(&1)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN2SPEED, _T("Turn Down 2%(&2)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN3SPEED, _T("Turn Down 3%(&3)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN5SPEED, _T("Turn Down 5%(&5)"));
	m_speedMenu.Append(MFS_ENABLED, ID_DOWN10SPEED, _T("Turn Down 10%(&T)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MFS_ENABLED, ID_UP0_1SPEED, _T("Turn Up 0.1%(&Z)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP1SPEED, _T("Turn Up 1%(&A)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP2SPEED, _T("Turn Up 2%(&B)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP3SPEED, _T("Turn Up 3%(&C)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP5SPEED, _T("Turn Up 5%(&D)"));
	m_speedMenu.Append(MFS_ENABLED, ID_UP10SPEED, _T("Turn Up 10%(&E)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(MF_ENABLED, ID_DECSPEED, _T("Decrease(&D)..."));
	m_speedMenu.Append(MF_ENABLED, ID_INCSPEED, _T("Increase(&D)..."));
	m_speedMenu.AppendSeparator();
	m_speedDecimalMenu.CreatePopup();
	m_speedDecimalMenu.Append(MFS_ENABLED, ID_SPEEDDEC_0, _T("0 digit(&0)"));
	m_speedDecimalMenu.Append(MFS_ENABLED, ID_SPEEDDEC_1, _T("1 digit(&1)"));
	m_speedDecimalMenu.Append(MFS_ENABLED, ID_SPEEDDEC_2, _T("2 digit(&2)"));
	m_speedMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedDecimalMenu,
		_T("Decimal Digit"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedMenu, 
		_T("Speed(&S)"));
	m_freqMenu.CreatePopup();
	m_freqMenu.Append(MFS_ENABLED, ID_RESETFREQ, _T("Reset Frequency(&R)"));
	m_freqMenu.AppendSeparator();
	m_setFreqMenu.CreatePopup();
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_50, _T("50%(&A)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_60, _T("60%(&B)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_70, _T("70%(&C)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_80, _T("80%(&D)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_90, _T("90%(&E)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_100, _T("100%(&F)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_110, _T("110%(&G)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_120, _T("120%(&H)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_130, _T("130%(&I)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_140, _T("140%(&J)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_150, _T("150%(&K)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_160, _T("160%(&L)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_170, _T("170%(&M)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_180, _T("180%(&N)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_190, _T("190%(&O)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_200, _T("200%(&P)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_250, _T("250%(&Q)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_300, _T("300%(&R)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_350, _T("350%(&S)"));
	m_setFreqMenu.Append(MFS_ENABLED, ID_FREQ_400, _T("400%(&T)"));
	m_freqMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setFreqMenu,
		_T("Set Frequency(&F)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN0_1FREQ, _T("Turn Down 0.1%(&0)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN1FREQ, _T("Turn Down 1%(&1)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN2FREQ, _T("Turn Down 2%(&2)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN3FREQ, _T("Turn Down 3%(&3)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN5FREQ, _T("Turn Down 5%(&5)"));
	m_freqMenu.Append(MFS_ENABLED, ID_DOWN10FREQ, _T("Turn Down 10%(&T)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MFS_ENABLED, ID_UP0_1FREQ, _T("Turn Up 0.1%(&Z)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP1FREQ, _T("Turn Up 1%(&A)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP2FREQ, _T("Turn Up 2%(&B)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP3FREQ, _T("Turn Up 3%(&C)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP5FREQ, _T("Turn Up 5%(&D)"));
	m_freqMenu.Append(MFS_ENABLED, ID_UP10FREQ, _T("Turn Up 10%(&E)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(MF_ENABLED, ID_DECFREQ, _T("Decrease(&F)..."));
	m_freqMenu.Append(MF_ENABLED, ID_INCFREQ, _T("Increase(&F)..."));
	m_freqMenu.AppendSeparator();
	m_freqDecimalMenu.CreatePopup();
	m_freqDecimalMenu.Append(MFS_ENABLED, ID_FREQDEC_0, _T("0 digit(&0)"));
	m_freqDecimalMenu.Append(MFS_ENABLED, ID_FREQDEC_1, _T("1 digit(&1)"));
	m_freqDecimalMenu.Append(MFS_ENABLED, ID_FREQDEC_2, _T("2 digit(&2)"));
	m_freqMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqDecimalMenu,
		_T("Decimal Digit"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqMenu, 
		_T("Frequency(&F)"));
	m_pitchMenu.CreatePopup();
	m_pitchMenu.Append(MFS_ENABLED, ID_RESETPITCH, _T("Reset pitch(&R)"));
	m_pitchMenu.AppendSeparator();
	m_setPitchMenu.CreatePopup();
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F12, _T("��12(&A)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F11, _T("��11(&B)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F10, _T("��10(&C)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F9, _T("��9(&D)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F8, _T("��8(&E)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F7, _T("��7(&F)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F6, _T("��6(&G)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F5, _T("��5(&H)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F4, _T("��4(&I)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F3, _T("��3(&J)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F2, _T("��2(&K)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_F1, _T("��1(&L)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_0, _T("0(&M)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S1, _T("��1(&N)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S2, _T("��2(&O)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S3, _T("��3(&P)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S4, _T("��4(&Q)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S5, _T("��5(&R)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S6, _T("��6(&S)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S7, _T("��7(&T)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S8, _T("��8(&U)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S9, _T("��9(&V)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S10, _T("��10(&W)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S11, _T("��11(&X)"));
	m_setPitchMenu.Append(MFS_ENABLED, ID_PITCH_S12, _T("��12(&Y)"));
	m_pitchMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setPitchMenu,
		_T("Set Pitch(&F)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN1PITCH, _T("Flat(&1)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN2PITCH, _T("Double Flat(&2)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_DOWN1OCTPITCH, _T("Down 1 Octave(&3)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(MFS_ENABLED, ID_UP1PITCH, _T("Sharp(&A)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_UP2PITCH, _T("Double Sharp(&B)"));
	m_pitchMenu.Append(MFS_ENABLED, ID_UP1OCTPITCH, _T("Up 1 Octave(&C)"));
	m_pitchMenu.AppendSeparator();
	m_pitchDecimalMenu.CreatePopup();
	m_pitchDecimalMenu.Append(MFS_ENABLED, ID_PITCHDEC_0, _T("0 digit(&0)"));
	m_pitchDecimalMenu.Append(MFS_CHECKED, ID_PITCHDEC_1, _T("1 digit(&1)"));
	m_pitchDecimalMenu.Append(MFS_ENABLED, ID_PITCHDEC_2, _T("2 digit(&2)"));
	m_pitchMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchDecimalMenu,
		_T("Decimal Digit"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchMenu, 
		_T("Pitch(&P)"));
	m_volumeMenu.CreatePopup();
	m_volumeMenu.Append(MFS_ENABLED, ID_RESETVOLUME, _T("Reset Volume(&R)"));
	m_volumeMenu.AppendSeparator();
	m_setVolumeMenu.CreatePopup();
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_0, _T("0%(&A)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_10, _T("10%(&B)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_20, _T("20%(&C)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_30, _T("30%(&D)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_40, _T("40%(&E)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_50, _T("50%(&F)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_60, _T("60%(&G)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_70, _T("70%(&H)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_80, _T("80%(&I)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_90, _T("90%(&J)"));
	m_setVolumeMenu.Append(MFS_ENABLED, ID_VOLUME_100, _T("100%(&K)"));
	m_volumeMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_setVolumeMenu,
		_T("Set Volume(&V)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_volumeMenu,
		_T("Volume(&V)"));
	m_eqPresetMenu.CreatePopup();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQFLAT, _T("FLAT(&F)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWSUPER, 
		_T("Boost Low(Ultra-strong)(&A)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWHIGHEST, 
		_T("Boost Low(Strongest)(&B)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWHIGH, 
		_T("Boost Low(Strong)(&C)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWMIDDLE, 
		_T("Boost Low(Middle)(&D)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWLOW, _T("Boost Low(Weak)(&E)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWLOWEST, 
		_T("Boost Low(Weakest)(&G)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLESUPER, 
		_T("Boost Middle(Ultra-strong)(&H)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEHIGHEST, 
		_T("Boost Middle(Strongest)(&I)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEHIGH, 
		_T("Boost Middle(Strong)(&J)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLEMIDDLE, 
		_T("Boost Middle(Middle)(&K)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLELOW, 
		_T("Boost Middle(Weak)(&L)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLELOWEST, 
		_T("Boost Middle(Weakest)(&M)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHSUPER, 
		_T("Boost High(Ultra-strong)(&N)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHHIGHEST, 
		_T("Boost High(Strongest)(&O)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHHIGH, 
		_T("Boost High(Strong)(&P)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHMIDDLE, 
		_T("Boost High(Middle)(&Q)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHLOW, 
		_T("Boost High(Weak)(&R)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHLOWEST, 
		_T("Boost High(Weakest)(&S)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTSUPER, 
		_T("Low Cut(Ultra-strong)(&T)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTHIGHEST, 
		_T("Low Cut(Strongest)(&U)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTHIGH, 
		_T("Low Cut(Strong)(&V)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTMIDDLE, 
		_T("Low Cut(Middle)(&W)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTLOW, _T("Low Cut(Weak)(&X)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQLOWCUTLOWEST, 
		_T("Low Cut(Weakest)(&Y)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTSUPER, 
		_T("Middle Cut(Ultra-strong)(&Z)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTHIGHEST, 
		_T("Middle Cut(Strongest)(&0)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTHIGH, 
		_T("Middle Cut(Strong)(&1)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTMIDDLE, 
		_T("Middle Cut(Middle)(&2)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTLOW, 
		_T("Middle Cut(Weak)(&3)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQMIDDLECUTLOWEST, 
		_T("Middle Cut(Weakest)(&4)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTSUPER, 
		_T("High Cut(Ultra-strong)(&5)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTHIGHEST, 
		_T("High Cut(Strongest)(&6)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTHIGH, 
		_T("High Cut(Strong)(&7)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTMIDDLE, 
		_T("High Cut(Middle)(&8)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTLOW, 
		_T("High Cut(Weak)(&9)"));
	m_eqPresetMenu.Append(MFS_ENABLED, ID_EQHIGHCUTLOWEST, 
		_T("High Cut(Weakest)(&0)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqPresetMenu, 
		_T("EQ Preset(&E)"));
	m_effectMenu.AppendSeparator();
	m_reverbMenu.CreatePopup();
	m_reverbMenu.Append(MFS_ENABLED, ID_REVERB_DEFAULT, _T("Default(&D)"));
	m_reverbMenu.AppendSeparator();
	m_reverbMenu.Append(MFS_ENABLED, ID_REVERB_CUSTOMIZE, _T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_reverbMenu, 
		_T("Reverb(&R)"));
	m_3dreverbMenu.CreatePopup();
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_DEFAULT, _T("Default(&D)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PADDEDCELL, 
		_T("Padded Cell(&P)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ROOM, _T("Room(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_BATHROOM, _T("Bathroom(&B)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LIVINGROOM, 
		_T("Living Room(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_STONEROOM, 
		_T("Stone Room(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_AUDITORIUM, 
		_T("Auditorium(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CONCERTHALL, 
		_T("Concert Hall(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CAVE, _T("Cave(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ARENA, _T("Arena(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_HANGAR, _T("Hangar(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CARPETEDHALLWAY, 
		_T("Carpeted Hallway(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_HALLWAY, _T("Hallway(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_STONECORRIDOR, 
		_T("Stone Corridor(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_ALLEY, _T("Alley(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_FOREST, _T("Forest(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CITY, _T("City(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MOUNTAINS, _T("Mountains(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_QUARRY, _T("Quarry(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PLAIN, _T("Plain(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PARKINGLOT, 
		_T("Parking Lot(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_SEWERPIPE, 
		_T("Sewer Pipe(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_UNDERWATER, 
		_T("Underwater(&R)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_SMALLROOM, 
		_T("Small Room(&S)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MEDIUMROOM, 
		_T("Medium Room(&M)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LARGEROOM, 
		_T("Large Room(&L)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_MEDIUMHALL, 
		_T("Medium Hall(&M)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_LARGEHALL, 
		_T("Large Hall(&L)"));
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_PLATE, _T("Plate(&P)"));
	m_3dreverbMenu.AppendSeparator();
	m_3dreverbMenu.Append(MFS_ENABLED, ID_3DREVERB_CUSTOMIZE,
		_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_3dreverbMenu, 
		_T("3D Reverb(&R)"));
	m_delayMenu.CreatePopup();
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DEFAULT, _T("Default(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_SHORT, _T("Short Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_MEDIUM, _T("Medium Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_LONG, _T("Long Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOSHORT,
					   _T("Stereo Short Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOMEDIUM,
					   _T("Stereo Medium Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOLONG,
					   _T("Stereo Long Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_MOUNTAIN, 
		_T("Mountain Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_BIG, _T("Big Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_STEREOBIG,
					   _T("Stereo Big Echo(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DOUBLING, _T("Doubling(&D)"));
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_DOUBLEKICK, 
		_T("Double Kick(&D)"));
	m_delayMenu.AppendSeparator();
	m_delayMenu.Append(MFS_ENABLED, ID_DELAY_CUSTOMIZE, 
		_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_delayMenu, 
		_T("Delay(&D)"));
	m_chorusMenu.CreatePopup();
	m_chorusMenu.Append(MFS_ENABLED, ID_CHORUS_DEFAULT, _T("Default(&D)"));
	m_chorusMenu.AppendSeparator();
	m_chorusMenu.Append(MFS_ENABLED, ID_CHORUS_CUSTOMIZE, _T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_chorusMenu,
						_T("Chorus(&C)"));
	m_compressorMenu.CreatePopup();
	m_compressorMenu.Append(MFS_ENABLED, ID_COMPRESSOR_DEFAULT,
							_T("Default(&D)"));
	m_compressorMenu.AppendSeparator();
	m_compressorMenu.Append(MFS_ENABLED, ID_COMPRESSOR_CUSTOMIZE,
							_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_compressorMenu,
						_T("Compressor(&C)"));
	m_flangerMenu.CreatePopup();
	m_flangerMenu.Append(MFS_ENABLED, ID_FLANGER_DEFAULT,
							_T("Default(&D)"));
	m_flangerMenu.AppendSeparator();
	m_flangerMenu.Append(MFS_ENABLED, ID_FLANGER_CUSTOMIZE,
							_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_flangerMenu,
						_T("Flanger(&F)"));
	m_gargleMenu.CreatePopup();
	m_gargleMenu.Append(MFS_ENABLED, ID_GARGLE_DEFAULT,
							_T("Default(&D)"));
	m_gargleMenu.AppendSeparator();
	m_gargleMenu.Append(MFS_ENABLED, ID_GARGLE_CUSTOMIZE,
							_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_gargleMenu,
						_T("Gargle(&F)"));
	m_distortionMenu.CreatePopup();
	m_distortionMenu.Append(MFS_ENABLED, ID_DISTORTION_DEFAULT, 
		_T("Default(&D)"));
	m_distortionMenu.AppendSeparator();
	m_distortionMenu.Append(MFS_ENABLED, ID_DISTORTION_CUSTOMIZE, 
		_T("Customize(&C)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_distortionMenu,
						_T("Distortion(&D)"));
	m_effectMenu.AppendSeparator();
	m_soundEffectMenu.CreatePopup();
	m_soundEffectMenu.Append(MFS_ENABLED, ID_RECORDNOISE,
		_T("Record Noise(&R)"));
	m_soundEffectMenu.Append(MFS_ENABLED, ID_WAVE, _T("Wave(&W)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_soundEffectMenu,
		_T("Sound Effects(&S)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_NORMALIZE, _T("Normalize(&N)"));
	m_effectMenu.Append(MFS_ENABLED, ID_VOCALCANCEL, _T("Vocal Cancel(&V)"));
	m_effectMenu.Append(MFS_ENABLED, ID_REVERSE, _T("Reverse Play(&R)"));
	m_effectMenu.Append(MFS_ENABLED, ID_RECORD, _T("Old Record Play(&F)"));
	m_effectMenu.Append(MFS_ENABLED, ID_LOWBATTERY, _T("Low Battery(&L)"));
	m_effectMenu.Append(MFS_ENABLED, ID_NOSENSE, _T("No Sense(&N)"));
	m_effectMenu.Append(MFS_ENABLED, ID_BASSCOPY, _T("Transcribe Bass(&T)"));
	m_effectMenu.Append(MFS_ENABLED, ID_CYMBALCOPY,
		_T("Transcribe Drums (Hi-Hat, Cymbals)(&H)"));
	m_effectMenu.Append(MFS_ENABLED, ID_EARTRAINING, _T("Ear Training(&E)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_MONORAL, _T("Monoral(&M)"));
	m_effectMenu.Append(MFS_ENABLED, ID_ONLYLEFT, _T("Only Left(&L)"));
	m_effectMenu.Append(MFS_ENABLED, ID_ONLYRIGHT, _T("Only Right(&R)"));
	m_effectMenu.Append(MFS_ENABLED, ID_CHANGELR, _T("Change LR(&C)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(MFS_ENABLED, ID_RESETALL, _T("Reset All(&R)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_effectMenu, _T("Effect(&E)"));

	// �V�X�e�����j���[
	m_systemMenu.CreatePopup();
	m_recoveryMenu.CreatePopup();
	m_recoverVisibleMenu.CreatePopup();
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERVIDEOSCREENVISIBLE, 
		_T("Video Screen(&V)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERTIMESLIDERVISIBLE, 
		_T("Position Slider(&T)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERSPEEDVISIBLE, 
		_T("Speed(&S)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERFREQVISIBLE, 
		_T("Frequency(&F)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERPITCHVISIBLE, 
		_T("Pitch(&P)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERVOLUMEVISIBLE, 
		_T("Volume(&V)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERPANVISIBLE, 
		_T("PAN(&P)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVEREQVISIBLE, 
		_T("Graphic Equalizer(&G)"));
	m_recoverVisibleMenu.Append(MFS_ENABLED, ID_RECOVERLISTVISIBLE, 
		_T("Playlist(&P)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverVisibleMenu, 
		_T("Visible(&V)"));
	m_recoverPlayModeMenu.CreatePopup();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERSLOOP, 
		_T("Single Loop(&1)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERALOOP, 
		_T("All Loop(&T)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERRANDOM, 
		_T("Random(&H)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERCONTINUE, 
		_T("Continue(&C)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERINSTANTLOOP, 
		_T("Loop when adding a marker(&I)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERSETPOSITIONAUTO, 
		_T("Set position automatic when adjusting marker position(&S)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERREVERSE, 
		_T("Reverse(&R)"));
	m_recoverPlayModeMenu.Append(MFS_ENABLED, ID_RECOVERRECORD, 
		_T("Record(&F)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverPlayModeMenu, 
		_T("Play Mode(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERWPOS, 
		_T("Window Position(&P)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERWSIZE, _T("Window Size(&S)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPLAYPOS,
		_T("Play Position(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERSPEED, _T("Speed(&S)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERFREQ, 
		_T("Frequency(&F)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPITCH, _T("Pitch(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERVOLUME, _T("Volume(&V)"));
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERPAN, _T("Pan(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVEREQ, 
		_T("Graphic Equalizer(&G)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(MFS_ENABLED, ID_RECOVERLIST, _T("Playlist(&P)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoveryMenu, 
		_T("Recover(&R)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_KEYSETTING, 
		_T("Shortcut Key Setting(&K)..."));
	m_systemMenu.Append(MF_ENABLED, ID_OUTKEYSETTING, 
		_T("Global Hot Key Setting(&G)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_LIMIT, _T("Max/Min Setting(&L)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_TIMERPLAY, _T("Timer Setting(&T)..."));
	m_systemMenu.Append(MF_ENABLED, ID_PLAYRANGE, 
		_T("Play Range(&R)..."));
	m_systemMenu.Append(MF_ENABLED, ID_PLAYPOSITION, 
		_T("Play Position(&P)..."));
	m_systemMenu.Append(MF_ENABLED, ID_FADEOUTSTOP, _T("Fade Out Stop(&F)"));
	m_fadeoutMenu.CreatePopup();
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP1SEC, _T("1 sec(&1)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP2SEC, _T("2 sec(&2)"));
	m_fadeoutMenu.Append(MFS_CHECKED, ID_FADEOUTSTOP3SEC, _T("3 sec(&3)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP4SEC, _T("4 sec(&4)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP5SEC, _T("5 sec(&5)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP6SEC, _T("6 sec(&6)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP7SEC, _T("7 sec(&7)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP8SEC, _T("8 sec(&8)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP9SEC, _T("9 sec(&9)"));
	m_fadeoutMenu.Append(MF_ENABLED, ID_FADEOUTSTOP10SEC, _T("10 sec(&A)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_fadeoutMenu,
		_T("Fade Out Stop Time(&G)"));
	m_systemMenu.Append(MF_ENABLED, ID_FADEOUTNEXT, _T("Fade Out Next(&F)"));
	m_fadeoutNextMenu.CreatePopup();
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT1SEC, _T("1 sec(&1)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT2SEC, _T("2 sec(&2)"));
	m_fadeoutNextMenu.Append(MFS_CHECKED, ID_FADEOUTNEXT3SEC, _T("3 sec(&3)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT4SEC, _T("4 sec(&4)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT5SEC, _T("5 sec(&5)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT6SEC, _T("6 sec(&6)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT7SEC, _T("7 sec(&7)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT8SEC, _T("8 sec(&8)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT9SEC, _T("9 sec(&9)"));
	m_fadeoutNextMenu.Append(MF_ENABLED, ID_FADEOUTNEXT10SEC, _T("10 sec(&A)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_fadeoutNextMenu,
		_T("Fade Out Next Time(&H)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_TWEET, _T("Tweet on Twitter(&T)..."));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_METRONOME, _T("Metronome(&M)..."));
	m_systemMenu.AppendSeparator();
	m_qualityMenu.CreatePopup();
	m_qualityMenu.Append(MFS_CHECKED, ID_QUALITY_NORMAL, _T("Normal(&N)"));
	m_qualityMenu.Append(MF_ENABLED, ID_QUALITY_ASIO, _T("ASIO(&A)"));
	m_qualityMenu.Append(MF_ENABLED, ID_QUALITY_WASAPI, _T("WASAPI(&W)"));
	m_systemMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_qualityMenu,
		_T("Quality(&Q)"));
	m_systemMenu.AppendSeparator();
	m_systemMenu.Append(MF_ENABLED, ID_DOUBLERUN, _T("Double Runnable(&D)"));
	m_systemMenu.Append(MF_ENABLED, ID_TOPMOST, _T("Bring Window Top(&S)"));
	m_systemMenu.Append(MF_ENABLED, ID_TASKTRAY, 
		_T("Minimize to System Tray(&T)"));
	m_systemMenu.Append(MF_ENABLED, ID_COPYTIME, 
		_T("Copy Current Position to Clipboard(&C)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_systemMenu, _T("System(&S)"));

	CheckItem(ID_CONTINUE, MF_CHECKED);

	// �w���v���j���[
	m_helpMenu.CreatePopup();
	m_helpMenu.Append(MFS_ENABLED, ID_MANUAL, _T("Manual(&M)..."));
	m_helpMenu.AppendSeparator();
	m_helpMenu.Append(MFS_ENABLED, ID_UPDATECHECK, _T("Update Check(&U)..."));
	m_helpMenu.Append(MFS_ENABLED, ID_VERSIONINFO, _T("Version(&A)..."));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_helpMenu, _T("Help(&H)"));
#endif // JP
	if(!m_hMenu || !(HMENU)m_fileMenu || !(HMENU)m_editMenu ||
	   !(HMENU)m_viewMenu || !(HMENU)m_playMenu || !(HMENU)m_returnMenu ||
	   !(HMENU)m_forwardMenu || !(HMENU)m_systemMenu ||
	   !(HMENU)m_recoveryMenu || !(HMENU)m_recoverVisibleMenu ||
	   !(HMENU)m_recoverPlayModeMenu || !(HMENU)m_helpMenu)
		return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// �`�a���[�v�̏�Ԃ�ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetABLoopState(BOOL bALoop, BOOL bBLoop)
{
	EnableItem(ID_SLOOP, !(bALoop || bBLoop) ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_ALOOP, !(bALoop || bBLoop) ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_RANDOM, !(bALoop || bBLoop) ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_MARKERPLAY, !(bALoop || bBLoop) ? MFS_ENABLED : 
		MFS_DISABLED);
	EnableItem(ID_ADDMARKER, !(bALoop || bBLoop) ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_DELETEMARKER, !(bALoop || bBLoop)
		? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_ABLOOP_A_SETTING, bALoop ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_ABLOOP_B_SETTING, bBLoop ? MFS_ENABLED : MFS_DISABLED);
}
//----------------------------------------------------------------------------
// �t�@�C�����ǂݍ��܂ꂽ���ǂ�����ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetFileLoadState(BOOL bLoad)
{
	EnableItem(ID_SAVEFILE, bLoad ? MFS_ENABLED : MFS_DISABLED);
	EnableItem(ID_SAVEALLFILE, bLoad ? MFS_ENABLED : MFS_DISABLED);
}
//----------------------------------------------------------------------------
// �f�B���C�̐ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetDelay(float fWetDryMix, float fFeedback,
		float fLeftDelay, float fRightDelay, BOOL lPanDelay, UINT uID)
{
	BOOL bDelay = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetDelay(fWetDryMix, fFeedback, fLeftDelay,
								  fRightDelay, lPanDelay, bDelay);
	m_rMainWnd.SetDelay(bDelay);
	UncheckDelayMenu();
	CheckItem(uID, bDelay ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �R�[���X�̐ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetChorus(float fWetDryMix, float fDepth, float fFeedback,
							  float fFreq, DWORD lWaveform, float fDelay,
							  DWORD lPhase, UINT uID)
{
	BOOL bChorus = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetChorus(fWetDryMix, fDepth, fFeedback, fFreq,
								   lWaveform, fDelay, lPhase, bChorus);
	m_rMainWnd.SetChorus(bChorus);
	UncheckChorusMenu();
	CheckItem(uID, bChorus ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �R���v���b�T�[�̐ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetCompressor(float fGain, float fAttack, float fRelease,
								  float fThreshold, float fRatio,
								  float fPredelay, UINT uID)
{
	BOOL bCompressor = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetCompressor(fGain, fAttack, fRelease, fThreshold,
									   fRatio, fPredelay, bCompressor);
	m_rMainWnd.SetCompressor(bCompressor);
	UncheckCompressorMenu();
	CheckItem(uID, bCompressor ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �t�����W���[�̐ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetFlanger(float fWetDryMix, float fDepth, float fFeedback,
							   float fFreq, DWORD lWaveform, float fDelay,
							   DWORD lPhase, UINT uID)
{
	BOOL bFlanger = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetFlanger(fWetDryMix, fDepth, fFeedback, fFreq,
									lWaveform, fDelay, lPhase, bFlanger);
	m_rMainWnd.SetFlanger(bFlanger);
	UncheckFlangerMenu();
	CheckItem(uID, bFlanger ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �K�[�O���̐ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetGargle(DWORD dwRateHz, DWORD dwWaveShape, UINT uID)
{
	BOOL bGargle = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetGargle(dwRateHz, dwWaveShape, bGargle);
	m_rMainWnd.SetGargle(bGargle);
	UncheckGargleMenu();
	CheckItem(uID, bGargle ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �f�B�X�g�[�V�����̐ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetDistortion(float fGain, float fEdge,
								  float fPostEQCenterFreq,
								  float fPostEQBandwidth,
								  float fPreLowpassCutoff, UINT uID)
{
	BOOL bDistortion = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetDistortion(fGain, fEdge, fPostEQCenterFreq,
									   fPostEQBandwidth, fPreLowpassCutoff,
									   bDistortion);
	m_rMainWnd.SetDistortion(bDistortion);
	UncheckDistortionMenu();
	CheckItem(uID, bDistortion ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ���o�[�u�̐ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetReverb(float fInGain, float fReverbMix,
	float fReverbTime, float fHighFreqRTRatio, UINT uID)
{
	BOOL bReverb = !IsItemChecked(uID);
	m_rMainWnd.GetSound().SetReverb(fInGain, fReverbMix, fReverbTime,
									fHighFreqRTRatio, bReverb);
	m_rMainWnd.SetReverb(bReverb);
	UncheckReverbMenu();
	CheckItem(uID, bReverb ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �R�c���o�[�u�̐ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::Set3DReverb(int lRoom, int lRoomHF,
	float flRoomRolloffFactor, float flDecayTime, float flDecayHFRatio,
	int lReflections, float flReflectionsDelay, int lReverb,
	float flReverbDelay, float flDiffusion, float flDensity,
	float flHFReference, UINT uID)
{
	BOOL bReverb = !IsItemChecked(uID);
	m_rMainWnd.GetSound().Set3DReverb(lRoom, lRoomHF, flRoomRolloffFactor, 
									  flDecayTime, flDecayHFRatio,
									  lReflections, flReflectionsDelay,
									  lReverb, flReverbDelay,  flDiffusion,
									  flDensity, flHFReference, bReverb);
	m_rMainWnd.Set3DReverb(bReverb);
	Uncheck3DReverbMenu();
	CheckItem(uID, bReverb ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �P�ȃ��[�v�̏�Ԃ�ݒ�
//----------------------------------------------------------------------------
void CMenu_MainWnd::SetSingleLoopState(BOOL bSLoop)
{
	CheckItem(ID_SLOOP, bSLoop ? MF_CHECKED : MF_UNCHECKED);
	EnableItem(ID_ALOOP, bSLoop ? MFS_DISABLED : MFS_ENABLED);
	EnableItem(ID_RANDOM, bSLoop ? MFS_DISABLED : MFS_ENABLED);
}
//----------------------------------------------------------------------------
// EQ �̕\����Ԃ�؂�ւ���
//----------------------------------------------------------------------------
void CMenu_MainWnd::SwitchEQVisible(UINT uID)
{
	BOOL bVisible = IsItemChecked(ID_EQ);
	if(bVisible) m_rMainWnd.SetEQVisible(); // ��\���ɂ��Ă���
	CheckItem(uID, IsItemChecked(uID) ? MF_UNCHECKED : MF_CHECKED);
	if(bVisible) m_rMainWnd.SetEQVisible(); // �ĕ\��
}
//----------------------------------------------------------------------------
// ���j���[�̃`�F�b�N��Ԃ�؂�ւ���
//----------------------------------------------------------------------------
void CMenu_MainWnd::SwitchItemChecked(UINT uID)
{
	BOOL bCheck = !IsItemChecked(uID);
	CheckItem(uID, bCheck ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ��~���t�F�[�h�A�E�g���ԃ��j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckFadeoutMenu()
{
	CheckItem(ID_FADEOUTSTOP1SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP2SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP3SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP4SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP5SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP6SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP7SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP8SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP9SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTSTOP10SEC, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �ؑ֎��t�F�[�h�A�E�g���ԃ��j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckFadeoutNextMenu()
{
	CheckItem(ID_FADEOUTNEXT1SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT2SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT3SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT4SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT5SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT6SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT7SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT8SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT9SEC, MF_UNCHECKED);
	CheckItem(ID_FADEOUTNEXT10SEC, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �R�[���X���j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckChorusMenu()
{
	CheckItem(ID_CHORUS_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_CHORUS_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �R���v���b�T�[���j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckCompressorMenu()
{
	CheckItem(ID_COMPRESSOR_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_COMPRESSOR_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �G�R�[���j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckDelayMenu()
{
	CheckItem(ID_DELAY_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_DELAY_SHORT, MF_UNCHECKED);
	CheckItem(ID_DELAY_MEDIUM, MF_UNCHECKED);
	CheckItem(ID_DELAY_LONG, MF_UNCHECKED);
	CheckItem(ID_DELAY_STEREOSHORT, MF_UNCHECKED);
	CheckItem(ID_DELAY_STEREOMEDIUM, MF_UNCHECKED);
	CheckItem(ID_DELAY_STEREOLONG, MF_UNCHECKED);
	CheckItem(ID_DELAY_MOUNTAIN, MF_UNCHECKED);
	CheckItem(ID_DELAY_BIG, MF_UNCHECKED);
	CheckItem(ID_DELAY_STEREOBIG, MF_UNCHECKED);
	CheckItem(ID_DELAY_DOUBLING, MF_UNCHECKED);
	CheckItem(ID_DELAY_DOUBLEKICK, MF_UNCHECKED);
	CheckItem(ID_DELAY_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �f�B�X�g�[�V�������j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckDistortionMenu()
{
	CheckItem(ID_DISTORTION_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_DISTORTION_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �t�����W���[���j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckFlangerMenu()
{
	CheckItem(ID_FLANGER_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_FLANGER_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �K�[�O�����j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckGargleMenu()
{
	CheckItem(ID_GARGLE_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_GARGLE_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �v���Z�b�g���j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckPresetMenu()
{
	if(IsItemChecked(ID_RECORD)) return;
	if(IsItemChecked(ID_LOWBATTERY)) return;
	if(IsItemChecked(ID_NOSENSE)) return;
	if(IsItemChecked(ID_EARTRAINING)) return;
	int nCount = GetMenuItemCount(m_presetMenu);
	for(int i = 1; i < nCount; i++) CheckItem(ID_PRESET + i, MF_UNCHECKED);
	EnableItem(ID_DELETEPRESET, MFS_DISABLED);
}
//----------------------------------------------------------------------------
// ���o�[�u���j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckReverbMenu()
{
	CheckItem(ID_REVERB_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_REVERB_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// 3D���o�[�u���j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::Uncheck3DReverbMenu()
{
	CheckItem(ID_3DREVERB_DEFAULT, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_PADDEDCELL, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_ROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_BATHROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_LIVINGROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_STONEROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_AUDITORIUM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_CONCERTHALL, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_CAVE, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_ARENA, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_HANGAR, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_CARPETEDHALLWAY, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_HALLWAY, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_STONECORRIDOR, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_ALLEY, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_FOREST, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_CITY, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_MOUNTAINS, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_QUARRY, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_PLAIN, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_PARKINGLOT, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_SEWERPIPE, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_UNDERWATER, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_SMALLROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_MEDIUMROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_LARGEROOM, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_MEDIUMHALL, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_LARGEHALL, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_PLATE, MF_UNCHECKED);
	CheckItem(ID_3DREVERB_CUSTOMIZE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ���ʉ����j���[�̃`�F�b�N���O��
//----------------------------------------------------------------------------
void CMenu_MainWnd::UncheckSoundEffectMenu()
{
	CheckItem(ID_RECORDNOISE, MF_UNCHECKED);
	CheckItem(ID_WAVE, MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCommand(int id, HWND/* hwndCtl*/, UINT/* codeNotify*/)
{
	switch(id)
	{
	case ID_OPENFILE:
		OnOpenFileMenuSelected();
		break;
	case ID_ADDFILE:
		OnAddFileMenuSelected();
		break;
	case ID_OPENFOLDER:
		OnOpenFolderMenuSelected();
		break;
	case ID_ADDFOLDER:
		OnAddFolderMenuSelected();
		break;
	case ID_OPENURL:
		OnOpenURLMenuSelected();
		break;
	case ID_ADDURL:
		OnAddURLMenuSelected();
		break;
	case ID_SAVEFILE:
		OnSaveFileMenuSelected();
		break;
	case ID_SAVEALLFILE:
		OnSaveAllFileMenuSelected();
		break;
	case ID_LAMECOMMANDLINE:
		OnLAMECommandLineMenuSelected();
		break;
	case ID_EXIT:
		OnExitMenuSelected();
		break;
	case ID_DELETE:
		OnDeleteMenuSelected();
		break;
	case ID_SELECTALL:
		OnSelectAllMenuSelected();
		break;
	case ID_VIDEOSCREEN:
		OnVideoScreenMenuSelected();
		break;
	case ID_LYRICS:
		OnLyricsMenuSelected();
		break;
	case ID_PITCHANALYSER:
		OnPitchAnalyserMenuSelected();
		break;
	case ID_TIMESLIDER:
		OnTimeSliderMenuSelected();
		break;
	case ID_EXPLORER:
		OnExplorerMenuSelected();
		break;
	case ID_SPEED:
		OnSpeedMenuSelected();
		break;
	case ID_FREQ:
		OnFreqMenuSelected();
		break;
	case ID_PITCH:
		OnPitchMenuSelected();
		break;
	case ID_VOLUME:
		OnVolumeMenuSelected();
		break;
	case ID_PAN:
		OnPanMenuSelected();
		break;
	case ID_EQ:
		OnEQMenuSelected();
		break;
	case ID_EQ20:
		OnEQ20MenuSelected();
		break;
	case ID_EQ25:
		OnEQ25MenuSelected();
		break;
	case ID_EQ31_5:
		OnEQ31_5MenuSelected();
		break;
	case ID_EQ40:
		OnEQ40MenuSelected();
		break;
	case ID_EQ50:
		OnEQ50MenuSelected();
		break;
	case ID_EQ63:
		OnEQ63MenuSelected();
		break;
	case ID_EQ80:
		OnEQ80MenuSelected();
		break;
	case ID_EQ100:
		OnEQ100MenuSelected();
		break;
	case ID_EQ125:
		OnEQ125MenuSelected();
		break;
	case ID_EQ160:
		OnEQ160MenuSelected();
		break;
	case ID_EQ200:
		OnEQ200MenuSelected();
		break;
	case ID_EQ250:
		OnEQ250MenuSelected();
		break;
	case ID_EQ315:
		OnEQ315MenuSelected();
		break;
	case ID_EQ400:
		OnEQ400MenuSelected();
		break;
	case ID_EQ500:
		OnEQ500MenuSelected();
		break;
	case ID_EQ630:
		OnEQ630MenuSelected();
		break;
	case ID_EQ800:
		OnEQ800MenuSelected();
		break;
	case ID_EQ1K:
		OnEQ1KMenuSelected();
		break;
	case ID_EQ1_25K:
		OnEQ1_25KMenuSelected();
		break;
	case ID_EQ1_6K:
		OnEQ1_6KMenuSelected();
		break;
	case ID_EQ2K:
		OnEQ2KMenuSelected();
		break;
	case ID_EQ2_5K:
		OnEQ2_5KMenuSelected();
		break;
	case ID_EQ3_15K:
		OnEQ3_15KMenuSelected();
		break;
	case ID_EQ4K:
		OnEQ4KMenuSelected();
		break;
	case ID_EQ5K:
		OnEQ5KMenuSelected();
		break;
	case ID_EQ6_3K:
		OnEQ6_3KMenuSelected();
		break;
	case ID_EQ8K:
		OnEQ8KMenuSelected();
		break;
	case ID_EQ10K:
		OnEQ10KMenuSelected();
		break;
	case ID_EQ12_5K:
		OnEQ12_5KMenuSelected();
		break;
	case ID_EQ16K:
		OnEQ16KMenuSelected();
		break;
	case ID_EQ20K:
		OnEQ20KMenuSelected();
		break;
	case ID_TAB:
		OnTabMenuSelected();
		break;
	case ID_PLAYLIST:
		OnPlayListMenuSelected();
		break;
	case ID_CLOSEALL:
		OnCloseAllMenuSelected();
		break;
	case ID_TOOLBAR_SIZES:
		OnToolbarSSizeMenuSelected();
		break;
	case ID_TOOLBAR_SIZEM:
		OnToolbarMSizeMenuSelected();
		break;
	case ID_TOOLBAR_SIZEL:
		OnToolbarLSizeMenuSelected();
		break;
	case ID_CUSTOMIZETOOLBAR:
		OnCustomizeToolbarMenuSelected();
		break;
	case ID_HEAD:
		OnHeadMenuSelected();
		break;
	case ID_PREV:
		OnPreviousMenuSelected();
		break;
	case ID_NEXT:
		OnNextMenuSelected();
		break;
	case ID_PAUSE:
		OnPauseMenuSelected();
		break;
	case ID_REWIND:
		OnRewindMenuSelected();
		break;
	case ID_FORWARD:
		OnForwardMenuSelected();
		break;
	case ID_PAUSE_RETURN1SEC:
		OnPauseAndReturn1SecMenuSelected();
		break;
	case ID_PAUSE_RETURN2SEC:
		OnPauseAndReturn2SecMenuSelected();
		break;
	case ID_PAUSE_RETURN3SEC:
		OnPauseAndReturn3SecMenuSelected();
		break;
	case ID_PAUSE_RETURN5SEC:
		OnPauseAndReturn5SecMenuSelected();
		break;
	case ID_PAUSE_RETURN10SEC:
		OnPauseAndReturn10SecMenuSelected();
		break;
	case ID_RETURN1SEC:
		OnReturn1SecMenuSelected();
		break;
	case ID_RETURN2SEC:
		OnReturn2SecMenuSelected();
		break;
	case ID_RETURN3SEC:
		OnReturn3SecMenuSelected();
		break;
	case ID_RETURN5SEC:
		OnReturn5SecMenuSelected();
		break;
	case ID_RETURN10SEC:
		OnReturn10SecMenuSelected();
		break;
	case ID_FORWARD1SEC:
		OnForward1SecMenuSelected();
		break;
	case ID_FORWARD2SEC:
		OnForward2SecMenuSelected();
		break;
	case ID_FORWARD3SEC:
		OnForward3SecMenuSelected();
		break;
	case ID_FORWARD5SEC:
		OnForward5SecMenuSelected();
		break;
	case ID_FORWARD10SEC:
		OnForward10SecMenuSelected();
		break;
	case ID_ADDPRESET:
		OnAddPresetMenuSelected();
		break;
	case ID_DELETEPRESET:
		OnDeletePresetMenuSelected();
		break;
	case ID_RESETSPEED:
		OnResetSpeedMenuSelected();
		break;
	case ID_SPEED_50:
		OnSetSpeed50MenuSelected();
		break;
	case ID_SPEED_60:
		OnSetSpeed60MenuSelected();
		break;
	case ID_SPEED_70:
		OnSetSpeed70MenuSelected();
		break;
	case ID_SPEED_80:
		OnSetSpeed80MenuSelected();
		break;
	case ID_SPEED_90:
		OnSetSpeed90MenuSelected();
		break;
	case ID_SPEED_100:
		OnSetSpeed100MenuSelected();
		break;
	case ID_SPEED_110:
		OnSetSpeed110MenuSelected();
		break;
	case ID_SPEED_120:
		OnSetSpeed120MenuSelected();
		break;
	case ID_SPEED_130:
		OnSetSpeed130MenuSelected();
		break;
	case ID_SPEED_140:
		OnSetSpeed140MenuSelected();
		break;
	case ID_SPEED_150:
		OnSetSpeed150MenuSelected();
		break;
	case ID_SPEED_160:
		OnSetSpeed160MenuSelected();
		break;
	case ID_SPEED_170:
		OnSetSpeed170MenuSelected();
		break;
	case ID_SPEED_180:
		OnSetSpeed180MenuSelected();
		break;
	case ID_SPEED_190:
		OnSetSpeed190MenuSelected();
		break;
	case ID_SPEED_200:
		OnSetSpeed200MenuSelected();
		break;
	case ID_SPEED_250:
		OnSetSpeed250MenuSelected();
		break;
	case ID_SPEED_300:
		OnSetSpeed300MenuSelected();
		break;
	case ID_SPEED_350:
		OnSetSpeed350MenuSelected();
		break;
	case ID_SPEED_400:
		OnSetSpeed400MenuSelected();
		break;
	case ID_DOWN0_1SPEED:
		OnDown0_1SpeedMenuSelected();
		break;
	case ID_DOWN1SPEED:
		OnDown1SpeedMenuSelected();
		break;
	case ID_DOWN2SPEED:
		OnDown2SpeedMenuSelected();
		break;
	case ID_DOWN3SPEED:
		OnDown3SpeedMenuSelected();
		break;
	case ID_DOWN5SPEED:
		OnDown5SpeedMenuSelected();
		break;
	case ID_DOWN10SPEED:
		OnDown10SpeedMenuSelected();
		break;
	case ID_UP0_1SPEED:
		OnUp0_1SpeedMenuSelected();
		break;
	case ID_UP1SPEED:
		OnUp1SpeedMenuSelected();
		break;
	case ID_UP2SPEED:
		OnUp2SpeedMenuSelected();
		break;
	case ID_UP3SPEED:
		OnUp3SpeedMenuSelected();
		break;
	case ID_UP5SPEED:
		OnUp5SpeedMenuSelected();
		break;
	case ID_UP10SPEED:
		OnUp10SpeedMenuSelected();
		break;
	case ID_RESETFREQ:
		OnResetFreqMenuSelected();
		break;
	case ID_FREQ_50:
		OnSetFreq50MenuSelected();
		break;
	case ID_FREQ_60:
		OnSetFreq60MenuSelected();
		break;
	case ID_FREQ_70:
		OnSetFreq70MenuSelected();
		break;
	case ID_FREQ_80:
		OnSetFreq80MenuSelected();
		break;
	case ID_FREQ_90:
		OnSetFreq90MenuSelected();
		break;
	case ID_FREQ_100:
		OnSetFreq100MenuSelected();
		break;
	case ID_FREQ_110:
		OnSetFreq110MenuSelected();
		break;
	case ID_FREQ_120:
		OnSetFreq120MenuSelected();
		break;
	case ID_FREQ_130:
		OnSetFreq130MenuSelected();
		break;
	case ID_FREQ_140:
		OnSetFreq140MenuSelected();
		break;
	case ID_FREQ_150:
		OnSetFreq150MenuSelected();
		break;
	case ID_FREQ_160:
		OnSetFreq160MenuSelected();
		break;
	case ID_FREQ_170:
		OnSetFreq170MenuSelected();
		break;
	case ID_FREQ_180:
		OnSetFreq180MenuSelected();
		break;
	case ID_FREQ_190:
		OnSetFreq190MenuSelected();
		break;
	case ID_FREQ_200:
		OnSetFreq200MenuSelected();
		break;
	case ID_FREQ_250:
		OnSetFreq250MenuSelected();
		break;
	case ID_FREQ_300:
		OnSetFreq300MenuSelected();
		break;
	case ID_FREQ_350:
		OnSetFreq350MenuSelected();
		break;
	case ID_FREQ_400:
		OnSetFreq400MenuSelected();
		break;
	case ID_DOWN0_1FREQ:
		OnDown0_1FreqMenuSelected();
		break;
	case ID_DOWN1FREQ:
		OnDown1FreqMenuSelected();
		break;
	case ID_DOWN2FREQ:
		OnDown2FreqMenuSelected();
		break;
	case ID_DOWN3FREQ:
		OnDown3FreqMenuSelected();
		break;
	case ID_DOWN5FREQ:
		OnDown5FreqMenuSelected();
		break;
	case ID_DOWN10FREQ:
		OnDown10FreqMenuSelected();
		break;
	case ID_UP0_1FREQ:
		OnUp0_1FreqMenuSelected();
		break;
	case ID_UP1FREQ:
		OnUp1FreqMenuSelected();
		break;
	case ID_UP2FREQ:
		OnUp2FreqMenuSelected();
		break;
	case ID_UP3FREQ:
		OnUp3FreqMenuSelected();
		break;
	case ID_UP5FREQ:
		OnUp5FreqMenuSelected();
		break;
	case ID_UP10FREQ:
		OnUp10FreqMenuSelected();
		break;
	case ID_RESETPITCH:
		OnResetPitchMenuSelected();
		break;
	case ID_PITCH_F12:
		OnSetPitchFlat12MenuSelected();
		break;
	case ID_PITCH_F11:
		OnSetPitchFlat11MenuSelected();
		break;
	case ID_PITCH_F10:
		OnSetPitchFlat10MenuSelected();
		break;
	case ID_PITCH_F9:
		OnSetPitchFlat9MenuSelected();
		break;
	case ID_PITCH_F8:
		OnSetPitchFlat8MenuSelected();
		break;
	case ID_PITCH_F7:
		OnSetPitchFlat7MenuSelected();
		break;
	case ID_PITCH_F6:
		OnSetPitchFlat6MenuSelected();
		break;
	case ID_PITCH_F5:
		OnSetPitchFlat5MenuSelected();
		break;
	case ID_PITCH_F4:
		OnSetPitchFlat4MenuSelected();
		break;
	case ID_PITCH_F3:
		OnSetPitchFlat3MenuSelected();
		break;
	case ID_PITCH_F2:
		OnSetPitchFlat2MenuSelected();
		break;
	case ID_PITCH_F1:
		OnSetPitchFlat1MenuSelected();
		break;
	case ID_PITCH_0:
		OnSetPitchNaturalMenuSelected();
		break;
	case ID_PITCH_S1:
		OnSetPitchSharp1MenuSelected();
		break;
	case ID_PITCH_S2:
		OnSetPitchSharp2MenuSelected();
		break;
	case ID_PITCH_S3:
		OnSetPitchSharp3MenuSelected();
		break;
	case ID_PITCH_S4:
		OnSetPitchSharp4MenuSelected();
		break;
	case ID_PITCH_S5:
		OnSetPitchSharp5MenuSelected();
		break;
	case ID_PITCH_S6:
		OnSetPitchSharp6MenuSelected();
		break;
	case ID_PITCH_S7:
		OnSetPitchSharp7MenuSelected();
		break;
	case ID_PITCH_S8:
		OnSetPitchSharp8MenuSelected();
		break;
	case ID_PITCH_S9:
		OnSetPitchSharp9MenuSelected();
		break;
	case ID_PITCH_S10:
		OnSetPitchSharp10MenuSelected();
		break;
	case ID_PITCH_S11:
		OnSetPitchSharp11MenuSelected();
		break;
	case ID_PITCH_S12:
		OnSetPitchSharp12MenuSelected();
		break;
	case ID_DOWN1PITCH:
		OnDown1PitchMenuSelected();
		break;
	case ID_DOWN2PITCH:
		OnDown2PitchMenuSelected();
		break;
	case ID_DOWN1OCTPITCH:
		OnDown1OctavePitchMenuSelected();
		break;
	case ID_UP1PITCH:
		OnUp1PitchMenuSelected();
		break;
	case ID_UP2PITCH:
		OnUp2PitchMenuSelected();
		break;
	case ID_UP1OCTPITCH:
		OnUp1OctavePitchMenuSelected();
		break;
	case ID_UPVOLUME:
		OnUpVolumeMenuSelected();
		break;
	case ID_DOWNVOLUME:
		OnDownVolumeMenuSelected();
		break;
	case ID_STOP:
		OnStopMenuSelected();
		break;
	case ID_SLOOP:
		OnSingleLoopMenuSelected();
		break;
	case ID_ALOOP:
		OnAllLoopMenuSelected();
		break;
	case ID_RANDOM:
		OnRandomMenuSelected();
		break;
	case ID_CONTINUE:
		OnContinueMenuSelected();
		break;
	case ID_SAMEARTIST:
		OnSameArtistMenuSelected();
		break;
	case ID_ABLOOP_A:
		OnABLoopAMenuSelected();
		break;
	case ID_ABLOOP_B:
		OnABLoopBMenuSelected();
		break;
	case ID_ABLOOP_A_SETTING:
		OnABLoopASettingMenuSelected();
		break;
	case ID_ABLOOP_B_SETTING:
		OnABLoopBSettingMenuSelected();
		break;
	case ID_MARKERPLAY:
		OnMarkerPlayMenuSelected();
		break;
	case ID_ADDMARKER:
		OnAddMarkerMenuSelected();
		break;
	case ID_DELETEMARKER:
		OnDeleteMarkerMenuSelected();
		break;
	case ID_COUNTLOOP:
		OnCountLoopMenuSelected();
		break;
	case ID_INSTANTLOOP:
		OnInstantLoopMenuSelected();
		break;
	case ID_SETPOSITIONAUTO:
		OnSetPositionAutoMenuSelected();
		break;
	case ID_RECORDNOISE:
		OnRecordNoiseMenuSelected();
		break;
	case ID_WAVE:
		OnWaveMenuSelected();
		break;
	case ID_NORMALIZE:
		OnNormalizeMenuSelected();
		break;
	case ID_VOCALCANCEL:
		OnVocalCancelMenuSelected();
		break;
	case ID_REVERSE:
		OnReverseMenuSelected();
		break;
	case ID_RECORD:
		OnRecordMenuSelected();
		break;
	case ID_LOWBATTERY:
		OnLowBatteryMenuSelected();
		break;
	case ID_NOSENSE:
		OnNoSenseMenuSelected();
		break;
	case ID_BASSCOPY:
		OnBassCopyMenuSelected();
		break;
	case ID_CYMBALCOPY:
		OnDrumsCopyMenuSelected();
		break;
	case ID_EARTRAINING:
		OnEarTrainingMenuSelected();
		break;
	case ID_MONORAL:
		OnMonoralMenuSelected();
		break;
	case ID_ONLYLEFT:
		OnOnlyLeftMenuSelected();
		break;
	case ID_ONLYRIGHT:
		OnOnlyRightMenuSelected();
		break;
	case ID_CHANGELR:
		OnChangeLRMenuSelected();
		break;
	case ID_RESETALL:
		OnResetAllMenuSelected();
		break;
	case ID_RECOVERVIDEOSCREENVISIBLE:
	case ID_RECOVERTIMESLIDERVISIBLE:
	case ID_RECOVERSPEEDVISIBLE:
	case ID_RECOVERFREQVISIBLE:
	case ID_RECOVERPITCHVISIBLE:
	case ID_RECOVERVOLUMEVISIBLE:
	case ID_RECOVERPANVISIBLE:
	case ID_RECOVEREQVISIBLE:
	case ID_RECOVERLISTVISIBLE:
	case ID_RECOVERSLOOP:
	case ID_RECOVERALOOP:
	case ID_RECOVERRANDOM:
	case ID_RECOVERCONTINUE:
	case ID_RECOVERINSTANTLOOP:
	case ID_RECOVERSETPOSITIONAUTO:
	case ID_RECOVERREVERSE:
	case ID_RECOVERRECORD:
	case ID_RECOVERWPOS:
	case ID_RECOVERWSIZE:
	case ID_RECOVERPLAYPOS:
	case ID_RECOVERSPEED:
	case ID_RECOVERFREQ:
	case ID_RECOVERPITCH:
	case ID_RECOVERVOLUME:
	case ID_RECOVERPAN:
	case ID_RECOVEREQ:
	case ID_RECOVERLIST:
		SwitchItemChecked(id);
		break;
	case ID_KEYSETTING:
		OnKeySettingMenuSelected();
		break;
	case ID_OUTKEYSETTING:
		OnOutKeySettingMenuSelected();
		break;
	case ID_LIMIT:
		OnLimitMenuSelected();
		break;
	case ID_TIMERPLAY:
		OnTimerPlayMenuSelected();
		break;
	case ID_PLAYRANGE:
		OnPlayRangeMenuSelected();
		break;
	case ID_PLAYPOSITION:
		OnPlayPositionMenuSelected();
		break;
	case ID_DECSPEED:
		OnDecSpeedMenuSelected();
		break;
	case ID_INCSPEED:
		OnIncSpeedMenuSelected();
		break;
	case ID_SPEEDDEC_0:
		OnSetSpeedDecimal0MenuSelected();
		break;
	case ID_SPEEDDEC_1:
		OnSetSpeedDecimal1MenuSelected();
		break;
	case ID_SPEEDDEC_2:
		OnSetSpeedDecimal2MenuSelected();
		break;
	case ID_DECFREQ:
		OnDecFreqMenuSelected();
		break;
	case ID_INCFREQ:
		OnIncFreqMenuSelected();
		break;
	case ID_FREQDEC_0:
		OnSetFreqDecimal0MenuSelected();
		break;
	case ID_FREQDEC_1:
		OnSetFreqDecimal1MenuSelected();
		break;
	case ID_FREQDEC_2:
		OnSetFreqDecimal2MenuSelected();
		break;
	case ID_PITCHDEC_0:
		OnSetPitchDecimal0MenuSelected();
		break;
	case ID_PITCHDEC_1:
		OnSetPitchDecimal1MenuSelected();
		break;
	case ID_PITCHDEC_2:
		OnSetPitchDecimal2MenuSelected();
		break;
	case ID_RESETVOLUME:
		OnResetVolumeMenuSelected();
		break;
	case ID_VOLUME_0:
		OnSetVolume0MenuSelected();
		break;
	case ID_VOLUME_10:
		OnSetVolume10MenuSelected();
		break;
	case ID_VOLUME_20:
		OnSetVolume20MenuSelected();
		break;
	case ID_VOLUME_30:
		OnSetVolume30MenuSelected();
		break;
	case ID_VOLUME_40:
		OnSetVolume40MenuSelected();
		break;
	case ID_VOLUME_50:
		OnSetVolume50MenuSelected();
		break;
	case ID_VOLUME_60:
		OnSetVolume60MenuSelected();
		break;
	case ID_VOLUME_70:
		OnSetVolume70MenuSelected();
		break;
	case ID_VOLUME_80:
		OnSetVolume80MenuSelected();
		break;
	case ID_VOLUME_90:
		OnSetVolume90MenuSelected();
		break;
	case ID_VOLUME_100:
		OnSetVolume100MenuSelected();
		break;
	case ID_FADEOUTSTOP:
		OnFadeoutMenuSelected();
		break;
	case ID_FADEOUTSTOP1SEC:
		OnFadeout1SecMenuSelected();
		break;
	case ID_FADEOUTSTOP2SEC:
		OnFadeout2SecMenuSelected();
		break;
	case ID_FADEOUTSTOP3SEC:
		OnFadeout3SecMenuSelected();
		break;
	case ID_FADEOUTSTOP4SEC:
		OnFadeout4SecMenuSelected();
		break;
	case ID_FADEOUTSTOP5SEC:
		OnFadeout5SecMenuSelected();
		break;
	case ID_FADEOUTSTOP6SEC:
		OnFadeout6SecMenuSelected();
		break;
	case ID_FADEOUTSTOP7SEC:
		OnFadeout7SecMenuSelected();
		break;
	case ID_FADEOUTSTOP8SEC:
		OnFadeout8SecMenuSelected();
		break;
	case ID_FADEOUTSTOP9SEC:
		OnFadeout9SecMenuSelected();
		break;
	case ID_FADEOUTSTOP10SEC:
		OnFadeout10SecMenuSelected();
		break;
	case ID_FADEOUTNEXT:
		OnFadeoutNextMenuSelected();
		break;
	case ID_FADEOUTNEXT1SEC:
		OnFadeoutNext1SecMenuSelected();
		break;
	case ID_FADEOUTNEXT2SEC:
		OnFadeoutNext2SecMenuSelected();
		break;
	case ID_FADEOUTNEXT3SEC:
		OnFadeoutNext3SecMenuSelected();
		break;
	case ID_FADEOUTNEXT4SEC:
		OnFadeoutNext4SecMenuSelected();
		break;
	case ID_FADEOUTNEXT5SEC:
		OnFadeoutNext5SecMenuSelected();
		break;
	case ID_FADEOUTNEXT6SEC:
		OnFadeoutNext6SecMenuSelected();
		break;
	case ID_FADEOUTNEXT7SEC:
		OnFadeoutNext7SecMenuSelected();
		break;
	case ID_FADEOUTNEXT8SEC:
		OnFadeoutNext8SecMenuSelected();
		break;
	case ID_FADEOUTNEXT9SEC:
		OnFadeoutNext9SecMenuSelected();
		break;
	case ID_FADEOUTNEXT10SEC:
		OnFadeoutNext10SecMenuSelected();
		break;
	case ID_TWEET:
		OnTweetMenuSelected();
		break;
	case ID_METRONOME:
		OnMetronomeMenuSelected();
		break;
	case ID_QUALITY_NORMAL:
		OnQualityNormalMenuSelected();
		break;
	case ID_QUALITY_ASIO:
		OnQualityASIOMenuSelected();
		break;
	case ID_QUALITY_WASAPI:
		OnQualityWASAPIMenuSelected();
		break;
	case ID_REVERB_DEFAULT:
		OnReverbDefaultMenuSelected();
		break;
	case ID_REVERB_CUSTOMIZE:
		OnReverbCustomizeMenuSelected();
		break;
	case ID_3DREVERB_DEFAULT:
		On3DReverbDefaultMenuSelected();
		break;
	case ID_3DREVERB_PADDEDCELL:
		On3DReverbPaddedCellMenuSelected();
		break;
	case ID_3DREVERB_ROOM:
		On3DReverbRoomMenuSelected();
		break;
	case ID_3DREVERB_BATHROOM:
		On3DReverbBathroomMenuSelected();
		break;
	case ID_3DREVERB_LIVINGROOM:
		On3DReverbLivingRoomMenuSelected();
		break;
	case ID_3DREVERB_STONEROOM:
		On3DReverbStoneRoomMenuSelected();
		break;
	case ID_3DREVERB_AUDITORIUM:
		On3DReverbAuditoriumMenuSelected();
		break;
	case ID_3DREVERB_CONCERTHALL:
		On3DReverbConcertHallMenuSelected();
		break;
	case ID_3DREVERB_CAVE:
		On3DReverbCaveMenuSelected();
		break;
	case ID_3DREVERB_ARENA:
		On3DReverbArenaMenuSelected();
		break;
	case ID_3DREVERB_HANGAR:
		On3DReverbHangarMenuSelected();
		break;
	case ID_3DREVERB_CARPETEDHALLWAY:
		On3DReverbCarpetedHallwayMenuSelected();
		break;
	case ID_3DREVERB_HALLWAY:
		On3DReverbHallwayMenuSelected();
		break;
	case ID_3DREVERB_STONECORRIDOR:
		On3DReverbStoneCorridorMenuSelected();
		break;
	case ID_3DREVERB_ALLEY:
		On3DReverbAlleyMenuSelected();
		break;
	case ID_3DREVERB_FOREST:
		On3DReverbForestMenuSelected();
		break;
	case ID_3DREVERB_CITY:
		On3DReverbCityMenuSelected();
		break;
	case ID_3DREVERB_MOUNTAINS:
		On3DReverbMountainsMenuSelected();
		break;
	case ID_3DREVERB_QUARRY:
		On3DReverbQuarryMenuSelected();
		break;
	case ID_3DREVERB_PLAIN:
		On3DReverbPlainMenuSelected();
		break;
	case ID_3DREVERB_PARKINGLOT:
		On3DReverbParkingLotMenuSelected();
		break;
	case ID_3DREVERB_SEWERPIPE:
		On3DReverbSewerPipeMenuSelected();
		break;
	case ID_3DREVERB_UNDERWATER:
		On3DReverbUnderwaterMenuSelected();
		break;
	case ID_3DREVERB_SMALLROOM:
		On3DReverbSmallRoomMenuSelected();
		break;
	case ID_3DREVERB_MEDIUMROOM:
		On3DReverbMediumRoomMenuSelected();
		break;
	case ID_3DREVERB_LARGEROOM:
		On3DReverbLargeRoomMenuSelected();
		break;
	case ID_3DREVERB_MEDIUMHALL:
		On3DReverbMediumHallMenuSelected();
		break;
	case ID_3DREVERB_LARGEHALL:
		On3DReverbLargeHallMenuSelected();
		break;
	case ID_3DREVERB_PLATE:
		On3DReverbPlateMenuSelected();
		break;
	case ID_3DREVERB_CUSTOMIZE:
		On3DReverbCustomizeMenuSelected();
		break;
	case ID_DELAY_DEFAULT:
		OnDelayDefaultMenuSelected();
		break;
	case ID_DELAY_SHORT:
		OnDelayShortMenuSelected();
		break;
	case ID_DELAY_MEDIUM:
		OnDelayMediumMenuSelected();
		break;
	case ID_DELAY_LONG:
		OnDelayLongMenuSelected();
		break;
	case ID_DELAY_STEREOSHORT:
		OnDelayStereoShortMenuSelected();
		break;
	case ID_DELAY_STEREOMEDIUM:
		OnDelayStereoMediumMenuSelected();
		break;
	case ID_DELAY_STEREOLONG:
		OnDelayStereoLongMenuSelected();
		break;
	case ID_DELAY_MOUNTAIN:
		OnDelayMountainMenuSelected();
		break;
	case ID_DELAY_BIG:
		OnDelayBigMenuSelected();
		break;
	case ID_DELAY_STEREOBIG:
		OnDelayStereoBigMenuSelected();
		break;
	case ID_DELAY_DOUBLING:
		OnDelayDoublingMenuSelected();
		break;
	case ID_DELAY_DOUBLEKICK:
		OnDelayDoubleKickMenuSelected();
		break;
	case ID_DELAY_CUSTOMIZE:
		OnDelayCustomizeMenuSelected();
		break;
	case ID_CHORUS_DEFAULT:
		OnChorusDefaultMenuSelected();
		break;
	case ID_CHORUS_CUSTOMIZE:
		OnChorusCustomizeMenuSelected();
		break;
	case ID_COMPRESSOR_DEFAULT:
		OnCompressorDefaultMenuSelected();
		break;
	case ID_COMPRESSOR_CUSTOMIZE:
		OnCompressorCustomizeMenuSelected();
		break;
	case ID_FLANGER_DEFAULT:
		OnFlangerDefaultMenuSelected();
		break;
	case ID_FLANGER_CUSTOMIZE:
		OnFlangerCustomizeMenuSelected();
		break;
	case ID_GARGLE_DEFAULT:
		OnGargleDefaultMenuSelected();
		break;
	case ID_GARGLE_CUSTOMIZE:
		OnGargleCustomizeMenuSelected();
		break;
	case ID_DISTORTION_DEFAULT:
		OnDistortionDefaultMenuSelected();
		break;
	case ID_DISTORTION_CUSTOMIZE:
		OnDistortionCustomizeMenuSelected();
		break;
	case ID_EQFLAT:
		OnEQFlatMenuSelected();
		break;
	case ID_EQLOWSUPER:
		OnEQLowSuperMenuSelected();
		break;
	case ID_EQLOWHIGHEST:
		OnEQLowHighestMenuSelected();
		break;
	case ID_EQLOWHIGH:
		OnEQLowHighMenuSelected();
		break;
	case ID_EQLOWMIDDLE:
		OnEQLowMiddleMenuSelected();
		break;
	case ID_EQLOWLOW:
		OnEQLowLowMenuSelected();
		break;
	case ID_EQLOWLOWEST:
		OnEQLowLowestMenuSelected();
		break;
	case ID_EQMIDDLESUPER:
		OnEQMiddleSuperMenuSelected();
		break;
	case ID_EQMIDDLEHIGHEST:
		OnEQMiddleHighestMenuSelected();
		break;
	case ID_EQMIDDLEHIGH:
		OnEQMiddleHighMenuSelected();
		break;
	case ID_EQMIDDLEMIDDLE:
		OnEQMiddleMiddleMenuSelected();
		break;
	case ID_EQMIDDLELOW:
		OnEQMiddleLowMenuSelected();
		break;
	case ID_EQMIDDLELOWEST:
		OnEQMiddleLowestMenuSelected();
		break;
	case ID_EQHIGHSUPER:
		OnEQHighSuperMenuSelected();
		break;
	case ID_EQHIGHHIGHEST:
		OnEQHighHighestMenuSelected();
		break;
	case ID_EQHIGHHIGH:
		OnEQHighHighMenuSelected();
		break;
	case ID_EQHIGHMIDDLE:
		OnEQHighMiddleMenuSelected();
		break;
	case ID_EQHIGHLOW:
		OnEQHighLowMenuSelected();
		break;
	case ID_EQHIGHLOWEST:
		OnEQHighLowestMenuSelected();
		break;
	case ID_EQLOWCUTSUPER:
		OnEQLowCutSuperMenuSelected();
		break;
	case ID_EQLOWCUTHIGHEST:
		OnEQLowCutHighestMenuSelected();
		break;
	case ID_EQLOWCUTHIGH:
		OnEQLowCutHighMenuSelected();
		break;
	case ID_EQLOWCUTMIDDLE:
		OnEQLowCutMiddleMenuSelected();
		break;
	case ID_EQLOWCUTLOW:
		OnEQLowCutLowMenuSelected();
		break;
	case ID_EQLOWCUTLOWEST:
		OnEQLowCutLowestMenuSelected();
		break;
	case ID_EQMIDDLECUTSUPER:
		OnEQMiddleCutSuperMenuSelected();
		break;
	case ID_EQMIDDLECUTHIGHEST:
		OnEQMiddleCutHighestMenuSelected();
		break;
	case ID_EQMIDDLECUTHIGH:
		OnEQMiddleCutHighMenuSelected();
		break;
	case ID_EQMIDDLECUTMIDDLE:
		OnEQMiddleCutMiddleMenuSelected();
		break;
	case ID_EQMIDDLECUTLOW:
		OnEQMiddleCutLowMenuSelected();
		break;
	case ID_EQMIDDLECUTLOWEST:
		OnEQMiddleCutLowestMenuSelected();
		break;
	case ID_EQHIGHCUTSUPER:
		OnEQHighCutSuperMenuSelected();
		break;
	case ID_EQHIGHCUTHIGHEST:
		OnEQHighCutHighestMenuSelected();
		break;
	case ID_EQHIGHCUTHIGH:
		OnEQHighCutHighMenuSelected();
		break;
	case ID_EQHIGHCUTMIDDLE:
		OnEQHighCutMiddleMenuSelected();
		break;
	case ID_EQHIGHCUTLOW:
		OnEQHighCutLowMenuSelected();
		break;
	case ID_EQHIGHCUTLOWEST:
		OnEQHighCutLowestMenuSelected();
		break;
	case ID_DOUBLERUN:
		OnDoubleRunMenuSelected();
		break;
	case ID_TOPMOST:
		OnTopMostMenuSelected();
		break;
	case ID_TASKTRAY:
		OnTaskTrayMenuSelected();
		break;
	case ID_COPYTIME:
		OnCopyTimeMenuSelected();
		break;
	case ID_MANUAL:
		OnManualMenuSelected();
		break;
	case ID_UPDATECHECK:
		OnUpdateCheckMenuSelected();
		break;
	case ID_VERSIONINFO:
		OnVersionInfoMenuSelected();
		break;
	case ID_RESTORE:
		OnRestoreMenuSelected();
		break;
	}
	if(id > ID_PRESET) OnPresetMenuSelected(id);
}
//----------------------------------------------------------------------------
// �t�@�C�� �� �J�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOpenFileMenuSelected()
{
	m_rMainWnd.ShowOpenFileDialog(TRUE);
}
//----------------------------------------------------------------------------
// �t�@�C�� �� �ǉ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAddFileMenuSelected()
{
	m_rMainWnd.ShowOpenFileDialog(FALSE);
}
//----------------------------------------------------------------------------
// �t�@�C�� �� �t�H���_���J�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOpenFolderMenuSelected()
{
	m_rMainWnd.ShowOpenFolderDialog(TRUE);
}
//----------------------------------------------------------------------------
// �t�@�C�� �� �t�H���_��ǉ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAddFolderMenuSelected()
{
	m_rMainWnd.ShowOpenFolderDialog(FALSE);
}
//----------------------------------------------------------------------------
// �t�@�C�� �� URL���J�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOpenURLMenuSelected()
{
	m_rMainWnd.ShowOpenURLWnd();
}
//----------------------------------------------------------------------------
// �t�@�C�� �� URL���J�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAddURLMenuSelected()
{
	BOOL bAdd = TRUE;
	m_rMainWnd.ShowOpenURLWnd(bAdd);
}
//----------------------------------------------------------------------------
// �t�@�C�� �� �ۑ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSaveFileMenuSelected()
{
	m_rMainWnd.ShowSaveFileDialog();
}
//----------------------------------------------------------------------------
// �t�@�C�� �� �ꊇ�ϊ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSaveAllFileMenuSelected()
{
	m_rMainWnd.ShowSaveAllFileDialog();
}
//----------------------------------------------------------------------------
// �t�@�C�� �� LAME�R�}���h���C���I�v�V�������j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnLAMECommandLineMenuSelected()
{
	m_rMainWnd.ShowLAMECommandLineWnd();
}
//----------------------------------------------------------------------------
// �t�@�C�� �� �I�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnExitMenuSelected()
{
	m_rMainWnd.Close();
}
//----------------------------------------------------------------------------
// �폜���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDeleteMenuSelected()
{
	m_rMainWnd.GetPlayList().DeleteSelectedItems();
}
//----------------------------------------------------------------------------
// ���ׂĂ�I�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSelectAllMenuSelected()
{
	m_rMainWnd.GetPlayList().SelectAll();
}
//----------------------------------------------------------------------------
// �\�� �� �r�f�I��ʃ��j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVideoScreenMenuSelected()
{
	m_rMainWnd.SetVideoScreenVisible();
	m_rMainWnd.StartLyrics();
	m_rMainWnd.StartPitchAnalyser();
}
//----------------------------------------------------------------------------
// �\�� �� �̎����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnLyricsMenuSelected()
{
	BOOL bChecked = !IsItemChecked(ID_LYRICS);
	CheckItem(ID_LYRICS, bChecked ? MF_CHECKED : MF_UNCHECKED);
	CheckItem(ID_PITCHANALYSER, MF_UNCHECKED);
	m_rMainWnd.StartLyrics();
	m_rMainWnd.StartPitchAnalyser();
}
//----------------------------------------------------------------------------
// �\�� �� �s�b�`�A�i���C�U���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPitchAnalyserMenuSelected()
{
	BOOL bChecked = !IsItemChecked(ID_PITCHANALYSER);
	CheckItem(ID_PITCHANALYSER, bChecked ? MF_CHECKED : MF_UNCHECKED);
	CheckItem(ID_LYRICS, MF_UNCHECKED);
	m_rMainWnd.StartLyrics();
	m_rMainWnd.StartPitchAnalyser();
}
//----------------------------------------------------------------------------
// �\�� �� �Đ��ʒu�X���C�_���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTimeSliderMenuSelected()
{
	m_rMainWnd.SetTimeSliderVisible();
}
//----------------------------------------------------------------------------
// �\�� �� �G�N�X�v���[�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnExplorerMenuSelected()
{
	m_rMainWnd.SetExplorerVisible();
}
//----------------------------------------------------------------------------
// �\�� �� �Đ����x���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSpeedMenuSelected()
{
	m_rMainWnd.SetSpeedVisible();
}
//----------------------------------------------------------------------------
// �\�� �� �Đ����g�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFreqMenuSelected()
{
	m_rMainWnd.SetFreqVisible();
}
//----------------------------------------------------------------------------
// �\�� �� �������j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPitchMenuSelected()
{
	m_rMainWnd.SetPitchVisible();
}
//----------------------------------------------------------------------------
// �\�� �� ���ʃ��j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVolumeMenuSelected()
{
	m_rMainWnd.SetVolumeVisible();
}
//----------------------------------------------------------------------------
// �\�� �� �p�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPanMenuSelected()
{
	m_rMainWnd.SetPanVisible();
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMenuSelected()
{
	m_rMainWnd.SetEQVisible();
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 20Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ20MenuSelected()
{
	SwitchEQVisible(ID_EQ20);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 25Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ25MenuSelected()
{
	SwitchEQVisible(ID_EQ25);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 31.5Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ31_5MenuSelected()
{
	SwitchEQVisible(ID_EQ31_5);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 40Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ40MenuSelected()
{
	SwitchEQVisible(ID_EQ40);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 50Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ50MenuSelected()
{
	SwitchEQVisible(ID_EQ50);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 63Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ63MenuSelected()
{
	SwitchEQVisible(ID_EQ63);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 80Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ80MenuSelected()
{
	SwitchEQVisible(ID_EQ80);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 100Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ100MenuSelected()
{
	SwitchEQVisible(ID_EQ100);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 125Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ125MenuSelected()
{
	SwitchEQVisible(ID_EQ125);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 160Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ160MenuSelected()
{
	SwitchEQVisible(ID_EQ160);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 200Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ200MenuSelected()
{
	SwitchEQVisible(ID_EQ200);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 250Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ250MenuSelected()
{
	SwitchEQVisible(ID_EQ250);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 315Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ315MenuSelected()
{
	SwitchEQVisible(ID_EQ315);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 400Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ400MenuSelected()
{
	SwitchEQVisible(ID_EQ400);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 500Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ500MenuSelected()
{
	SwitchEQVisible(ID_EQ500);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 630Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ630MenuSelected()
{
	SwitchEQVisible(ID_EQ630);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 800Hz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ800MenuSelected()
{
	SwitchEQVisible(ID_EQ800);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 1KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ1KMenuSelected()
{
	SwitchEQVisible(ID_EQ1K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 1.25KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ1_25KMenuSelected()
{
	SwitchEQVisible(ID_EQ1_25K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 1.6KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ1_6KMenuSelected()
{
	SwitchEQVisible(ID_EQ1_6K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 2KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ2KMenuSelected()
{
	SwitchEQVisible(ID_EQ2K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 2.5KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ2_5KMenuSelected()
{
	SwitchEQVisible(ID_EQ2_5K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 3.15KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ3_15KMenuSelected()
{
	SwitchEQVisible(ID_EQ3_15K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 4KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ4KMenuSelected()
{
	SwitchEQVisible(ID_EQ4K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 5KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ5KMenuSelected()
{
	SwitchEQVisible(ID_EQ5K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 6.3KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ6_3KMenuSelected()
{
	SwitchEQVisible(ID_EQ6_3K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 8KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ8KMenuSelected()
{
	SwitchEQVisible(ID_EQ8K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 10KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ10KMenuSelected()
{
	SwitchEQVisible(ID_EQ10K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 12.5KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ12_5KMenuSelected()
{
	SwitchEQVisible(ID_EQ12_5K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 16KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ16KMenuSelected()
{
	SwitchEQVisible(ID_EQ16K);
}
//----------------------------------------------------------------------------
// �\�� �� �O���t�B�b�N�C�R���C�U �� 20KHz ���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQ20KMenuSelected()
{
	SwitchEQVisible(ID_EQ20K);
}
//----------------------------------------------------------------------------
// �\�� �� �^�u���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTabMenuSelected()
{
	m_rMainWnd.SetTabVisible();
}
//----------------------------------------------------------------------------
// �\�� �� �Đ����X�g���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPlayListMenuSelected()
{
	m_rMainWnd.SetPlayListVisible();
}
//----------------------------------------------------------------------------
// �\�� �� �S�ẴR���g���[������郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCloseAllMenuSelected()
{
	if(IsItemChecked(ID_VIDEOSCREEN)) OnVideoScreenMenuSelected();
	if(IsItemChecked(ID_TIMESLIDER)) OnTimeSliderMenuSelected();
	if(IsItemChecked(ID_SPEED)) OnSpeedMenuSelected();
	if(IsItemChecked(ID_FREQ)) OnFreqMenuSelected();
	if(IsItemChecked(ID_PITCH)) OnPitchMenuSelected();
	if(IsItemChecked(ID_VOLUME)) OnVolumeMenuSelected();
	if(IsItemChecked(ID_PAN)) OnPanMenuSelected();
	if(IsItemChecked(ID_EQ)) OnEQMenuSelected();
	if(IsItemChecked(ID_PLAYLIST)) OnPlayListMenuSelected();
}
//----------------------------------------------------------------------------
// �\�� �� �c�[���o�[ �� �T�C�Y�i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnToolbarSSizeMenuSelected()
{
	m_rMainWnd.GetToolBar().SetSSize();
	m_rMainWnd.SetMinMax(520);
	m_rMainWnd.ResetAllControlPos();
	m_rMainWnd.ResetSize();
	CheckItem(ID_TOOLBAR_SIZES, MFS_CHECKED);
	CheckItem(ID_TOOLBAR_SIZEM, MFS_UNCHECKED);
	CheckItem(ID_TOOLBAR_SIZEL, MFS_UNCHECKED);
}
//----------------------------------------------------------------------------
// �\�� �� �c�[���o�[ �� �T�C�Y�i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnToolbarMSizeMenuSelected()
{
	m_rMainWnd.GetToolBar().SetMSize();
	m_rMainWnd.SetMinMax(570);
	m_rMainWnd.ResetAllControlPos();
	m_rMainWnd.ResetSize();
	CheckItem(ID_TOOLBAR_SIZES, MFS_UNCHECKED);
	CheckItem(ID_TOOLBAR_SIZEM, MFS_CHECKED);
	CheckItem(ID_TOOLBAR_SIZEL, MFS_UNCHECKED);
}
//----------------------------------------------------------------------------
// �\�� �� �c�[���o�[ �� �T�C�Y�i��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnToolbarLSizeMenuSelected()
{
	m_rMainWnd.GetToolBar().SetLSize();
	m_rMainWnd.SetMinMax(620);
	m_rMainWnd.ResetAllControlPos();
	m_rMainWnd.ResetSize();
	CheckItem(ID_TOOLBAR_SIZES, MFS_UNCHECKED);
	CheckItem(ID_TOOLBAR_SIZEM, MFS_UNCHECKED);
	CheckItem(ID_TOOLBAR_SIZEL, MFS_CHECKED);
}
//----------------------------------------------------------------------------
// �\�� �� �c�[���o�[�̃J�X�^�}�C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCustomizeToolbarMenuSelected()
{
	SendMessage((HWND)m_rMainWnd.GetToolBar(), TB_CUSTOMIZE, 0, 0);
	m_rMainWnd.ShowTime();
}
//----------------------------------------------------------------------------
// �Đ� �� ���o�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnHeadMenuSelected()
{
	m_rMainWnd.Head();
}
//----------------------------------------------------------------------------
// �Đ� �� �O�փ��j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPreviousMenuSelected()
{
	if(!m_rMainWnd.IsMarkerPlay())
		m_rMainWnd.PlayPrevious();
	else
		m_rMainWnd.SetPrevMarker();
}
//----------------------------------------------------------------------------
// �Đ� �� ���փ��j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnNextMenuSelected()
{
	if(!m_rMainWnd.IsMarkerPlay())
		m_rMainWnd.PlayNext(FALSE, FALSE);
	else
		m_rMainWnd.SetNextMarker();
}
//----------------------------------------------------------------------------
// �Đ� �� �ꎞ��~���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseMenuSelected()
{
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// �Đ� �� �����߂����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRewindMenuSelected()
{
	if(IsItemChecked(ID_REWIND)) m_rMainWnd.StopRewind();
	else m_rMainWnd.StartRewind();
}
//----------------------------------------------------------------------------
// �Đ� �� �����胁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForwardMenuSelected()
{
	if(IsItemChecked(ID_FORWARD)) m_rMainWnd.StopForward();
	else m_rMainWnd.StartForward();
}
//----------------------------------------------------------------------------
// �ꎞ��~��1�b�߂郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseAndReturn1SecMenuSelected()
{
	if(!m_rMainWnd.GetSound().ChannelIsStopped() && !m_rMainWnd.GetSound().ChannelIsPausing())
		m_rMainWnd.ReturnSeconds(1);
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// �ꎞ��~��2�b�߂郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseAndReturn2SecMenuSelected()
{
	if(!m_rMainWnd.GetSound().ChannelIsStopped() && !m_rMainWnd.GetSound().ChannelIsPausing())
		m_rMainWnd.ReturnSeconds(2);
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// �ꎞ��~��3�b�߂郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseAndReturn3SecMenuSelected()
{
	if(!m_rMainWnd.GetSound().ChannelIsStopped() && !m_rMainWnd.GetSound().ChannelIsPausing())
		m_rMainWnd.ReturnSeconds(3);
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// �ꎞ��~��5�b�߂郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseAndReturn5SecMenuSelected()
{
	if(!m_rMainWnd.GetSound().ChannelIsStopped() && !m_rMainWnd.GetSound().ChannelIsPausing())
		m_rMainWnd.ReturnSeconds(5);
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// �ꎞ��~��10�b�߂郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPauseAndReturn10SecMenuSelected()
{
	if(!m_rMainWnd.GetSound().ChannelIsStopped() && !m_rMainWnd.GetSound().ChannelIsPausing())
		m_rMainWnd.ReturnSeconds(10);
	m_rMainWnd.Pause();
}
//----------------------------------------------------------------------------
// �Đ� �� 1�b�߂郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReturn1SecMenuSelected()
{
	m_rMainWnd.ReturnSeconds(1);
}
//----------------------------------------------------------------------------
// �Đ� �� 2�b�߂郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReturn2SecMenuSelected()
{
	m_rMainWnd.ReturnSeconds(2);
}
//----------------------------------------------------------------------------
// �Đ� �� 3�b�߂郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReturn3SecMenuSelected()
{
	m_rMainWnd.ReturnSeconds(3);
}
//----------------------------------------------------------------------------
// �Đ� �� 5�b�߂郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReturn5SecMenuSelected()
{
	m_rMainWnd.ReturnSeconds(5);
}
//----------------------------------------------------------------------------
// �Đ� �� 10�b�߂郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReturn10SecMenuSelected()
{
	m_rMainWnd.ReturnSeconds(10);
}
//----------------------------------------------------------------------------
// �Đ� �� 1�b�i�ރ��j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForward1SecMenuSelected()
{
	m_rMainWnd.ForwardSeconds(1);
}
//----------------------------------------------------------------------------
// �Đ� �� 2�b�i�ރ��j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForward2SecMenuSelected()
{
	m_rMainWnd.ForwardSeconds(2);
}
//----------------------------------------------------------------------------
// �Đ� �� 3�b�i�ރ��j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForward3SecMenuSelected()
{
	m_rMainWnd.ForwardSeconds(3);
}
//----------------------------------------------------------------------------
// �Đ� �� 5�b�i�ރ��j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForward5SecMenuSelected()
{
	m_rMainWnd.ForwardSeconds(5);
}
//----------------------------------------------------------------------------
// �Đ� �� 10�b�i�ރ��j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnForward10SecMenuSelected()
{
	m_rMainWnd.ForwardSeconds(10);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� �v���Z�b�g �� ���݂̐ݒ��ǉ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAddPresetMenuSelected()
{
	m_rMainWnd.AddPreset();
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� �v���Z�b�g �� �I�𒆂̃v���Z�b�g���폜���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDeletePresetMenuSelected()
{
	m_rMainWnd.DeletePreset();
	UncheckPresetMenu();
	OnResetAllMenuSelected();
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� �v���Z�b�g���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPresetMenuSelected(int id)
{
	if(IsItemChecked(id)) {
		OnResetAllMenuSelected();
		UncheckPresetMenu();
	}
	else {
		OnResetAllMenuSelected();
		m_rMainWnd.SetPreset(id - ID_PRESET);
		UncheckPresetMenu();
		CheckItem(id, MF_CHECKED);
		EnableItem(ID_DELETEPRESET, MFS_ENABLED);
	}
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �f�t�H���g�ɖ߂����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnResetSpeedMenuSelected()
{
	m_rMainWnd.ResetSpeed();
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 50%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed50MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(50.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(50 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(50.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 60%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed60MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(60.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(60 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(60.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 70%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed70MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(70.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(70 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(70.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 80%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed80MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(80.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(80 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(80.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 90%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed90MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(90.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(90 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(90.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 100%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed100MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(100.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(100 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(100.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 110%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed110MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(110.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(110 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(110.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 120%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed120MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(120.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(120 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(120.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 130%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed130MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(130.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(130 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(130.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 140%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed140MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(140.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(140 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(140.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 150%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed150MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(150.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(150 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(150.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 160%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed160MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(160.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(160 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(160.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 170%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed170MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(170.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(170 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(170.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 180%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed180MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(180.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(180 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(180.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 190%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed190MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(190.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(190 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(190.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 200%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed200MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(200.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(200 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(200.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 250%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed250MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(250.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(250 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(250.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 300%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed300MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(300.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(300 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(300.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 350%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed350MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(350.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(350 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(350.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 400%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeed400MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetSpeedSlider().GetDecimalDigit());
	m_rMainWnd.GetSpeedLabel().SetSpeed(400.0);
	m_rMainWnd.GetSpeedSlider().SetThumbPos((int)(400 * dCalc), TRUE);
	m_rMainWnd.SetSpeed(400.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 0.1%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown0_1SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(0.1);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 1%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown1SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(1);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 2%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown2SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(2);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 3%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown3SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(3);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 5%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown5SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(5);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 10%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown10SpeedMenuSelected()
{
	m_rMainWnd.DownSpeed(10);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 0.1%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp0_1SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(0.1);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 1%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp1SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(1);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 2%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp2SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(2);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 3%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp3SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(3);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 5%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp5SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(5);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� 10%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp10SpeedMenuSelected()
{
	m_rMainWnd.UpSpeed(10);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� �f�t�H���g�ɖ߂����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnResetFreqMenuSelected()
{
	m_rMainWnd.ResetFreq();
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 50%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq50MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(50.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(50 * dCalc), TRUE);
	m_rMainWnd.SetFreq(50.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 60%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq60MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(60.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(60 * dCalc), TRUE);
	m_rMainWnd.SetFreq(60.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 70%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq70MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(70.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(70 * dCalc), TRUE);
	m_rMainWnd.SetFreq(70.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 80%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq80MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(80.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(80 * dCalc), TRUE);
	m_rMainWnd.SetFreq(80.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 90%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq90MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(90.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(90 * dCalc), TRUE);
	m_rMainWnd.SetFreq(90.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 100%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq100MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(100.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(100 * dCalc), TRUE);
	m_rMainWnd.SetFreq(100.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 110%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq110MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(110.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(110 * dCalc), TRUE);
	m_rMainWnd.SetFreq(110.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 120%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq120MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(120.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(120 * dCalc), TRUE);
	m_rMainWnd.SetFreq(120.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 130%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq130MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(130.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(130 * dCalc), TRUE);
	m_rMainWnd.SetFreq(130.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 140%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq140MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(140.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(140 * dCalc), TRUE);
	m_rMainWnd.SetFreq(140.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 150%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq150MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(150.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(150 * dCalc), TRUE);
	m_rMainWnd.SetFreq(150.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 160%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq160MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(160.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(160 * dCalc), TRUE);
	m_rMainWnd.SetFreq(160.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 170%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq170MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(170.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(170 * dCalc), TRUE);
	m_rMainWnd.SetFreq(170.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 180%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq180MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(180.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(180 * dCalc), TRUE);
	m_rMainWnd.SetFreq(180.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 190%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq190MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(190.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(190 * dCalc), TRUE);
	m_rMainWnd.SetFreq(190.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 200%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq200MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(200.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(200 * dCalc), TRUE);
	m_rMainWnd.SetFreq(200.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 250%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq250MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(250.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(250 * dCalc), TRUE);
	m_rMainWnd.SetFreq(250.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 300%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq300MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(300.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(300 * dCalc), TRUE);
	m_rMainWnd.SetFreq(300.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 350%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq350MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(350.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(350 * dCalc), TRUE);
	m_rMainWnd.SetFreq(350.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����x �� �ݒ� �� 400%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreq400MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetFreqSlider().GetDecimalDigit());
	m_rMainWnd.GetFreqLabel().SetFreq(400.0);
	m_rMainWnd.GetFreqSlider().SetThumbPos((int)(400 * dCalc), TRUE);
	m_rMainWnd.SetFreq(400.0);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 0.1%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown0_1FreqMenuSelected()
{
	m_rMainWnd.DownFreq(0.1);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 1%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown1FreqMenuSelected()
{
	m_rMainWnd.DownFreq(1);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 2%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown2FreqMenuSelected()
{
	m_rMainWnd.DownFreq(2);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 3%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown3FreqMenuSelected()
{
	m_rMainWnd.DownFreq(3);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 5%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown5FreqMenuSelected()
{
	m_rMainWnd.DownFreq(5);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 10%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown10FreqMenuSelected()
{
	m_rMainWnd.DownFreq(10);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 0.1%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp0_1FreqMenuSelected()
{
	m_rMainWnd.UpFreq(0.1);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 1%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp1FreqMenuSelected()
{
	m_rMainWnd.UpFreq(1);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 2%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp2FreqMenuSelected()
{
	m_rMainWnd.UpFreq(2);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 3%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp3FreqMenuSelected()
{
	m_rMainWnd.UpFreq(3);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 5%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp5FreqMenuSelected()
{
	m_rMainWnd.UpFreq(5);
}
//----------------------------------------------------------------------------
// �Đ� �� �Đ����g�� �� 10%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp10FreqMenuSelected()
{
	m_rMainWnd.UpFreq(10);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �f�t�H���g�ɖ߂����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnResetPitchMenuSelected()
{
	m_rMainWnd.ResetPitch();
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��12���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat12MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-12.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-12 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-12.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��11���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat11MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-11.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-11 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-11.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��10���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat10MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-10.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-10 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-10.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��9���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat9MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-9.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-9 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-9.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��8���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat8MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-8.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-8 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-8.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��7���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat7MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-7.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-7 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-7.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��6���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat6MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-6.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-6 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-6.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��5���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat5MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-5.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-5 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-5.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��4���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat4MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-4.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-4 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-4.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��3���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat3MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-3.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-3 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-3.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��2���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat2MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-2.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-2 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-2.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��1���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchFlat1MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(-1.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(-1 * dCalc), TRUE);
	m_rMainWnd.SetPitch(-1.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� 0���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchNaturalMenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(0.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(0 * dCalc), TRUE);
	m_rMainWnd.SetPitch(0.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��1���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp1MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(1.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(1 * dCalc), TRUE);
	m_rMainWnd.SetPitch(1.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��2���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp2MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(2.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(2 * dCalc), TRUE);
	m_rMainWnd.SetPitch(2.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��3���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp3MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(3.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(3 * dCalc), TRUE);
	m_rMainWnd.SetPitch(3.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��4���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp4MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(4.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(4 * dCalc), TRUE);
	m_rMainWnd.SetPitch(4.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��5���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp5MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(5.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(5 * dCalc), TRUE);
	m_rMainWnd.SetPitch(5.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��6���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp6MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(6.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(6 * dCalc), TRUE);
	m_rMainWnd.SetPitch(6.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��7���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp7MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(7.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(7 * dCalc), TRUE);
	m_rMainWnd.SetPitch(7.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��8���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp8MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(8.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(8 * dCalc), TRUE);
	m_rMainWnd.SetPitch(8.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��9���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp9MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(9.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(9 * dCalc), TRUE);
	m_rMainWnd.SetPitch(9.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��10���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp10MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(10.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(10 * dCalc), TRUE);
	m_rMainWnd.SetPitch(10.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��11���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp11MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(11.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(11 * dCalc), TRUE);
	m_rMainWnd.SetPitch(11.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����w�� �� ��12���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchSharp12MenuSelected()
{
	double dCalc = pow(10.0, m_rMainWnd.GetPitchSlider().GetDecimalDigit());
	m_rMainWnd.GetPitchLabel().SetPitch(12.0);
	m_rMainWnd.GetPitchSlider().SetThumbPos((int)(12 * dCalc), TRUE);
	m_rMainWnd.SetPitch(12.0);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� ���������郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown1PitchMenuSelected()
{
	m_rMainWnd.DownPitch(1);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �S�������郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown2PitchMenuSelected()
{
	m_rMainWnd.DownPitch(2);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �P�I�N�^�[�u�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDown1OctavePitchMenuSelected()
{
	m_rMainWnd.DownPitch(12);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �����グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp1PitchMenuSelected()
{
	m_rMainWnd.UpPitch(1);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �S���グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp2PitchMenuSelected()
{
	m_rMainWnd.UpPitch(2);
}
//----------------------------------------------------------------------------
// �Đ� �� ���� �� �P�I�N�^�[�u�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUp1OctavePitchMenuSelected()
{
	m_rMainWnd.UpPitch(12);
}
//----------------------------------------------------------------------------
// ���ʂ�1%�グ�郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUpVolumeMenuSelected()
{
	m_rMainWnd.UpVolume(1);
}
//----------------------------------------------------------------------------
// ���ʂ�1%�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDownVolumeMenuSelected()
{
	m_rMainWnd.DownVolume(1);
}
//----------------------------------------------------------------------------
// �Đ� �� ��~���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnStopMenuSelected()
{
	m_rMainWnd.Stop(FALSE);
}
//----------------------------------------------------------------------------
// �Đ� �� �P�ȃ��[�v���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSingleLoopMenuSelected()
{
	m_rMainWnd.SetSingleLoop();
}
//----------------------------------------------------------------------------
// �Đ� �� �S�ȃ��[�v���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAllLoopMenuSelected()
{
	m_rMainWnd.SetAllLoop();
}
//----------------------------------------------------------------------------
// �Đ� �� �����_���Đ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRandomMenuSelected()
{
	m_rMainWnd.SetRandom();
}
//----------------------------------------------------------------------------
// �Đ� �� �A���Đ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnContinueMenuSelected()
{
	m_rMainWnd.SetContinue();
}
//----------------------------------------------------------------------------
// �Đ� �� �����A�[�e�B�X�g�̋Ȃ��Đ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSameArtistMenuSelected()
{
	SwitchItemChecked(ID_SAMEARTIST);
}
//----------------------------------------------------------------------------
// �Đ� �� �`�a���[�v�i�`�j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnABLoopAMenuSelected()
{
	m_rMainWnd.SetABLoopA();
}
//----------------------------------------------------------------------------
// �Đ� �� �`�a���[�v�i�a�j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnABLoopBMenuSelected()
{
	m_rMainWnd.SetABLoopB();
}
//----------------------------------------------------------------------------
// �Đ� �� �`�a���[�v�i�`�j�̈ʒu�ݒ胁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnABLoopASettingMenuSelected()
{
	m_rMainWnd.SetABLoopASetting();
}
//----------------------------------------------------------------------------
// �Đ� �� �`�a���[�v�i�a�j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnABLoopBSettingMenuSelected()
{
	m_rMainWnd.SetABLoopBSetting();
}
//----------------------------------------------------------------------------
// �Đ� �� �}�[�J�[�Đ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnMarkerPlayMenuSelected()
{
	m_rMainWnd.SetMarkerPlay();
}
//----------------------------------------------------------------------------
// �Đ� �� �}�[�J�[�ǉ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnAddMarkerMenuSelected()
{
	m_rMainWnd.AddMarker();
}
//----------------------------------------------------------------------------
// �Đ� �� �}�[�J�[�폜���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDeleteMarkerMenuSelected()
{
	m_rMainWnd.DeleteMarker();
}
//----------------------------------------------------------------------------
// �Đ� �� �񐔃��[�v���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCountLoopMenuSelected()
{
	m_rMainWnd.SetCountLoop();
}
//----------------------------------------------------------------------------
// �Đ� �� �}�[�J�[�ǉ����Ƀ��[�v���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnInstantLoopMenuSelected()
{
	m_rMainWnd.SetInstantLoop();
}
//----------------------------------------------------------------------------
// �Đ� �� �}�[�J�[�ʒu�ύX���ɍĐ��ʒu�ύX���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPositionAutoMenuSelected()
{
	m_rMainWnd.SetPositionAuto();
}
//----------------------------------------------------------------------------
// �Đ� �� ���R�[�h�m�C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRecordNoiseMenuSelected()
{
	BOOL bRecordNoise = !IsItemChecked(ID_RECORDNOISE);
	m_rMainWnd.SetRecordNoise(bRecordNoise);
}
//----------------------------------------------------------------------------
// �Đ� �� �g�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnWaveMenuSelected()
{
	BOOL bWave = !IsItemChecked(ID_WAVE);
	m_rMainWnd.SetWave(bWave);
}
//----------------------------------------------------------------------------
// �Đ� �� �m�[�}���C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnNormalizeMenuSelected()
{
	m_rMainWnd.SetNormalize();
}
//----------------------------------------------------------------------------
// �Đ� �� �{�[�J���L�����Z�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVocalCancelMenuSelected()
{
	m_rMainWnd.SetVocalCancel();
}
//----------------------------------------------------------------------------
// �Đ� �� �t��]�Đ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReverseMenuSelected()
{
	m_rMainWnd.SetReverse();
}
//----------------------------------------------------------------------------
// �Đ� �� �Âт����R�[�h�Đ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRecordMenuSelected()
{
	m_rMainWnd.SetRecord();
}
//----------------------------------------------------------------------------
// �Đ� �� �G�t�F�N�g �� �d�r�؂ꃁ�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnLowBatteryMenuSelected()
{
	m_rMainWnd.SetLowBattery();
}
//----------------------------------------------------------------------------
// �Đ� �� �G�t�F�N�g �� �̂ւ����[�h���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnNoSenseMenuSelected()
{
	m_rMainWnd.SetNoSense();
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� �x�[�X�̎��R�s���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnBassCopyMenuSelected()
{
	if(IsItemChecked(ID_NOSENSE)) m_rMainWnd.SetNoSense();
	BOOL bChecked = !IsItemChecked(ID_BASSCOPY);
	if(bChecked) {
		m_rMainWnd.SetFreq(100.0);
		m_rMainWnd.GetPitchLabel().SetPitch(12.0);
		m_rMainWnd.GetPitchSlider().SetThumbPos((LONG)(12 * pow(10.0,
			m_rMainWnd.GetPitchSlider().GetDecimalDigit())), TRUE);
		m_rMainWnd.SetPitch(12.0);
		m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -30,
						 -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
						 -30, -30, -30, -30);
	}
	else {
		m_rMainWnd.SetFreq(100.0);
		m_rMainWnd.GetPitchLabel().SetPitch(0.0);
		m_rMainWnd.GetPitchSlider().SetThumbPos(0L, TRUE);
		m_rMainWnd.SetPitch(0.0);
		OnEQFlatMenuSelected();
	}
	CheckItem(ID_BASSCOPY, bChecked ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� �h�����i�n�C�n�b�g�A�V���o���j�̎��R�s���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDrumsCopyMenuSelected()
{
	BOOL bChecked = !IsItemChecked(ID_CYMBALCOPY);
	if(bChecked) {
		m_rMainWnd.SetFreq(100.0);
		m_rMainWnd.GetPitchLabel().SetPitch(0.0);
		m_rMainWnd.GetPitchSlider().SetThumbPos(0L, TRUE);
		m_rMainWnd.SetPitch(0.0);
		m_rMainWnd.SetEQ(-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
						 -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
						 -30, -30, 0, 0, 0, 0, 0, 0, 0);
	}
	else {
		m_rMainWnd.SetFreq(100.0);
		m_rMainWnd.GetPitchLabel().SetPitch(0.0);
		m_rMainWnd.GetPitchSlider().SetThumbPos(0L, TRUE);
		m_rMainWnd.SetPitch(0.0);
		OnEQFlatMenuSelected();
	}
	CheckItem(ID_CYMBALCOPY, bChecked ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �Đ� �� �G�t�F�N�g �� ���o�g���[�j���O���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEarTrainingMenuSelected()
{
	m_rMainWnd.SetEarTraining();
}
//----------------------------------------------------------------------------
// �Đ� �� ���m�������j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnMonoralMenuSelected()
{
	m_rMainWnd.SetMonoral();
}
//----------------------------------------------------------------------------
// �Đ� �� ���̂ݍĐ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOnlyLeftMenuSelected()
{
	m_rMainWnd.SetOnlyLeft();
}
//----------------------------------------------------------------------------
// �Đ� �� �E�̂ݍĐ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOnlyRightMenuSelected()
{
	m_rMainWnd.SetOnlyRight();
}
//----------------------------------------------------------------------------
// �Đ� �� ���E����ւ����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnChangeLRMenuSelected()
{
	m_rMainWnd.SetChangeLR();
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� �S�ăf�t�H���g�ɖ߂����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnResetAllMenuSelected()
{
	m_rMainWnd.SetRecordNoise(FALSE);
	m_rMainWnd.SetWave(FALSE);
	m_rMainWnd.ResetSpeed();
	m_rMainWnd.ResetFreq();
	m_rMainWnd.ResetPitch();
	OnEQFlatMenuSelected();
	m_rMainWnd.GetPanLabel().SetPan(0);
	m_rMainWnd.GetPanSlider().SetThumbPos(0);
	m_rMainWnd.SetPan(0);
	CheckItem(ID_REVERB_DEFAULT, MF_CHECKED);
	SetReverb(0.0f, 0.0f, 1000.0f, 0.001f, ID_REVERB_DEFAULT);
	CheckItem(ID_3DREVERB_DEFAULT, MF_CHECKED);
	Set3DReverb(-1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f, 200, 0.011f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_DEFAULT);
	CheckItem(ID_DELAY_DEFAULT, MF_CHECKED);
	SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_DEFAULT);
	CheckItem(ID_CHORUS_DEFAULT, MF_CHECKED);
	SetChorus(50.0f, 10.0f, 25.0f, 1.1f, 1, 16.0f, BASS_DX8_PHASE_90,
				ID_CHORUS_DEFAULT);
	CheckItem(ID_COMPRESSOR_DEFAULT, MF_CHECKED);
	SetCompressor(0.0f, 10.0f, 200.0f, -20.0f, 3.0f, 4.0f,
					ID_COMPRESSOR_DEFAULT);
	CheckItem(ID_FLANGER_DEFAULT, MF_CHECKED);
	SetFlanger(50.0f, 100.0f, -50.0f, 0.25f, 1, 2.0f, BASS_DX8_PHASE_ZERO,
				ID_FLANGER_DEFAULT);
	CheckItem(ID_GARGLE_DEFAULT, MF_CHECKED);
	SetGargle(20, 0, ID_GARGLE_DEFAULT);
	CheckItem(ID_DISTORTION_DEFAULT, MF_CHECKED);
	SetDistortion(-18.0f, 15.0f, 2400.0f, 2400.0f, 8000.0f,
					ID_DISTORTION_DEFAULT);
	if(IsItemChecked(ID_NORMALIZE)) m_rMainWnd.SetNormalize();
	if(IsItemChecked(ID_VOCALCANCEL)) m_rMainWnd.SetVocalCancel();
	if(IsItemChecked(ID_REVERSE)) m_rMainWnd.SetReverse();
	if(IsItemChecked(ID_RECORD)) m_rMainWnd.SetRecord();
	if(IsItemChecked(ID_LOWBATTERY)) m_rMainWnd.SetLowBattery();
	if(IsItemChecked(ID_NOSENSE)) m_rMainWnd.SetNoSense();
	if(IsItemChecked(ID_EARTRAINING)) m_rMainWnd.SetEarTraining();
	if(IsItemChecked(ID_MONORAL)) m_rMainWnd.SetMonoral();
	if(IsItemChecked(ID_ONLYLEFT)) m_rMainWnd.SetOnlyLeft();
	if(IsItemChecked(ID_ONLYRIGHT)) m_rMainWnd.SetOnlyRight();
	if(IsItemChecked(ID_CHANGELR)) m_rMainWnd.SetChangeLR();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �V���[�g�J�b�g�L�[�ݒ胁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnKeySettingMenuSelected()
{
	m_rMainWnd.SetKeySetting();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �O���[�o���z�b�g�L�[�ݒ胁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnOutKeySettingMenuSelected()
{
	m_rMainWnd.SetOutKeySetting();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ő�l�^�ŏ��l�ݒ胁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnLimitMenuSelected()
{
	m_rMainWnd.SetLimit();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �^�C�}�[�ݒ胁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTimerPlayMenuSelected()
{
	m_rMainWnd.SetTimerPlay();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ��͈̓��j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPlayRangeMenuSelected()
{
	m_rMainWnd.SetPlayRange();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ��ʒu���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnPlayPositionMenuSelected()
{
	m_rMainWnd.SetPlayPosition();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ����x�����񂾂�x�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDecSpeedMenuSelected()
{
	m_rMainWnd.SetDecSpeed();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ����x�����񂾂񑬂����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnIncSpeedMenuSelected()
{
	m_rMainWnd.SetIncSpeed();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ����x �� �����_���� �� 0�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeedDecimal0MenuSelected()
{
	CheckItem(ID_SPEEDDEC_0, MF_CHECKED);
	CheckItem(ID_SPEEDDEC_1, MF_UNCHECKED);
	CheckItem(ID_SPEEDDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetSpeedLabel().SetDecimalDigit(0);
	m_rMainWnd.GetSpeedSlider().SetDecimalDigit(0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ����x �� �����_���� �� 1�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeedDecimal1MenuSelected()
{
	CheckItem(ID_SPEEDDEC_0, MF_UNCHECKED);
	CheckItem(ID_SPEEDDEC_1, MF_CHECKED);
	CheckItem(ID_SPEEDDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetSpeedLabel().SetDecimalDigit(1);
	m_rMainWnd.GetSpeedSlider().SetDecimalDigit(1);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ����x �� �����_���� �� 2�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetSpeedDecimal2MenuSelected()
{
	CheckItem(ID_SPEEDDEC_0, MF_UNCHECKED);
	CheckItem(ID_SPEEDDEC_1, MF_UNCHECKED);
	CheckItem(ID_SPEEDDEC_2, MF_CHECKED);
	m_rMainWnd.GetSpeedLabel().SetDecimalDigit(2);
	m_rMainWnd.GetSpeedSlider().SetDecimalDigit(2);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ����g�������񂾂�x�����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDecFreqMenuSelected()
{
	m_rMainWnd.SetDecFreq();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ����g�������񂾂񑬂����郁�j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnIncFreqMenuSelected()
{
	m_rMainWnd.SetIncFreq();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ����g�� �� �����_���� �� 0�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreqDecimal0MenuSelected()
{
	CheckItem(ID_FREQDEC_0, MF_CHECKED);
	CheckItem(ID_FREQDEC_1, MF_UNCHECKED);
	CheckItem(ID_FREQDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetFreqLabel().SetDecimalDigit(0);
	m_rMainWnd.GetFreqSlider().SetDecimalDigit(0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ����g�� �� �����_���� �� 1�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreqDecimal1MenuSelected()
{
	CheckItem(ID_FREQDEC_0, MF_UNCHECKED);
	CheckItem(ID_FREQDEC_1, MF_CHECKED);
	CheckItem(ID_FREQDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetFreqLabel().SetDecimalDigit(1);
	m_rMainWnd.GetFreqSlider().SetDecimalDigit(1);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ����g�� �� �����_���� �� 2�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetFreqDecimal2MenuSelected()
{
	CheckItem(ID_FREQDEC_0, MF_UNCHECKED);
	CheckItem(ID_FREQDEC_1, MF_UNCHECKED);
	CheckItem(ID_FREQDEC_2, MF_CHECKED);
	m_rMainWnd.GetFreqLabel().SetDecimalDigit(2);
	m_rMainWnd.GetFreqSlider().SetDecimalDigit(2);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ���� �� �����_���� �� 0�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchDecimal0MenuSelected()
{
	CheckItem(ID_PITCHDEC_0, MF_CHECKED);
	CheckItem(ID_PITCHDEC_1, MF_UNCHECKED);
	CheckItem(ID_PITCHDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetPitchLabel().SetDecimalDigit(0);
	m_rMainWnd.GetPitchSlider().SetDecimalDigit(0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ���� �� �����_���� �� 1�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchDecimal1MenuSelected()
{
	CheckItem(ID_PITCHDEC_0, MF_UNCHECKED);
	CheckItem(ID_PITCHDEC_1, MF_CHECKED);
	CheckItem(ID_PITCHDEC_2, MF_UNCHECKED);
	m_rMainWnd.GetPitchLabel().SetDecimalDigit(1);
	m_rMainWnd.GetPitchSlider().SetDecimalDigit(1);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ���� �� �����_���� �� 2�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetPitchDecimal2MenuSelected()
{
	CheckItem(ID_PITCHDEC_0, MF_UNCHECKED);
	CheckItem(ID_PITCHDEC_1, MF_UNCHECKED);
	CheckItem(ID_PITCHDEC_2, MF_CHECKED);
	m_rMainWnd.GetPitchLabel().SetDecimalDigit(2);
	m_rMainWnd.GetPitchSlider().SetDecimalDigit(2);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� �f�t�H���g�ɖ߂����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnResetVolumeMenuSelected()
{
	m_rMainWnd.ResetVolume();
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 0%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume0MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(0.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(0, TRUE);
	m_rMainWnd.SetVolume(0.0);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 10%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume10MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(10.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(100, TRUE);
	m_rMainWnd.SetVolume(10.0);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 20%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume20MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(20.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(200, TRUE);
	m_rMainWnd.SetVolume(20.0);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 30%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume30MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(30.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(300, TRUE);
	m_rMainWnd.SetVolume(30.0);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 40%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume40MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(40.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(400, TRUE);
	m_rMainWnd.SetVolume(40.0);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 50%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume50MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(50.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(500, TRUE);
	m_rMainWnd.SetVolume(50.0);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 60%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume60MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(60.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(600, TRUE);
	m_rMainWnd.SetVolume(60.0);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 70%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume70MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(70.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(700, TRUE);
	m_rMainWnd.SetVolume(70.0);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 80%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume80MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(80.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(800, TRUE);
	m_rMainWnd.SetVolume(80.0);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 90%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume90MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(90.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(900, TRUE);
	m_rMainWnd.SetVolume(90.0);
}
//----------------------------------------------------------------------------
// �G�t�F�N�g �� ���� �� 100%���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnSetVolume100MenuSelected()
{
	m_rMainWnd.GetVolumeLabel().SetVolume(100.0);
	m_rMainWnd.GetVolumeSlider().SetThumbPos(1000, TRUE);
	m_rMainWnd.SetVolume(100.0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Đ���~���Ƀt�F�[�h�A�E�g���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutMenuSelected()
{
	BOOL bCheck = !IsItemChecked(ID_FADEOUTSTOP);
	CheckItem(ID_FADEOUTSTOP, bCheck ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ��~���t�F�[�h�A�E�g���� �� 1�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout1SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP1SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ��~���t�F�[�h�A�E�g���� �� 2�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout2SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP2SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ��~���t�F�[�h�A�E�g���� �� 3�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout3SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP3SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ��~���t�F�[�h�A�E�g���� �� 4�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout4SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP4SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ��~���t�F�[�h�A�E�g���� �� 5�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout5SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP5SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ��~���t�F�[�h�A�E�g���� �� 6�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout6SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP6SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ��~���t�F�[�h�A�E�g���� �� 7�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout7SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP7SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ��~���t�F�[�h�A�E�g���� �� 8�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout8SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP8SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ��~���t�F�[�h�A�E�g���� �� 9�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout9SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP9SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ��~���t�F�[�h�A�E�g���� �� 10�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeout10SecMenuSelected()
{
	UncheckFadeoutMenu();
	CheckItem(ID_FADEOUTSTOP10SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �Ȃ̐ؑ֎��Ƀt�F�[�h�A�E�g���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNextMenuSelected()
{
	BOOL bCheck = !IsItemChecked(ID_FADEOUTNEXT);
	CheckItem(ID_FADEOUTNEXT, bCheck ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ؑ֎��t�F�[�h�A�E�g���� �� 1�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext1SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT1SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ؑ֎��t�F�[�h�A�E�g���� �� 2�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext2SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT2SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ؑ֎��t�F�[�h�A�E�g���� �� 3�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext3SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT3SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ؑ֎��t�F�[�h�A�E�g���� �� 4�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext4SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT4SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ؑ֎��t�F�[�h�A�E�g���� �� 5�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext5SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT5SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ؑ֎��t�F�[�h�A�E�g���� �� 6�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext6SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT6SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ؑ֎��t�F�[�h�A�E�g���� �� 7�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext7SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT7SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ؑ֎��t�F�[�h�A�E�g���� �� 8�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext8SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT8SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ؑ֎��t�F�[�h�A�E�g���� �� 9�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext9SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT9SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ؑ֎��t�F�[�h�A�E�g���� �� 10�b���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFadeoutNext10SecMenuSelected()
{
	UncheckFadeoutNextMenu();
	CheckItem(ID_FADEOUTNEXT10SEC, MF_CHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� Twitter�łԂ₭���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTweetMenuSelected()
{
	m_rMainWnd.Tweet();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ���g���m�[�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnMetronomeMenuSelected()
{
	m_rMainWnd.SetMetronome();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ���� �� �m�[�}�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnQualityNormalMenuSelected()
{
	CheckItem(ID_QUALITY_NORMAL, MFS_CHECKED);
	CheckItem(ID_QUALITY_ASIO, MFS_UNCHECKED);
	CheckItem(ID_QUALITY_WASAPI, MFS_UNCHECKED);
	m_rMainWnd.GetSound().StopASIO();
	m_rMainWnd.GetSound().StopWASAPI();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ���� �� ASIO���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnQualityASIOMenuSelected()
{
	CheckItem(ID_QUALITY_NORMAL, MFS_UNCHECKED);
	CheckItem(ID_QUALITY_ASIO, MFS_CHECKED);
	CheckItem(ID_QUALITY_WASAPI, MFS_UNCHECKED);
	m_rMainWnd.GetSound().StopWASAPI();
	m_rMainWnd.GetSound().StartASIO();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ���� �� WASAPI���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnQualityWASAPIMenuSelected()
{
	CheckItem(ID_QUALITY_NORMAL, MFS_UNCHECKED);
	CheckItem(ID_QUALITY_ASIO, MFS_UNCHECKED);
	CheckItem(ID_QUALITY_WASAPI, MFS_CHECKED);
	m_rMainWnd.GetSound().StopASIO();
	m_rMainWnd.GetSound().StartWASAPI();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� ���o�[�u �� �f�t�H���g���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReverbDefaultMenuSelected()
{
	SetReverb(0.0f, 0.0f, 1000.0f, 0.001f, ID_REVERB_DEFAULT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� ���o�[�u �� �J�X�^�}�C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnReverbCustomizeMenuSelected()
{
	if(IsItemChecked(ID_REVERB_CUSTOMIZE))
		SetReverb(0.0f, 0.0f, 1000.0f, 0.001f, ID_REVERB_CUSTOMIZE);
	else m_rMainWnd.ShowReverbCustomizeWnd();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� �f�t�H���g���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbDefaultMenuSelected()
{
	Set3DReverb(-1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f, 200, 0.011f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_DEFAULT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Padded Cell���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbPaddedCellMenuSelected()
{
	Set3DReverb(-1000, -6000, 0.0f, 0.17f, 0.10f, -1204, 0.001f, 207, 0.002f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_PADDEDCELL);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Room���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbRoomMenuSelected()
{
	Set3DReverb(-1000, -454, 0.0f, 0.4f, 0.83f, -1646, 0.002f, 53, 0.003f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_ROOM);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Bathroom���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbBathroomMenuSelected()
{
	Set3DReverb(-1000, -1200, 0.0f, 1.49f, 0.54f, -370, 0.007f, 1030, 0.011f,
			  100.0f, 60.0f, 5000.0f, ID_3DREVERB_BATHROOM);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� LivingRoom���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbLivingRoomMenuSelected()
{
	Set3DReverb(-1000, -6000, 0.0f, 0.50f, 0.10f, -1376, 0.003f, -1104, 0.004f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_LIVINGROOM);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� StoneRoom���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbStoneRoomMenuSelected()
{
	Set3DReverb(-1000, -300, 0.0f, 2.31f, 0.64f, -711, 0.012f, 83, 0.017f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_STONEROOM);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Auditorium���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbAuditoriumMenuSelected()
{
	Set3DReverb(-1000, -476, 0.0f, 4.32f, 0.59f, -789, 0.020f, -289, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_AUDITORIUM);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� ConcertHall���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbConcertHallMenuSelected()
{
	Set3DReverb(-1000, -500, 0.0f, 3.92f, 0.70f, -1230, 0.020f, -2, 0.029f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_CONCERTHALL);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Cave���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCaveMenuSelected()
{
	Set3DReverb(-1000, 0, 0.0f, 2.91f, 1.30f, -602, 0.015f, -302, 0.022f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_CAVE);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Arena���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbArenaMenuSelected()
{
	Set3DReverb(-1000, -698, 0.0f, 7.24f, 0.33f, -1166, 0.020f, 16, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_ARENA);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Hangar���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbHangarMenuSelected()
{
	Set3DReverb(-1000, -1000, 0.0f,10.05f, 0.23f, -602, 0.020f, 198, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_HANGAR);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� CarpetedHallway���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCarpetedHallwayMenuSelected()
{
	Set3DReverb(-1000, -4000, 0.0f, 0.30f, 0.10f, -1831, 0.002f, -1630, 0.030f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_CARPETEDHALLWAY);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Hallway���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbHallwayMenuSelected()
{
	Set3DReverb(-1000, -300, 0.0f, 1.49f, 0.59f, -1219, 0.007f, 441, 0.011f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_HALLWAY);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� StoneCorridor���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbStoneCorridorMenuSelected()
{
	Set3DReverb(-1000, -237, 0.0f, 2.70f, 0.79f, -1214, 0.013f, 395, 0.020f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_STONECORRIDOR);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Alley���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbAlleyMenuSelected()
{
	Set3DReverb(-1000, -270, 0.0f, 1.49f, 0.86f, -1204, 0.007f, -4, 0.011f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_ALLEY);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Forest���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbForestMenuSelected()
{
	Set3DReverb(-1000, -3300, 0.0f, 1.49f, 0.54f, -2560, 0.162f, -613, 0.088f,
			  79.0f, 100.0f, 5000.0f, ID_3DREVERB_FOREST);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� City���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCityMenuSelected()
{
	Set3DReverb(-1000, -800, 0.0f, 1.49f, 0.67f, -2273, 0.007f, -2217, 0.011f,
			  50.0f, 100.0f, 5000.0f, ID_3DREVERB_CITY);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Mountains���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbMountainsMenuSelected()
{
	Set3DReverb(-1000, -2500, 0.0f, 1.49f, 0.21f, -2780, 0.300f, -2014, 0.100f,
			  27.0f, 100.0f, 5000.0f, ID_3DREVERB_MOUNTAINS);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Quarry���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbQuarryMenuSelected()
{
	Set3DReverb(-1000, -1000, 0.0f, 1.49f, 0.83f,-10000, 0.061f, 500, 0.025f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_QUARRY);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Plain���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbPlainMenuSelected()
{
	Set3DReverb(-1000, -2000, 0.0f, 1.49f, 0.50f, -2466, 0.179f, -2514, 0.100f,
			  21.0f, 100.0f, 5000.0f, ID_3DREVERB_PLAIN);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� ParkingLot���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbParkingLotMenuSelected()
{
	Set3DReverb(-1000, 0, 0.0f, 1.65f, 1.50f, -1363, 0.008f, -1153, 0.012f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_PARKINGLOT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� SewerPipe���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbSewerPipeMenuSelected()
{
	Set3DReverb(-1000, -1000, 0.0f, 2.81f, 0.14f, 429, 0.014f, 648, 0.021f,
			  80.0f, 60.0f, 5000.0f, ID_3DREVERB_SEWERPIPE);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Underwater���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbUnderwaterMenuSelected()
{
	Set3DReverb(-1000, -4000, 0.0f, 1.49f, 0.10f, -449, 0.007f, 1700, 0.011f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_UNDERWATER);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Small Room���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbSmallRoomMenuSelected()
{
	Set3DReverb(-1000, -600, 0.0f, 1.10f, 0.83f, -400, 0.005f, 500, 0.010f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_SMALLROOM);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Medium Room���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbMediumRoomMenuSelected()
{
	Set3DReverb(-1000, -600, 0.0f, 1.30f, 0.83f, -1000, 0.010f, -200, 0.020f,
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_MEDIUMROOM);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Large Room���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbLargeRoomMenuSelected()
{
	Set3DReverb(-1000, -600, 0.0f, 1.50f, 0.83f, -1600, 0.020f, -1000, 0.040f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_LARGEROOM);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Medium Hall���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbMediumHallMenuSelected()
{
	Set3DReverb(-1000, -600, 0.0f, 1.80f, 0.70f, -1300, 0.015f, -800, 0.030f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_MEDIUMHALL);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Large Hall���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbLargeHallMenuSelected()
{
	Set3DReverb(-1000, -600, 0.0f, 1.80f, 0.70f, -2000, 0.030f, -1400, 0.060f, 
			  100.0f, 100.0f, 5000.0f, ID_3DREVERB_LARGEHALL);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� Plate���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbPlateMenuSelected()
{
	Set3DReverb(-1000, -200, 0.0f, 1.30f, 0.90f, 0, 0.002f, 0, 0.010f, 100.0f, 
			  75.0f, 5000.0f, ID_3DREVERB_PLATE);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� �R�c���o�[�u �� �J�X�^�}�C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::On3DReverbCustomizeMenuSelected()
{
	if(IsItemChecked(ID_3DREVERB_CUSTOMIZE))
		Set3DReverb(-1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f, 200, 0.011f,
					100.0f, 100.0f, 5000.0f, ID_3DREVERB_CUSTOMIZE);
	else m_rMainWnd.Show3DReverbCustomizeWnd();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Default���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayDefaultMenuSelected()
{
	SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_DEFAULT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Short Echo���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayShortMenuSelected()
{
	SetDelay(15, 50, 150, 150, FALSE, ID_DELAY_SHORT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Medium Echo���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayMediumMenuSelected()
{
	SetDelay(15, 50, 300, 300, FALSE, ID_DELAY_MEDIUM);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Long Echo���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayLongMenuSelected()
{
	SetDelay(15, 50, 600, 600, FALSE, ID_DELAY_LONG);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Stereo Short Echo���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoShortMenuSelected()
{
	SetDelay(15, 50, 300, 150, TRUE, ID_DELAY_STEREOSHORT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Stetreo Medium Echo���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoMediumMenuSelected()
{
	SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_STEREOMEDIUM);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Stereo Long Echo���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoLongMenuSelected()
{
	SetDelay(15, 50, 1200, 600, TRUE, ID_DELAY_STEREOLONG);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Mountain Echo���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayMountainMenuSelected()
{
	SetDelay(20, 0, 1500, 1500, FALSE, ID_DELAY_MOUNTAIN);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Big Echo���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayBigMenuSelected()
{
	SetDelay(40, 50, 300, 300, FALSE, ID_DELAY_BIG);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Stereo Big Echo���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayStereoBigMenuSelected()
{
	SetDelay(40, 50, 600, 300, TRUE, ID_DELAY_STEREOBIG);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Doubling���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayDoublingMenuSelected()
{
	SetDelay(100, 0, 31, 1, TRUE, ID_DELAY_DOUBLING);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� Double Kick���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayDoubleKickMenuSelected()
{
	SetDelay(50, 0, 100, 100, FALSE, ID_DELAY_DOUBLEKICK);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Delay �� �J�X�^�}�C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDelayCustomizeMenuSelected()
{
	if(IsItemChecked(ID_DELAY_CUSTOMIZE))
		SetDelay(8, 50, 600, 300, TRUE, ID_DELAY_CUSTOMIZE);
	else m_rMainWnd.ShowDelayCustomizeWnd();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Chorus �� Default���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnChorusDefaultMenuSelected()
{
	SetChorus(50.0f, 10.0f, 25.0f, 1.1f, 1, 16.0f, BASS_DX8_PHASE_90,
			  ID_CHORUS_DEFAULT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Chorus �� �J�X�^�}�C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnChorusCustomizeMenuSelected()
{
	if(IsItemChecked(ID_CHORUS_CUSTOMIZE))
		SetChorus(50.0f, 10.0f, 25.0f, 1.1f, 1, 16.0f, BASS_DX8_PHASE_90,
				  ID_CHORUS_CUSTOMIZE);
	else m_rMainWnd.ShowChorusCustomizeWnd();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Compressor �� Default���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCompressorDefaultMenuSelected()
{
	SetCompressor(0.0f, 10.0f, 200.0f, -20.0f, 3.0f, 4.0f,
				  ID_COMPRESSOR_DEFAULT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Compressor �� �J�X�^�}�C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCompressorCustomizeMenuSelected()
{
	if(IsItemChecked(ID_COMPRESSOR_CUSTOMIZE))
		SetCompressor(0.0f, 10.0f, 200.0f, -20.0f, 3.0f, 4.0f,
					  ID_COMPRESSOR_CUSTOMIZE);
	else m_rMainWnd.ShowCompressorCustomizeWnd();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Flanger �� Default���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFlangerDefaultMenuSelected()
{
	SetFlanger(50.0f, 100.0f, -50.0f, 0.25f, 1, 2.0f, BASS_DX8_PHASE_ZERO,
			   ID_FLANGER_DEFAULT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Flanger �� �J�X�^�}�C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnFlangerCustomizeMenuSelected()
{
	if(IsItemChecked(ID_FLANGER_CUSTOMIZE))
		SetFlanger(50.0f, 100.0f, -50.0f, 0.25f, 1, 2.0f, BASS_DX8_PHASE_ZERO,
				   ID_FLANGER_CUSTOMIZE);
	else m_rMainWnd.ShowFlangerCustomizeWnd();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Gargle �� Default���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnGargleDefaultMenuSelected()
{
	SetGargle(20, 0, ID_GARGLE_DEFAULT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Gargle �� �J�X�^�}�C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnGargleCustomizeMenuSelected()
{
	if(IsItemChecked(ID_GARGLE_CUSTOMIZE))
		SetGargle(20, 0, ID_GARGLE_CUSTOMIZE);
	else m_rMainWnd.ShowGargleCustomizeWnd();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Distortion �� Default���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDistortionDefaultMenuSelected()
{
	SetDistortion(-18.0f, 15.0f, 2400.0f, 2400.0f, 8000.0f,
				  ID_DISTORTION_DEFAULT);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �G�t�F�N�g �� Distortion �� �J�X�^�}�C�Y���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDistortionCustomizeMenuSelected()
{
	if(IsItemChecked(ID_DISTORTION_CUSTOMIZE))
		SetDistortion(-18.0f, 15.0f, 2400.0f, 2400.0f, 8000.0f,
					  ID_DISTORTION_CUSTOMIZE);
	else m_rMainWnd.ShowDistortionCustomizeWnd();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� FLAT���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQFlatMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�����i���ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowSuperMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -30, -30, -30, -30,
					 -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
					 -30, -30, -30, -30);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�����i�ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowHighestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -15, -15, -15, -15,
					 -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15,
					 -15, -15, -15, -15);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�����i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowHighMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -12, -12, -12, -12,
					 -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,
					 -12, -12, -12, -12);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�����i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -9, -9, -9, -9, -9,
					 -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�����i��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowLowMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6, -6, -6, -6, -6,
					 -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�����i�Ŏ�j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowLowestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, -3, -3, -3,
					 -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i���ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleSuperMenuSelected()
{
	m_rMainWnd.SetEQ(-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
					 -30, 0, 0, 0, 0, 0, 0, 0, 0, 0, -30, -30, -30, -30, -30,
					 -30, -30, -30, -30, -30);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i�ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleHighestMenuSelected()
{
	m_rMainWnd.SetEQ(-15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15,
					 -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, -15, -15, -15, -15, -15,
					 -15, -15, -15, -15, -15);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleHighMenuSelected()
{
	m_rMainWnd.SetEQ(-12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,
					 -12, 0, 0, 0, 0, 0, 0, 0, 0, 0, -12, -12, -12, -12, -12,
					 -12, -12, -12, -12, -12);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(-9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleLowMenuSelected()
{
	m_rMainWnd.SetEQ(-6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i�Ŏ�j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleLowestMenuSelected()
{
	m_rMainWnd.SetEQ(-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i���ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighSuperMenuSelected()
{
	m_rMainWnd.SetEQ(-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
					 -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i�ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighHighestMenuSelected()
{
	m_rMainWnd.SetEQ(-15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15,
					 -15, -15, -15, -15, -15, -15, -15, -15, -15, -15, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighHighMenuSelected()
{
	m_rMainWnd.SetEQ(-12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,
					 -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(-9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
					 -9, -9, -9, -9, -9, -9, -9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighLowMenuSelected()
{
	m_rMainWnd.SetEQ(-6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,
					 -6, -6, -6, -6, -6, -6, -6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� ���������i�Ŏ�j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighLowestMenuSelected()
{
	m_rMainWnd.SetEQ(-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3,
					 -3, -3, -3, -3, -3, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�J�b�g�i���ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutSuperMenuSelected()
{
	m_rMainWnd.SetEQ(-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30,
					 -30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�J�b�g�i�ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutHighestMenuSelected()
{
	m_rMainWnd.SetEQ(-15, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15,
					 -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�J�b�g�i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutHighMenuSelected()
{
	m_rMainWnd.SetEQ(-12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,
					 -12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�J�b�g�i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(-9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
					 -9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�J�b�g�i��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutLowMenuSelected()
{
	m_rMainWnd.SetEQ(-6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,
					 -6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �ቹ�J�b�g�i�Ŏ�j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQLowCutLowestMenuSelected()
{
	m_rMainWnd.SetEQ(-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3,
					 -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i���ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutSuperMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -30, -30, -30, -30,
					 -30, -30, -30, -30, -30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i�ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutHighestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -15, -15, -15, -15,
					 -15, -15, -15, -15, -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutHighMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -12, -12, -12, -12,
					 -12, -12, -12, -12, -12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -9, -9, -9, -9, -9,
					 -9, -9, -9, -9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutLowMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6, -6, -6, -6, -6,
					 -6, -6, -6, -6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i�Ŏ�j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQMiddleCutLowestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -3, -3, -3, -3,
					 -3, -3, -3, -3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i���ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutSuperMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i�ŋ��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutHighestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -15, -15, -15, -15, -15, -15, -15, -15, -15, -15);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutHighMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i���j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutMiddleMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i��j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutLowMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� EQ�v���Z�b�g �� �����J�b�g�i�Ŏ�j���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnEQHighCutLowestMenuSelected()
{
	m_rMainWnd.SetEQ(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ���d�N�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnDoubleRunMenuSelected()
{
	m_rMainWnd.SetDoubleRun();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �őO�ʕ\�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTopMostMenuSelected()
{
	m_rMainWnd.SetTopMost();
}
//----------------------------------------------------------------------------
// �V�X�e�� �� �ŏ������^�X�N�g���C�Ɋi�[���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnTaskTrayMenuSelected()
{
	BOOL bCheck = !IsItemChecked(ID_TASKTRAY);
	CheckItem(ID_TASKTRAY, bCheck ? MF_CHECKED : MF_UNCHECKED);
}
//----------------------------------------------------------------------------
// �V�X�e�� �� ���݂̍Đ��ʒu���N���b�v�{�[�h�ɃR�s�[���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnCopyTimeMenuSelected()
{
	m_rMainWnd.CopyTime();
}
//----------------------------------------------------------------------------
// �w���v �� �}�j���A�����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnManualMenuSelected()
{
#if JP
	ShellExecute(m_rMainWnd, _T("open"),
				_T("http://soft.edolfzoku.com/hayaemon2/manual.html"), NULL,
				NULL, SW_SHOWDEFAULT);
#else // JP
	tstring manualPath = m_rApp.GetFilePath() + _T("manual\\index.html");
	ShellExecute(NULL, _T("open"), manualPath.c_str(), NULL, NULL, NULL);
#endif // JP
}
//----------------------------------------------------------------------------
// �w���v �� �A�b�v�f�[�g�̊m�F���j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnUpdateCheckMenuSelected()
{
	HINTERNET hInternet = InternetOpen(_T("VersionCheck"),
		INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(hInternet == NULL) {
		MessageBox(m_rMainWnd, _T("�C���^�[�l�b�g�ɐڑ��ł��܂���B"),
			_T("�I�t���C��"), 0);
		CloseHandle(hInternet);
		return;
	}
	tstring strVersion = m_rApp.GetVersionInfo();
	strVersion = CUtils::Replace(strVersion, _T("."), _T(""));
	int nPos = strVersion.find(_T("��"), 0);
	tstring strFileName = _T("Hayaemon");
	if(nPos > 0) {
		int nNextVersion = _ttoi(strVersion.substr(0, nPos).c_str()) + 1;
		TCHAR chVersion[255];
		_stprintf_s(chVersion, _T("%d"), nNextVersion);
		strFileName += (tstring)chVersion + _T(".zip");
	}
	else {
		int nNextVersion = _ttoi(strVersion.substr(0, nPos).c_str()) + 2;
		TCHAR chVersion[255];
		_stprintf_s(chVersion, _T("%d"), nNextVersion);
		strFileName += (tstring)chVersion + _T(".zip");
	}
	HINTERNET hFile = InternetOpenUrl(hInternet,
		((tstring)_T("http://soft.edolfzoku.com/hayaemon2/")
			+ strFileName).c_str(), NULL, 0, 0, 0);
	TCHAR chBuf[512];
	DWORD dwLen = 512;
	HttpQueryInfo(hFile, HTTP_QUERY_CONTENT_LENGTH, chBuf, &dwLen, NULL);
	if(_ttoi(chBuf) > 2000000) {
#if JP
		int nButton = MessageBox(0,
			_T("�ŐV�ł����J����Ă��܂��B\n�����T�C�g�ɃA�N�Z�X���܂����H"),
			_T("�m�F"), MB_YESNO | MB_ICONQUESTION);
		if(nButton == IDYES)
			ShellExecute(m_rMainWnd, _T("open"),
				_T("http://soft.edolfzoku.com/hayaemon2/"), NULL, NULL,
				SW_SHOWDEFAULT);
#else // JP
		int nButton = MessageBox(0,
			_T("The latest version has been released.\n")
			_T("Do you want to access the official site?"),
			_T("Question"), MB_YESNO | MB_ICONQUESTION);
		if(nButton == IDYES)
			ShellExecute(m_rMainWnd, _T("open"),
				_T("http://en.edolfzoku.com/hayaemon2/"), NULL, NULL,
				SW_SHOWDEFAULT);
#endif // JP
	}
	else {
#if JP
		MessageBox(0, _T("���g���̃o�[�W�����͍ŐV�ł��B"), _T("���"),
			MB_ICONINFORMATION);
#else // JP
		MessageBox(0, _T("Your version is latest."), _T("Information"),
			MB_ICONINFORMATION);
#endif // JP
	}
	CloseHandle(hInternet);
	CloseHandle(hFile);
}
//----------------------------------------------------------------------------
// �w���v �� �o�[�W������񃁃j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnVersionInfoMenuSelected()
{
	tstring str = m_rApp.GetName() + _T(" ");
	tstring strVersion = m_rApp.GetVersionInfo();
	int nPos = strVersion.find(_T("��"), 0);
	if(nPos > 0) {
		str += _T("Version ") + strVersion.substr(0, nPos);
#if JP
		str += _T(" �� ");
#else // JP
		str += _T(" beta ");
#endif // JP
		str += strVersion.substr(nPos + 1);
	}
	else {
		str += _T("Version ") + strVersion +
#if JP
			   _T(" �����");
#else // JP
			   _T(" stable");
#endif // JP
	}
	str += _T("\n\n�@") + m_rApp.GetAuthorName()
		+ _T(" <") + m_rApp.GetAuthorEMail() + _T(">\n�@")
		+ m_rApp.GetAuthorWebSiteName() + _T(" : ") + m_rApp.GetAuthorURL();
	MessageBox(m_rMainWnd, str.c_str(),
#if JP
			   _T("�o�[�W�������"),
#else // JP
			   _T("Version"),
#endif // JP
			   0);
}
//----------------------------------------------------------------------------
// ���̃T�C�Y�ɖ߂����j���[���I�����ꂽ
//----------------------------------------------------------------------------
void CMenu_MainWnd::OnRestoreMenuSelected()
{
	SendMessage(m_rMainWnd, WM_TRAY, 0L, WM_LBUTTONDOWN);
}
//----------------------------------------------------------------------------
