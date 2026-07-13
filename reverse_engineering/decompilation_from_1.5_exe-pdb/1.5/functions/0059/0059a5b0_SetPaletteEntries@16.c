/*
 * Entry: 0059a5b0
 * Name: _SetPaletteEntries@16
 * Namespace: Global
 * Signature: UINT _SetPaletteEntries@16(HPALETTE hpal, UINT iStart, UINT cEntries, PALETTEENTRY * pPalEntries)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _SetPaletteEntries_16(HPALETTE hpal,UINT iStart,UINT cEntries,PALETTEENTRY *pPalEntries)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = SetPaletteEntries(hpal,iStart,cEntries,pPalEntries);
  return UVar1;
}
