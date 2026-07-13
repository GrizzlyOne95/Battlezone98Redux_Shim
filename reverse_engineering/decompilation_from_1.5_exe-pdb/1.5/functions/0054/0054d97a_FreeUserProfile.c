/*
 * Entry: 0054d97a
 * Name: FreeUserProfile
 * Namespace: Global
 * Signature: void FreeUserProfile(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FreeUserProfile(void)

{
  free(UserProfilePtr);
  UserProfilePtr = (i76_total *)0x0;
  return;
}
