/*
 * Entry: 0049070e
 * Name: CWaveFile::ReadMMIO
 * Namespace: CWaveFile
 * Signature: T_HRESULT ReadMMIO(CWaveFile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CWaveFile::ReadMMIO(CWaveFile *this)

{
  _MMCKINFO *pmmcki;
  MMRESULT MVar1;
  LONG LVar2;
  tWAVEFORMATEX *ptVar3;
  uint uVar4;
  _MMCKINFO local_2c;
  undefined4 local_18;
  ulong uStack_14;
  ulong uStack_10;
  undefined4 uStack_c;
  uint local_8;
  
  pmmcki = &this->m_ckRiff;
  this->m_pwfx = (tWAVEFORMATEX *)0x0;
  MVar1 = mmioDescend((HMMIO)this->m_hmmio,(LPMMCKINFO)pmmcki,(MMCKINFO *)0x0,0);
  if (MVar1 != 0) {
    return 0x80004005;
  }
  if (pmmcki->ckid != 0x46464952) {
    return 0x80004005;
  }
  if ((this->m_ckRiff).fccType != 0x45564157) {
    return 0x80004005;
  }
  local_2c.ckid = 0x20746d66;
  MVar1 = mmioDescend((HMMIO)this->m_hmmio,&local_2c,(MMCKINFO *)pmmcki,0x10);
  if (MVar1 != 0) {
    return 0x80004005;
  }
  if (local_2c.cksize < 0x10) {
    return 0x80004005;
  }
  LVar2 = mmioRead((HMMIO)this->m_hmmio,(HPSTR)&local_18,0x10);
  if (LVar2 != 0x10) {
    return 0x80004005;
  }
  if ((short)local_18 == 1) {
    ptVar3 = operator_new__(0x12);
    this->m_pwfx = ptVar3;
    if (ptVar3 == (tWAVEFORMATEX *)0x0) {
      return 0x80004005;
    }
    ptVar3->wFormatTag = (short)local_18;
    ptVar3->nChannels = local_18._2_2_;
    ptVar3->nSamplesPerSec = uStack_14;
    ptVar3->nAvgBytesPerSec = uStack_10;
    ptVar3->nBlockAlign = (undefined2)uStack_c;
    ptVar3->wBitsPerSample = uStack_c._2_2_;
    this->m_pwfx->cbSize = 0;
  }
  else {
    local_8 = 0;
    LVar2 = mmioRead((HMMIO)this->m_hmmio,(HPSTR)&local_8,2);
    if (LVar2 != 2) {
      return 0x80004005;
    }
    ptVar3 = operator_new__((local_8 & 0xffff) + 0x12);
    this->m_pwfx = ptVar3;
    if (ptVar3 == (tWAVEFORMATEX *)0x0) {
      return 0x80004005;
    }
    ptVar3->wFormatTag = (short)local_18;
    ptVar3->nChannels = local_18._2_2_;
    ptVar3->nSamplesPerSec = uStack_14;
    ptVar3->nAvgBytesPerSec = uStack_10;
    ptVar3->nBlockAlign = (undefined2)uStack_c;
    ptVar3->wBitsPerSample = uStack_c._2_2_;
    this->m_pwfx->cbSize = (ushort)local_8;
    uVar4 = mmioRead((HMMIO)this->m_hmmio,(HPSTR)(this->m_pwfx + 1),local_8 & 0xffff);
    if (uVar4 != (local_8 & 0xffff)) goto LAB_00490824;
  }
  MVar1 = mmioAscend((HMMIO)this->m_hmmio,&local_2c,0);
  if (MVar1 == 0) {
    return 0;
  }
LAB_00490824:
  if (this->m_pwfx != (tWAVEFORMATEX *)0x0) {
    operator_delete(this->m_pwfx);
    this->m_pwfx = (tWAVEFORMATEX *)0x0;
  }
  return 0x80004005;
}
