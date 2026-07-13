/*
 * Entry: 0059a586
 * Name: _CreateCompatibleDC@4
 * Namespace: Global
 * Signature: HDC _CreateCompatibleDC@4(HDC hdc)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HDC _CreateCompatibleDC_4(HDC hdc)

{
  HDC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a586. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateCompatibleDC(hdc);
  return pHVar1;
}
