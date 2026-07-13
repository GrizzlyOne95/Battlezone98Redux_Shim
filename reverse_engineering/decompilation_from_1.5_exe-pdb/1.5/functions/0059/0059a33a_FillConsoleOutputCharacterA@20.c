/*
 * Entry: 0059a33a
 * Name: _FillConsoleOutputCharacterA@20
 * Namespace: Global
 * Signature: BOOL _FillConsoleOutputCharacterA@20(HANDLE hConsoleOutput, CHAR cCharacter, DWORD nLength, COORD dwWriteCoord, LPDWORD lpNumberOfCharsWritten)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _FillConsoleOutputCharacterA_20
               (HANDLE hConsoleOutput,CHAR cCharacter,DWORD nLength,COORD dwWriteCoord,
               LPDWORD lpNumberOfCharsWritten)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a33a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = FillConsoleOutputCharacterA
                    (hConsoleOutput,cCharacter,nLength,dwWriteCoord,lpNumberOfCharsWritten);
  return BVar1;
}
