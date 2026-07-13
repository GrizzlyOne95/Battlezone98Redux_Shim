/*
 * Entry: 0059a214
 * Name: _SetConsoleCtrlHandler@8
 * Namespace: Global
 * Signature: BOOL _SetConsoleCtrlHandler@8(PHANDLER_ROUTINE HandlerRoutine, BOOL Add)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetConsoleCtrlHandler_8(PHANDLER_ROUTINE HandlerRoutine,BOOL Add)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a214. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetConsoleCtrlHandler(HandlerRoutine,Add);
  return BVar1;
}
