/*
 * Entry: 0059a5ec
 * Name: _BitBlt@36
 * Namespace: Global
 * Signature: BOOL _BitBlt@36(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _BitBlt_36(HDC hdc,int x,int y,int cx,int cy,HDC hdcSrc,int x1,int y1,DWORD rop)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = BitBlt(hdc,x,y,cx,cy,hdcSrc,x1,y1,rop);
  return BVar1;
}
