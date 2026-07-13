/*
 * Entry: 0059a616
 * Name: _CreateCompatibleBitmap@12
 * Namespace: Global
 * Signature: HBITMAP _CreateCompatibleBitmap@12(HDC hdc, int cx, int cy)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HBITMAP _CreateCompatibleBitmap_12(HDC hdc,int cx,int cy)

{
  HBITMAP pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a616. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateCompatibleBitmap(hdc,cx,cy);
  return pHVar1;
}
