/*
 * Entry: 004e9ebf
 * Name: UserPref_vehicleTexture
 * Namespace: Global
 * Signature: uchar UserPref_vehicleTexture(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl UserPref_vehicleTexture(void)

{
  return (UserProfilePtr->graphicDetail).vehTex;
}
