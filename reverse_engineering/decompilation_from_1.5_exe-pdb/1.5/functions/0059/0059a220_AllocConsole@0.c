/*
 * Entry: 0059a220
 * Name: _AllocConsole@0
 * Namespace: Global
 * Signature: BOOL _AllocConsole@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _AllocConsole_0(void)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a220. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = AllocConsole();
  return BVar1;
}
