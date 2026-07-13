/*
 * Entry: 0059a376
 * Name: _CreateThread@24
 * Namespace: Global
 * Signature: HANDLE _CreateThread@24(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _CreateThread_24(LPSECURITY_ATTRIBUTES lpThreadAttributes,SIZE_T dwStackSize,
                       LPTHREAD_START_ROUTINE lpStartAddress,LPVOID lpParameter,
                       DWORD dwCreationFlags,LPDWORD lpThreadId)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a376. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = CreateThread(lpThreadAttributes,dwStackSize,lpStartAddress,lpParameter,dwCreationFlags,
                        lpThreadId);
  return pvVar1;
}
