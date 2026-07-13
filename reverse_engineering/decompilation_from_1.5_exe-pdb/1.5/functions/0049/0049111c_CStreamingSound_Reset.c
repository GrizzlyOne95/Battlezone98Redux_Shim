/*
 * Entry: 0049111c
 * Name: CStreamingSound::Reset
 * Namespace: CStreamingSound
 * Signature: T_HRESULT Reset(CStreamingSound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CStreamingSound::Reset(CStreamingSound *this)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uStack_8;
  
  if ((*(int *)this->_padding_ != 0) && (this->_padding_ != 0)) {
    this->m_dwLastPlayPos = 0;
    this->m_dwPlayProgress = 0;
    this->m_dwNextWriteOffset = 0;
    this->m_bFillNextNotificationWithSilence = false;
    uStack_8 = (uint)this & 0xffffff;
    iVar1 = CSound::RestoreBuffer
                      ((CSound *)this,*(IDirectSoundBuffer **)this->_padding_,
                       (bool *)((int)&uStack_8 + 3));
    if ((iVar1 < 0) ||
       ((uStack_8._3_1_ != '\0' &&
        (iVar1 = CSound::FillBufferWithSound
                           ((CSound *)this,*(IDirectSoundBuffer **)this->_padding_,false), iVar1 < 0
        )))) {
      uVar2 = 0x80004005;
    }
    else {
      CWaveFile::ResetFile((CWaveFile *)this->_padding_);
      uVar2 = (**(code **)(**(int **)this->_padding_ + 0x34))(*(int **)this->_padding_,0);
    }
    return uVar2;
  }
  return 0x800401f0;
}
