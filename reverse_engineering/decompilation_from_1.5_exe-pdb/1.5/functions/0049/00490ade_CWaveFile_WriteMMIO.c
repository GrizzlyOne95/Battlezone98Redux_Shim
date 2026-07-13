/*
 * Entry: 00490ade
 * Name: CWaveFile::WriteMMIO
 * Namespace: CWaveFile
 * Signature: T_HRESULT WriteMMIO(CWaveFile * this, tWAVEFORMATEX * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CWaveFile::WriteMMIO(CWaveFile *this,tWAVEFORMATEX *param_1)

{
  HMMIO pHVar1;
  MMRESULT MVar2;
  LONG LVar3;
  _MMCKINFO local_1c;
  char local_8 [4];
  
  local_8[0] = -1;
  local_8[1] = -1;
  local_8[2] = -1;
  local_8[3] = -1;
  (this->m_ckRiff).cksize = 0;
  pHVar1 = (HMMIO)this->m_hmmio;
  (this->m_ckRiff).fccType = 0x45564157;
  MVar2 = mmioCreateChunk(pHVar1,(LPMMCKINFO)&this->m_ckRiff,0x20);
  if (MVar2 != 0) {
    return 0x80004005;
  }
  pHVar1 = (HMMIO)this->m_hmmio;
  (this->m_ck).ckid = 0x20746d66;
  (this->m_ck).cksize = 0x10;
  MVar2 = mmioCreateChunk(pHVar1,(LPMMCKINFO)&this->m_ck,0);
  if (MVar2 == 0) {
    if (param_1->wFormatTag == 1) {
      LVar3 = mmioWrite((HMMIO)this->m_hmmio,(char *)param_1,0x10);
      if (LVar3 != 0x10) {
        return 0x80004005;
      }
    }
    else {
      LVar3 = mmioWrite((HMMIO)this->m_hmmio,(char *)param_1,param_1->cbSize + 0x12);
      if (LVar3 != param_1->cbSize + 0x12) {
        return 0x80004005;
      }
    }
    MVar2 = mmioAscend((HMMIO)this->m_hmmio,(LPMMCKINFO)&this->m_ck,0);
    if (MVar2 == 0) {
      local_1c.cksize = 0;
      local_1c.ckid = 0x74636166;
      MVar2 = mmioCreateChunk((HMMIO)this->m_hmmio,&local_1c,0);
      if ((MVar2 == 0) && (LVar3 = mmioWrite((HMMIO)this->m_hmmio,local_8,4), LVar3 == 4)) {
        MVar2 = mmioAscend((HMMIO)this->m_hmmio,&local_1c,0);
        return -(uint)(MVar2 != 0) & 0x80004005;
      }
    }
    return 0x80004005;
  }
  return 0x80004005;
}
