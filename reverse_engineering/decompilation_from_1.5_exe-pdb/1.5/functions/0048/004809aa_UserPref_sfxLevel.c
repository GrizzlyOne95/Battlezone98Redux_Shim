/*
 * Entry: 004809aa
 * Name: UserPref_sfxLevel
 * Namespace: Global
 * Signature: uchar UserPref_sfxLevel(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl UserPref_sfxLevel(void)

{
  return (UserProfilePtr->audioControl).sfx;
}
