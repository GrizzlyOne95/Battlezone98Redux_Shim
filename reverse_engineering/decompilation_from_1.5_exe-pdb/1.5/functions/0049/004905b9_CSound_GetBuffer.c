/*
 * Entry: 004905b9
 * Name: CSound::GetBuffer
 * Namespace: CSound
 * Signature: IDirectSoundBuffer * GetBuffer(CSound * this, ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

IDirectSoundBuffer * __thiscall CSound::GetBuffer(CSound *this,ulong param_1)

{
  IDirectSoundBuffer *pIVar1;
  
  if ((this->m_apDSBuffer == (IDirectSoundBuffer **)0x0) || (this->m_dwNumBuffers <= param_1)) {
    pIVar1 = (IDirectSoundBuffer *)0x0;
  }
  else {
    pIVar1 = this->m_apDSBuffer[param_1];
  }
  return pIVar1;
}
