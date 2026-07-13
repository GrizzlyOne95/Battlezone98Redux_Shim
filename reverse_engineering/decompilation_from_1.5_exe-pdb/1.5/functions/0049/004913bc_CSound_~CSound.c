/*
 * Entry: 004913bc
 * Name: CSound::~CSound
 * Namespace: CSound
 * Signature: void ~CSound(CSound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CSound::~CSound(CSound *this)

{
  IDirectSoundBuffer *pIVar1;
  CWaveFile *this_00;
  uint uVar2;
  
  uVar2 = 0;
  this->_padding_ = (int)&_vftable_;
  if (this->m_dwNumBuffers != 0) {
    do {
      if (this->m_apDSBuffer[uVar2] != (IDirectSoundBuffer *)0x0) {
        pIVar1 = this->m_apDSBuffer[uVar2];
        (**(code **)((int)*pIVar1 + 8))(pIVar1);
        this->m_apDSBuffer[uVar2] = (IDirectSoundBuffer *)0x0;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < this->m_dwNumBuffers);
  }
  if (this->m_apDSBuffer != (IDirectSoundBuffer **)0x0) {
    operator_delete__(this->m_apDSBuffer);
    this->m_apDSBuffer = (IDirectSoundBuffer **)0x0;
  }
  this_00 = this->m_pWaveFile;
  if (this_00 != (CWaveFile *)0x0) {
    CWaveFile::~CWaveFile(this_00);
    operator_delete(this_00);
    this->m_pWaveFile = (CWaveFile *)0x0;
  }
  return;
}
