/*
 * Entry: 0059a49c
 * Name: _GetSystemMetrics@4
 * Namespace: Global
 * Signature: int _GetSystemMetrics@4(int nIndex)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _GetSystemMetrics_4(int nIndex)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a49c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetSystemMetrics(nIndex);
  return iVar1;
}
