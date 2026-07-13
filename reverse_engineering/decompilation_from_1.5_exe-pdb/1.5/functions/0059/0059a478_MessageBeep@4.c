/*
 * Entry: 0059a478
 * Name: _MessageBeep@4
 * Namespace: Global
 * Signature: BOOL _MessageBeep@4(UINT uType)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _MessageBeep_4(UINT uType)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a478. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = MessageBeep(uType);
  return BVar1;
}
