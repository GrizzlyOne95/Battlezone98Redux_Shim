/*
 * Entry: 00532d28
 * Name: Ordnance_GetOwner
 * Namespace: Global
 * Signature: _OBJ76 * Ordnance_GetOwner(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl Ordnance_GetOwner(_OBJ76 *param_1)

{
  void *pvVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->class_ptr;
  }
  return *(_OBJ76 **)((int)pvVar1 + 0xcc);
}
