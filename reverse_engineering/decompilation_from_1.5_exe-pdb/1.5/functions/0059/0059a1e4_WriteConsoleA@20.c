/*
 * Entry: 0059a1e4
 * Name: _WriteConsoleA@20
 * Namespace: Global
 * Signature: BOOL _WriteConsoleA@20(HANDLE hConsoleOutput, void * lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _WriteConsoleA_20(HANDLE hConsoleOutput,void *lpBuffer,DWORD nNumberOfCharsToWrite,
                      LPDWORD lpNumberOfCharsWritten,LPVOID lpReserved)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a1e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = WriteConsoleA(hConsoleOutput,lpBuffer,nNumberOfCharsToWrite,lpNumberOfCharsWritten,
                        lpReserved);
  return BVar1;
}
