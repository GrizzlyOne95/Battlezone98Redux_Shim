/*
 * Entry: 0059a2c8
 * Name: _FindClose@4
 * Namespace: Global
 * Signature: BOOL _FindClose@4(HANDLE hFindFile)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _FindClose_4(HANDLE hFindFile)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = FindClose(hFindFile);
  return BVar1;
}
