//----------------------------------------------------------------------------
// RMenu_Taskbar.cpp : �^�X�N�o�[�p�E�N���b�N���j���[�̊Ǘ����s��
//----------------------------------------------------------------------------
#include <windows.h>
#include "MainWnd.h"
#include "RMenu_Taskbar.h"
//----------------------------------------------------------------------------
// �쐬
//----------------------------------------------------------------------------
BOOL CRMenu_Taskbar::Create()
{
	CMenu::CreatePopup();
#if JP
	// �t�@�C�����j���[
	Append(GetItemFlags(ID_OPENFILE), ID_OPENFILE,
						_T("�t�@�C�����J��(&O)..."));
	Append(GetItemFlags(ID_ADDFILE), ID_ADDFILE, _T("�t�@�C����ǉ�(&P)..."));
	Append(GetItemFlags(ID_OPENFOLDER), ID_OPENFOLDER,
						_T("�t�H���_���J��(&F)..."));
	Append(GetItemFlags(ID_ADDFOLDER), ID_ADDFOLDER,
						_T("�t�H���_��ǉ�(&G)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_SAVEFILE), ID_SAVEFILE, _T("�ۑ�(&S)..."));
	Append(GetItemFlags(ID_SAVEALLFILE), ID_SAVEALLFILE,
						_T("�ꊇ�ϊ�(&A)..."));
	AppendSeparator();

	// �Đ����j���[
	Append(GetItemFlags(ID_PAUSE), ID_PAUSE, _T("�Đ�/�ꎞ��~(&P)"));
	Append(GetItemFlags(ID_STOP), ID_STOP, _T("��~(&S)"));
	Append(GetItemFlags(ID_HEAD), ID_HEAD, _T("���o��(&T)"));
	Append(GetItemFlags(ID_PREV), ID_PREV, _T("�O��(&V)"));
	Append(GetItemFlags(ID_NEXT), ID_NEXT, _T("����(&N)"));
	Append(GetItemFlags(ID_REWIND), ID_REWIND, _T("�����߂�(&R)"));
	Append(GetItemFlags(ID_FORWARD), ID_FORWARD, _T("������(&A)"));
	m_returnMenu.CreatePopup();
	m_returnMenu.Append(GetItemFlags(ID_RETURN1SEC), ID_RETURN1SEC,
						_T("1�b�߂�(&1)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN2SEC), ID_RETURN2SEC,
						_T("2�b�߂�(&2)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN3SEC), ID_RETURN3SEC,
						_T("3�b�߂�(&3)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN5SEC), ID_RETURN5SEC,
						_T("5�b�߂�(&5)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN10SEC), ID_RETURN10SEC,
						_T("10�b�߂�(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_returnMenu, _T("�߂�(&R)"));
	m_forwardMenu.CreatePopup();
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD1SEC), ID_FORWARD1SEC,
						 _T("1�b�i��(&1)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD2SEC), ID_FORWARD2SEC,
						 _T("2�b�i��(&2)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD3SEC), ID_FORWARD3SEC,
						 _T("3�b�i��(&3)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD5SEC), ID_FORWARD5SEC,
						 _T("5�b�i��(&5)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD10SEC), ID_FORWARD10SEC,
						 _T("10�b�i��(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_forwardMenu, _T("�i��(&F)"));
	AppendSeparator();
	Append(GetItemFlags(ID_SLOOP), ID_SLOOP, _T("�P�ȃ��[�v(&1)"));
	Append(GetItemFlags(ID_ALOOP), ID_ALOOP, _T("�S�ȃ��[�v(&T)"));
	Append(GetItemFlags(ID_RANDOM), ID_RANDOM, _T("�����_���Đ�(&H)"));
	Append(GetItemFlags(ID_CONTINUE), ID_CONTINUE, _T("�A���Đ�(&C)"));

	// �G�t�F�N�g���j���[
	m_effectMenu.CreatePopup();
	m_speedMenu.CreatePopup();
	m_speedMenu.Append(GetItemFlags(ID_RESETSPEED), ID_RESETSPEED,
					   _T("�f�t�H���g�ɖ߂�(&R)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_DOWN0_1SPEED), ID_DOWN0_1SPEED,
					   _T("0.1%������(&0)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN1SPEED), ID_DOWN1SPEED,
					   _T("1%������(&1)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN2SPEED), ID_DOWN2SPEED,
					   _T("2%������(&2)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN3SPEED), ID_DOWN3SPEED,
					   _T("3%������(&3)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN5SPEED), ID_DOWN5SPEED,
					   _T("5%������(&5)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN10SPEED), ID_DOWN10SPEED,
					   _T("10%������(&T)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_UP0_1SPEED), ID_UP0_1SPEED,
					   _T("0.1%�グ��(&Z)"));
	m_speedMenu.Append(GetItemFlags(ID_UP1SPEED), ID_UP1SPEED,
					   _T("1%�グ��(&A)"));
	m_speedMenu.Append(GetItemFlags(ID_UP2SPEED), ID_UP2SPEED,
					   _T("2%�グ��(&B)"));
	m_speedMenu.Append(GetItemFlags(ID_UP3SPEED), ID_UP3SPEED,
					   _T("3%�グ��(&C)"));
	m_speedMenu.Append(GetItemFlags(ID_UP5SPEED), ID_UP5SPEED,
					   _T("5%�グ��(&D)"));
	m_speedMenu.Append(GetItemFlags(ID_UP10SPEED), ID_UP10SPEED,
					   _T("10%�グ��(&E)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_DECSPEED), ID_DECSPEED,
					   _T("���񂾂�x������(&D)..."));
	m_speedMenu.Append(GetItemFlags(ID_INCSPEED), ID_INCSPEED,
					   _T("���񂾂񑬂�����(&D)..."));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedMenu,
						_T("�Đ����x(&S)"));
	m_freqMenu.CreatePopup();
	m_freqMenu.Append(GetItemFlags(ID_RESETFREQ), ID_RESETFREQ,
					  _T("�f�t�H���g�ɖ߂�(&R)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_DOWN0_1FREQ), ID_DOWN0_1FREQ,
					  _T("0.1%������(&0)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN1FREQ), ID_DOWN1FREQ,
					  _T("1%������(&1)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN2FREQ), ID_DOWN2FREQ,
					  _T("2%������(&2)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN3FREQ), ID_DOWN3FREQ,
					  _T("3%������(&3)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN5FREQ), ID_DOWN5FREQ,
					  _T("5%������(&5)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN10FREQ), ID_DOWN10FREQ,
					  _T("10%������(&T)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_UP0_1FREQ), ID_UP0_1FREQ,
					  _T("0.1%�グ��(&Z)"));
	m_freqMenu.Append(GetItemFlags(ID_UP1FREQ), ID_UP1FREQ,
					  _T("1%�グ��(&A)"));
	m_freqMenu.Append(GetItemFlags(ID_UP2FREQ), ID_UP2FREQ,
					  _T("2%�グ��(&B)"));
	m_freqMenu.Append(GetItemFlags(ID_UP3FREQ), ID_UP3FREQ,
					  _T("3%�グ��(&C)"));
	m_freqMenu.Append(GetItemFlags(ID_UP5FREQ), ID_UP5FREQ,
					  _T("5%�グ��(&D)"));
	m_freqMenu.Append(GetItemFlags(ID_UP10FREQ), ID_UP10FREQ,
					  _T("10%�グ��(&E)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_DECFREQ), ID_DECFREQ,
					  _T("���񂾂�x������(&F)..."));
	m_freqMenu.Append(GetItemFlags(ID_INCFREQ), ID_INCFREQ,
					  _T("���񂾂񑬂�����(&F)..."));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqMenu,
						_T("�Đ����g��(&F)"));
	m_pitchMenu.CreatePopup();
	m_pitchMenu.Append(GetItemFlags(ID_RESETPITCH), ID_RESETPITCH,
					   _T("�f�t�H���g�ɖ߂�(&R)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(GetItemFlags(ID_DOWN1PITCH), ID_DOWN1PITCH,
					   _T("����������(&1)"));
	m_pitchMenu.Append(GetItemFlags(ID_DOWN2PITCH), ID_DOWN2PITCH,
					   _T("�S��������(&2)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(GetItemFlags(ID_UP1PITCH), ID_UP1PITCH,
					   _T("�����グ��(&A)"));
	m_pitchMenu.Append(GetItemFlags(ID_UP2PITCH), ID_UP2PITCH,
					   _T("�S���グ��(&B)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchMenu,
						_T("����(&P)"));
	m_eqPresetMenu.CreatePopup();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQFLAT), ID_EQFLAT, _T("FLAT(&F)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWHIGHEST), ID_EQLOWHIGHEST,
						  _T("�ቹ�����i�ŋ��j(&A)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWHIGH), ID_EQLOWHIGH,
						  _T("�ቹ�����i���j(&B)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWMIDDLE), ID_EQLOWMIDDLE,
						  _T("�ቹ�����i���j(&C)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWLOW), ID_EQLOWLOW,
						  _T("�ቹ�����i��j(&D)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWLOWEST), ID_EQLOWLOWEST,
						  _T("�ቹ�����i�Ŏ�j(&E)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEHIGHEST), ID_EQMIDDLEHIGHEST,
						  _T("���������i�ŋ��j(&G)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEHIGH), ID_EQMIDDLEHIGH,
						  _T("���������i���j(&H)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEMIDDLE), ID_EQMIDDLEMIDDLE,
						  _T("���������i���j(&I)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLELOW), ID_EQMIDDLELOW,
						  _T("���������i��j(&J)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLELOWEST), ID_EQMIDDLELOWEST,
						  _T("���������i�Ŏ�j(&K)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHHIGHEST), ID_EQHIGHHIGHEST,
						  _T("���������i�ŋ��j(&L)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHHIGH), ID_EQHIGHHIGH,
						  _T("���������i���j(&M)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHMIDDLE), ID_EQHIGHMIDDLE,
						  _T("���������i���j(&N)"));

	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHLOW), ID_EQHIGHLOW,
						  _T("���������i��j(&O)"));

	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHLOWEST), ID_EQHIGHLOWEST,
						  _T("���������i�Ŏ�j(&P)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqPresetMenu,
						_T("EQ�v���Z�b�g(&E)"));
	m_effectMenu.AppendSeparator();
	m_reverbMenu.CreatePopup();
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_DEFAULT), ID_3DREVERB_DEFAULT,
						_T("�f�t�H���g(&D)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PADDEDCELL),
						ID_3DREVERB_PADDEDCELL,
						_T("�N�b�V��������̈��S��(&P)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ROOM), ID_3DREVERB_ROOM,
						_T("����(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_BATHROOM), ID_3DREVERB_BATHROOM,
						_T("����(&B)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LIVINGROOM),
						ID_3DREVERB_LIVINGROOM, _T("���r���O(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_STONEROOM), ID_3DREVERB_STONEROOM,
						_T("�Ύ�(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_AUDITORIUM),
						ID_3DREVERB_AUDITORIUM, _T("�u��(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CONCERTHALL),
						ID_3DREVERB_CONCERTHALL, _T("�R���T�[�g�z�[��(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CAVE), ID_3DREVERB_CAVE,
						_T("���A(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ARENA), ID_3DREVERB_ARENA,
						_T("�A���[�i(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_HANGAR), ID_3DREVERB_HANGAR,
						_T("�[��(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CARPETEDHALLWAY),
						ID_3DREVERB_CARPETEDHALLWAY,
						_T("�J�[�y�b�g��~�����L��(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_HALLWAY), ID_3DREVERB_HALLWAY,
						_T("�L��(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_STONECORRIDOR),
						ID_3DREVERB_STONECORRIDOR, _T("�΂̘L��(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ALLEY), ID_3DREVERB_ALLEY,
						_T("���ʂ�(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_FOREST), ID_3DREVERB_FOREST,
						_T("�X��(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CITY), ID_3DREVERB_CITY,
						_T("�s�s(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MOUNTAINS), ID_3DREVERB_MOUNTAINS,
						_T("�R(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_QUARRY), ID_3DREVERB_QUARRY,
						_T("�̐Ώ�(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PLAIN), ID_3DREVERB_PLAIN,
						_T("����(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PARKINGLOT),
						ID_3DREVERB_PARKINGLOT, _T("���ԏ�(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_SEWERPIPE), ID_3DREVERB_SEWERPIPE,
						_T("������(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_UNDERWATER),
						ID_3DREVERB_UNDERWATER, _T("����(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_SMALLROOM), ID_3DREVERB_SMALLROOM,
						_T("������(&S)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MEDIUMROOM),
						ID_3DREVERB_MEDIUMROOM, _T("������(&M)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LARGEROOM), ID_3DREVERB_LARGEROOM,
						_T("�啔��(&L)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MEDIUMHALL),
						ID_3DREVERB_MEDIUMHALL, _T("���z�[��(&M)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LARGEHALL), ID_3DREVERB_LARGEHALL,
						_T("��z�[��(&L)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PLATE), ID_3DREVERB_PLATE,
						_T("�v���[�g(&P)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_reverbMenu,
						_T("�R�c���o�[�u(&R)"));
	m_delayMenu.CreatePopup();
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DEFAULT), ID_DELAY_DEFAULT,
					   _T("�f�t�H���g(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_SHORT), ID_DELAY_SHORT,
					   _T("�Z���G�R�[(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_MEDIUM), ID_DELAY_MEDIUM,
					   _T("�����炢�̃G�R�[(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_LONG), ID_DELAY_LONG,
					   _T("�����G�R�[(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOSHORT),
					   ID_DELAY_STEREOSHORT, _T("�X�e���I�̒Z���G�R�[(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOMEDIUM),
					   ID_DELAY_STEREOMEDIUM,
					   _T("�X�e���I�̒����炢�̃G�R�[(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOLONG), ID_DELAY_STEREOLONG,
					   _T("�X�e���I�̒����G�R�[(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_MOUNTAIN), ID_DELAY_MOUNTAIN,
					   _T("�R�т�(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_BIG), ID_DELAY_BIG,
					   _T("�傫���G�R�[(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOBIG), ID_DELAY_STEREOBIG,
					   _T("�X�e���I�̑傫���G�R�[(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DOUBLING), ID_DELAY_DOUBLING,
					   _T("�_�u�����O(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DOUBLEKICK), ID_DELAY_DOUBLEKICK,
					   _T("�_�u���L�b�N(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_delayMenu,
						_T("�f�B���C(&D)"));
	m_chorusMenu.CreatePopup();
	m_chorusMenu.Append(GetItemFlags(ID_CHORUS_DEFAULT), ID_CHORUS_DEFAULT,
						_T("�f�t�H���g(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_chorusMenu,
						_T("�R�[���X(&C)"));
	m_compressorMenu.CreatePopup();
	m_compressorMenu.Append(GetItemFlags(ID_COMPRESSOR_DEFAULT),
							ID_COMPRESSOR_DEFAULT, _T("�f�t�H���g(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_compressorMenu,
						_T("�R���v���b�T�[(&C)"));
	m_flangerMenu.CreatePopup();
	m_flangerMenu.Append(GetItemFlags(ID_FLANGER_DEFAULT), ID_FLANGER_DEFAULT,
						 _T("�f�t�H���g(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_flangerMenu,
						_T("�t�����W���[(&F)"));
	m_gargleMenu.CreatePopup();
	m_gargleMenu.Append(GetItemFlags(ID_GARGLE_DEFAULT), ID_GARGLE_DEFAULT,
						_T("�f�t�H���g(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_gargleMenu,
						_T("�K�[�O��(&G)"));
	m_distortionMenu.CreatePopup();
	m_distortionMenu.Append(GetItemFlags(ID_DISTORTION_DEFAULT),
							ID_DISTORTION_DEFAULT, _T("�f�t�H���g(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_distortionMenu,
						_T("�f�B�X�g�[�V����(&D)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(GetItemFlags(ID_NORMALIZE), ID_NORMALIZE,
						_T("�m�[�}���C�Y(&N)"));
	m_effectMenu.Append(GetItemFlags(ID_VOCALCANCEL), ID_VOCALCANCEL,
						_T("�{�[�J���L�����Z��(&V)"));
	m_effectMenu.Append(GetItemFlags(ID_REVERSE), ID_REVERSE,
						_T("�t��]�Đ�(&R)"));
	m_effectMenu.Append(GetItemFlags(ID_RECORD), ID_RECORD,
						_T("�Âт����R�[�h�Đ�(&F)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(GetItemFlags(ID_MONORAL), ID_MONORAL,
						_T("���m����(&M)"));
	m_effectMenu.Append(GetItemFlags(ID_ONLYLEFT), ID_ONLYLEFT,
						_T("���̂ݍĐ�(&L)"));
	m_effectMenu.Append(GetItemFlags(ID_ONLYRIGHT), ID_ONLYRIGHT,
						_T("�E�̂ݍĐ�(&R)"));
	m_effectMenu.Append(GetItemFlags(ID_CHANGELR), ID_CHANGELR,
						_T("���E����ւ�(&C)"));
	Append(MF_POPUP | MF_MENUBARBREAK, (UINT_PTR)(HMENU)m_effectMenu,
		   _T("�G�t�F�N�g(&E)"));
	AppendSeparator();

	// �V�X�e�����j���[
	m_recoveryMenu.CreatePopup();
	m_recoverVisibleMenu.CreatePopup();
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERVIDEOSCREENVISIBLE),
								ID_RECOVERVIDEOSCREENVISIBLE,
								_T("�r�f�I���(&V)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERTIMESLIDERVISIBLE),
								ID_RECOVERTIMESLIDERVISIBLE,
								_T("�Đ��ʒu�X���C�_(&T)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERSPEEDVISIBLE),
								ID_RECOVERSPEEDVISIBLE,
								_T("�Đ����x(&S)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERFREQVISIBLE),
								ID_RECOVERFREQVISIBLE,
								_T("�Đ����g��(&F)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERPITCHVISIBLE),
								ID_RECOVERPITCHVISIBLE,
								_T("����(&P)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERVOLUMEVISIBLE),
								ID_RECOVERVOLUMEVISIBLE,
								_T("����(&V)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERPANVISIBLE),
								ID_RECOVERPANVISIBLE,
								_T("�p��(&P)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVEREQVISIBLE),
								ID_RECOVEREQVISIBLE,
								_T("�O���t�B�b�N�C�R���C�U(&G)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERLISTVISIBLE),
								ID_RECOVERLISTVISIBLE, _T("�Đ����X�g(&P)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverVisibleMenu,
						  _T("�\�����(&V)"));
	m_recoverPlayModeMenu.CreatePopup();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERSLOOP),
								 ID_RECOVERSLOOP, _T("�P�ȃ��[�v(&1)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERALOOP),
								 ID_RECOVERALOOP, _T("�S�ȃ��[�v(&T)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERRANDOM),
								 ID_RECOVERRANDOM, _T("�����_���Đ�(&H)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERCONTINUE),
								 ID_RECOVERCONTINUE, _T("�A���Đ�(&C)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERINSTANTLOOP),
								 ID_RECOVERINSTANTLOOP,
								 _T("�}�[�J�[�ǉ����Ƀ��[�v(&I)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERSETPOSITIONAUTO),
								 ID_RECOVERSETPOSITIONAUTO,
								 _T("�}�[�J�[�ʒu�ύX���ɍĐ��ʒu�ύX(&S)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERREVERSE),
								 ID_RECOVERREVERSE, _T("�t��]�Đ�(&R)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERRECORD),
								 ID_RECOVERRECORD,
								 _T("�Âт����R�[�h�Đ�(&F)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverPlayModeMenu,
						  _T("�Đ����[�h(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERWPOS), ID_RECOVERWPOS,
						  _T("�E�B���h�E�ʒu(&P)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERWSIZE), ID_RECOVERWSIZE,
						  _T("�E�B���h�E�T�C�Y(&S)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERSPEED), ID_RECOVERSPEED,
						  _T("�Đ����x(&S)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERFREQ),
						  ID_RECOVERFREQ, _T("�Đ����g��(&F)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERPITCH), ID_RECOVERPITCH,
						  _T("����(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERVOLUME), ID_RECOVERVOLUME,
						  _T("����(&V)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERPAN), ID_RECOVERPAN,
						  _T("�p��(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVEREQ), ID_RECOVEREQ,
						  _T("�O���t�B�b�N�C�R���C�U(&G)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERLIST), ID_RECOVERLIST,
						  _T("�Đ����X�g(&P)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoveryMenu, _T("����(&R)"));
	AppendSeparator();
	Append(GetItemFlags(ID_KEYSETTING), ID_KEYSETTING,
		   _T("�V���[�g�J�b�g�L�[�ݒ�(&K)..."));
	Append(GetItemFlags(ID_OUTKEYSETTING), ID_OUTKEYSETTING,
		   _T("�O���[�o���z�b�g�L�[�ݒ�(&G)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_TIMERPLAY), ID_TIMERPLAY,
		   _T("�^�C�}�[�ݒ�(&T)..."));
	Append(GetItemFlags(ID_PLAYPOSITION), ID_PLAYPOSITION,
		   _T("�Đ��ʒu(&P)..."));
	Append(GetItemFlags(ID_FADEOUTSTOP), ID_FADEOUTSTOP,
		   _T("�Đ���~���Ƀt�F�[�h�A�E�g(&F)"));
	Append(GetItemFlags(ID_FADEOUTNEXT), ID_FADEOUTNEXT,
		   _T("�Ȃ̐ؑ֎��Ƀt�F�[�h�A�E�g(&F)"));
	AppendSeparator();
	Append(GetItemFlags(ID_METRONOME), ID_METRONOME,
		   _T("���g���m�[���@�\(&M)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_DOUBLERUN), ID_DOUBLERUN, _T("���d�N��(&D)"));
	Append(GetItemFlags(ID_TOPMOST), ID_TOPMOST, _T("�őO�ʕ\��(&S)"));
	Append(GetItemFlags(ID_COPYTIME), ID_COPYTIME,
		   _T("���݂̍Đ��ʒu���R�s�[(&C)"));
	AppendSeparator();

	// �w���v���j���[
	Append(GetItemFlags(ID_MANUAL), ID_MANUAL, _T("�}�j���A��(&M)..."));
	Append(GetItemFlags(ID_VERSIONINFO), ID_VERSIONINFO,
		   _T("�o�[�W�������(&A)..."));

	AppendSeparator();
	Append(MFS_ENABLED, ID_RESTORE, _T("���̃T�C�Y�ɖ߂�(&R)"));
	AppendSeparator();
	Append(GetItemFlags(ID_EXIT), ID_EXIT, _T("�I��(&X)"));
#else // JP
	// �t�@�C�����j���[
	Append(GetItemFlags(ID_OPENFILE), ID_OPENFILE, _T("Open files(&O)..."));
	Append(GetItemFlags(ID_ADDFILE), ID_ADDFILE, _T("Add files(&P)..."));
	Append(GetItemFlags(ID_OPENFOLDER), ID_OPENFOLDER,
		   _T("Open directory(&F)..."));
	Append(GetItemFlags(ID_ADDFOLDER), ID_ADDFOLDER,
		   _T("Add directory(&G)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_SAVEFILE), ID_SAVEFILE, _T("Save(&S)..."));
	Append(GetItemFlags(ID_SAVEALLFILE), ID_SAVEALLFILE,
		   _T("Save all(&A)..."));
	AppendSeparator();

	// �Đ����j���[
	Append(GetItemFlags(ID_PAUSE), ID_PAUSE, _T("Play/Pause(&P)"));
	Append(GetItemFlags(ID_STOP), ID_STOP, _T("Stop(&S)"));
	Append(GetItemFlags(ID_HEAD), ID_HEAD, _T("Head(&T)"));
	Append(GetItemFlags(ID_PREV), ID_PREV, _T("Previous(&V)"));
	Append(GetItemFlags(ID_NEXT), ID_NEXT, _T("Next(&N)"));
	Append(GetItemFlags(ID_REWIND), ID_REWIND, _T("Rewind(&R)"));
	Append(GetItemFlags(ID_FORWARD), ID_FORWARD, _T("Forward(&A)"));
	m_returnMenu.CreatePopup();
	m_returnMenu.Append(GetItemFlags(ID_RETURN1SEC), ID_RETURN1SEC,
						_T("Rewind 1 sec.(&1)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN2SEC), ID_RETURN2SEC,
						_T("Rewind 2 sec.(&2)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN3SEC), ID_RETURN3SEC,
						_T("Rewind 3 sec.(&3)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN5SEC), ID_RETURN5SEC,
						_T("Rewind 5 sec.(&5)"));
	m_returnMenu.Append(GetItemFlags(ID_RETURN10SEC), ID_RETURN10SEC,
						_T("Rewind 10 sec.(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_returnMenu, _T("Rewind(&R)"));
	m_forwardMenu.CreatePopup();
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD1SEC), ID_FORWARD1SEC,
						 _T("Forward 1 sec.(&1)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD2SEC), ID_FORWARD2SEC,
						 _T("Forward 2 sec.(&2)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD3SEC), ID_FORWARD3SEC,
						 _T("Forward 3 sec.(&3)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD5SEC), ID_FORWARD5SEC,
						 _T("Forward 5 sec.(&5)"));
	m_forwardMenu.Append(GetItemFlags(ID_FORWARD10SEC), ID_FORWARD10SEC,
						 _T("Forward 10 sec.(&T)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_forwardMenu, _T("Forward(&F)"));
	AppendSeparator();
	Append(GetItemFlags(ID_SLOOP), ID_SLOOP, _T("Single loop(&1)"));
	Append(GetItemFlags(ID_ALOOP), ID_ALOOP, _T("All loop(&T)"));
	Append(GetItemFlags(ID_RANDOM), ID_RANDOM, _T("Random play(&H)"));
	Append(GetItemFlags(ID_CONTINUE), ID_CONTINUE, _T("Continuous play(&C)"));

	// �G�t�F�N�g���j���[
	m_effectMenu.CreatePopup();
	m_speedMenu.CreatePopup();
	m_speedMenu.Append(GetItemFlags(ID_RESETSPEED), ID_RESETSPEED,
					   _T("Reset Speed(&R)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_DOWN0_1SPEED), ID_DOWN0_1SPEED,
					   _T("Turn down 0.1%(&0)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN1SPEED), ID_DOWN1SPEED,
					   _T("Turn down 1%(&1)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN2SPEED), ID_DOWN2SPEED,
					   _T("Turn down 2%(&2)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN3SPEED), ID_DOWN3SPEED,
					   _T("Turn down 3%(&3)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN5SPEED), ID_DOWN5SPEED,
					   _T("Turn down 5%(&5)"));
	m_speedMenu.Append(GetItemFlags(ID_DOWN10SPEED), ID_DOWN10SPEED,
					   _T("Turn down 10%(&T)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_UP0_1SPEED), ID_UP0_1SPEED,
					   _T("Turn up 0.1%(&Z)"));
	m_speedMenu.Append(GetItemFlags(ID_UP1SPEED), ID_UP1SPEED,
					   _T("Turn up 1%(&A)"));
	m_speedMenu.Append(GetItemFlags(ID_UP2SPEED), ID_UP2SPEED,
					   _T("Turn up 2%(&B)"));
	m_speedMenu.Append(GetItemFlags(ID_UP3SPEED), ID_UP3SPEED,
					   _T("Turn up 3%(&C)"));
	m_speedMenu.Append(GetItemFlags(ID_UP5SPEED), ID_UP5SPEED,
					   _T("Turn up 5%(&D)"));
	m_speedMenu.Append(GetItemFlags(ID_UP10SPEED), ID_UP10SPEED,
					   _T("Turn up 10%(&E)"));
	m_speedMenu.AppendSeparator();
	m_speedMenu.Append(GetItemFlags(ID_DECSPEED), ID_DECSPEED,
					   _T("Decrease(&D)..."));
	m_speedMenu.Append(GetItemFlags(ID_INCSPEED), ID_INCSPEED,
					   _T("Increase(&D)..."));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_speedMenu,
					   _T("Speed(&S)"));
	m_freqMenu.CreatePopup();
	m_freqMenu.Append(GetItemFlags(ID_RESETFREQ), ID_RESETFREQ,
					  _T("Reset Frequency(&R)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_DOWN0_1FREQ), ID_DOWN0_1FREQ,
					  _T("Turn down 0.1%(&0)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN1FREQ), ID_DOWN1FREQ,
					  _T("Turn down 1%(&1)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN2FREQ), ID_DOWN2FREQ,
					  _T("Turn down 2%(&2)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN3FREQ), ID_DOWN3FREQ,
					  _T("Turn down 3%(&3)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN5FREQ), ID_DOWN5FREQ,
					  _T("Turn down 5%(&5)"));
	m_freqMenu.Append(GetItemFlags(ID_DOWN10FREQ), ID_DOWN10FREQ,
					  _T("Turn down 10%(&T)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_UP0_1FREQ), ID_UP0_1FREQ,
					  _T("Turn up 0.1%(&Z)"));
	m_freqMenu.Append(GetItemFlags(ID_UP1FREQ), ID_UP1FREQ,
					  _T("Turn up 1%(&A)"));
	m_freqMenu.Append(GetItemFlags(ID_UP2FREQ), ID_UP2FREQ,
					  _T("Turn up 2%(&B)"));
	m_freqMenu.Append(GetItemFlags(ID_UP3FREQ), ID_UP3FREQ,
					  _T("Turn up 3%(&C)"));
	m_freqMenu.Append(GetItemFlags(ID_UP5FREQ), ID_UP5FREQ,
					  _T("Turn up 5%(&D)"));
	m_freqMenu.Append(GetItemFlags(ID_UP10FREQ), ID_UP10FREQ,
					  _T("Turn up 10%(&E)"));
	m_freqMenu.AppendSeparator();
	m_freqMenu.Append(GetItemFlags(ID_DECFREQ), ID_DECFREQ,
					  _T("Decrease(&F)..."));
	m_freqMenu.Append(GetItemFlags(ID_INCFREQ), ID_INCFREQ,
					  _T("Increase(&F)..."));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_freqMenu,
						_T("Frequency(&F)"));
	m_pitchMenu.CreatePopup();
	m_pitchMenu.Append(GetItemFlags(ID_RESETPITCH), ID_RESETPITCH,
					   _T("Reset pitch(&R)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(GetItemFlags(ID_DOWN1PITCH), ID_DOWN1PITCH,
					   _T("Flat(&1)"));
	m_pitchMenu.Append(GetItemFlags(ID_DOWN2PITCH), ID_DOWN2PITCH,
					   _T("Double flat(&2)"));
	m_pitchMenu.AppendSeparator();
	m_pitchMenu.Append(GetItemFlags(ID_UP1PITCH), ID_UP1PITCH,
					   _T("Sharp(&A)"));
	m_pitchMenu.Append(GetItemFlags(ID_UP2PITCH), ID_UP2PITCH,
					   _T("Double sharp(&B)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_pitchMenu,
						_T("Pitch(&P)"));
	m_eqPresetMenu.CreatePopup();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQFLAT), ID_EQFLAT, _T("FLAT(&F)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWHIGHEST), ID_EQLOWHIGHEST,
						  _T("Boost low(strongest)(&A)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWHIGH), ID_EQLOWHIGH,
						  _T("Boost low(strong)(&B)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWMIDDLE), ID_EQLOWMIDDLE,
						  _T("Boost low(middle)(&C)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWLOW), ID_EQLOWLOW,
						  _T("Boost low(weak)(&D)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQLOWLOWEST), ID_EQLOWLOWEST,
						  _T("Boost low(weakest)(&E)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEHIGHEST), ID_EQMIDDLEHIGHEST,
						  _T("Boost middle(strongest)(&G)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEHIGH), ID_EQMIDDLEHIGH,
						  _T("Boost middle(strong)(&H)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLEMIDDLE), ID_EQMIDDLEMIDDLE,
						  _T("Boost middle(middle)(&I)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLELOW), ID_EQMIDDLELOW,
						  _T("Boost middle(weak)(&J)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQMIDDLELOWEST), ID_EQMIDDLELOWEST,
						  _T("Boost middle(weakest)(&K)"));
	m_eqPresetMenu.AppendSeparator();
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHHIGHEST), ID_EQHIGHHIGHEST,
						  _T("Boost high(strongest)(&L)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHHIGH), ID_EQHIGHHIGH,
						  _T("Boost high(strong)(&M)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHMIDDLE), ID_EQHIGHMIDDLE,
						  _T("Boost high(middle)(&N)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHLOW), ID_EQHIGHLOW,
						  _T("Boost high(weak)(&O)"));
	m_eqPresetMenu.Append(GetItemFlags(ID_EQHIGHLOWEST), ID_EQHIGHLOWEST,
						  _T("Boost high(weakest)(&P)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_eqPresetMenu,
						_T("EQ preset(&E)"));
	m_effectMenu.AppendSeparator();
	m_reverbMenu.CreatePopup();
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_DEFAULT), ID_3DREVERB_DEFAULT,
						_T("Default(&D)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PADDEDCELL),
						ID_3DREVERB_PADDEDCELL, _T("Padded Cell(&P)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ROOM), ID_3DREVERB_ROOM,
						_T("Room(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_BATHROOM), ID_3DREVERB_BATHROOM,
						_T("Bathroom(&B)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LIVINGROOM),
						ID_3DREVERB_LIVINGROOM, _T("Living Room(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_STONEROOM), ID_3DREVERB_STONEROOM,
						_T("Stone Room(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_AUDITORIUM),
						ID_3DREVERB_AUDITORIUM, _T("Auditorium(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CONCERTHALL),
						ID_3DREVERB_CONCERTHALL, _T("Concert Hall(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CAVE), ID_3DREVERB_CAVE,
						_T("Cave(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ARENA), ID_3DREVERB_ARENA,
						_T("Arena(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_HANGAR), ID_3DREVERB_HANGAR,
						_T("Hangar(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CARPETEDHALLWAY),
						ID_3DREVERB_CARPETEDHALLWAY, _T("Carpeted Hallway(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_HALLWAY), ID_3DREVERB_HALLWAY,
						_T("Hallway(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_STONECORRIDOR),
						ID_3DREVERB_STONECORRIDOR, _T("Stone Corridor(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_ALLEY), ID_3DREVERB_ALLEY,
						_T("Alley(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_FOREST), ID_3DREVERB_FOREST,
						_T("Forest(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_CITY), ID_3DREVERB_CITY,
						_T("City(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MOUNTAINS), ID_3DREVERB_MOUNTAINS,
						_T("Mountains(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_QUARRY), ID_3DREVERB_QUARRY,
						_T("Quarry(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PLAIN), ID_3DREVERB_PLAIN,
						_T("Plain(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PARKINGLOT),
						ID_3DREVERB_PARKINGLOT, _T("Parking Lot(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_SEWERPIPE), ID_3DREVERB_SEWERPIPE,
						_T("Sewer Pipe(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_UNDERWATER),
						ID_3DREVERB_UNDERWATER, _T("Underwater(&R)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_SMALLROOM), ID_3DREVERB_SMALLROOM,
						_T("Small Room(&S)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MEDIUMROOM),
						ID_3DREVERB_MEDIUMROOM, _T("Medium Room(&M)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LARGEROOM), ID_3DREVERB_LARGEROOM,
						_T("Large Room(&L)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_MEDIUMHALL),
						ID_3DREVERB_MEDIUMHALL, _T("Medium Hall(&M)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_LARGEHALL), ID_3DREVERB_LARGEHALL,
						_T("Large Hall(&L)"));
	m_reverbMenu.Append(GetItemFlags(ID_3DREVERB_PLATE), ID_3DREVERB_PLATE,
						_T("Plate(&P)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_reverbMenu,
						_T("Reverb(&R)"));
	m_delayMenu.CreatePopup();
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DEFAULT), ID_DELAY_DEFAULT,
					   _T("Default(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_SHORT), ID_DELAY_SHORT,
					   _T("Short Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_MEDIUM), ID_DELAY_MEDIUM,
					   _T("Medium Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_LONG), ID_DELAY_LONG,
					   _T("Long Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOSHORT),
					   ID_DELAY_STEREOSHORT, _T("Stereo Short Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOMEDIUM),
					   ID_DELAY_STEREOMEDIUM, _T("Stereo Medium Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOLONG), ID_DELAY_STEREOLONG,
					   _T("Stereo Long Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_MOUNTAIN), ID_DELAY_MOUNTAIN,
					   _T("Mountain Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_BIG), ID_DELAY_BIG,
					   _T("Big Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_STEREOBIG), ID_DELAY_STEREOBIG,
					   _T("Stereo Big Echo(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DOUBLING), ID_DELAY_DOUBLING,
					   _T("Doubling(&D)"));
	m_delayMenu.Append(GetItemFlags(ID_DELAY_DOUBLEKICK), ID_DELAY_DOUBLEKICK,
					   _T("Double Kick(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_delayMenu,
						_T("Delay(&D)"));
	m_chorusMenu.CreatePopup();
	m_chorusMenu.Append(GetItemFlags(ID_CHORUS_DEFAULT), ID_CHORUS_DEFAULT,
						_T("Default(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_chorusMenu,
						_T("Chorus(&C)"));
	m_compressorMenu.CreatePopup();
	m_compressorMenu.Append(GetItemFlags(ID_COMPRESSOR_DEFAULT),
							ID_COMPRESSOR_DEFAULT, _T("Default(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_compressorMenu,
						_T("Compressor(&C)"));
	m_flangerMenu.CreatePopup();
	m_flangerMenu.Append(GetItemFlags(ID_FLANGER_DEFAULT), ID_FLANGER_DEFAULT,
							_T("Default(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_flangerMenu,
						_T("Flanger(&F)"));
	m_gargleMenu.CreatePopup();
	m_gargleMenu.Append(GetItemFlags(ID_GARGLE_DEFAULT), ID_GARGLE_DEFAULT,
							_T("Default(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_gargleMenu,
						_T("Gargle(&F)"));
	m_distortionMenu.CreatePopup();
	m_distortionMenu.Append(GetItemFlags(ID_DISTORTION_DEFAULT), ID_DISTORTION_DEFAULT, _T("Default(&D)"));
	m_effectMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_distortionMenu,
						_T("Distortion(&D)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(GetItemFlags(ID_NORMALIZE), ID_NORMALIZE,
						_T("Normalize(&N)"));
	m_effectMenu.Append(GetItemFlags(ID_VOCALCANCEL), ID_VOCALCANCEL,
						_T("Vocal cancel(&V)"));
	m_effectMenu.Append(GetItemFlags(ID_REVERSE), ID_REVERSE,
						_T("Reverse play(&R)"));
	m_effectMenu.Append(GetItemFlags(ID_RECORD), ID_RECORD,
						_T("Old record play(&F)"));
	m_effectMenu.AppendSeparator();
	m_effectMenu.Append(GetItemFlags(ID_MONORAL), ID_MONORAL,
						_T("Monoral(&M)"));
	m_effectMenu.Append(GetItemFlags(ID_ONLYLEFT), ID_ONLYLEFT,
						_T("Only left(&L)"));
	m_effectMenu.Append(GetItemFlags(ID_ONLYRIGHT), ID_ONLYRIGHT,
						_T("Only right(&R)"));
	m_effectMenu.Append(GetItemFlags(ID_CHANGELR), ID_CHANGELR,
						_T("Change LR(&C)"));
	Append(MF_POPUP | MF_MENUBARBREAK, (UINT_PTR)(HMENU)m_effectMenu,
		   _T("Effect(&E)"));
	AppendSeparator();

	// �V�X�e�����j���[
	m_recoveryMenu.CreatePopup();
	m_recoverVisibleMenu.CreatePopup();
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERVIDEOSCREENVISIBLE),
								ID_RECOVERVIDEOSCREENVISIBLE,
								_T("Video screen(&V)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERTIMESLIDERVISIBLE),
								ID_RECOVERTIMESLIDERVISIBLE,
								_T("Position slider(&T)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERSPEEDVISIBLE),
								ID_RECOVERSPEEDVISIBLE, _T("Speed(&S)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERFREQVISIBLE),
								ID_RECOVERFREQVISIBLE, _T("Frequency(&F)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERPITCHVISIBLE),
								ID_RECOVERPITCHVISIBLE, _T("Pitch(&P)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERVOLUMEVISIBLE),
								ID_RECOVERVOLUMEVISIBLE,
								_T("Volume(&V)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERPANVISIBLE),
								ID_RECOVERPANVISIBLE,
								_T("Pan(&P)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVEREQVISIBLE),
								ID_RECOVEREQVISIBLE,
								_T("Graphic Equalizer(&G)"));
	m_recoverVisibleMenu.Append(GetItemFlags(ID_RECOVERLISTVISIBLE),
								ID_RECOVERLISTVISIBLE, _T("Playlist(&P)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverVisibleMenu,
						  _T("Visible(&V)"));
	m_recoverPlayModeMenu.CreatePopup();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERSLOOP),
								 ID_RECOVERSLOOP, _T("Single loop(&1)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERALOOP),
								 ID_RECOVERALOOP, _T("All loop(&T)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERRANDOM),
								 ID_RECOVERRANDOM, _T("Random(&H)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERCONTINUE),
								 ID_RECOVERCONTINUE, _T("Continue(&C)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERINSTANTLOOP),
								 ID_RECOVERINSTANTLOOP,
								_T("Loop when adding a marker(&I)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERSETPOSITIONAUTO),
								 ID_RECOVERSETPOSITIONAUTO,
								 _T("Set position automatic when ")
								 _T("adjusting marker position(&S)"));
	m_recoverPlayModeMenu.AppendSeparator();
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERREVERSE),
								 ID_RECOVERREVERSE, _T("Reverse(&R)"));
	m_recoverPlayModeMenu.Append(GetItemFlags(ID_RECOVERRECORD),
								 ID_RECOVERRECORD, _T("Record(&F)"));
	m_recoveryMenu.Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoverPlayModeMenu,
						  _T("Play mode(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERWPOS), ID_RECOVERWPOS,
						  _T("Window position(&P)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERWSIZE), ID_RECOVERWSIZE,
						  _T("Window size(&S)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERSPEED), ID_RECOVERSPEED,
						  _T("Speed(&S)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERFREQ),
						  ID_RECOVERFREQ, _T("Frequency(&F)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERPITCH), ID_RECOVERPITCH,
						  _T("Pitch(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERVOLUME), ID_RECOVERVOLUME,
						  _T("Volume(&V)"));
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERPAN), ID_RECOVERPAN,
						  _T("Pan(&P)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVEREQ), ID_RECOVEREQ,
						  _T("Graphic Equalizer(&G)"));
	m_recoveryMenu.AppendSeparator();
	m_recoveryMenu.Append(GetItemFlags(ID_RECOVERLIST), ID_RECOVERLIST,
						  _T("Playlist(&P)"));
	Append(MF_POPUP, (UINT_PTR)(HMENU)m_recoveryMenu, _T("Recover(&R)"));
	AppendSeparator();
	Append(GetItemFlags(ID_KEYSETTING), ID_KEYSETTING,
		   _T("Shortcut key setting(&K)..."));
	Append(GetItemFlags(ID_OUTKEYSETTING), ID_OUTKEYSETTING,
		   _T("Global hot key setting(&G)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_TIMERPLAY), ID_TIMERPLAY,
		   _T("Timer setting(&T)..."));
	Append(GetItemFlags(ID_PLAYPOSITION), ID_PLAYPOSITION,
		   _T("Play position(&P)..."));
	Append(GetItemFlags(ID_FADEOUTSTOP), ID_FADEOUTSTOP,
		   _T("Fade out stop(&F)"));
	Append(GetItemFlags(ID_FADEOUTNEXT), ID_FADEOUTNEXT,
		   _T("Fade out next(&F)"));
	AppendSeparator();
	Append(GetItemFlags(ID_METRONOME), ID_METRONOME, _T("Metronome(&M)..."));
	AppendSeparator();
	Append(GetItemFlags(ID_DOUBLERUN), ID_DOUBLERUN,
		   _T("Double runnable(&D)"));
	Append(GetItemFlags(ID_TOPMOST), ID_TOPMOST, _T("Bring window top(&S)"));
	Append(GetItemFlags(ID_TASKTRAY), ID_TASKTRAY,
		   _T("Minimize to system tray(&T)"));
	Append(GetItemFlags(ID_COPYTIME), ID_COPYTIME,
		   _T("Copy current position to clipboard(&C)"));
	AppendSeparator();

	// �w���v���j���[
	Append(GetItemFlags(ID_MANUAL), ID_MANUAL, _T("Manual(&M)..."));
	Append(GetItemFlags(ID_VERSIONINFO), ID_VERSIONINFO, _T("Version(&A)..."));

	AppendSeparator();
	Append(MFS_ENABLED, ID_RESTORE, _T("Restore(&R)"));
	AppendSeparator();
	Append(GetItemFlags(ID_EXIT), ID_EXIT, _T("Exit(&X)"));
#endif // JP
	if(!m_hMenu)
		return FALSE;
	return TRUE;
}
//----------------------------------------------------------------------------
// �A�C�e���̃t���O�𓾂�
//----------------------------------------------------------------------------
UINT CRMenu_Taskbar::GetItemFlags(UINT uID)
{
	CMenu & rMenu = (CMenu &)m_rParent.GetMenu();
	return rMenu.GetState(uID);
}
//----------------------------------------------------------------------------
