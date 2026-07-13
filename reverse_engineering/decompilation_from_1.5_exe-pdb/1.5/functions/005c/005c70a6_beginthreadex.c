/*
 * Entry: 005c70a6
 * Name: beginthreadex
 * Namespace: Global
 * Signature: undefined beginthreadex()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* beginthreadex */

void __cdecl
beginthreadex(void *param_1,uint param_2,_StartAddress *param_3,void *param_4,uint param_5,
             uint *param_6)

{
                    /* WARNING: Could not recover jumptable at 0x005c70a6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _beginthreadex(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}
