/*
 * Entry: 005c7c52
 * Name: _InterlockedCompareExchange@12
 * Namespace: Global
 * Signature: LONG _InterlockedCompareExchange@12(LONG * Destination, LONG Exchange, LONG Comperand)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LONG _InterlockedCompareExchange_12(LONG *Destination,LONG Exchange,LONG Comperand)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c7c52. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = InterlockedCompareExchange(Destination,Exchange,Comperand);
  return LVar1;
}
