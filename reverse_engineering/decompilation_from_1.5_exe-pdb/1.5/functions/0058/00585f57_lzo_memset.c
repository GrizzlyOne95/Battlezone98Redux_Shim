/*
 * Entry: 00585f57
 * Name: lzo_memset
 * Namespace: Global
 * Signature: void * lzo_memset(void * param_1, int param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl lzo_memset(void *param_1,int param_2,ulong param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c6dfc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = memset(param_1,param_2,param_3);
  return pvVar1;
}
