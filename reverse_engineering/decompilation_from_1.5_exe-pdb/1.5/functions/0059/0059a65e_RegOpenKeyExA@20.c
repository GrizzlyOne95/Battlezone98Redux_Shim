/*
 * Entry: 0059a65e
 * Name: _RegOpenKeyExA@20
 * Namespace: Global
 * Signature: LSTATUS _RegOpenKeyExA@20(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LSTATUS _RegOpenKeyExA_20(HKEY hKey,LPCSTR lpSubKey,DWORD ulOptions,REGSAM samDesired,
                         PHKEY phkResult)

{
  LSTATUS LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a65e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = RegOpenKeyExA(hKey,lpSubKey,ulOptions,samDesired,phkResult);
  return LVar1;
}
