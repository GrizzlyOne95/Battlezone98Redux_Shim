/*
 * Entry: 0059a3d6
 * Name: _GetWindowRect@8
 * Namespace: Global
 * Signature: BOOL _GetWindowRect@8(HWND hWnd, LPRECT lpRect)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GetWindowRect_8(HWND hWnd,LPRECT lpRect)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3d6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetWindowRect(hWnd,lpRect);
  return BVar1;
}
