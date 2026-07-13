/*
 * Entry: 004967c9
 * Name: GameObject_DamageAlloc
 * Namespace: Global
 * Signature: int GameObject_DamageAlloc(_OBJ76 * param_1, DAMAGE * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GameObject_DamageAlloc(_OBJ76 *param_1,DAMAGE *param_2,VECTOR_3D *param_3)

{
  void *pvVar1;
  uint uVar2;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->gameObj;
  }
  uVar2 = (**(code **)(*(int *)((int)pvVar1 + 0x20) + 0x38))(param_2,param_3);
  return uVar2 & 0xff;
}
