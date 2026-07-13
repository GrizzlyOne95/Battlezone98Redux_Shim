/*
 * Entry: 0059a208
 * Name: _FreeLibrary@4
 * Namespace: Global
 * Signature: BOOL _FreeLibrary@4(HMODULE hLibModule)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _FreeLibrary_4(HMODULE hLibModule)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a208. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = FreeLibrary(hLibModule);
  return BVar1;
}
