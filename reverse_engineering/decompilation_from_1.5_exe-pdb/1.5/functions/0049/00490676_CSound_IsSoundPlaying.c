/*
 * Entry: 00490676
 * Name: CSound::IsSoundPlaying
 * Namespace: CSound
 * Signature: bool IsSoundPlaying(CSound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall CSound::IsSoundPlaying(CSound *this)

{
  IDirectSoundBuffer *pIVar1;
  uint uVar2;
  undefined4 local_c;
  undefined4 uStack_8;
  
  uStack_8 = (uint)this & 0xffffff;
  if (this->m_apDSBuffer == (IDirectSoundBuffer **)0x0) {
    uStack_8._3_1_ = 0;
  }
  else {
    uVar2 = 0;
    if (this->m_dwNumBuffers != 0) {
      do {
        if (this->m_apDSBuffer[uVar2] != (IDirectSoundBuffer *)0x0) {
          local_c = 0;
          pIVar1 = this->m_apDSBuffer[uVar2];
          (**(code **)((int)*pIVar1 + 0x24))(pIVar1,&local_c);
          uStack_8 = CONCAT13(uStack_8._3_1_ | (byte)local_c & 1,(undefined3)uStack_8);
        }
        uVar2 = uVar2 + 1;
      } while (uVar2 < this->m_dwNumBuffers);
    }
  }
  return (bool)uStack_8._3_1_;
}
