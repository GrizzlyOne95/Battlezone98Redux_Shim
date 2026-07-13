/*
 * Entry: 0059a568
 * Name: _GdiFlush@0
 * Namespace: Global
 * Signature: BOOL _GdiFlush@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GdiFlush_0(void)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a568. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GdiFlush();
  return BVar1;
}
