/*
 * Entry: 004ada4e
 * Name: UserPref_unlimitedRadar
 * Namespace: Global
 * Signature: int UserPref_unlimitedRadar(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_unlimitedRadar(void)

{
  int iVar1;
  
  iVar1 = Net_IsNetGame();
  if ((iVar1 == 0) && ((UserProfilePtr->playOption & 0x200U) != 0)) {
    return 1;
  }
  return 0;
}
