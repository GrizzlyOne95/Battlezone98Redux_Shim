/*
 * Entry: 004716a1
 * Name: UserPref_voiceLevel
 * Namespace: Global
 * Signature: uchar UserPref_voiceLevel(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl UserPref_voiceLevel(void)

{
  return (UserProfilePtr->audioControl).voice;
}
