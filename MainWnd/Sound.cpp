//----------------------------------------------------------------------------
// Sound.cpp : ���̍Đ��Ǘ�
//----------------------------------------------------------------------------
#include <windows.h>
#include <shlwapi.h>
#include "../App.h"
#include "../Common/Utils.h"
#include "../Common/bassenc.h"
#include "../Common/bassmix.h"
#include "../Common/bassasio.h"
#include "../Common/basswasapi.h"
#include "MainWnd.h"
#include "Sound.h"
#include "../Common/BASS_DSHOW.h"
#include "ProgressWnd_MainWnd.h"
//----------------------------------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------------------------------
CSound::CSound(CApp & app, CMainWnd & mainWnd, BOOL bMainStream)
	: m_rApp(app), m_rMainWnd(mainWnd), m_hVideoStream(0), m_bLoop(FALSE),
	  m_bABLoopA(FALSE), m_bABLoopB(FALSE), m_bVideo(FALSE), m_nLoopPosA(0),
	  m_nLoopPosB(0), m_strCurFile(_T("")), m_nCurFile(0), m_hFx125Hz(0),
	  m_hFx250Hz(0), m_hFx500Hz(0), m_hFx1KHz(0), m_hFx2KHz(0), m_hFx4KHz(0),
	  m_hFx8KHz(0), m_hFx16KHz(0), m_hFxReverb(0), m_hFx3DReverb(0),
	  m_hFxDelay(0),
	  m_hFxChorus(0), m_hFxCompressor(0), m_hFxFlanger(0), m_hFxGargle(0),
	  m_hFxDistortion(0), m_hFxVolume(0), m_hMonoralDsp(0),
	  m_hVocalCancelDsp(0), m_hOnlyLeftDsp(0), m_hOnlyRightDsp(0),
	  m_hChangeLRDsp(0), m_hNormalizeDsp(0), m_hPanDsp(0),
	  m_bMainStream(bMainStream), m_hMixer(0), m_hNSF(0), m_nNSFCount(0),
	  m_nNSFCurrent(0)
{
	if(bMainStream) LoadWmaPlugin();
}
//----------------------------------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------------------------------
CSound::~CSound()
{
	BASS_ASIO_Free();
	BASS_WASAPI_Free();
}
//----------------------------------------------------------------------------
// �}�[�J�[�̒ǉ�
//----------------------------------------------------------------------------
void CSound::AddMarker(QWORD nPos)
{
	m_arrayMarker.push_back(nPos);
	std::sort(m_arrayMarker.begin(), m_arrayMarker.end());
}
//----------------------------------------------------------------------------
// �}�[�J�[�̈ʒu��ύX
//----------------------------------------------------------------------------
int CSound::ChangeMarkerPos(int nMarker, QWORD nPos)
{
	m_arrayMarker[nMarker] = nPos;
	std::sort(m_arrayMarker.begin(), m_arrayMarker.end());
	for(int i = 0; i < (int)m_arrayMarker.size(); i++) {
		if(m_arrayMarker[i] == nPos) return i;
	}
	return 0;
}
//----------------------------------------------------------------------------
// �}�[�J�[�̍폜
//----------------------------------------------------------------------------
void CSound::EraseMarker(int nMarker)
{
	m_arrayMarker.erase(m_arrayMarker.begin() + nMarker);
}
//----------------------------------------------------------------------------
// ASIO�̏�����
//----------------------------------------------------------------------------
BOOL CSound::InitASIO()
{
	if(!BASS_ASIO_Init(0, 0)) {
		return FALSE;
	}
	BASS_ASIO_ChannelEnable(0, 0, &AsioProc, NULL);
	BASS_ASIO_ChannelJoin(0, 1, 0);
	BASS_ASIO_ChannelSetFormat(0, 0, BASS_ASIO_FORMAT_FLOAT);
	return TRUE;
}
//----------------------------------------------------------------------------
// �T�C�Y�̃��Z�b�g
//----------------------------------------------------------------------------
void CSound::ResetSize(int left, int top, int right, int bottom)
{
	if(right >= bottom) { // �������c�����傫���ꍇ
		int nHeight = bottom;
		int nWidth = (int)(nHeight * m_nWidth / m_nHeight);
		xVideo_ChannelResizeWindow(m_hVideoStream, 0,
			(int)(right / 2 - nWidth / 2),
			0, nWidth, nHeight);
	}
	else {  // �c�����������傫���ꍇ
		int nWidth = right;
		int nHeight = (int)(nWidth * m_nHeight / m_nWidth);
		xVideo_ChannelResizeWindow(m_hVideoStream, 0, 0,
			(int)(bottom / 2 - nHeight / 2), nWidth, nHeight);
	}
}
//----------------------------------------------------------------------------
// �Đ�
//----------------------------------------------------------------------------
BOOL CSound::ChannelPlay()
{
	ChannelRemoveSync();
	if(m_bABLoopB && m_nLoopPosB < ChannelGetLength())
		ChannelSetSync(BASS_SYNC_POS, m_nLoopPosB, LoopSyncProc,
						(DWORD *)this);
	else ChannelSetSync(BASS_SYNC_END, 0, LoopSyncProc, (DWORD *)this);
	return CBass::ChannelPlay();
}
//----------------------------------------------------------------------------
// �}�[�J�[�̃N���A
//----------------------------------------------------------------------------
void CSound::ClearMarker()
{
	m_arrayMarker.clear();
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 20Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ20(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx20Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx20Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 25Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ25(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx25Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx25Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx25Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx25Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx25Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx25Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 31.5Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ31_5(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx31_5Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx31_5Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx31_5Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx31_5Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx31_5Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx31_5Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 40Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ40(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx40Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx40Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx40Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx40Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx40Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx40Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 50Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ50(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx50Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx50Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx50Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx50Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx50Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx50Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 63Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ63(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx63Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx63Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx63Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx63Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx63Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx63Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 80Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ80(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx80Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx80Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx80Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx80Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx80Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx80Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 100Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ100(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx100Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx100Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx100Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx100Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx100Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx100Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 125Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ125(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx125Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx125Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx125Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx125Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx125Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx125Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 160Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ160(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx160Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx160Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx160Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx160Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx160Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx160Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 200Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ200(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx200Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx200Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx200Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx200Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx200Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx200Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 250Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ250(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx250Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx250Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx250Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx250Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx250Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx250Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 315Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ315(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx315Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx315Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx315Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx315Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx315Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx315Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 400Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ400(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx400Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx400Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx400Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx400Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx400Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx400Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 500Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ500(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx500Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx500Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx500Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx500Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx500Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx500Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 630Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ630(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx630Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx630Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx630Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx630Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx630Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx630Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 800Hz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ800(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx800Hz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx800Hz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx800Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx800Hz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx800Hz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx800Hz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 1KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ1K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 1.25KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ1_25K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1_25KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1_25KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_25KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_25KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_25KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_25KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 1.6KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ1_6K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1_6KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx1_6KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_6KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_6KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_6KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx1_6KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 2KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ2K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx2KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx2KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 2.5KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ2_5K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx2_5KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx2_5KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2_5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2_5KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2_5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx2_5KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 3.15KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ3_15K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx3_15KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx3_15KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx3_15KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx3_15KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx3_15KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx3_15KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 4KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ4K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx4KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx4KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx4KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx4KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx4KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx4KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 5KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ5K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx5KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx5KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx5KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx5KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 6.3KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ6_3K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx6_3KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx6_3KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx6_3KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx6_3KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx6_3KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx6_3KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 8KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ8K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx8KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx8KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx8KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx8KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx8KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx8KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 10KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ10K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx10KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx10KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx10KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx10KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx10KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx10KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 12.5KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ12_5K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx12_5KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx12_5KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx12_5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx12_5KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx12_5KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx12_5KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 16KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ16K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx16KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx16KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx16KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx16KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx16KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx16KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// �C�R���C�U ( 20KHz ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetEQ20K(float fCenter, float fBandwidth, float fGain)
{
	if(-15.0f <= fGain && fGain <= 15.0f) { 
		BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, fGain,
			BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx20KHz, &p);
		BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, 0.0f, BASS_BFX_CHANALL};
		BASS_FXSetParameters(m_hFx20KHz_2, &p2);
	}
	else {
		if(fGain < -15.0f) {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, -15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain + 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20KHz_2, &p2);
		}
		else {
			BASS_BFX_PEAKEQ p = {0, fBandwidth, 0.0f, fCenter, 15.0f,
				BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20KHz, &p);
			BASS_BFX_PEAKEQ p2 = {0, fBandwidth, 0.0f, fCenter, fGain - 15.0f, BASS_BFX_CHANALL};
			BASS_FXSetParameters(m_hFx20KHz_2, &p2);
		}
	}
}
//----------------------------------------------------------------------------
// ���o�[�u�̃p�����[�^�𓾂�
//----------------------------------------------------------------------------
BOOL CSound::GetReverb(BASS_DX8_REVERB * bdr)
{
	if(!m_hFxReverb) return FALSE;
	return BASS_FXGetParameters(m_hFxReverb, bdr);
}
//----------------------------------------------------------------------------
// ���o�[�u�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetReverb(BOOL bReverb)
{
	if(bReverb) {
		if(m_hFxReverb) ChannelRemoveFX(m_hFxReverb);
		m_hFxReverb = ChannelSetFX(BASS_FX_DX8_REVERB, 0);
		SetReverb();
	}
	else ChannelRemoveFX(m_hFxReverb), m_hFxReverb = 0;
}
//----------------------------------------------------------------------------
// ���o�[�u�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetReverb()
{
	BASS_FXSetParameters(m_hFxReverb, &m_bdr);
}
//----------------------------------------------------------------------------
// ���o�[�u�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetReverb(float fInGain, float fReverbMix, float fReverbTime,
					   float fHighFreqRTRatio, BOOL bReverb)
{
	BASS_DX8_REVERB _bdr = {fInGain, fReverbMix, fReverbTime,
							fHighFreqRTRatio};
	m_bdr = _bdr;
	BASS_FXSetParameters(m_hFxReverb, &m_bdr);
}
//----------------------------------------------------------------------------
// �R�c���o�[�u�̃p�����[�^�𓾂�
//----------------------------------------------------------------------------
BOOL CSound::Get3DReverb(BASS_DX8_I3DL2REVERB * bdir)
{
	if(!m_hFx3DReverb) return FALSE;
	return BASS_FXGetParameters(m_hFx3DReverb, bdir);
}
//----------------------------------------------------------------------------
// �R�c���o�[�u�̐ݒ�
//----------------------------------------------------------------------------
void CSound::Set3DReverb(BOOL b3DReverb)
{
	if(b3DReverb) {
		if(m_hFx3DReverb) ChannelRemoveFX(m_hFx3DReverb);
		m_hFx3DReverb = ChannelSetFX(BASS_FX_DX8_I3DL2REVERB, 0);
		Set3DReverb();
	}
	else ChannelRemoveFX(m_hFx3DReverb), m_hFx3DReverb = 0;
}
//----------------------------------------------------------------------------
// �R�c���o�[�u�̐ݒ�
//----------------------------------------------------------------------------
void CSound::Set3DReverb()
{
	BASS_FXSetParameters(m_hFx3DReverb, &m_bdir);
}
//----------------------------------------------------------------------------
// �R�c���o�[�u�̐ݒ�
//----------------------------------------------------------------------------
void CSound::Set3DReverb(int lRoom, int lRoomHF, float flRoomRolloffFactor,
					   float flDecayTime, float flDecayHFRatio,
					   int lReflections, float flReflectionsDelay, int lReverb,
					   float flReverbDelay, float flDiffusion, float flDensity,
					   float flHFReference, BOOL b3DReverb)
{
	BASS_DX8_I3DL2REVERB _bdir = {lRoom, lRoomHF, flRoomRolloffFactor,
								  flDecayTime, flDecayHFRatio, lReflections,
								  flReflectionsDelay, lReverb, flReverbDelay, 
								  flDiffusion, flDensity, flHFReference};
	m_bdir = _bdir;
	BASS_FXSetParameters(m_hFx3DReverb, &m_bdir);
}
//----------------------------------------------------------------------------
// �f�B���C�̃p�����[�^�𓾂�
//----------------------------------------------------------------------------
BOOL CSound::GetDelay(BASS_DX8_ECHO * bde)
{
	if(!m_hFxDelay) return FALSE;
	return BASS_FXGetParameters(m_hFxDelay, bde);
}
//----------------------------------------------------------------------------
// �f�B���C�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetDelay(BOOL bDelay)
{
	if(bDelay) {
		if(m_hFxDelay) ChannelRemoveFX(m_hFxDelay);
		m_hFxDelay = ChannelSetFX(BASS_FX_DX8_ECHO, 0);
		SetDelay();
	}
	else
		ChannelRemoveFX(m_hFxDelay), m_hFxDelay = 0;
}
//----------------------------------------------------------------------------
// �f�B���C�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetDelay()
{
	BASS_FXSetParameters(m_hFxDelay, &m_bde);
}
//----------------------------------------------------------------------------
// �f�B���C�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetDelay(float fWetDryMix, float fFeedback, float fLeftDelay,
					  float fRightDelay, BOOL lPanDelay, BOOL bDelay)
{
	BASS_DX8_ECHO _bde = {fWetDryMix, fFeedback, fLeftDelay, fRightDelay,
						  lPanDelay};
	m_bde = _bde;
	BASS_FXSetParameters(m_hFxDelay, &m_bde);
}
//----------------------------------------------------------------------------
// �f�B�X�g�[�V�����̃p�����[�^�𓾂�
//----------------------------------------------------------------------------
BOOL CSound::GetDistortion(BASS_DX8_DISTORTION * bdd)
{
	if(!m_hFxDistortion) return FALSE;
	return BASS_FXGetParameters(m_hFxDistortion, bdd);
}
//----------------------------------------------------------------------------
// �f�B�X�g�[�V�����̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetDistortion(BOOL bDistortion)
{
	if(bDistortion) {
		if(m_hFxDistortion) ChannelRemoveFX(m_hFxDistortion);
		m_hFxDistortion = ChannelSetFX(BASS_FX_DX8_DISTORTION, 0);
		SetDistortion();
	}
	else
		ChannelRemoveFX(m_hFxDistortion), m_hFxDistortion = 0;
}
//----------------------------------------------------------------------------
// �f�B�X�g�[�V�����̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetDistortion()
{
	BASS_FXSetParameters(m_hFxDistortion, &m_bdd);
}
//----------------------------------------------------------------------------
// �f�B�X�g�[�V�����̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetDistortion(float fGain, float fEdge,
						   float fPostEQCenterFreq, float fPostEQBandwidth,
						   float fPreLowpassCutoff, BOOL bDistortion)
{
	BASS_DX8_DISTORTION _bdd = {fGain, fEdge, fPostEQCenterFreq,
								fPostEQBandwidth, fPreLowpassCutoff};
	m_bdd = _bdd;
	BASS_FXSetParameters(m_hFxDistortion, &m_bdd);
}
//----------------------------------------------------------------------------
// �R�[���X�̃p�����[�^�𓾂�
//----------------------------------------------------------------------------
BOOL CSound::GetChorus(BASS_DX8_CHORUS * bdc)
{
	if(!m_hFxChorus) return FALSE;
	return BASS_FXGetParameters(m_hFxChorus, bdc);
}
//----------------------------------------------------------------------------
// �R�[���X�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetChorus(BOOL bChorus)
{
	if(bChorus) {
		if(m_hFxChorus) ChannelRemoveFX(m_hFxChorus);
		m_hFxChorus = ChannelSetFX(BASS_FX_DX8_CHORUS, 0);
		SetChorus();
	}
	else
		ChannelRemoveFX(m_hFxChorus), m_hFxChorus = 0;
}
//----------------------------------------------------------------------------
// �R�[���X�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetChorus()
{
	BASS_FXSetParameters(m_hFxChorus, &m_bdc);
}
//----------------------------------------------------------------------------
// �R�[���X�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetChorus(float fWetDryMix, float fDepth, float fFeedback,
					   float fFreq, DWORD lWaveform, float fDelay,
					   DWORD lPhase, BOOL bChorus)
{
	BASS_DX8_CHORUS _bdc = {fWetDryMix, fDepth, fFeedback, fFreq,
							lWaveform, fDelay, lPhase};
	m_bdc = _bdc;
	BASS_FXSetParameters(m_hFxChorus, &m_bdc);
}
//----------------------------------------------------------------------------
// �R���v���b�T�[�̃p�����[�^�𓾂�
//----------------------------------------------------------------------------
BOOL CSound::GetCompressor(BASS_DX8_COMPRESSOR * bdcmp)
{
	if(!m_hFxCompressor) return FALSE;
	return BASS_FXGetParameters(m_hFxCompressor, bdcmp);
}
//----------------------------------------------------------------------------
// �R���v���b�T�[�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetCompressor(BOOL bCompressor)
{
	if(bCompressor) {
		if(m_hFxCompressor) ChannelRemoveFX(m_hFxCompressor);
		m_hFxCompressor = ChannelSetFX(BASS_FX_DX8_COMPRESSOR, 0);
		SetCompressor();
	}
	else
		ChannelRemoveFX(m_hFxCompressor), m_hFxCompressor = 0;
}
//----------------------------------------------------------------------------
// �R���v���b�T�[�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetCompressor()
{
	BASS_FXSetParameters(m_hFxCompressor, &m_bdcmp);
}
//----------------------------------------------------------------------------
// �R���v���b�T�[�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetCompressor(float fGain, float fAttack, float fRelease,
						   float fThreshold, float fRatio, float fPredelay,
						   BOOL bCompressor)
{
	BASS_DX8_COMPRESSOR _bdcmp = {fGain, fAttack, fRelease, fThreshold,
								  fRatio, fPredelay};
	m_bdcmp = _bdcmp;
	BASS_FXSetParameters(m_hFxCompressor, &m_bdcmp);
}
//----------------------------------------------------------------------------
// �t�����W���[�̃p�����[�^�𓾂�
//----------------------------------------------------------------------------
BOOL CSound::GetFlanger(BASS_DX8_FLANGER * bdf)
{
	if(!m_hFxFlanger) return FALSE;
	return BASS_FXGetParameters(m_hFxFlanger, bdf);
}
//----------------------------------------------------------------------------
// �t�����W���[�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetFlanger(BOOL bFlanger)
{
	if(bFlanger) {
		if(m_hFxFlanger) ChannelRemoveFX(m_hFxFlanger);
		m_hFxFlanger = ChannelSetFX(BASS_FX_DX8_FLANGER, 0);
		SetFlanger();
	}
	else
		ChannelRemoveFX(m_hFxFlanger), m_hFxFlanger = 0;
}
//----------------------------------------------------------------------------
// �t�����W���[�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetFlanger()
{
	BASS_FXSetParameters(m_hFxFlanger, &m_bdf);
}
//----------------------------------------------------------------------------
// �t�����W���[�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetFlanger(float fWetDryMix, float fDepth, float fFeedback,
						float fFreq, DWORD lWaveform, float fDelay,
						DWORD lPhase, BOOL bFlanger)
{
	BASS_DX8_FLANGER _bdf = {fWetDryMix, fDepth, fFeedback, fFreq,
							 lWaveform, fDelay, lPhase};
	m_bdf = _bdf;
	BASS_FXSetParameters(m_hFxFlanger, &m_bdf);
}
//----------------------------------------------------------------------------
// �K�[�O���̃p�����[�^�𓾂�
//----------------------------------------------------------------------------
BOOL CSound::GetGargle(BASS_DX8_GARGLE * bdg)
{
	if(!m_hFxGargle) return FALSE;
	return BASS_FXGetParameters(m_hFxGargle, bdg);
}
//----------------------------------------------------------------------------
// �K�[�O���̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetGargle(BOOL bGargle)
{
	if(bGargle) {
		if(m_hFxGargle) ChannelRemoveFX(m_hFxGargle);
		m_hFxGargle = ChannelSetFX(BASS_FX_DX8_GARGLE, 0);
		SetGargle();
	}
	else
		ChannelRemoveFX(m_hFxGargle), m_hFxGargle = 0;
}
//----------------------------------------------------------------------------
// �K�[�O���̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetGargle()
{
	BASS_FXSetParameters(m_hFxGargle, &m_bdg);
}
//----------------------------------------------------------------------------
// �K�[�O���̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetGargle(DWORD dwRateHz, DWORD dwWaveShape, BOOL bGargle)
{
	BASS_DX8_GARGLE _bdg = {dwRateHz, dwWaveShape};
	m_bdg = _bdg;
	BASS_FXSetParameters(m_hFxGargle, &m_bdg);
}
//----------------------------------------------------------------------------
// ���[�v�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetLoop(BOOL bLoop)
{
	m_bLoop = bLoop;
}
//----------------------------------------------------------------------------
// AB���[�v ( A ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetABLoopA(BOOL bLoop)
{
	m_bABLoopA = bLoop;
	m_nLoopPosA = 0;
}
//----------------------------------------------------------------------------
// AB���[�v ( B ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetABLoopB(BOOL bLoop)
{
	m_bABLoopB = bLoop;
	m_nLoopPosB = ChannelGetLength();
	ChannelRemoveSync();
	ChannelSetSync(BASS_SYNC_END, 0, LoopSyncProc, (DWORD *)this);
}
//----------------------------------------------------------------------------
// AB���[�v ( A ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetLoopPosA(QWORD nPos)
{
	m_nLoopPosA = nPos;
}
//----------------------------------------------------------------------------
// AB���[�v ( B ) �̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetLoopPosB(QWORD nPos)
{
	m_bABLoopB = TRUE;
	m_nLoopPosB = nPos;
	ChannelRemoveSync();
	if(nPos >= ChannelGetLength())
		ChannelSetSync(BASS_SYNC_END, 0, LoopSyncProc, (DWORD *)this);
	else
		ChannelSetSync(BASS_SYNC_POS, m_nLoopPosB, LoopSyncProc, (DWORD *)this);
}
//----------------------------------------------------------------------------
// ASIO�̊J�n
//----------------------------------------------------------------------------
void CSound::StartASIO()
{
	StopASIO();
	if(m_hStream) {
		BASS_CHANNELINFO info;
		BASS_ChannelGetInfo(m_hStream, &info);
		BASS_ASIO_ChannelSetRate(0, 0, info.freq);
		BASS_ASIO_SetRate(info.freq);
		BASS_ASIO_Start(0);
	}
}
//----------------------------------------------------------------------------
// ASIO�̒�~
//----------------------------------------------------------------------------
void CSound::StopASIO()
{
	if(BASS_ASIO_IsStarted()) BASS_ASIO_Stop();
}
//----------------------------------------------------------------------------
// WASAPI�̊J�n
//----------------------------------------------------------------------------
void CSound::StartWASAPI()
{
	if(m_rMainWnd.IsVideo()) return;

	BOOL bStopped = ChannelIsStopped();
	BOOL bPausing = ChannelIsPausing();
	StopWASAPI();
	if(!BASS_WASAPI_Init(-1, 0, 0,
			BASS_WASAPI_AUTOFORMAT | BASS_WASAPI_EXCLUSIVE,
			0.4f, 0.05f, WasapiProc, (DWORD *)this)) {
		if(!BASS_WASAPI_Init(-1, 0, 0, BASS_WASAPI_AUTOFORMAT, 0.4f, 0.05f,
				WasapiProc, (DWORD *)this)) {
			return;
		}
	}
	BASS_WASAPI_INFO wi;
	BASS_WASAPI_GetInfo(&wi);
	m_hMixer = BASS_Mixer_StreamCreate(wi.freq, wi.chans,
		BASS_SAMPLE_FLOAT | BASS_STREAM_DECODE);
	if(m_hStream) {
		double dPos = ChannelGetSecondsPosition();
		if(dPos >= 0.25) dPos -= 0.25;
		StreamFree();
		if(!BASS_WASAPI_Start()) {
			BASS_WASAPI_Free();
			return;
		}
		if(PathIsURL(m_strCurFile.c_str()))
			StreamCreateURL(m_strCurFile.c_str());
		else StreamCreateFile(m_strCurFile.c_str());
		ClearMarker();
		m_rMainWnd.SetAllEffects();
		ChannelSetSecondsPosition(dPos);
		if(bStopped || bPausing) PauseWASAPI();
	}
}
//----------------------------------------------------------------------------
// WASAPI�̒�~
//----------------------------------------------------------------------------
void CSound::StopWASAPI()
{
	if(BASS_WASAPI_IsStarted()) {
		BOOL bPlaying = FALSE;
		double dPos;
		BOOL bStopped, bPausing;
		if(m_hStream) {
			bPlaying = TRUE;
			dPos = ChannelGetSecondsPosition();
			if(dPos >= 0.25) dPos -= 0.25;
			bStopped = ChannelIsStopped();
			bPausing = ChannelIsPausing();
		}
		BASS_WASAPI_Stop(FALSE);
		BASS_WASAPI_Free();
		BASS_Free();
		Init(m_rMainWnd);
		if(bPlaying) {
			StreamFree();
			if(PathIsURL(m_strCurFile.c_str()))
				StreamCreateURL(m_strCurFile.c_str());
			else StreamCreateFile(m_strCurFile.c_str());
			ClearMarker();
			m_rMainWnd.SetAllEffects();
			ChannelSetSecondsPosition(dPos);
			if(!bStopped && !bPausing) m_rMainWnd.GetSound().ChannelPlay();
		}
	}
}
//----------------------------------------------------------------------------
// WASAPI�̈ꎞ��~
//----------------------------------------------------------------------------
void CSound::PauseWASAPI()
{
	if(BASS_WASAPI_IsStarted()) BASS_WASAPI_Stop(FALSE);
}
//----------------------------------------------------------------------------
// WASAPI�̍ĊJ
//----------------------------------------------------------------------------
void CSound::ResumeWASAPI()
{
	BASS_WASAPI_Start();
}
//----------------------------------------------------------------------------
// �e���|�𓾂�
//----------------------------------------------------------------------------
float CSound::GetTempo()
{
	return CBassFx::GetTempo() + 100.0f;
}
//----------------------------------------------------------------------------
// �e���|�̐ݒ�
//----------------------------------------------------------------------------
BOOL CSound::SetTempo(float tempo)
{
	return CBassFx::SetTempo(tempo - 100.0f);
}
//----------------------------------------------------------------------------
// �T���v�����[�g�𓾂�
//----------------------------------------------------------------------------
float CSound::GetSampleRate()
{
	return CBassFx::GetSampleRate() * 100.0f / ChannelGetFreq();
}
//----------------------------------------------------------------------------
// �T���v�����[�g�̐ݒ�
//----------------------------------------------------------------------------
BOOL CSound::SetSampleRate(float samplerate)
{
	return CBassFx::SetSampleRate(ChannelGetFreq() * samplerate / 100.0f);
}
//----------------------------------------------------------------------------
// ���ʂ̐ݒ�
//----------------------------------------------------------------------------
BOOL CSound::ChannelSetVolume(float volume)
{
	BASS_BFX_VOLUME p = {0, volume / 100.0f};
	return BASS_FXSetParameters(m_hFxVolume, &p);
}
//----------------------------------------------------------------------------
// �r�f�I�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetVideo(BOOL bVideo)
{
	m_bVideo = bVideo;
}
//----------------------------------------------------------------------------
// ���[�v
//----------------------------------------------------------------------------
UINT CSound::OnLoop()
{
	if(m_bABLoopA || m_bABLoopB || m_bLoop) {
		if(!m_rMainWnd.CheckLoop()) return 1;
		if(!ChannelSetPosition(m_nLoopPosA)) return 0;
		return 1;
	}
	return 0;
}
//----------------------------------------------------------------------------
// �ۑ�
//----------------------------------------------------------------------------
void CSound::SaveFile(LPCTSTR lpszFilePath, int nFormat)
{
	// nFormat : 0 ( WAVE ), 1 ( MP3 ), 2 ( OGG )

	if(GetCurFileName() == _T("")) return;
	if(nFormat == 1) { // MP3
		tstring strLamePath = m_rApp.GetFilePath() + _T("lame.exe");
		if(GetFileAttributes(strLamePath.c_str()) == 0xFFFFFFFF) {
#if JP
			MessageBox(m_rMainWnd, _T("MP3�`���ł̕ۑ��ɂ́ALAME.EXE���K�v")
				_T("�ł��B\nHayaemon.exe�Ɠ����f�B���N�g����LAME.EXE��u����")
				_T("�������B"), _T("���O��t���ĕۑ�"), MB_ICONINFORMATION);
#else // JP
			MessageBox(m_rMainWnd, _T("To save MP3 file, lame.exe is ")
					   _T("required.\nPut lame.exe in the same directory ")
					   _T("as hayaemon.exe."), _T("Save file"),
					   MB_ICONINFORMATION);
#endif // JP
			return;
		}
	}
	else if(nFormat == 2) { // OGG
		tstring strLamePath = m_rApp.GetFilePath() + _T("oggenc.exe");
		if(GetFileAttributes(strLamePath.c_str()) == 0xFFFFFFFF) {
#if JP
			MessageBox(m_rMainWnd, _T("Ogg Vorbis�`���ł̕ۑ��ɂ́A")
				_T("oggenc.exe���K�v�ł��B\nHayaemon.exe�Ɠ����f�B���N�g��")
				_T("��oggenc.exe��u���ĉ������B"), _T("���O��t���ĕۑ�"),
				MB_ICONINFORMATION);
#else // JP
			MessageBox(m_rMainWnd, _T("To save Ogg Vorbis file, oggenc.exe ")
					   _T("is required.\nPut oggenc.exe in the same directory")
					   _T("as hayaemon.exe."), _T("Save file"),
					   MB_ICONINFORMATION);
#endif // JP
			return;
		}
	}

	m_rMainWnd.KillTimer(m_rMainWnd.IDT_TIME);
	QWORD curPos = ChannelGetPosition();

	// AB���[�v���̏ꍇ�́AA����B�܂ł�ۑ�
	BOOL bABLoopA = m_bABLoopA;
	BOOL bABLoopB = m_bABLoopB;
	QWORD nStartPosition = m_bABLoopA ? GetLoopPosA() : 0;
	QWORD nEndPosition = m_bABLoopB ? GetLoopPosB() : ChannelGetLength();
	int nStartPosition_sec = m_bABLoopA ? (int)GetLoopPosA_sec() : 0;
	int nEndPosition_sec = m_bABLoopB ?
		(int)GetLoopPosB_sec() : (int)ChannelGetSecondsLength();

	BOOL bPlaying = FALSE;
	if(ChannelPause()) bPlaying = TRUE;

	StreamCreateFile(m_strCurFile.c_str(), TRUE);
	m_rMainWnd.SetAllEffects();
	SetPan(m_rMainWnd.GetPanSlider().GetThumbPos());

	BOOL bRet;
	if(nFormat == 0) { // WAVE
		tstring strCmdLine = CUtils::Replace(lpszFilePath, _T("\\"),
											 _T("\\\\"));
		bRet = BASS_Encode_Start(m_hStream, (char*)strCmdLine.c_str(),
								 BASS_ENCODE_PCM | BASS_ENCODE_FP_16BIT |
								 BASS_ENCODE_AUTOFREE | BASS_IF_UNICODE, NULL,
								 0);
	}
	else if(nFormat == 1) { // MP3
		tstring strCmdLine = m_rApp.GetFilePath();
		strCmdLine += _T("lame ");
		strCmdLine += m_rMainWnd.GetStrLAMECommandLine();
		strCmdLine += _T(" - \"");
		strCmdLine += lpszFilePath;
		strCmdLine += _T("\"");
		bRet = BASS_Encode_Start(m_hStream, (char*)strCmdLine.c_str(),
								 BASS_ENCODE_FP_16BIT | BASS_ENCODE_AUTOFREE |
								 BASS_IF_UNICODE, NULL, 0);
	}
	else if(nFormat == 2) { // OGG
		tstring strCmdLine = m_rApp.GetFilePath();
		strCmdLine += _T("oggenc -o \"");
		strCmdLine += lpszFilePath;
		strCmdLine += _T("\" -");
		bRet = BASS_Encode_Start(m_hStream, (char*)strCmdLine.c_str(),
								 BASS_ENCODE_AUTOFREE | BASS_IF_UNICODE, NULL,
								 0);
	}

	if(!bRet) {
		_tremove(lpszFilePath);
		StreamCreateFile(m_strCurFile.c_str());
		m_rMainWnd.SetAllEffects();
		if(curPos > 0) ChannelSetPosition(curPos);
		if(bPlaying) m_rMainWnd.Pause();
		if(bABLoopA) SetLoopPosA(nStartPosition);
		if(bABLoopB) SetLoopPosB(nEndPosition);
		return;
	}

	CProgressWnd_MainWnd wnd(m_rApp, m_rMainWnd);
	wnd.Create();
#if JP
	tstring title = _T("�ۑ��� - ");
#else // JP
	tstring title = _T("Saving - ");
#endif // JP
	title += CUtils::GetFileName(lpszFilePath);
	wnd.SetCaption(title.c_str());

	wnd.SetProgressRange(0, nEndPosition_sec - nStartPosition_sec);
	wnd.Show(SW_SHOW);
	wnd.Update();

	if(m_bABLoopA) ChannelSetPosition(nStartPosition);
	float buf[10000];
	int i = 0;
	MSG msg;
	while(ChannelIsActive()) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if(GetMessage(&msg, NULL, 0, 0) > 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// �E�B���h�E������ꂽ�ꍇ�́A�I��
			if(!IsWindow(wnd)) {
				BASS_Encode_Stop(m_hStream);
				_tremove(lpszFilePath);
				break;
			}
		}

		LONG c = ChannelGetData(buf, sizeof(buf) | BASS_DATA_FLOAT);
		if(!m_rMainWnd.GetMenu().IsItemChecked(ID_REVERSE))
			wnd.SetProgressPos((int)ChannelGetSecondsPosition() -
							   (int)nStartPosition);
		else
			wnd.SetProgressPos((int)ChannelGetSecondsLength() -
							   (int)ChannelGetSecondsPosition() -
							   (int)nStartPosition);
		fflush(stdout);

		if(m_bABLoopB && ChannelGetPosition() >= nEndPosition)
			break;
	}

	BASS_Encode_Stop(m_hStream);
	StreamCreateFile(m_strCurFile.c_str());
	m_rMainWnd.SetAllEffects();
	if(curPos > 0) ChannelSetPosition(curPos);
	if(bPlaying) m_rMainWnd.Pause();
	if(bABLoopA) SetLoopPosA(nStartPosition);
	if(bABLoopB) SetLoopPosB(nEndPosition);
}
//----------------------------------------------------------------------------
// �t�@�C���̓ǂݍ���
//----------------------------------------------------------------------------
BOOL CSound::StreamCreateURL(LPCTSTR lpFilePath, BOOL bDecode)
{
	BOOL bRet = FALSE;
	if(!m_bMainStream) {
		bRet = CBassFx::StreamCreateURL(lpFilePath);
		TempoCreate(bDecode);
		m_strCurFile = lpFilePath;
		m_nLoopPosA = 0;
		m_nLoopPosB = ChannelGetLength();
		return bRet;
	}

	TCHAR ext[_MAX_EXT];
	_tsplitpath_s(lpFilePath, NULL, 0, NULL, 0, NULL, 0, ext, _MAX_EXT);
	if(_tcsicmp(ext, _T(".avi")) == 0 || _tcsicmp(ext, _T(".wmv")) == 0 ||
	   _tcsicmp(ext, _T(".mp4")) == 0 || _tcsicmp(ext, _T(".mkv")) == 0 ||
	   _tcsicmp(ext, _T(".flv")) == 0) {
		StreamFree();
		if(m_rMainWnd.IsFullScreen())
			m_hVideoStream = xVideo_StreamCreateFile((PVOID)lpFilePath, 0,
										(HWND)m_rMainWnd.GetVideoScreenWnd(),
										BASS_STREAM_DECODE | xVideo_UNICODE);
		else
			m_hVideoStream = xVideo_StreamCreateFile((PVOID)lpFilePath, 0,
										(HWND)m_rMainWnd.GetVideoScreen(),
										BASS_STREAM_DECODE | xVideo_UNICODE);

		xVideo_ChannelInfo xci;
		xVideo_ChannelGetInfo(m_hVideoStream, &xci);
		m_nWidth = xci.Width;
		m_nHeight = xci.Height;

		if(!m_rMainWnd.IsFullScreen())
			ResetSize(0, 0, m_rMainWnd.GetVideoScreen().GetWidth(),
						m_rMainWnd.GetVideoScreen().GetHeight());

		m_hStream = m_hVideoStream;
		TempoCreate(bDecode);
		m_strCurFile = lpFilePath;
		m_nLoopPosA = 0;
		m_nLoopPosB = ChannelGetLength();
		m_hFx20Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx25Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx31_5Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx40Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx50Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx63Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx80Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx100Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx125Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx160Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx200Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx250Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx315Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx400Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx500Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx630Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx800Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_25KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_6KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx3_15KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx4KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx6_3KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx8KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx10KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx12_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx16KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx25Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx31_5Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx40Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx50Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx63Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx80Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx100Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx125Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx160Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx200Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx250Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx315Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx400Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx500Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx630Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx800Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_25KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_6KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx3_15KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx4KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx6_3KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx8KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx10KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx12_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx16KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFxVolume = ChannelSetFX(BASS_FX_BFX_VOLUME, 1);

		if(m_hStream) {
			m_rMainWnd.SetVideo(TRUE);
			bRet = TRUE;
		}
	}

	if(!bRet) {
		bRet = CBassFx::StreamCreateURL(lpFilePath);
		ReverseCreate();
		TempoCreate(bDecode || BASS_WASAPI_IsStarted());
		m_strCurFile = lpFilePath;
		m_nLoopPosA = 0;
		m_nLoopPosB = ChannelGetLength();
		m_hFx20Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx25Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx31_5Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx40Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx50Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx63Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx80Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx100Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx125Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx160Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx200Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx250Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx315Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx400Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx500Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx630Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx800Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_25KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_6KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx3_15KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx4KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx6_3KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx8KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx10KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx12_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx16KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx25Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx31_5Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx40Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx50Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx63Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx80Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx100Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx125Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx160Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx200Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx250Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx315Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx400Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx500Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx630Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx800Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_25KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_6KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx3_15KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx4KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx6_3KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx8KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx10KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx12_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx16KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFxVolume = ChannelSetFX(BASS_FX_BFX_VOLUME, 1);
		if(BASS_WASAPI_IsStarted())
			BASS_Mixer_StreamAddChannel(m_hMixer, m_hStream,
				BASS_SPEAKER_FRONT | BASS_STREAM_AUTOFREE);
		m_rMainWnd.SetVideo(FALSE);
	}
	return bRet;
}
//----------------------------------------------------------------------------
// �t�@�C���̓ǂݍ���
//----------------------------------------------------------------------------
BOOL CSound::StreamCreateFile(LPCTSTR lpFilePath, BOOL bDecode, int nCount)
{
	BOOL bRet = FALSE;
	if(!m_bMainStream) {
		bRet = CBassFx::StreamCreateFile(lpFilePath);
		TempoCreate(bDecode);
		m_strCurFile = lpFilePath;
		m_nLoopPosA = 0;
		m_nLoopPosB = ChannelGetLength();
		return bRet;
	}

	TCHAR ext[_MAX_EXT];
	_tsplitpath_s(lpFilePath, NULL, 0, NULL, 0, NULL, 0, ext, _MAX_EXT);

	m_nNSFCount = 0;
	if(_tcsicmp(ext, _T(".nsf")) == 0)
		return StreamCreateNSFFile(lpFilePath, nCount);

	if(_tcsicmp(ext, _T(".avi")) == 0 || _tcsicmp(ext, _T(".wmv")) == 0 ||
	   _tcsicmp(ext, _T(".mp4")) == 0 || _tcsicmp(ext, _T(".mkv")) == 0 ||
	   _tcsicmp(ext, _T(".flv")) == 0) {
		StreamFree();
		if(m_rMainWnd.IsFullScreen())
			m_hVideoStream = xVideo_StreamCreateFile((PVOID)lpFilePath, 0,
										(HWND)m_rMainWnd.GetVideoScreenWnd(),
										BASS_STREAM_DECODE | xVideo_UNICODE);
		else
			m_hVideoStream = xVideo_StreamCreateFile((PVOID)lpFilePath, 0,
										(HWND)m_rMainWnd.GetVideoScreen(),
										BASS_STREAM_DECODE | xVideo_UNICODE);

		xVideo_ChannelInfo xci;
		xVideo_ChannelGetInfo(m_hVideoStream, &xci);
		m_nWidth = xci.Width;
		m_nHeight = xci.Height;

		if(!m_rMainWnd.IsFullScreen())
			ResetSize(0, 0, m_rMainWnd.GetVideoScreen().GetWidth(),
						m_rMainWnd.GetVideoScreen().GetHeight());

		m_hStream = m_hVideoStream;
		TempoCreate(bDecode);
		m_strCurFile = lpFilePath;
		m_nLoopPosA = 0;
		m_nLoopPosB = ChannelGetLength();
		m_hFx20Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx25Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx31_5Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx40Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx50Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx63Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx80Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx100Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx125Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx160Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx200Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx250Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx315Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx400Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx500Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx630Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx800Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_25KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_6KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx3_15KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx4KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx6_3KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx8KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx10KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx12_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx16KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx25Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx31_5Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx40Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx50Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx63Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx80Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx100Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx125Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx160Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx200Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx250Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx315Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx400Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx500Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx630Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx800Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_25KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_6KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx3_15KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx4KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx6_3KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx8KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx10KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx12_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx16KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFxVolume = ChannelSetFX(BASS_FX_BFX_VOLUME, 1);

		if(m_hStream) {
			m_rMainWnd.SetVideo(TRUE);
			bRet = TRUE;
		}
	}

	if(!bRet) {
		bRet = CBassFx::StreamCreateFile(lpFilePath);
		ReverseCreate();
		TempoCreate(bDecode || BASS_WASAPI_IsStarted());
		m_strCurFile = lpFilePath;
		m_nLoopPosA = 0;
		m_nLoopPosB = ChannelGetLength();
		m_hFx20Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx25Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx31_5Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx40Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx50Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx63Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx80Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx100Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx125Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx160Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx200Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx250Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx315Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx400Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx500Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx630Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx800Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_25KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_6KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx3_15KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx4KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx6_3KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx8KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx10KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx12_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx16KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx25Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx31_5Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx40Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx50Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx63Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx80Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx100Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx125Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx160Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx200Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx250Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx315Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx400Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx500Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx630Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx800Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_25KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx1_6KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx2_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx3_15KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx4KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx6_3KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx8KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx10KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx12_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx16KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFx20KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
		m_hFxVolume = ChannelSetFX(BASS_FX_BFX_VOLUME, 1);
		if(BASS_WASAPI_IsStarted())
			BASS_Mixer_StreamAddChannel(m_hMixer, m_hStream,
				BASS_SPEAKER_FRONT | BASS_STREAM_AUTOFREE);
		m_rMainWnd.SetVideo(FALSE);
	}
	return bRet;
}
//----------------------------------------------------------------------------
// NSF�t�@�C���p�X�g���[���̍쐬
//----------------------------------------------------------------------------
BOOL CSound::StreamCreateNSFFile(LPCTSTR lpFilePath, int nCount)
{
	StreamFree();

	if(m_hNSF) {
		NSFSDK_Terminate(m_hNSF);
		m_hNSF = 0;
	}

	HANDLE hFile = CreateFile(lpFilePath, GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	DWORD dwSize = GetFileSize(hFile, NULL);
	if((int)dwSize <= 0) return FALSE;

	PBYTE pBuf = new BYTE[dwSize];
	DWORD dwBytes;
	ReadFile(hFile, pBuf, dwSize, &dwBytes, NULL);
	CloseHandle(hFile);

	m_hNSF = NSFSDK_Load(pBuf, dwSize);
	m_nNSFCount = NSFSDK_GetSongMax(m_hNSF);
	m_nNSFCurrent = nCount;
	NSFSDK_SetSongNo(m_hNSF, nCount);
	LPSTR pStrTitle;
	LPSTR pStrComposer;
	LPSTR pStrCopyright;
	LPSTR pStrDetail;
	NSFSDK_GetFileInfo(&pStrTitle, &pStrComposer, &pStrCopyright, &pStrDetail);

	TCHAR chTitle[255];
	TCHAR chComposer[255];
#ifdef UNICODE
	int cchWC = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pStrTitle, -1,
		NULL, 0);
	wchar_t *wszTitle = new wchar_t[cchWC];
	memset(wszTitle, 0, cchWC * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pStrTitle, -1, wszTitle,
		cchWC);
	_tcscpy_s(chTitle, cchWC + 1, wszTitle);
	delete[] wszTitle;

	cchWC = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pStrComposer, -1,
		NULL, 0);
	wchar_t *wszComposer = new wchar_t[cchWC];
	memset(wszComposer, 0, cchWC * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pStrComposer, -1, wszComposer,
		cchWC);
	_tcscpy_s(chComposer, cchWC + 1, wszComposer);
	delete[] wszComposer;
#else
	chTitle = pStrTitle;
	chComposer = pStrComposer;
#endif
	m_rMainWnd.GetCurPlayList().SetItem(m_nCurFile - 1, 2, chTitle);
	m_rMainWnd.GetCurPlayList().SetItem(m_nCurFile - 1, 3, chComposer);

	NSFSDK_SetFrequency(m_hNSF, 44100);
	NSFSDK_SetChannel(m_hNSF, NSFSDK_GetChannel(m_hNSF));
	NSFSDK_SetNosefartFilter(m_hNSF, 0);
	NSFSDK_Reset(m_hNSF);
	m_hStream = BASS_StreamCreate(44100, 2, 0, (STREAMPROC*)WriteStream,
		(DWORD *)this);
	m_strCurFile = lpFilePath;
	m_nLoopPosA = 0;
	m_nLoopPosB = ChannelGetLength();
	m_hFx20Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx25Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx31_5Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx40Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx50Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx63Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx80Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx100Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx125Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx160Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx200Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx250Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx315Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx400Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx500Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx630Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx800Hz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx1KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx1_25KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx1_6KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx2KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx2_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx3_15KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx4KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx6_3KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx8KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx10KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx12_5KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx16KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx20KHz = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx20Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx25Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx31_5Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx40Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx50Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx63Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx80Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx100Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx125Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx160Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx200Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx250Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx315Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx400Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx500Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx630Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx800Hz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx1KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx1_25KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx1_6KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx2KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx2_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx3_15KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx4KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx6_3KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx8KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx10KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx12_5KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx16KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFx20KHz_2 = ChannelSetFX(BASS_FX_BFX_PEAKEQ, 0);
	m_hFxVolume = ChannelSetFX(BASS_FX_BFX_VOLUME, 1);
	if(BASS_WASAPI_IsStarted())
		BASS_Mixer_StreamAddChannel(m_hMixer, m_hStream,
			BASS_SPEAKER_FRONT | BASS_STREAM_AUTOFREE);

	m_rMainWnd.SetVideo(FALSE);

	delete[] pBuf;

	return TRUE;
}
//----------------------------------------------------------------------------
// �X�g���[���̉��
//----------------------------------------------------------------------------
void CSound::StreamFree()
{
	if(m_hVideoStream) xVideo_StreamFree(m_hVideoStream), m_hVideoStream = 0;
	CBassFx::StreamFree();
}
//----------------------------------------------------------------------------
// �E�B���h�E�̐ݒ�
//----------------------------------------------------------------------------
void CSound::ChannelSetWindow()
{
	if(m_rMainWnd.IsFullScreen())
		xVideo_ChannelSetWindow(m_hVideoStream, 0,
								(HWND)m_rMainWnd.GetVideoScreenWnd());
	else
		xVideo_ChannelSetWindow(m_hVideoStream, 0,
								(HWND)m_rMainWnd.GetVideoScreen());
}
//----------------------------------------------------------------------------
// ���m�������̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetMonoral(BOOL bMonoral)
{
	if(bMonoral)
		m_hMonoralDsp = BASS_ChannelSetDSP(m_hStream, &Monoral, 0, 1);
	else BASS_ChannelRemoveDSP(m_hStream, m_hMonoralDsp);
}
//----------------------------------------------------------------------------
// ���m�������p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
void CALLBACK CSound::Monoral(HDSP handle, DWORD channel,
	void *buffer, DWORD length, void *user)
{
	float *data = (float*)buffer;
	int max = length / 4;
	for(int a = 0; a < max; a += 2)
		data[a] = data[a + 1] = ((data[a]) + data[a + 1]) * 0.5f;
}
//----------------------------------------------------------------------------
// �{�[�J���L�����Z���̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetVocalCancel(BOOL bVocalCancel)
{
	if(bVocalCancel)
		m_hVocalCancelDsp = BASS_ChannelSetDSP(m_hStream, &VocalCancel, 0, 1);
	else BASS_ChannelRemoveDSP(m_hStream, m_hVocalCancelDsp);
}
//----------------------------------------------------------------------------
// �{�[�J���L�����Z���p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
void CALLBACK CSound::VocalCancel(HDSP handle, DWORD channel,
	void *buffer, DWORD length, void *user)
{
	float *data = (float*)buffer;
	int max = length / 4;
	for(int a = 0; a < max; a += 2)
		data[a] = data[a + 1] = ((-data[a]) + data[a + 1]) * 0.5f;
}
//----------------------------------------------------------------------------
// ���E����ւ��̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetChangeLR(BOOL bChangeLR)
{
	if(bChangeLR)
		m_hChangeLRDsp = BASS_ChannelSetDSP(m_hStream, &ChangeLR, 0, 2);
	else BASS_ChannelRemoveDSP(m_hStream, m_hChangeLRDsp);
}
//----------------------------------------------------------------------------
// ���E����ւ��p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
void CALLBACK CSound::ChangeLR(HDSP handle, DWORD channel,
	void *buffer, DWORD length, void *user)
{
	float *data = (float*)buffer;
	int max = length / 4;
	float f;
	for(int a = 0; a < max; a += 2) {
		f = data[a];
		data[a] = data[a + 1];
		data[a + 1] = f;
	}
}
//----------------------------------------------------------------------------
// ���̂ݍĐ��̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetOnlyLeft(BOOL bOnlyLeft)
{
	if(bOnlyLeft)
		m_hOnlyLeftDsp = BASS_ChannelSetDSP(m_hStream, &OnlyLeft, 0, 2);
	else BASS_ChannelRemoveDSP(m_hStream, m_hOnlyLeftDsp);
}
//----------------------------------------------------------------------------
// ���̂ݍĐ��p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
void CALLBACK CSound::OnlyLeft(HDSP handle, DWORD channel,
	void *buffer, DWORD length, void *user)
{
	float *data = (float*)buffer;
	int max = length / 4;
	for(int a = 0; a < max; a += 2) data[a + 1] = data[a];
}
//----------------------------------------------------------------------------
// �E�̂ݍĐ��̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetOnlyRight(BOOL bOnlyRight)
{
	if(bOnlyRight)
		m_hOnlyRightDsp = BASS_ChannelSetDSP(m_hStream, &OnlyRight, 0, 2);
	else BASS_ChannelRemoveDSP(m_hStream, m_hOnlyRightDsp);
}
//----------------------------------------------------------------------------
// �E�̂ݍĐ��p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
void CALLBACK CSound::OnlyRight(HDSP handle, DWORD channel,
	void *buffer, DWORD length, void *user)
{
	float *data = (float*)buffer;
	int max = length / 4;
	for(int a = 0; a < max; a += 2) data[a] = data[a + 1];
}
//----------------------------------------------------------------------------
// �m�[�}���C�Y�̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetNormalize(BOOL bNormalize)
{
	if(bNormalize) {
		HSTREAM decoder = BASS_StreamCreateFile(FALSE, m_strCurFile.c_str(), 0,
			0, BASS_SAMPLE_FLOAT | BASS_STREAM_DECODE | BASS_IF_UNICODE);
		if(!decoder) decoder = BASS_APE_StreamCreateFile(FALSE,
			m_strCurFile.c_str(), 0, 0,
			BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT | BASS_IF_UNICODE);
		if(!decoder) decoder = BASS_CD_StreamCreateFile(
			(char*)m_strCurFile.c_str(),
			BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT | BASS_IF_UNICODE);
		if(!decoder) decoder = BASS_FLAC_StreamCreateFile(FALSE,
			m_strCurFile.c_str(), 0, 0,
			BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT | BASS_IF_UNICODE);
		if(!decoder) decoder = BASS_AAC_StreamCreateFile(FALSE,
			m_strCurFile.c_str(), 0, 0,
			BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT | BASS_IF_UNICODE);
		if(!decoder) decoder = BASS_MP4_StreamCreateFile(FALSE,
			m_strCurFile.c_str(), 0, 0,
			BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT | BASS_IF_UNICODE);
		BASS_ChannelSetPosition(decoder, 0, BASS_POS_DECODETO);
		m_peak = 0;
		while(BASS_ChannelIsActive(decoder)) {
			DWORD level = BASS_ChannelGetLevel(decoder);
			int left = LOWORD(level);
			int right = HIWORD(level);
			if(m_peak < left) m_peak = left;
			if(m_peak < right) m_peak = right;
		}
		BASS_StreamFree(decoder);
		if(m_peak > 32767) m_peak = 32767;

		m_hNormalizeDsp = BASS_ChannelSetDSP(m_hStream, &Normalize, &m_peak,
											 3);
	}
	else BASS_ChannelRemoveDSP(m_hStream, m_hNormalizeDsp);
}
//----------------------------------------------------------------------------
// �m�[�}���C�Y�p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
void CALLBACK CSound::Normalize(HDSP handle, DWORD channel,
									   void *buffer, DWORD length, void *user)
{
	int *peak = (int*)user;
	float *data = (float*)buffer;
	int max = length / 4;
	for(int a = 0; a < max; a++) data[a] = data[a] * 32767 / *peak;
}
//----------------------------------------------------------------------------
// �p���̐ݒ�
//----------------------------------------------------------------------------
void CSound::SetPan(int nPan)
{
	m_nPan = nPan;
	m_hPanDsp = BASS_ChannelSetDSP(m_hStream, &Pan, &m_nPan, 4);
}
//----------------------------------------------------------------------------
// �p���p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
void CALLBACK CSound::Pan(HDSP handle, DWORD channel,
									   void *buffer, DWORD length, void *user)
{
	int *pnPan = (int*)user;
	float fPan = *pnPan / 100.0f;
	float *data = (float*)buffer;
	int max = length / 4;
	for(int a = 0; a < max; a += 2) {
		if(fPan > 0.00f) data[a] = data[a] * (1.00f - fPan);
		else data[a + 1] = data[a + 1] * (1.00f + fPan);
	}
}
//----------------------------------------------------------------------------
// ���[�v�p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
void CALLBACK CSound::LoopSyncProc(HSYNC handle, DWORD channel,
	DWORD data, void *user)
{
	CSound* pthis = (CSound*)user;
	CMainWnd* mainWnd = &pthis->GetMainWnd();
 	if(!pthis->OnLoop()) mainWnd->SetFinish(TRUE);
}
//----------------------------------------------------------------------------
// ASIO�p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
DWORD CALLBACK CSound::AsioProc(BOOL input, DWORD channel, void *buffer,
								DWORD length, void *user)
{
	DWORD c = BASS_ChannelGetData(channel, buffer, length);
	if(c == -1) c = 0;
	return c;
}
//----------------------------------------------------------------------------
// WASAPI�p�R�[���o�b�N�֐�
//----------------------------------------------------------------------------
DWORD CALLBACK CSound::WasapiProc(void *buffer, DWORD length, void *user)
{
	CSound* pthis = (CSound*)user;
	DWORD c = BASS_ChannelGetData(pthis->GetMixer(), buffer, length);
	if(c == -1) c = 0;
	return c;
}
//----------------------------------------------------------------------------
DWORD CALLBACK CSound::WriteStream(HSTREAM handle, short *buffer, DWORD length,
	void *user)
{
	CSound* pthis = (CSound*)user;
	short * pBuf = new short[length / 2];
	NSFSDK_Render(pthis->m_hNSF, pBuf, length / 4);
	int max = length / 4;
	for(int i = 0; i < max; i++) {
		buffer[i * 2] = pBuf[i];
		buffer[i * 2 + 1] = pBuf[i];
	}
	delete [] pBuf;

	return length;
}
//----------------------------------------------------------------------------
