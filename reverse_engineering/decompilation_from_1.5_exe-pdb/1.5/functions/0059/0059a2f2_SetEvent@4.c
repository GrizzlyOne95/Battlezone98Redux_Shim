/*
 * Entry: 0059a2f2
 * Name: _SetEvent@4
 * Namespace: Global
 * Signature: BOOL _SetEvent@4(HANDLE hEvent)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _SetEvent_4(HANDLE hEvent)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2f2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetEvent(hEvent);
  return BVar1;
}
