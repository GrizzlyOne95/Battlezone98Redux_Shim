/*
 * Entry: 00490842
 * Name: CWaveFile::ResetFile
 * Namespace: CWaveFile
 * Signature: T_HRESULT ResetFile(CWaveFile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CWaveFile::ResetFile(CWaveFile *this)

{
  HMMIO pHVar1;
  undefined4 uVar2;
  LONG LVar3;
  MMRESULT MVar4;
  
  if (this->m_bIsReadingFromMemory == false) {
    pHVar1 = (HMMIO)this->m_hmmio;
    if (pHVar1 == (HMMIO)0x0) {
      return 0x800401f0;
    }
    if (this->m_dwFlags == 1) {
      LVar3 = mmioSeek(pHVar1,(this->m_ckRiff).dwDataOffset + 4,0);
      if (LVar3 != -1) {
        pHVar1 = (HMMIO)this->m_hmmio;
        (this->m_ck).ckid = 0x61746164;
        MVar4 = mmioDescend(pHVar1,(LPMMCKINFO)&this->m_ck,(MMCKINFO *)&this->m_ckRiff,0x10);
LAB_004908a9:
        if (MVar4 == 0) goto LAB_0049085c;
      }
    }
    else {
      (this->m_ck).ckid = 0x61746164;
      (this->m_ck).cksize = 0;
      MVar4 = mmioCreateChunk(pHVar1,(LPMMCKINFO)&this->m_ck,0);
      if (MVar4 == 0) {
        MVar4 = mmioGetInfo((HMMIO)this->m_hmmio,(LPMMIOINFO)&this->m_mmioinfoOut,0);
        goto LAB_004908a9;
      }
    }
    uVar2 = 0x80004005;
  }
  else {
    this->m_pbDataCur = this->m_pbData;
LAB_0049085c:
    uVar2 = 0;
  }
  return uVar2;
}
