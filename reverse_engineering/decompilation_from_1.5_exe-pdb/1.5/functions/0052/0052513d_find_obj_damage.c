/*
 * Entry: 0052513d
 * Name: find_obj_damage
 * Namespace: Global
 * Signature: void find_obj_damage(_OBJ76 * param_1, DAMAGE * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl find_obj_damage(_OBJ76 *param_1,DAMAGE *param_2)

{
  _OBJ76 *in_EAX;
  DAMAGE *pDVar1;
  undefined4 *in_ECX;
  DAMAGE local_34;
  DAMAGE local_24;
  DAMAGE local_14;
  
  if (in_EAX == (_OBJ76 *)0x0) {
    *(ushort *)(in_ECX + 2) = *(ushort *)(in_ECX + 2) & 0xfc38 | 8;
  }
  else {
    if (in_EAX->class_id == CLASS_ID_ORDNANCE) {
      pDVar1 = Ordnance_GetDamage(&local_34,in_EAX);
    }
    else if (in_EAX->class_id == CLASS_ID_EXPLOSION) {
      pDVar1 = Explosion_GetDamage(&local_24,in_EAX);
    }
    else {
      pDVar1 = GameObject_GetDamage(&local_14,in_EAX);
    }
    *in_ECX = pDVar1->damager;
    in_ECX[1] = pDVar1->dmg_source;
    in_ECX[2] = *(undefined4 *)&pDVar1->field_0x8;
    in_ECX[3] = pDVar1->dmg_value;
  }
  return;
}
