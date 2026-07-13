/*
 * Entry: 0059a64c
 * Name: _GetOpenFileNameA@4
 * Namespace: Global
 * Signature: BOOL _GetOpenFileNameA@4(LPOPENFILENAMEA param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GetOpenFileNameA_4(LPOPENFILENAMEA param_1)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a64c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetOpenFileNameA(param_1);
  return BVar1;
}
