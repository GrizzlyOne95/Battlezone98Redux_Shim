/*
 * Entry: 00525248
 * Name: Damage_Resolve
 * Namespace: Global
 * Signature: void Damage_Resolve(_OBJ76 * param_1, _OBJ76 * param_2, VECTOR_3D * param_3, VECTOR_3D * param_4, VECTOR_3D * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Damage_Resolve(_OBJ76 *param_1,_OBJ76 *param_2,VECTOR_3D *param_3,VECTOR_3D *param_4,
              VECTOR_3D *param_5)

{
  DAMAGE *pDVar1;
  int iVar2;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  DAMAGE local_44;
  DAMAGE local_34;
  DAMAGE local_24;
  DAMAGE local_14;
  
  local_14.damager = (_OBJ76 *)0x0;
  local_14.dmg_source = (_OBJ76 *)0x0;
  local_14._8_4_ = 0;
  local_14.dmg_value = 0.0;
  if (param_2 == (_OBJ76 *)0x0) {
    local_14._8_4_ = 8;
  }
  else {
    if (param_2->class_id == CLASS_ID_ORDNANCE) {
      pDVar1 = Ordnance_GetDamage(&local_44,param_2);
    }
    else if (param_2->class_id == CLASS_ID_EXPLOSION) {
      pDVar1 = Explosion_GetDamage(&local_34,param_2);
    }
    else {
      pDVar1 = GameObject_GetDamage(&local_24,param_2);
    }
    local_14.damager = pDVar1->damager;
    local_14.dmg_source = pDVar1->dmg_source;
    local_14._8_4_ = *(undefined4 *)&pDVar1->field_0x8;
    local_14.dmg_value = pDVar1->dmg_value;
  }
  if ((local_14._8_4_ & 8) != 0) {
    local_14.dmg_value = calc_collision_damage(param_1,param_2,unaff_EDI,unaff_ESI);
    iVar2 = is_user_vhcl(param_1);
    if ((iVar2 != 0) && (20.0 < local_14.dmg_value)) {
      WiggleOneShot((local_14.dmg_value - 20.0) * 0.5);
    }
    if ((((param_2 != (_OBJ76 *)0x0) && (param_1 != (_OBJ76 *)0x0)) &&
        (((*(byte *)((int)&param_1->flags + 2) ^ *(byte *)((int)&param_2->flags + 2)) & 0xf) == 0))
       && (((param_2->class_id == CLASS_ID_HELICOPTER || (param_2->class_id == CLASS_ID_VEHICLE)) &&
           ((param_1->class_id == CLASS_ID_HELICOPTER || (param_1->class_id == CLASS_ID_VEHICLE)))))
       ) {
      local_14.dmg_value = 0.0;
    }
  }
  ClassAllocateDamage(param_1,&local_14,param_5);
  return;
}
