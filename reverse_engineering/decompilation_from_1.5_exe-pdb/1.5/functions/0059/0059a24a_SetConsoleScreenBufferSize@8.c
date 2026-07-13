/*
 * Entry: 0059a24a
 * Name: _SetConsoleScreenBufferSize@8
 * Namespace: Global
 * Signature: BOOL _SetConsoleScreenBufferSize@8(HANDLE hConsoleOutput, COORD dwSize)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetConsoleScreenBufferSize_8(HANDLE hConsoleOutput,COORD dwSize)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a24a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetConsoleScreenBufferSize(hConsoleOutput,dwSize);
  return BVar1;
}
