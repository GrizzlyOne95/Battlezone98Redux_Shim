/*
 * Entry: 0059a62e
 * Name: _PatBlt@24
 * Namespace: Global
 * Signature: BOOL _PatBlt@24(HDC hdc, int x, int y, int w, int h, DWORD rop)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _PatBlt_24(HDC hdc,int x,int y,int w,int h,DWORD rop)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a62e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = PatBlt(hdc,x,y,w,h,rop);
  return BVar1;
}
