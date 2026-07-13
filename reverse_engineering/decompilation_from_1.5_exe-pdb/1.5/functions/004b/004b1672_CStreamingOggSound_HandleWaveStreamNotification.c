/*
 * Entry: 004b1672
 * Name: CStreamingOggSound::HandleWaveStreamNotification
 * Namespace: CStreamingOggSound
 * Signature: T_HRESULT HandleWaveStreamNotification(CStreamingOggSound * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
CStreamingOggSound::HandleWaveStreamNotification(CStreamingOggSound *this,int param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_1c [4];
  uint local_18;
  int local_14;
  ulong local_10;
  void *local_c;
  bool local_5;
  
  local_c = (void *)0x0;
  local_14 = 0;
  if ((undefined4 *)this->_padding_ == (undefined4 *)0x0) {
    iVar3 = -0x7ffbfe10;
  }
  else {
    iVar3 = CSound::RestoreBuffer((CSound *)this,*(IDirectSoundBuffer **)this->_padding_,&local_5);
    if (-1 < iVar3) {
      if (local_5 == false) {
        piVar1 = *(int **)this->_padding_;
        iVar3 = (**(code **)(*piVar1 + 0x2c))
                          (piVar1,this->m_dwNextWriteOffset,this->m_dwNotifySize,&local_c,&local_10,
                           &local_14,local_1c);
        if (iVar3 < 0) {
          return iVar3;
        }
        if ((local_c == (void *)0x0) || (local_14 != 0)) {
          return 0x8000ffff;
        }
        DecodeToBuffer(this,local_c,local_10,param_1);
        (**(code **)(**(int **)this->_padding_ + 0x4c))
                  (*(int **)this->_padding_,local_c,local_10,0,0);
        iVar3 = (**(code **)(**(int **)this->_padding_ + 0x10))
                          (*(int **)this->_padding_,&local_18,0);
        if (iVar3 < 0) {
          return iVar3;
        }
        uVar2 = this->m_dwLastPlayPos;
        if (local_18 < uVar2) {
          iVar3 = this->_padding_ - uVar2;
        }
        else {
          iVar3 = -uVar2;
        }
        this->m_dwPlayProgress = this->m_dwPlayProgress + iVar3 + local_18;
        this->m_dwLastPlayPos = local_18;
        if ((this->m_bFillWithSilence != 0) && (this->m_UnpackedSize <= this->m_dwPlayProgress)) {
          (**(code **)(**(int **)this->_padding_ + 0x48))(*(int **)this->_padding_);
        }
        this->m_dwNextWriteOffset = (this->m_dwNextWriteOffset + local_10) % (uint)this->_padding_;
      }
      else {
        iVar3 = FillBufferWithSound(this,*(IDirectSoundBuffer **)this->_padding_,0);
        if (iVar3 < 0) {
          return iVar3;
        }
      }
      iVar3 = 0;
    }
  }
  return iVar3;
}
