/*
 * Entry: 0059a490
 * Name: _SetMenu@8
 * Namespace: Global
 * Signature: BOOL _SetMenu@8(HWND hWnd, HMENU hMenu)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetMenu_8(HWND hWnd,HMENU hMenu)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a490. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetMenu(hWnd,hMenu);
  return BVar1;
}
