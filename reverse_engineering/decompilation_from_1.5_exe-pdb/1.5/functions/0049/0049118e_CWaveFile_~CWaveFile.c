/*
 * Entry: 0049118e
 * Name: CWaveFile::~CWaveFile
 * Namespace: CWaveFile
 * Signature: void ~CWaveFile(CWaveFile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CWaveFile::~CWaveFile(CWaveFile *this)

{
  Close(this);
  if ((this->m_bIsReadingFromMemory == false) && (this->m_pwfx != (tWAVEFORMATEX *)0x0)) {
    operator_delete__(this->m_pwfx);
    this->m_pwfx = (tWAVEFORMATEX *)0x0;
  }
  return;
}
