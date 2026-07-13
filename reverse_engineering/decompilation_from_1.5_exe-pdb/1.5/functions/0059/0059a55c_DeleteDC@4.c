/*
 * Entry: 0059a55c
 * Name: _DeleteDC@4
 * Namespace: Global
 * Signature: BOOL _DeleteDC@4(HDC hdc)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _DeleteDC_4(HDC hdc)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a55c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DeleteDC(hdc);
  return BVar1;
}
