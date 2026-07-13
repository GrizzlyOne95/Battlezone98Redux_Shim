/*
 * Entry: 0059a5e6
 * Name: _GetTextColor@4
 * Namespace: Global
 * Signature: COLORREF _GetTextColor@4(HDC hdc)
 * Symbol source: IMPORTED
 * Export status: ok
 */

COLORREF _GetTextColor_4(HDC hdc)

{
  COLORREF CVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5e6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CVar1 = GetTextColor(hdc);
  return CVar1;
}
