/*
 * Entry: 00478720
 * Name: UserPref_resolution
 * Namespace: Global
 * Signature: uchar UserPref_resolution(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl UserPref_resolution(void)

{
  return (UserProfilePtr->graphicDetail).resolution;
}
