/*
 * Entry: 0059a5aa
 * Name: _GetSystemPaletteEntries@16
 * Namespace: Global
 * Signature: UINT _GetSystemPaletteEntries@16(HDC hdc, UINT iStart, UINT cEntries, LPPALETTEENTRY pPalEntries)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _GetSystemPaletteEntries_16(HDC hdc,UINT iStart,UINT cEntries,LPPALETTEENTRY pPalEntries)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5aa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetSystemPaletteEntries(hdc,iStart,cEntries,pPalEntries);
  return UVar1;
}
