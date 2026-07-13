/*
 * Entry: 0059a57a
 * Name: _SetTextColor@8
 * Namespace: Global
 * Signature: COLORREF _SetTextColor@8(HDC hdc, COLORREF color)
 * Symbol source: IMPORTED
 * Export status: ok
 */

COLORREF _SetTextColor_8(HDC hdc,COLORREF color)

{
  COLORREF CVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a57a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CVar1 = SetTextColor(hdc,color);
  return CVar1;
}
