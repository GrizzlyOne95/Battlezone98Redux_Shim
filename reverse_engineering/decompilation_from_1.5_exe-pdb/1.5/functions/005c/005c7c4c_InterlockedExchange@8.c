/*
 * Entry: 005c7c4c
 * Name: _InterlockedExchange@8
 * Namespace: Global
 * Signature: LONG _InterlockedExchange@8(LONG * Target, LONG Value)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LONG _InterlockedExchange_8(LONG *Target,LONG Value)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c7c4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = InterlockedExchange(Target,Value);
  return LVar1;
}
