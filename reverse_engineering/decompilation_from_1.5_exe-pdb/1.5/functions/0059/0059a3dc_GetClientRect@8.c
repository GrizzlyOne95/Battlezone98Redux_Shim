/*
 * Entry: 0059a3dc
 * Name: _GetClientRect@8
 * Namespace: Global
 * Signature: BOOL _GetClientRect@8(HWND hWnd, LPRECT lpRect)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GetClientRect_8(HWND hWnd,LPRECT lpRect)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetClientRect(hWnd,lpRect);
  return BVar1;
}
