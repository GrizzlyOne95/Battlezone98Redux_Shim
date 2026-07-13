/*
 * Entry: 0059a340
 * Name: _WriteConsoleOutputCharacterA@20
 * Namespace: Global
 * Signature: BOOL _WriteConsoleOutputCharacterA@20(HANDLE hConsoleOutput, LPCSTR lpCharacter, DWORD nLength, COORD dwWriteCoord, LPDWORD lpNumberOfCharsWritten)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _WriteConsoleOutputCharacterA_20
               (HANDLE hConsoleOutput,LPCSTR lpCharacter,DWORD nLength,COORD dwWriteCoord,
               LPDWORD lpNumberOfCharsWritten)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a340. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = WriteConsoleOutputCharacterA
                    (hConsoleOutput,lpCharacter,nLength,dwWriteCoord,lpNumberOfCharsWritten);
  return BVar1;
}
