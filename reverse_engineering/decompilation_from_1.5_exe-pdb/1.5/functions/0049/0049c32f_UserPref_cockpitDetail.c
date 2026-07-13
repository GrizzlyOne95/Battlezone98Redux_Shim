/*
 * Entry: 0049c32f
 * Name: UserPref_cockpitDetail
 * Namespace: Global
 * Signature: uchar UserPref_cockpitDetail(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl UserPref_cockpitDetail(void)

{
  return (UserProfilePtr->graphicDetail).cockpit;
}
