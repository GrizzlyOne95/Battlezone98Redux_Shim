/*
 * Entry: 00532cb5
 * Name: Ordnance_GetDamage
 * Namespace: Global
 * Signature: DAMAGE * Ordnance_GetDamage(DAMAGE * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DAMAGE * __cdecl Ordnance_GetDamage(DAMAGE *__return_storage_ptr__,_OBJ76 *param_1)

{
  void *pvVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->class_ptr;
  }
  __return_storage_ptr__->damager = *(_OBJ76 **)((int)pvVar1 + 100);
  __return_storage_ptr__->dmg_source = *(_OBJ76 **)((int)pvVar1 + 0x68);
  *(undefined4 *)&__return_storage_ptr__->field_0x8 = *(undefined4 *)((int)pvVar1 + 0x6c);
  __return_storage_ptr__->dmg_value = *(float *)((int)pvVar1 + 0x70);
  return __return_storage_ptr__;
}
