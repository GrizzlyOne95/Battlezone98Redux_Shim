/*
 * Entry: 00485cf4
 * Name: UserPref_unlimitedArmor
 * Namespace: Global
 * Signature: int UserPref_unlimitedArmor(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_unlimitedArmor(void)

{
  int iVar1;
  
  iVar1 = Net_IsNetGame();
  if ((iVar1 == 0) && ((UserProfilePtr->playOption & 8) != 0)) {
    return 1;
  }
  return 0;
}
