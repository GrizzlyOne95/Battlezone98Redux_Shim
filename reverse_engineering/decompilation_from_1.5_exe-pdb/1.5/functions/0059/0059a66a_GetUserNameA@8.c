/*
 * Entry: 0059a66a
 * Name: _GetUserNameA@8
 * Namespace: Global
 * Signature: BOOL _GetUserNameA@8(LPSTR lpBuffer, LPDWORD pcbBuffer)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _GetUserNameA_8(LPSTR lpBuffer,LPDWORD pcbBuffer)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a66a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetUserNameA(lpBuffer,pcbBuffer);
  return BVar1;
}
