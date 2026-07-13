/*
 * Entry: 00471978
 * Name: CDInitVolume
 * Namespace: Global
 * Signature: int CDInitVolume(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl CDInitVolume(void)

{
  bool bVar1;
  UINT UVar2;
  MMRESULT MVar3;
  UINT_PTR UVar4;
  UINT_PTR local_40;
  tagAUXCAPSA local_38;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_40 = 0xffffffff;
  UVar4 = 0;
  bVar1 = false;
  UVar2 = auxGetNumDevs();
  if (0 < (int)UVar2) {
    do {
      if (bVar1) {
        return local_40;
      }
      MVar3 = auxGetDevCapsA(UVar4,&local_38,0x30);
      if (MVar3 != 0) {
        return -1;
      }
      if (local_38.wTechnology == 1) {
        bVar1 = true;
        local_40 = UVar4;
      }
      UVar4 = UVar4 + 1;
    } while ((int)UVar4 < (int)UVar2);
    if ((!bVar1) && (UVar4 = 0, 0 < (int)UVar2)) {
      do {
        if (bVar1) {
          return local_40;
        }
        MVar3 = auxGetDevCapsA(UVar4,&local_38,0x30);
        if (MVar3 != 0) {
          return -1;
        }
        if (local_38.wTechnology == 2) {
          bVar1 = true;
          local_40 = UVar4;
        }
        UVar4 = UVar4 + 1;
      } while ((int)UVar4 < (int)UVar2);
    }
  }
  return local_40;
}
