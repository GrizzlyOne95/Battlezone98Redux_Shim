/*
 * Entry: 00496738
 * Name: GameObject_GetDamage
 * Namespace: Global
 * Signature: DAMAGE * GameObject_GetDamage(DAMAGE * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DAMAGE * __cdecl GameObject_GetDamage(DAMAGE *__return_storage_ptr__,_OBJ76 *param_1)

{
  uint uVar1;
  void *pvVar2;
  short sVar3;
  ushort uVar4;
  
  __return_storage_ptr__->damager = (_OBJ76 *)0x0;
  __return_storage_ptr__->dmg_source = (_OBJ76 *)0x0;
  *(undefined4 *)&__return_storage_ptr__->field_0x8 = 0;
  __return_storage_ptr__->dmg_value = 0.0;
  uVar1 = param_1->flags;
  __return_storage_ptr__->damager = param_1;
  __return_storage_ptr__->dmg_source = param_1;
  pvVar2 = param_1->gameObj;
  uVar4 = ((ushort)((uVar1 & 0x30) != 0) | ((ushort)(uVar1 >> 5) & 1) * 2) << 4 |
          *(ushort *)&__return_storage_ptr__->field_0x8 & 0xffc8 | 8;
  *(ushort *)&__return_storage_ptr__->field_0x8 = uVar4;
  if (pvVar2 == (void *)0x0) {
    *(ushort *)&__return_storage_ptr__->field_0x8 =
         ((ushort)((uVar1 >> 0x10) << 6) ^ uVar4) & 0x3c0 ^ uVar4;
  }
  else {
    sVar3 = (**(code **)(*(int *)((int)pvVar2 + 0x20) + 4))();
    *(ushort *)&__return_storage_ptr__->field_0x8 =
         *(ushort *)&__return_storage_ptr__->field_0x8 ^
         (sVar3 << 6 ^ *(ushort *)&__return_storage_ptr__->field_0x8) & 0x3c0;
  }
  return __return_storage_ptr__;
}
