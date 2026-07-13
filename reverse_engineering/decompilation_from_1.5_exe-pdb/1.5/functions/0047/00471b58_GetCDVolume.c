/*
 * Entry: 00471b58
 * Name: GetCDVolume
 * Namespace: Global
 * Signature: long GetCDVolume(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl GetCDVolume(void)

{
  MMRESULT MVar1;
  uint local_8;
  
  if (auxCDRomID != -1) {
    MVar1 = auxGetVolume(auxCDRomID,&local_8);
    if (MVar1 == 0) {
      return local_8 & 0xffff;
    }
  }
  return -1;
}
