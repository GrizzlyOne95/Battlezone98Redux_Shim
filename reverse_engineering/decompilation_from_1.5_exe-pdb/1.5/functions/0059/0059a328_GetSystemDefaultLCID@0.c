/*
 * Entry: 0059a328
 * Name: _GetSystemDefaultLCID@0
 * Namespace: Global
 * Signature: LCID _GetSystemDefaultLCID@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LCID _GetSystemDefaultLCID_0(void)

{
  LCID LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a328. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = GetSystemDefaultLCID();
  return LVar1;
}
