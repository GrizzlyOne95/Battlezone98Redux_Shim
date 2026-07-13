/*
 * Entry: 0059a1f0
 * Name: _SetConsoleTextAttribute@8
 * Namespace: Global
 * Signature: BOOL _SetConsoleTextAttribute@8(HANDLE hConsoleOutput, WORD wAttributes)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetConsoleTextAttribute_8(HANDLE hConsoleOutput,WORD wAttributes)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a1f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetConsoleTextAttribute(hConsoleOutput,wAttributes);
  return BVar1;
}
