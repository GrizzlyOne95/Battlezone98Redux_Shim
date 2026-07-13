/*
 * Entry: 0059a4c6
 * Name: _InvalidateRect@12
 * Namespace: Global
 * Signature: BOOL _InvalidateRect@12(HWND hWnd, RECT * lpRect, BOOL bErase)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _InvalidateRect_12(HWND hWnd,RECT *lpRect,BOOL bErase)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4c6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = InvalidateRect(hWnd,lpRect,bErase);
  return BVar1;
}
