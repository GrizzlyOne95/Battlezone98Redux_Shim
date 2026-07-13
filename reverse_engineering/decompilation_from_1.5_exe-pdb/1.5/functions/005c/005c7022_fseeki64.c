/*
 * Entry: 005c7022
 * Name: fseeki64
 * Namespace: Global
 * Signature: undefined fseeki64()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* fseeki64 */

void __cdecl fseeki64(FILE *param_1,undefined4 param_2,longlong param_3,int param_4)

{
                    /* WARNING: Could not recover jumptable at 0x005c7022. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _fseeki64(param_1,param_3,param_4);
  return;
}
