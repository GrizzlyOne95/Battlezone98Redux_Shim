/*
 * Entry: 0059a430
 * Name: _ShowCursor@4
 * Namespace: Global
 * Signature: int _ShowCursor@4(BOOL bShow)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _ShowCursor_4(BOOL bShow)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a430. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = ShowCursor(bShow);
  return iVar1;
}
