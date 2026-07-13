/*
 * Entry: 0059a484
 * Name: _GetDC@4
 * Namespace: Global
 * Signature: HDC _GetDC@4(HWND hWnd)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HDC _GetDC_4(HWND hWnd)

{
  HDC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a484. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetDC(hWnd);
  return pHVar1;
}
