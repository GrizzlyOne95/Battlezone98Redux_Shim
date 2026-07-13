/*
 * Entry: 0059a29e
 * Name: _CreateEventA@16
 * Namespace: Global
 * Signature: HANDLE _CreateEventA@16(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _CreateEventA_16(LPSECURITY_ATTRIBUTES lpEventAttributes,BOOL bManualReset,BOOL bInitialState
                       ,LPCSTR lpName)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a29e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = CreateEventA(lpEventAttributes,bManualReset,bInitialState,lpName);
  return pvVar1;
}
