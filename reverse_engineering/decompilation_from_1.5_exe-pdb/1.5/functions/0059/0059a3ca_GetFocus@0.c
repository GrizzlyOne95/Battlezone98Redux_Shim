/*
 * Entry: 0059a3ca
 * Name: _GetFocus@0
 * Namespace: Global
 * Signature: HWND _GetFocus@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HWND _GetFocus_0(void)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a3ca. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetFocus();
  return pHVar1;
}
