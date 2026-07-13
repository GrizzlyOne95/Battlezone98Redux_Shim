/*
 * Entry: 0059a5da
 * Name: _GetTextAlign@4
 * Namespace: Global
 * Signature: UINT _GetTextAlign@4(HDC hdc)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UINT _GetTextAlign_4(HDC hdc)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5da. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetTextAlign(hdc);
  return UVar1;
}
