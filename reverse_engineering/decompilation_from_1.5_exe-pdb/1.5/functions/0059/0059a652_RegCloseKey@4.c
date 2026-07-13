/*
 * Entry: 0059a652
 * Name: _RegCloseKey@4
 * Namespace: Global
 * Signature: LSTATUS _RegCloseKey@4(HKEY hKey)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LSTATUS _RegCloseKey_4(HKEY hKey)

{
  LSTATUS LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a652. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = RegCloseKey(hKey);
  return LVar1;
}
