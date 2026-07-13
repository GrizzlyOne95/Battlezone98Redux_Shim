/*
 * Entry: 0059a310
 * Name: _GetModuleFileNameA@12
 * Namespace: Global
 * Signature: DWORD _GetModuleFileNameA@12(HMODULE hModule, LPSTR lpFilename, DWORD nSize)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _GetModuleFileNameA_12(HMODULE hModule,LPSTR lpFilename,DWORD nSize)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a310. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetModuleFileNameA(hModule,lpFilename,nSize);
  return DVar1;
}
