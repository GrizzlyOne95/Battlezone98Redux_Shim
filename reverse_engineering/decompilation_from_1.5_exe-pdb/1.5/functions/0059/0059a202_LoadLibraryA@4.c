/*
 * Entry: 0059a202
 * Name: _LoadLibraryA@4
 * Namespace: Global
 * Signature: HMODULE _LoadLibraryA@4(LPCSTR lpLibFileName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HMODULE _LoadLibraryA_4(LPCSTR lpLibFileName)

{
  HMODULE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a202. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadLibraryA(lpLibFileName);
  return pHVar1;
}
