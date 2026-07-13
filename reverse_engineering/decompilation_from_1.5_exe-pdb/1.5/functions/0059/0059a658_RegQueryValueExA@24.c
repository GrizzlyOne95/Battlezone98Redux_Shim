/*
 * Entry: 0059a658
 * Name: _RegQueryValueExA@24
 * Namespace: Global
 * Signature: LSTATUS _RegQueryValueExA@24(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LSTATUS _RegQueryValueExA_24
                  (HKEY hKey,LPCSTR lpValueName,LPDWORD lpReserved,LPDWORD lpType,LPBYTE lpData,
                  LPDWORD lpcbData)

{
  LSTATUS LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a658. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = RegQueryValueExA(hKey,lpValueName,lpReserved,lpType,lpData,lpcbData);
  return LVar1;
}
