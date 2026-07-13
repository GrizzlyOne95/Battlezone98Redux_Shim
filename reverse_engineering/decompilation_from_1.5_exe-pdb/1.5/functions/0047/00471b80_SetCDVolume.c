/*
 * Entry: 00471b80
 * Name: SetCDVolume
 * Namespace: Global
 * Signature: int SetCDVolume(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetCDVolume(long param_1)

{
  uint uVar1;
  MMRESULT MVar2;
  
  if (param_1 != -0x5550556) {
    if (param_1 != -0x4440445) {
      if (param_1 < 0) {
        param_1 = 0;
      }
      else if (10 < param_1) {
        param_1 = 10;
      }
      uVar1 = (param_1 * 0xffff) / 10;
      if ((auxCDRomID != -1) && (MVar2 = auxSetVolume(auxCDRomID,uVar1 << 0x10 | uVar1), MVar2 == 0)
         ) {
        return 1;
      }
      return 0;
    }
    if (auxCDRomID != -1) {
      auxSetVolume(auxCDRomID,auxCDRomVol);
    }
  }
  return 1;
}
