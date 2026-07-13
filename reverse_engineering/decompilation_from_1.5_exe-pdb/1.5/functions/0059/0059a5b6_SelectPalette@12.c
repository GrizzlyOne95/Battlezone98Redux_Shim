/*
 * Entry: 0059a5b6
 * Name: _SelectPalette@12
 * Namespace: Global
 * Signature: HPALETTE _SelectPalette@12(HDC hdc, HPALETTE hPal, BOOL bForceBkgd)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HPALETTE _SelectPalette_12(HDC hdc,HPALETTE hPal,BOOL bForceBkgd)

{
  HPALETTE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5b6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = SelectPalette(hdc,hPal,bForceBkgd);
  return pHVar1;
}
