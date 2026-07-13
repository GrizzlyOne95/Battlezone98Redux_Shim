/*
 * Entry: 0059a2ec
 * Name: _WaitForSingleObject@8
 * Namespace: Global
 * Signature: DWORD _WaitForSingleObject@8(HANDLE hHandle, DWORD dwMilliseconds)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _WaitForSingleObject_8(HANDLE hHandle,DWORD dwMilliseconds)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = WaitForSingleObject(hHandle,dwMilliseconds);
  return DVar1;
}
