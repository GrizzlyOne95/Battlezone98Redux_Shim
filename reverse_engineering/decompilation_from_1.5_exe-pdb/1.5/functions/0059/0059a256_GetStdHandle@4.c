/*
 * Entry: 0059a256
 * Name: _GetStdHandle@4
 * Namespace: Global
 * Signature: HANDLE _GetStdHandle@4(DWORD nStdHandle)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _GetStdHandle_4(DWORD nStdHandle)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a256. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GetStdHandle(nStdHandle);
  return pvVar1;
}
