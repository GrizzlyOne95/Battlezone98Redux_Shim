/*
 * Entry: 00477ef1
 * Name: UserPref_lineskip
 * Namespace: Global
 * Signature: uchar UserPref_lineskip(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl UserPref_lineskip(void)

{
  uchar uVar1;
  
  uVar1 = '\0';
  if (useD3D == 0) {
    uVar1 = (UserProfilePtr->graphicDetail).lineskip;
  }
  return uVar1;
}
