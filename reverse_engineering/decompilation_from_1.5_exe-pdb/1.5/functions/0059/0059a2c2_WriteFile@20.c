/*
 * Entry: 0059a2c2
 * Name: _WriteFile@20
 * Namespace: Global
 * Signature: BOOL _WriteFile@20(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _WriteFile_20(HANDLE hFile,LPCVOID lpBuffer,DWORD nNumberOfBytesToWrite,
                  LPDWORD lpNumberOfBytesWritten,LPOVERLAPPED lpOverlapped)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2c2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = WriteFile(hFile,lpBuffer,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
  return BVar1;
}
