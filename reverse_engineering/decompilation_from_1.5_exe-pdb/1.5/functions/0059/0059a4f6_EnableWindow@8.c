/*
 * Entry: 0059a4f6
 * Name: _EnableWindow@8
 * Namespace: Global
 * Signature: BOOL _EnableWindow@8(HWND hWnd, BOOL bEnable)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _EnableWindow_8(HWND hWnd,BOOL bEnable)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4f6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = EnableWindow(hWnd,bEnable);
  return BVar1;
}
