/*
 * Entry: 0050434b
 * Name: UserPref_terrain
 * Namespace: Global
 * Signature: uchar UserPref_terrain(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl UserPref_terrain(void)

{
  return (UserProfilePtr->graphicDetail).terrain;
}
