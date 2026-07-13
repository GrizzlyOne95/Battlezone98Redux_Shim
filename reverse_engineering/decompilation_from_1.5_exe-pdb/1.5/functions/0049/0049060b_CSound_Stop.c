/*
 * Entry: 0049060b
 * Name: CSound::Stop
 * Namespace: CSound
 * Signature: T_HRESULT Stop(CSound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall CSound::Stop(CSound *this)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = 0;
  if (this->m_apDSBuffer == (IDirectSoundBuffer **)0x0) {
    uVar2 = 0x800401f0;
  }
  else {
    uVar3 = 0;
    if (this->m_dwNumBuffers != 0) {
      do {
        uVar1 = (**(code **)((int)*this->m_apDSBuffer[uVar3] + 0x48))(this->m_apDSBuffer[uVar3]);
        uVar2 = uVar2 | uVar1;
        uVar3 = uVar3 + 1;
      } while (uVar3 < this->m_dwNumBuffers);
    }
  }
  return uVar2;
}
