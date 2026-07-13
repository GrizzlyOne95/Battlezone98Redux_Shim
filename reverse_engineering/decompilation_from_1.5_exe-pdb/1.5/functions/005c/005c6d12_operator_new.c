/*
 * Entry: 005c6d12
 * Name: operator_new
 * Namespace: Global
 * Signature: void * operator_new(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* void * __cdecl operator new(unsigned int) */

void * __cdecl operator_new(uint param_1)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c6d12. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = operator_new(param_1);
  return pvVar1;
}
