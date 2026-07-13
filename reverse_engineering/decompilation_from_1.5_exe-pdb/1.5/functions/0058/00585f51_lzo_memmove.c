/*
 * Entry: 00585f51
 * Name: lzo_memmove
 * Namespace: Global
 * Signature: void * lzo_memmove(void * param_1, void * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* lzo_memmove */

void * __cdecl lzo_memmove(void *param_1,void *param_2,ulong param_3)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00585f51. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = memmove(param_1,param_2,param_3);
  return pvVar1;
}
