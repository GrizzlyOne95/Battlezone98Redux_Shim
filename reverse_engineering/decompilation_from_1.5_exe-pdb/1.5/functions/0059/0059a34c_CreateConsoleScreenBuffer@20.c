/*
 * Entry: 0059a34c
 * Name: _CreateConsoleScreenBuffer@20
 * Namespace: Global
 * Signature: HANDLE _CreateConsoleScreenBuffer@20(DWORD dwDesiredAccess, DWORD dwShareMode, SECURITY_ATTRIBUTES * lpSecurityAttributes, DWORD dwFlags, LPVOID lpScreenBufferData)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _CreateConsoleScreenBuffer_20
                 (DWORD dwDesiredAccess,DWORD dwShareMode,SECURITY_ATTRIBUTES *lpSecurityAttributes,
                 DWORD dwFlags,LPVOID lpScreenBufferData)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a34c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = CreateConsoleScreenBuffer
                     (dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwFlags,lpScreenBufferData);
  return pvVar1;
}
