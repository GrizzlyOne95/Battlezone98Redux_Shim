/*
 * Entry: 00495081
 * Name: UserPref_unlimitedAmmo
 * Namespace: Global
 * Signature: int UserPref_unlimitedAmmo(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_unlimitedAmmo(void)

{
  int iVar1;
  
  iVar1 = Net_IsNetGame();
  if ((iVar1 == 0) && ((UserProfilePtr->playOption & 4) != 0)) {
    return 1;
  }
  return 0;
}
