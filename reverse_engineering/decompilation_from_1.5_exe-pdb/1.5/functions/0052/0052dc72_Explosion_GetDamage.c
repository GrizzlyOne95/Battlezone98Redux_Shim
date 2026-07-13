/*
 * Entry: 0052dc72
 * Name: Explosion_GetDamage
 * Namespace: Global
 * Signature: DAMAGE * Explosion_GetDamage(DAMAGE * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DAMAGE * __cdecl Explosion_GetDamage(DAMAGE *__return_storage_ptr__,_OBJ76 *param_1)

{
  void *pvVar1;
  
  pvVar1 = param_1->class_ptr;
  __return_storage_ptr__->damager = *(_OBJ76 **)((int)pvVar1 + 0x20);
  __return_storage_ptr__->dmg_source = *(_OBJ76 **)((int)pvVar1 + 0x24);
  *(undefined4 *)&__return_storage_ptr__->field_0x8 = *(undefined4 *)((int)pvVar1 + 0x28);
  __return_storage_ptr__->dmg_value = *(float *)((int)pvVar1 + 0x2c);
  return __return_storage_ptr__;
}
