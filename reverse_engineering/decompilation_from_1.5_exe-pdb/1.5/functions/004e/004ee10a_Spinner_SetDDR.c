/*
 * Entry: 004ee10a
 * Name: Spinner_SetDDR
 * Namespace: Global
 * Signature: void Spinner_SetDDR(_OBJ76 * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Spinner_SetDDR(_OBJ76 *param_1,long param_2)

{
  void *pvVar1;
  
  pvVar1 = param_1->class_ptr;
  *(long *)((int)pvVar1 + 0x10) = param_2;
  *(long *)((int)pvVar1 + 0xc) = param_2;
  return;
}
