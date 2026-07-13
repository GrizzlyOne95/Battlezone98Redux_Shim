/*
 * Entry: 0059a5f8
 * Name: _GetTextMetricsA@8
 * Namespace: Global
 * Signature: BOOL _GetTextMetricsA@8(HDC hdc, LPTEXTMETRICA lptm)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GetTextMetricsA_8(HDC hdc,LPTEXTMETRICA lptm)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetTextMetricsA(hdc,lptm);
  return BVar1;
}
