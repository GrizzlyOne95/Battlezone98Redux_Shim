/*
 * Entry: 00490bcf
 * Name: CWaveFile::Write
 * Namespace: CWaveFile
 * Signature: T_HRESULT Write(CWaveFile * this, uint param_1, uchar * param_2, uint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CWaveFile::Write(CWaveFile *this,uint param_1,uchar *param_2,uint *param_3)

{
  _MMIOINFO *pmmioinfo;
  char **ppcVar1;
  undefined4 uVar2;
  MMRESULT MVar3;
  uint uVar4;
  
  uVar4 = 0;
  if (this->m_bIsReadingFromMemory == false) {
    if (this->m_hmmio == (HMMIO__ *)0x0) {
      uVar2 = 0x800401f0;
    }
    else if ((param_3 == (uint *)0x0) || (param_2 == (uchar *)0x0)) {
      uVar2 = 0x80070057;
    }
    else {
      *param_3 = 0;
      if (param_1 != 0) {
        do {
          if ((this->m_mmioinfoOut).pchNext == (this->m_mmioinfoOut).pchEndWrite) {
            pmmioinfo = &this->m_mmioinfoOut;
            pmmioinfo->dwFlags = pmmioinfo->dwFlags | 0x10000000;
            MVar3 = mmioAdvance((HMMIO)this->m_hmmio,(LPMMIOINFO)pmmioinfo,1);
            if (MVar3 != 0) {
              return 0x80004005;
            }
          }
          *(this->m_mmioinfoOut).pchNext = param_2[uVar4];
          ppcVar1 = &(this->m_mmioinfoOut).pchNext;
          *ppcVar1 = *ppcVar1 + 1;
          *param_3 = *param_3 + 1;
          uVar4 = uVar4 + 1;
        } while (uVar4 < param_1);
      }
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0x80004001;
  }
  return uVar2;
}
