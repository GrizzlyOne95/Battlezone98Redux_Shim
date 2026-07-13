/*
 * Entry: 0059a646
 * Name: _GetSaveFileNameA@4
 * Namespace: Global
 * Signature: BOOL _GetSaveFileNameA@4(LPOPENFILENAMEA param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GetSaveFileNameA_4(LPOPENFILENAMEA param_1)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a646. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetSaveFileNameA(param_1);
  return BVar1;
}
