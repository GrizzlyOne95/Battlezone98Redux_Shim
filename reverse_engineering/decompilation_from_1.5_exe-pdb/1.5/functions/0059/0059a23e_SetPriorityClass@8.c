/*
 * Entry: 0059a23e
 * Name: _SetPriorityClass@8
 * Namespace: Global
 * Signature: BOOL _SetPriorityClass@8(HANDLE hProcess, DWORD dwPriorityClass)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetPriorityClass_8(HANDLE hProcess,DWORD dwPriorityClass)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a23e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetPriorityClass(hProcess,dwPriorityClass);
  return BVar1;
}
