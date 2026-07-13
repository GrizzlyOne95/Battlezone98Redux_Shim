/*
 * Entry: 0059a20e
 * Name: _GetPrivateProfileIntA@16
 * Namespace: Global
 * Signature: UINT _GetPrivateProfileIntA@16(LPCSTR lpAppName, LPCSTR lpKeyName, INT nDefault, LPCSTR lpFileName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _GetPrivateProfileIntA_16(LPCSTR lpAppName,LPCSTR lpKeyName,INT nDefault,LPCSTR lpFileName)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a20e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetPrivateProfileIntA(lpAppName,lpKeyName,nDefault,lpFileName);
  return UVar1;
}
