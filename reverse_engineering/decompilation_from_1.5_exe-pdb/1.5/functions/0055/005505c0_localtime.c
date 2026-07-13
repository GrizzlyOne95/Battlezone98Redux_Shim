/*
 * Entry: 005505c0
 * Name: localtime
 * Namespace: Global
 * Signature: tm * localtime(__time64_t * _Time)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tm * __cdecl localtime(__time64_t *_Time)

{
  tm *ptVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005505c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  ptVar1 = _localtime64(_Time);
  return ptVar1;
}
