/*
 * Entry: 00539e88
 * Name: UserPref_specialTrigger
 * Namespace: Global
 * Signature: int UserPref_specialTrigger(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UserPref_specialTrigger(void)

{
  return (uint)UserProfilePtr->playOption >> 10 & 1;
}
