/*
 * Entry: 0059a53e
 * Name: _RedrawWindow@16
 * Namespace: Global
 * Signature: BOOL _RedrawWindow@16(HWND hWnd, RECT * lprcUpdate, HRGN hrgnUpdate, UINT flags)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _RedrawWindow_16(HWND hWnd,RECT *lprcUpdate,HRGN hrgnUpdate,UINT flags)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a53e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = RedrawWindow(hWnd,lprcUpdate,hrgnUpdate,flags);
  return BVar1;
}
