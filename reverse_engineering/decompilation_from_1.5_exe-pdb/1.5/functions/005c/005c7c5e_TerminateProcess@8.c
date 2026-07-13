/*
 * Entry: 005c7c5e
 * Name: _TerminateProcess@8
 * Namespace: Global
 * Signature: BOOL _TerminateProcess@8(HANDLE hProcess, UINT uExitCode)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _TerminateProcess_8(HANDLE hProcess,UINT uExitCode)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c7c5e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = TerminateProcess(hProcess,uExitCode);
  return BVar1;
}
