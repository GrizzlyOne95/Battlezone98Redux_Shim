/*
 * Entry: 0059a418
 * Name: _MsgWaitForMultipleObjects@20
 * Namespace: Global
 * Signature: DWORD _MsgWaitForMultipleObjects@20(DWORD nCount, HANDLE * pHandles, BOOL fWaitAll, DWORD dwMilliseconds, DWORD dwWakeMask)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _MsgWaitForMultipleObjects_20
                (DWORD nCount,HANDLE *pHandles,BOOL fWaitAll,DWORD dwMilliseconds,DWORD dwWakeMask)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a418. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = MsgWaitForMultipleObjects(nCount,pHandles,fWaitAll,dwMilliseconds,dwWakeMask);
  return DVar1;
}
