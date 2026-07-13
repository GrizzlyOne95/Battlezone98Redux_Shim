/*
 * Entry: 00490f46
 * Name: CStreamingSound::HandleWaveStreamNotification
 * Namespace: CStreamingSound
 * Signature: T_HRESULT HandleWaveStreamNotification(CStreamingSound * this, bool param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall
CStreamingSound::HandleWaveStreamNotification(CStreamingSound *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined1 local_20 [4];
  uint local_1c;
  int local_18;
  uint local_14;
  uchar *local_10;
  ulong local_c;
  bool local_5;
  
  local_10 = (uchar *)0x0;
  local_18 = 0;
  if (((undefined4 *)this->_padding_ == (undefined4 *)0x0) || (this->_padding_ == 0)) {
    return 0x800401f0;
  }
  local_5 = false;
  iVar2 = CSound::RestoreBuffer((CSound *)this,*(IDirectSoundBuffer **)this->_padding_,&local_5);
  if (-1 < iVar2) {
    if (local_5 == false) {
      piVar1 = *(int **)this->_padding_;
      iVar2 = (**(code **)(*piVar1 + 0x2c))
                        (piVar1,this->m_dwNextWriteOffset,this->m_dwNotifySize,&local_10,&local_c,
                         &local_18,local_20);
      if (-1 < iVar2) {
        if (local_18 != 0) {
          return 0x8000ffff;
        }
        if (this->m_bFillNextNotificationWithSilence == false) {
          iVar2 = CWaveFile::Read((CWaveFile *)this->_padding_,local_10,local_c,&local_14);
          if (iVar2 < 0) {
            return 0x80004005;
          }
        }
        else {
          memset(local_10,(*(short *)(*(int *)this->_padding_ + 0xe) != 8) - 1U & 0x80,local_c);
          local_14 = local_c;
        }
        if (local_14 < local_c) {
          uVar3 = local_14;
          if (param_1) {
            do {
              iVar2 = CWaveFile::ResetFile((CWaveFile *)this->_padding_);
              if (iVar2 < 0) {
                return 0x80004005;
              }
              iVar2 = CWaveFile::Read((CWaveFile *)this->_padding_,local_10 + uVar3,local_c - uVar3,
                                      &local_14);
              if (iVar2 < 0) {
                return 0x80004005;
              }
              uVar3 = uVar3 + local_14;
            } while (uVar3 < local_c);
          }
          else {
            memset(local_10 + local_14,(*(short *)(*(int *)this->_padding_ + 0xe) != 8) - 1U & 0x80,
                   local_c - local_14);
            this->m_bFillNextNotificationWithSilence = true;
          }
        }
        (**(code **)(**(int **)this->_padding_ + 0x4c))
                  (*(int **)this->_padding_,local_10,local_c,0,0);
        iVar2 = (**(code **)(**(int **)this->_padding_ + 0x10))
                          (*(int **)this->_padding_,&local_1c,0);
        if (-1 < iVar2) {
          uVar3 = this->m_dwLastPlayPos;
          if (local_1c < uVar3) {
            iVar2 = this->_padding_ - uVar3;
          }
          else {
            iVar2 = -uVar3;
          }
          this->m_dwPlayProgress = this->m_dwPlayProgress + iVar2 + local_1c;
          this->m_dwLastPlayPos = local_1c;
          if ((this->m_bFillNextNotificationWithSilence != false) &&
             (*(uint *)(this->_padding_ + 0x30) <= this->m_dwPlayProgress)) {
            (**(code **)(**(int **)this->_padding_ + 0x48))(*(int **)this->_padding_);
          }
          this->m_dwNextWriteOffset = (this->m_dwNextWriteOffset + local_c) % (uint)this->_padding_;
          return 0;
        }
      }
    }
    else {
      iVar2 = CSound::FillBufferWithSound
                        ((CSound *)this,*(IDirectSoundBuffer **)this->_padding_,false);
      if (-1 < iVar2) {
        return 0;
      }
    }
  }
  return 0x80004005;
}
