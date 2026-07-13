/*
 * Entry: 0049fd66
 * Name: CSound::GetDSBuffer
 * Namespace: CSound
 * Signature: IDirectSoundBuffer * * GetDSBuffer(CSound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

IDirectSoundBuffer ** __thiscall CSound::GetDSBuffer(CSound *this)

{
  return this->m_apDSBuffer;
}
