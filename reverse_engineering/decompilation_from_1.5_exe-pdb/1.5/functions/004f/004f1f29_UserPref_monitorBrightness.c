/*
 * Entry: 004f1f29
 * Name: UserPref_monitorBrightness
 * Namespace: Global
 * Signature: uchar UserPref_monitorBrightness(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl UserPref_monitorBrightness(void)

{
  return (UserProfilePtr->graphicDetail).brightness + '\x01';
}
