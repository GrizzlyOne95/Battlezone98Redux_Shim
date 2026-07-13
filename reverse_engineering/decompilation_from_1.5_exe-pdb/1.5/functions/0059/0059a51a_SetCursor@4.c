/*
 * Entry: 0059a51a
 * Name: _SetCursor@4
 * Namespace: Global
 * Signature: HCURSOR _SetCursor@4(HCURSOR hCursor)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HCURSOR _SetCursor_4(HCURSOR hCursor)

{
  HCURSOR pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a51a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = SetCursor(hCursor);
  return pHVar1;
}
