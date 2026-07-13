/*
 * Entry: 004b15fe
 * Name: CStreamingOggSound::CStreamingOggSound
 * Namespace: CStreamingOggSound
 * Signature: CStreamingOggSound * CStreamingOggSound(CStreamingOggSound * this, IDirectSoundBuffer * param_1, ulong param_2, OggVorbis_File * param_3, ulong param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CStreamingOggSound * __thiscall
CStreamingOggSound::CStreamingOggSound
          (CStreamingOggSound *this,IDirectSoundBuffer *param_1,ulong param_2,
          OggVorbis_File *param_3,ulong param_4)

{
  CSound::CSound((CSound *)this,&param_1,param_2,1,(CWaveFile *)0x0);
  this->m_dwNotifySize = param_4;
  this->m_vf = param_3;
  this->_padding_ = (int)&_vftable_;
  this->m_dwLastPlayPos = 0;
  this->m_dwPlayProgress = 0;
  this->m_dwNextWriteOffset = 0;
  this->m_bFillWithSilence = 0;
  this->m_bitstream = 0;
  this->m_UnpackedSize = 0;
  this->m_bValid = 1;
  FillBufferWithSound(this,*(IDirectSoundBuffer **)this->_padding_,0);
  return this;
}
