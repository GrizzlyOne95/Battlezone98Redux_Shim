/*
 * Entry: 0059a670
 * Name: _ShellExecuteA@24
 * Namespace: Global
 * Signature: HINSTANCE _ShellExecuteA@24(HWND hwnd, LPCSTR lpOperation, LPCSTR lpFile, LPCSTR lpParameters, LPCSTR lpDirectory, INT nShowCmd)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HINSTANCE _ShellExecuteA_24(HWND hwnd,LPCSTR lpOperation,LPCSTR lpFile,LPCSTR lpParameters,
                           LPCSTR lpDirectory,INT nShowCmd)

{
  HINSTANCE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a670. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = ShellExecuteA(hwnd,lpOperation,lpFile,lpParameters,lpDirectory,nShowCmd);
  return pHVar1;
}
