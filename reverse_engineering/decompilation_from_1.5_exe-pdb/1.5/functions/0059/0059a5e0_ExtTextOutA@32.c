/*
 * Entry: 0059a5e0
 * Name: _ExtTextOutA@32
 * Namespace: Global
 * Signature: BOOL _ExtTextOutA@32(HDC hdc, int x, int y, UINT options, RECT * lprect, LPCSTR lpString, UINT c, INT * lpDx)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _ExtTextOutA_32(HDC hdc,int x,int y,UINT options,RECT *lprect,LPCSTR lpString,UINT c,INT *lpDx)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ExtTextOutA(hdc,x,y,options,lprect,lpString,c,lpDx);
  return BVar1;
}
