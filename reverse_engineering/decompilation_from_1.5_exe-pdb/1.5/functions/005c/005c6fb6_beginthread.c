/*
 * Entry: 005c6fb6
 * Name: beginthread
 * Namespace: Global
 * Signature: undefined beginthread()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* beginthread */

void __cdecl beginthread(_StartAddress *param_1,uint param_2,void *param_3)

{
                    /* WARNING: Could not recover jumptable at 0x005c6fb6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _beginthread(param_1,param_2,param_3);
  return;
}
