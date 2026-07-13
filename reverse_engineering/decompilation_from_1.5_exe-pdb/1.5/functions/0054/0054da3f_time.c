/*
 * Entry: 0054da3f
 * Name: time
 * Namespace: Global
 * Signature: __time64_t time(__time64_t * _Time)
 * Symbol source: IMPORTED
 * Export status: ok
 */

__time64_t __cdecl time(__time64_t *_Time)

{
  __time64_t _Var1;
  
                    /* WARNING: Could not recover jumptable at 0x0054da3f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _Var1 = _time64(_Time);
  return _Var1;
}
