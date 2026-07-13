/*
 * Entry: 0059a436
 * Name: _ClipCursor@4
 * Namespace: Global
 * Signature: BOOL _ClipCursor@4(RECT * lpRect)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _ClipCursor_4(RECT *lpRect)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a436. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ClipCursor(lpRect);
  return BVar1;
}
