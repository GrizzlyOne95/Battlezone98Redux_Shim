/*
 * Entry: 005c6faa
 * Name: time64
 * Namespace: Global
 * Signature: undefined time64()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* time64 */

__time64_t __cdecl time64(__time64_t *param_1)

{
  __time64_t _Var1;
  
                    /* WARNING: Could not recover jumptable at 0x005c6faa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _Var1 = _time64(param_1);
  return _Var1;
}
