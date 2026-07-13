/*
 * Entry: 0049141b
 * Name: CStreamingSound::CStreamingSound
 * Namespace: CStreamingSound
 * Signature: CStreamingSound * CStreamingSound(CStreamingSound * this, IDirectSoundBuffer * param_1, ulong param_2, CWaveFile * param_3, ulong param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CStreamingSound * __thiscall
CStreamingSound::CStreamingSound
          (CStreamingSound *this,IDirectSoundBuffer *param_1,ulong param_2,CWaveFile *param_3,
          ulong param_4)

{
  CSound::CSound((CSound *)this,&param_1,param_2,1,param_3);
  this->m_dwLastPlayPos = 0;
  this->m_dwPlayProgress = 0;
  this->m_dwNextWriteOffset = 0;
  this->m_bFillNextNotificationWithSilence = false;
  this->_padding_ = (int)&_vftable_;
  this->m_dwNotifySize = param_4;
  return this;
}
