/*
 * Entry: 004ec8f4
 * Name: obj_class_alloc
 * Namespace: Global
 * Signature: void * obj_class_alloc(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl obj_class_alloc(long param_1)

{
  void *pvVar1;
  
  if (hClassHeap != (void *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x004ec8fe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    pvVar1 = malloc(param_1);
    return pvVar1;
  }
  return (void *)0x0;
}
