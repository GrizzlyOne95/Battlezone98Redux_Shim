/*
 * Entry: 004716aa
 * Name: UserPref_numChannels
 * Namespace: Global
 * Signature: uchar UserPref_numChannels(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl UserPref_numChannels(void)

{
  return (UserProfilePtr->audioControl).channels;
}
