/*
 * Entry: 0059a5bc
 * Name: _CreatePalette@4
 * Namespace: Global
 * Signature: HPALETTE _CreatePalette@4(LOGPALETTE * plpal)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HPALETTE _CreatePalette_4(LOGPALETTE *plpal)

{
  HPALETTE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreatePalette(plpal);
  return pHVar1;
}
