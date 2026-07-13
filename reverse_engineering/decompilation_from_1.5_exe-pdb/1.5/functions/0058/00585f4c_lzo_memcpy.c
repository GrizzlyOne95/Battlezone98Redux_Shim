/*
 * Entry: 00585f4c
 * Name: lzo_memcpy
 * Namespace: Global
 * Signature: void * lzo_memcpy(void * param_1, void * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl lzo_memcpy(void *param_1,void *param_2,ulong param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c6f4a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = memcpy(param_1,param_2,param_3);
  return pvVar1;
}
