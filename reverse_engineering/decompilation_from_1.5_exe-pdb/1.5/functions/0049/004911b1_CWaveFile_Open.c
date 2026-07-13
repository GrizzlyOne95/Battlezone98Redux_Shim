/*
 * Entry: 004911b1
 * Name: CWaveFile::Open
 * Namespace: CWaveFile
 * Signature: T_HRESULT Open(CWaveFile * this, char * param_1, tWAVEFORMATEX * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall
CWaveFile::Open(CWaveFile *this,char *param_1,tWAVEFORMATEX *param_2,ulong param_3)

{
  HMMIO pHVar1;
  HGLOBAL hResData;
  DWORD DVar2;
  LPVOID pvVar3;
  HPSTR pcVar4;
  int iVar5;
  _MMIOINFO local_4c;
  
  this->m_dwFlags = param_3;
  this->m_bIsReadingFromMemory = false;
  if (param_3 == 1) {
    if (param_1 == (char *)0x0) {
      return 0x80070057;
    }
    if (this->m_pwfx != (tWAVEFORMATEX *)0x0) {
      operator_delete__(this->m_pwfx);
      this->m_pwfx = (tWAVEFORMATEX *)0x0;
    }
    pHVar1 = mmioOpenA(param_1,(LPMMIOINFO)0x0,0x10000);
    this->m_hmmio = (HMMIO__ *)pHVar1;
    if (pHVar1 == (HMMIO)0x0) {
      param_3 = (ulong)FindResourceA((HMODULE)0x0,param_1,"WAVE");
      if (((HRSRC)param_3 == (HRSRC)0x0) &&
         (param_3 = (ulong)FindResourceA((HMODULE)0x0,param_1,"WAV"), (HRSRC)param_3 == (HRSRC)0x0))
      {
        return 0x80004005;
      }
      hResData = LoadResource((HMODULE)0x0,(HRSRC)param_3);
      if (hResData == (HGLOBAL)0x0) {
        return 0x80004005;
      }
      DVar2 = SizeofResource((HMODULE)0x0,(HRSRC)param_3);
      if (DVar2 == 0) {
        return 0x80004005;
      }
      pvVar3 = LockResource(hResData);
      if (pvVar3 == (LPVOID)0x0) {
        return 0x80004005;
      }
      pcVar4 = operator_new__(DVar2);
      memcpy(pcVar4,pvVar3,DVar2);
      memset(&local_4c,0,0x48);
      local_4c.fccIOProc = 0x204d454d;
      local_4c.cchBuffer = DVar2;
      local_4c.pchBuffer = pcVar4;
      pHVar1 = mmioOpenA((LPSTR)0x0,&local_4c,0x10000);
      this->m_hmmio = (HMMIO__ *)pHVar1;
    }
    iVar5 = ReadMMIO(this);
    if (-1 < iVar5) {
      iVar5 = ResetFile(this);
      if (iVar5 < 0) {
        return 0x80004005;
      }
      this->m_dwSize = (this->m_ck).cksize;
      return iVar5;
    }
  }
  else {
    pHVar1 = mmioOpenA(param_1,(LPMMIOINFO)0x0,0x11002);
    this->m_hmmio = (HMMIO__ *)pHVar1;
    if (pHVar1 == (HMMIO)0x0) {
      return 0x80004005;
    }
    iVar5 = WriteMMIO(this,param_2);
    if (-1 < iVar5) {
      iVar5 = ResetFile(this);
      if (iVar5 < 0) {
        return 0x80004005;
      }
      return iVar5;
    }
  }
  mmioClose((HMMIO)this->m_hmmio,0);
  return 0x80004005;
}
