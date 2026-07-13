/*
 * Entry: 0059a36a
 * Name: _WritePrivateProfileStringA@16
 * Namespace: Global
 * Signature: BOOL _WritePrivateProfileStringA@16(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpString, LPCSTR lpFileName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _WritePrivateProfileStringA_16
               (LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpString,LPCSTR lpFileName)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a36a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = WritePrivateProfileStringA(lpAppName,lpKeyName,lpString,lpFileName);
  return BVar1;
}
