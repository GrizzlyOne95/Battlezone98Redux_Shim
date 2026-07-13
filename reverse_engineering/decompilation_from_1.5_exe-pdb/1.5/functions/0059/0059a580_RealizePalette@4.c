/*
 * Entry: 0059a580
 * Name: _RealizePalette@4
 * Namespace: Global
 * Signature: UINT _RealizePalette@4(HDC hdc)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _RealizePalette_4(HDC hdc)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a580. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = RealizePalette(hdc);
  return UVar1;
}
