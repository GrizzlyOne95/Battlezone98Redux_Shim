/*
 * Entry: 0059a364
 * Name: _GetPrivateProfileStringA@24
 * Namespace: Global
 * Signature: DWORD _GetPrivateProfileStringA@24(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpDefault, LPSTR lpReturnedString, DWORD nSize, LPCSTR lpFileName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _GetPrivateProfileStringA_24
                (LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpDefault,LPSTR lpReturnedString,
                DWORD nSize,LPCSTR lpFileName)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a364. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetPrivateProfileStringA(lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize,lpFileName);
  return DVar1;
}
