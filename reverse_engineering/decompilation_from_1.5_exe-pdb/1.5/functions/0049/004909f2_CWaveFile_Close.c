/*
 * Entry: 004909f2
 * Name: CWaveFile::Close
 * Namespace: CWaveFile
 * Signature: T_HRESULT Close(CWaveFile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CWaveFile::Close(CWaveFile *this)

{
  _MMIOINFO *pmmioinfo;
  _MMCKINFO *pmmcki;
  _MMCKINFO *pmmcki_00;
  HMMIO pHVar1;
  MMRESULT MVar2;
  undefined4 uVar3;
  CWaveFile *local_4;
  
  local_4 = this;
  if (this->m_dwFlags == 1) {
    mmioClose((HMMIO)this->m_hmmio,0);
    this->m_hmmio = (HMMIO__ *)0x0;
LAB_00490ad6:
    uVar3 = 0;
  }
  else {
    pHVar1 = (HMMIO)this->m_hmmio;
    pmmioinfo = &this->m_mmioinfoOut;
    pmmioinfo->dwFlags = pmmioinfo->dwFlags | 0x10000000;
    if (pHVar1 == (HMMIO)0x0) {
      return 0x800401f0;
    }
    MVar2 = mmioSetInfo(pHVar1,(LPCMMIOINFO)pmmioinfo,0);
    if (MVar2 == 0) {
      pmmcki = &this->m_ck;
      MVar2 = mmioAscend((HMMIO)this->m_hmmio,(LPMMCKINFO)pmmcki,0);
      if (MVar2 == 0) {
        pmmcki_00 = &this->m_ckRiff;
        MVar2 = mmioAscend((HMMIO)this->m_hmmio,(LPMMCKINFO)pmmcki_00,0);
        if (MVar2 == 0) {
          mmioSeek((HMMIO)this->m_hmmio,0,0);
          MVar2 = mmioDescend((HMMIO)this->m_hmmio,(LPMMCKINFO)pmmcki_00,(MMCKINFO *)0x0,0);
          if (MVar2 == 0) {
            pHVar1 = (HMMIO)this->m_hmmio;
            pmmcki->ckid = 0x74636166;
            MVar2 = mmioDescend(pHVar1,(LPMMCKINFO)pmmcki,(MMCKINFO *)pmmcki_00,0x10);
            if (MVar2 == 0) {
              local_4 = (CWaveFile *)0x0;
              mmioWrite((HMMIO)this->m_hmmio,(char *)&local_4,4);
              mmioAscend((HMMIO)this->m_hmmio,(LPMMCKINFO)pmmcki,0);
            }
            MVar2 = mmioAscend((HMMIO)this->m_hmmio,(LPMMCKINFO)pmmcki_00,0);
            if (MVar2 == 0) {
              mmioClose((HMMIO)this->m_hmmio,0);
              this->m_hmmio = (HMMIO__ *)0x0;
              goto LAB_00490ad6;
            }
          }
        }
      }
    }
    uVar3 = 0x80004005;
  }
  return uVar3;
}
