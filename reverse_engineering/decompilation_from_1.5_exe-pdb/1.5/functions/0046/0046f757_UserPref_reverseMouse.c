/*
 * Entry: 0046f757
 * Name: UserPref_reverseMouse
 * Namespace: Global
 * Signature: int UserPref_reverseMouse(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_reverseMouse(void)

{
  return (uint)UserProfilePtr->playOption >> 6 & 1;
}
