/*
 * Entry: 0059a1fc
 * Name: _GetProcAddress@8
 * Namespace: Global
 * Signature: FARPROC _GetProcAddress@8(HMODULE hModule, LPCSTR lpProcName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FARPROC _GetProcAddress_8(HMODULE hModule,LPCSTR lpProcName)

{
  FARPROC pFVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a1fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pFVar1 = GetProcAddress(hModule,lpProcName);
  return pFVar1;
}
