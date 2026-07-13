/*
 * Entry: 0059a592
 * Name: _CreateFontIndirectA@4
 * Namespace: Global
 * Signature: HFONT _CreateFontIndirectA@4(LOGFONTA * lplf)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HFONT _CreateFontIndirectA_4(LOGFONTA *lplf)

{
  HFONT pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a592. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateFontIndirectA(lplf);
  return pHVar1;
}
