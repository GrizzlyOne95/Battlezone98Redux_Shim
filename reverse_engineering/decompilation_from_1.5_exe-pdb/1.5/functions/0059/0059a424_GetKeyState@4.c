/*
 * Entry: 0059a424
 * Name: _GetKeyState@4
 * Namespace: Global
 * Signature: SHORT _GetKeyState@4(int nVirtKey)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SHORT _GetKeyState_4(int nVirtKey)

{
  SHORT SVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a424. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SVar1 = GetKeyState(nVirtKey);
  return SVar1;
}
