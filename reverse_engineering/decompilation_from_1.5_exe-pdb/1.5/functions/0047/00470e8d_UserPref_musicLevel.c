/*
 * Entry: 00470e8d
 * Name: UserPref_musicLevel
 * Namespace: Global
 * Signature: uchar UserPref_musicLevel(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl UserPref_musicLevel(void)

{
  return (UserProfilePtr->audioControl).music;
}
