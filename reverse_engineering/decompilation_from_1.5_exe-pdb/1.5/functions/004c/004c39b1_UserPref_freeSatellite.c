/*
 * Entry: 004c39b1
 * Name: UserPref_freeSatellite
 * Namespace: Global
 * Signature: int UserPref_freeSatellite(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_freeSatellite(void)

{
  int iVar1;
  
  iVar1 = Net_IsNetGame();
  if ((iVar1 == 0) && ((UserProfilePtr->playOption & 0x100U) != 0)) {
    return 1;
  }
  return 0;
}
