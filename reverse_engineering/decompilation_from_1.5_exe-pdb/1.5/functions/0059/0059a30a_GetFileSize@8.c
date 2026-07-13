/*
 * Entry: 0059a30a
 * Name: _GetFileSize@8
 * Namespace: Global
 * Signature: DWORD _GetFileSize@8(HANDLE hFile, LPDWORD lpFileSizeHigh)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _GetFileSize_8(HANDLE hFile,LPDWORD lpFileSizeHigh)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a30a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetFileSize(hFile,lpFileSizeHigh);
  return DVar1;
}
