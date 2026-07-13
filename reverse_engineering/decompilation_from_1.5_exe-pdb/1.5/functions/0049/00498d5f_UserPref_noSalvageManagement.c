/*
 * Entry: 00498d5f
 * Name: UserPref_noSalvageManagement
 * Namespace: Global
 * Signature: int UserPref_noSalvageManagement(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_noSalvageManagement(void)

{
  int iVar1;
  
  iVar1 = Net_IsNetGame();
  if ((iVar1 == 0) && ((UserProfilePtr->playOption & 2) != 0)) {
    return 1;
  }
  return 0;
}
