/*
 * Entry: 0059a226
 * Name: _SetConsoleTitleA@4
 * Namespace: Global
 * Signature: BOOL _SetConsoleTitleA@4(LPCSTR lpConsoleTitle)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetConsoleTitleA_4(LPCSTR lpConsoleTitle)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a226. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetConsoleTitleA(lpConsoleTitle);
  return BVar1;
}
