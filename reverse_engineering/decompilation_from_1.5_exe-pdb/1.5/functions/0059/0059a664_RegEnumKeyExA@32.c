/*
 * Entry: 0059a664
 * Name: _RegEnumKeyExA@32
 * Namespace: Global
 * Signature: LSTATUS _RegEnumKeyExA@32(HKEY hKey, DWORD dwIndex, LPSTR lpName, LPDWORD lpcchName, LPDWORD lpReserved, LPSTR lpClass, LPDWORD lpcchClass, PFILETIME lpftLastWriteTime)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LSTATUS _RegEnumKeyExA_32(HKEY hKey,DWORD dwIndex,LPSTR lpName,LPDWORD lpcchName,LPDWORD lpReserved,
                         LPSTR lpClass,LPDWORD lpcchClass,PFILETIME lpftLastWriteTime)

{
  LSTATUS LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a664. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = RegEnumKeyExA(hKey,dwIndex,lpName,lpcchName,lpReserved,lpClass,lpcchClass,
                        lpftLastWriteTime);
  return LVar1;
}
