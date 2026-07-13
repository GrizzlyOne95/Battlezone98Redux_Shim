/*
 * Entry: 0059a4a2
 * Name: _AdjustWindowRect@12
 * Namespace: Global
 * Signature: BOOL _AdjustWindowRect@12(LPRECT lpRect, DWORD dwStyle, BOOL bMenu)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _AdjustWindowRect_12(LPRECT lpRect,DWORD dwStyle,BOOL bMenu)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a4a2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = AdjustWindowRect(lpRect,dwStyle,bMenu);
  return BVar1;
}
