/*
 * Entry: 004908d7
 * Name: CWaveFile::Read
 * Namespace: CWaveFile
 * Signature: T_HRESULT Read(CWaveFile * this, uchar * param_1, ulong param_2, ulong * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CWaveFile::Read(CWaveFile *this,uchar *param_1,ulong param_2,ulong *param_3)

{
  uchar uVar1;
  uchar *puVar2;
  uint uVar3;
  MMRESULT MVar4;
  uint uVar5;
  _MMIOINFO local_4c;
  
  if (this->m_bIsReadingFromMemory == false) {
    uVar5 = 0;
    if (this->m_hmmio != (HMMIO__ *)0x0) {
      if ((param_1 == (uchar *)0x0) || (param_3 == (ulong *)0x0)) {
        return 0x80070057;
      }
      *param_3 = 0;
      MVar4 = mmioGetInfo((HMMIO)this->m_hmmio,&local_4c,0);
      if (MVar4 == 0) {
        uVar3 = (this->m_ck).cksize;
        if (uVar3 < param_2) {
          param_2 = uVar3;
        }
        (this->m_ck).cksize = uVar3 - param_2;
        if (param_2 != 0) {
          do {
            if (local_4c.pchNext == local_4c.pchEndRead) {
              MVar4 = mmioAdvance((HMMIO)this->m_hmmio,&local_4c,0);
              if (MVar4 != 0) {
                return 0x80004005;
              }
              if (local_4c.pchNext == local_4c.pchEndRead) {
                return 0x80004005;
              }
            }
            uVar1 = *local_4c.pchNext;
            local_4c.pchNext = local_4c.pchNext + 1;
            param_1[uVar5] = uVar1;
            uVar5 = uVar5 + 1;
          } while (uVar5 < param_2);
        }
        MVar4 = mmioSetInfo((HMMIO)this->m_hmmio,&local_4c,0);
        if (MVar4 == 0) {
          *param_3 = param_2;
          return 0;
        }
      }
      return 0x80004005;
    }
  }
  else if (this->m_pbDataCur != (uchar *)0x0) {
    if (param_3 != (ulong *)0x0) {
      *param_3 = 0;
    }
    puVar2 = this->m_pbDataCur;
    if (this->m_pbData + this->m_ulDataSize < puVar2 + param_2) {
      param_2 = (ulong)(this->m_pbData + (this->m_ulDataSize - (int)puVar2));
    }
    memcpy(param_1,puVar2,param_2);
    if (param_3 != (ulong *)0x0) {
      *param_3 = param_2;
    }
    return 0;
  }
  return 0x800401f0;
}
