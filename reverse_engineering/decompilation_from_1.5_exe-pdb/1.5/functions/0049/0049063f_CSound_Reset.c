/*
 * Entry: 0049063f
 * Name: CSound::Reset
 * Namespace: CSound
 * Signature: T_HRESULT Reset(CSound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CSound::Reset(CSound *this)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  if (this->m_apDSBuffer == (IDirectSoundBuffer **)0x0) {
    return 0x800401f0;
  }
  uVar2 = 0;
  uVar3 = 0;
  if (this->m_dwNumBuffers != 0) {
    do {
      uVar1 = (**(code **)((int)*this->m_apDSBuffer[uVar3] + 0x34))(this->m_apDSBuffer[uVar3],0);
      uVar2 = uVar2 | uVar1;
      uVar3 = uVar3 + 1;
    } while (uVar3 < this->m_dwNumBuffers);
  }
  return uVar2;
}
