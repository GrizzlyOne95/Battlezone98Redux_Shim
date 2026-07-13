/*
 * Entry: 00490558
 * Name: CSound::GetFreeBuffer
 * Namespace: CSound
 * Signature: IDirectSoundBuffer * GetFreeBuffer(CSound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

IDirectSoundBuffer * __thiscall CSound::GetFreeBuffer(CSound *this)

{
  IDirectSoundBuffer *pIVar1;
  uint uVar2;
  ulong uVar3;
  bool bVar4;
  CSound *local_8;
  
  if (this->m_apDSBuffer == (IDirectSoundBuffer **)0x0) {
    pIVar1 = (IDirectSoundBuffer *)0x0;
  }
  else {
    uVar3 = 0;
    bVar4 = this->m_dwNumBuffers == 0;
    local_8 = this;
    if (this->m_dwNumBuffers != 0) {
      do {
        if (this->m_apDSBuffer[uVar3] != (IDirectSoundBuffer *)0x0) {
          local_8 = (CSound *)0x0;
          pIVar1 = this->m_apDSBuffer[uVar3];
          (**(code **)((int)*pIVar1 + 0x24))(pIVar1,&local_8);
          if (((uint)local_8 & 1) == 0) break;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < this->m_dwNumBuffers);
      bVar4 = uVar3 == this->m_dwNumBuffers;
    }
    if (bVar4) {
      uVar2 = rand();
      pIVar1 = this->m_apDSBuffer[uVar2 % this->m_dwNumBuffers];
    }
    else {
      pIVar1 = this->m_apDSBuffer[uVar3];
    }
  }
  return pIVar1;
}
