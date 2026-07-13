/*
 * Entry: 004cef2e
 * Name: UserPref_strategyHelp
 * Namespace: Global
 * Signature: int UserPref_strategyHelp(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_strategyHelp(void)

{
  return (uint)UserProfilePtr->playOption >> 7 & 1;
}
