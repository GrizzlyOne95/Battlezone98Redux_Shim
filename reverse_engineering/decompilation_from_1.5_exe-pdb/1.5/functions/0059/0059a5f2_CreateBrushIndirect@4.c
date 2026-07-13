/*
 * Entry: 0059a5f2
 * Name: _CreateBrushIndirect@4
 * Namespace: Global
 * Signature: HBRUSH _CreateBrushIndirect@4(LOGBRUSH * plbrush)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HBRUSH _CreateBrushIndirect_4(LOGBRUSH *plbrush)

{
  HBRUSH pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5f2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateBrushIndirect(plbrush);
  return pHVar1;
}
