/*
 * Entry: 0059a316
 * Name: _GetModuleHandleA@4
 * Namespace: Global
 * Signature: HMODULE _GetModuleHandleA@4(LPCSTR lpModuleName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HMODULE _GetModuleHandleA_4(LPCSTR lpModuleName)

{
  HMODULE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a316. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetModuleHandleA(lpModuleName);
  return pHVar1;
}
