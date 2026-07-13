/*
 * Entry: 0059a250
 * Name: _SetConsoleWindowInfo@12
 * Namespace: Global
 * Signature: BOOL _SetConsoleWindowInfo@12(HANDLE hConsoleOutput, BOOL bAbsolute, SMALL_RECT * lpConsoleWindow)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetConsoleWindowInfo_12(HANDLE hConsoleOutput,BOOL bAbsolute,SMALL_RECT *lpConsoleWindow)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a250. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetConsoleWindowInfo(hConsoleOutput,bAbsolute,lpConsoleWindow);
  return BVar1;
}
