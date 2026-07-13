/*
 * Entry: 0059a232
 * Name: _SetThreadPriority@8
 * Namespace: Global
 * Signature: BOOL _SetThreadPriority@8(HANDLE hThread, int nPriority)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetThreadPriority_8(HANDLE hThread,int nPriority)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a232. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetThreadPriority(hThread,nPriority);
  return BVar1;
}
