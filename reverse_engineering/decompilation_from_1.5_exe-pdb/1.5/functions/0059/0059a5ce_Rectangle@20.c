/*
 * Entry: 0059a5ce
 * Name: _Rectangle@20
 * Namespace: Global
 * Signature: BOOL _Rectangle@20(HDC hdc, int left, int top, int right, int bottom)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _Rectangle_20(HDC hdc,int left,int top,int right,int bottom)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5ce. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = Rectangle(hdc,left,top,right,bottom);
  return BVar1;
}
