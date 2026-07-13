/*
 * Entry: 0059a538
 * Name: _EnumChildWindows@12
 * Namespace: Global
 * Signature: BOOL _EnumChildWindows@12(HWND hWndParent, WNDENUMPROC lpEnumFunc, LPARAM lParam)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _EnumChildWindows_12(HWND hWndParent,WNDENUMPROC lpEnumFunc,LPARAM lParam)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a538. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = EnumChildWindows(hWndParent,lpEnumFunc,lParam);
  return BVar1;
}
