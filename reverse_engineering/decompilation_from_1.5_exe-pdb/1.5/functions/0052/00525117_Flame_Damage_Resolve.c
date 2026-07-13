/*
 * Entry: 00525117
 * Name: Flame_Damage_Resolve
 * Namespace: Global
 * Signature: void Flame_Damage_Resolve(_OBJ76 * param_1, DAMAGE param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Flame_Damage_Resolve(_OBJ76 *param_1,DAMAGE param_2,VECTOR_3D *param_3)

{
  ClassAllocateDamage(param_1,&param_2,param_3);
  if (param_2.damager != (_OBJ76 *)0x0) {
    is_vhcl(param_1);
  }
  return;
}
