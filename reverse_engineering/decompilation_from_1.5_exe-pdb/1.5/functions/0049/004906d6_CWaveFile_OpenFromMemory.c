/*
 * Entry: 004906d6
 * Name: CWaveFile::OpenFromMemory
 * Namespace: CWaveFile
 * Signature: T_HRESULT OpenFromMemory(CWaveFile * this, uchar * param_1, ulong param_2, tWAVEFORMATEX * param_3, ulong param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
CWaveFile::OpenFromMemory
          (CWaveFile *this,uchar *param_1,ulong param_2,tWAVEFORMATEX *param_3,ulong param_4)

{
  this->m_pwfx = param_3;
  this->m_ulDataSize = param_2;
  this->m_pbData = param_1;
  this->m_pbDataCur = param_1;
  this->m_bIsReadingFromMemory = true;
  return -(uint)(param_4 != 1) & 0x80004001;
}
