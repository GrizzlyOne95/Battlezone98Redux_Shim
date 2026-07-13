/*
 * Entry: 004b1789
 * Name: CStreamingOggSound::Reset
 * Namespace: CStreamingOggSound
 * Signature: T_HRESULT Reset(CStreamingOggSound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CStreamingOggSound::Reset(CStreamingOggSound *this)

{
  undefined4 uVar1;
  int iVar2;
  uint unaff_ESI;
  undefined4 uStack_8;
  
  if (*(int *)this->_padding_ == 0) {
    uVar1 = 0x800401f0;
  }
  else {
    uStack_8 = this;
    if ((this->m_bValid != 0) &&
       (iVar2 = ov_raw_seek(this->m_vf,(ulonglong)unaff_ESI << 0x20), iVar2 != 0)) {
      Trace("  ::Reset() got error %d\n");
    }
    this->m_dwLastPlayPos = 0;
    this->m_dwPlayProgress = 0;
    this->m_dwNextWriteOffset = 0;
    this->m_bFillWithSilence = 0;
    this->m_bitstream = 0;
    this->m_UnpackedSize = 0;
    CSound::RestoreBuffer
              ((CSound *)this,*(IDirectSoundBuffer **)this->_padding_,(bool *)((int)&uStack_8 + 3));
    if ((uStack_8._3_1_ != '\0') &&
       (iVar2 = FillBufferWithSound(this,*(IDirectSoundBuffer **)this->_padding_,0), iVar2 < 0)) {
      return iVar2;
    }
    uVar1 = (**(code **)(**(int **)this->_padding_ + 0x34))(*(int **)this->_padding_,0);
  }
  return uVar1;
}
