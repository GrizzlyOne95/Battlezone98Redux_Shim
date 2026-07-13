/*
 * Entry: 0059a5d4
 * Name: _SetTextAlign@8
 * Namespace: Global
 * Signature: UINT _SetTextAlign@8(HDC hdc, UINT align)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _SetTextAlign_8(HDC hdc,UINT align)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = SetTextAlign(hdc,align);
  return UVar1;
}
