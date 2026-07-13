/*
 * Entry: 0059a3a0
 * Name: _ShowWindow@8
 * Namespace: Global
 * Signature: BOOL _ShowWindow@8(HWND hWnd, int nCmdShow)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _ShowWindow_8(HWND hWnd,int nCmdShow)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ShowWindow(hWnd,nCmdShow);
  return BVar1;
}
