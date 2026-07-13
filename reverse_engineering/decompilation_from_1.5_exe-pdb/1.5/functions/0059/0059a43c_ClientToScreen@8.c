/*
 * Entry: 0059a43c
 * Name: _ClientToScreen@8
 * Namespace: Global
 * Signature: BOOL _ClientToScreen@8(HWND hWnd, LPPOINT lpPoint)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _ClientToScreen_8(HWND hWnd,LPPOINT lpPoint)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a43c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ClientToScreen(hWnd,lpPoint);
  return BVar1;
}
