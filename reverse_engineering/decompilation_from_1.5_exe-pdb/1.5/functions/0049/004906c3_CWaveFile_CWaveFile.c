/*
 * Entry: 004906c3
 * Name: CWaveFile::CWaveFile
 * Namespace: CWaveFile
 * Signature: CWaveFile * CWaveFile(CWaveFile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CWaveFile * __thiscall CWaveFile::CWaveFile(CWaveFile *this)

{
  this->m_pwfx = (tWAVEFORMATEX *)0x0;
  this->m_hmmio = (HMMIO__ *)0x0;
  this->m_dwSize = 0;
  this->m_bIsReadingFromMemory = false;
  return this;
}
