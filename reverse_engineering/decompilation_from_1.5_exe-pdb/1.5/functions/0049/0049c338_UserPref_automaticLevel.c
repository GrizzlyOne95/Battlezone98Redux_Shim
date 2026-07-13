/*
 * Entry: 0049c338
 * Name: UserPref_automaticLevel
 * Namespace: Global
 * Signature: int UserPref_automaticLevel(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_automaticLevel(void)

{
  return (uint)UserProfilePtr->playOption >> 4 & 1;
}
