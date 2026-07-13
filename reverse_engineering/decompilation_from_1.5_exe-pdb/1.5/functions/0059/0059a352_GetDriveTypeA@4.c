/*
 * Entry: 0059a352
 * Name: _GetDriveTypeA@4
 * Namespace: Global
 * Signature: UINT _GetDriveTypeA@4(LPCSTR lpRootPathName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _GetDriveTypeA_4(LPCSTR lpRootPathName)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a352. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetDriveTypeA(lpRootPathName);
  return UVar1;
}
