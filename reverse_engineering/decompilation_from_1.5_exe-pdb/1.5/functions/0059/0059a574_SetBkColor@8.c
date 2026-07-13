/*
 * Entry: 0059a574
 * Name: _SetBkColor@8
 * Namespace: Global
 * Signature: COLORREF _SetBkColor@8(HDC hdc, COLORREF color)
 * Symbol source: IMPORTED
 * Export status: ok
 */

COLORREF _SetBkColor_8(HDC hdc,COLORREF color)

{
  COLORREF CVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a574. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CVar1 = SetBkColor(hdc,color);
  return CVar1;
}
