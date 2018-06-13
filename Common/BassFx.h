//----------------------------------------------------------------------------
// BassFx.h : bass_fx.dll �̊Ǘ����s��
//----------------------------------------------------------------------------
#ifndef BassFxH
#define BassFxH

#include "Bass.h"
#include "bass_fx.h"
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
//----------------------------------------------------------------------------
// bass_fx.dll �̊Ǘ����s���N���X
//----------------------------------------------------------------------------
class CBassFx : public CBass
{
public: // �֐�

	CBassFx() { }
	virtual ~CBassFx() { }

	virtual void TempoCreate(BOOL bDecode = FALSE) {
		if(bDecode)
			m_hStream = BASS_FX_TempoCreate(m_hStream, BASS_FX_FREESOURCE | BASS_STREAM_DECODE);
		else
			m_hStream = BASS_FX_TempoCreate(m_hStream, BASS_FX_FREESOURCE);
	}
	virtual float GetTempo() {
		float tempo;
		BASS_ChannelGetAttribute(m_hStream, BASS_ATTRIB_TEMPO, &tempo);
		return tempo;
	}
	virtual BOOL SetTempo(float tempo) {
		return BASS_ChannelSetAttribute(m_hStream, BASS_ATTRIB_TEMPO, tempo);
	}
	virtual float GetSampleRate() {
		float samplerate;
		BASS_ChannelGetAttribute(m_hStream, BASS_ATTRIB_TEMPO_FREQ, &samplerate);
		return samplerate;
	}
	virtual BOOL SetSampleRate(float samplerate) {
		return BASS_ChannelSetAttribute(m_hStream, BASS_ATTRIB_TEMPO_FREQ, samplerate);
	}
	virtual float GetPitch() {
		float pitch;
		BASS_ChannelGetAttribute(m_hStream, BASS_ATTRIB_TEMPO_PITCH, &pitch);
		return pitch;
	}
	virtual BOOL SetPitch(float pitch) {
		return BASS_ChannelSetAttribute(m_hStream, BASS_ATTRIB_TEMPO_PITCH, pitch);
	}
	virtual void ReverseCreate()
	{
		m_hStream = BASS_FX_ReverseCreate(m_hStream, 2, BASS_FX_FREESOURCE | BASS_STREAM_DECODE);
	}
	virtual BOOL SetReverse(BOOL bReverse = TRUE)
	{
		DWORD chan = BASS_FX_TempoGetSource(m_hStream);
		return BASS_ChannelSetAttribute(chan, BASS_ATTRIB_REVERSE_DIR, (float)(bReverse ? BASS_FX_RVS_REVERSE : BASS_FX_RVS_FORWARD));
	}

protected: // �����o�ϐ�

};
//----------------------------------------------------------------------------

#endif