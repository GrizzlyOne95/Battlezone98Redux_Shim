/*
 * Entry: 00478729
 * Name: UserPref_arcadeMode
 * Namespace: Global
 * Signature: int UserPref_arcadeMode(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_arcadeMode(void)

{
  int iVar1;
  
  iVar1 = Net_IsNetGame();
  if ((iVar1 != 0) || (iVar1 = 1, (UserProfilePtr->playOption & 1) == 0)) {
    iVar1 = 0;
  }
  return iVar1;
}
