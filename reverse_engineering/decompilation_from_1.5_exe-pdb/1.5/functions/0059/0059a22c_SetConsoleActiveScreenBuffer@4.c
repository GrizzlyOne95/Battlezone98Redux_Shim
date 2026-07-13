/*
 * Entry: 0059a22c
 * Name: _SetConsoleActiveScreenBuffer@4
 * Namespace: Global
 * Signature: BOOL _SetConsoleActiveScreenBuffer@4(HANDLE hConsoleOutput)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetConsoleActiveScreenBuffer_4(HANDLE hConsoleOutput)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a22c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetConsoleActiveScreenBuffer(hConsoleOutput);
  return BVar1;
}
