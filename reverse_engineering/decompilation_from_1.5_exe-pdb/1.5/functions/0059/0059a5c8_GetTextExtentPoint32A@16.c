/*
 * Entry: 0059a5c8
 * Name: _GetTextExtentPoint32A@16
 * Namespace: Global
 * Signature: BOOL _GetTextExtentPoint32A@16(HDC hdc, LPCSTR lpString, int c, LPSIZE psizl)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GetTextExtentPoint32A_16(HDC hdc,LPCSTR lpString,int c,LPSIZE psizl)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetTextExtentPoint32A(hdc,lpString,c,psizl);
  return BVar1;
}
