/*
 * Entry: 0059a2bc
 * Name: _CreateFileA@28
 * Namespace: Global
 * Signature: HANDLE _CreateFileA@28(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _CreateFileA_28(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
                      LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,
                      DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = CreateFileA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,
                       dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
  return pvVar1;
}
