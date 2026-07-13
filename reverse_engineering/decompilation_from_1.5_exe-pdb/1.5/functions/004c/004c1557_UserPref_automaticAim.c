/*
 * Entry: 004c1557
 * Name: UserPref_automaticAim
 * Namespace: Global
 * Signature: int UserPref_automaticAim(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_automaticAim(void)

{
  return (uint)UserProfilePtr->playOption >> 5 & 1;
}
