/*
 * Entry: 00475592
 * Name: WorldVelocity
 * Namespace: Global
 * Signature: VECTOR_3D * WorldVelocity(VECTOR_3D * __return_storage_ptr__, VECTOR_3D param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
WorldVelocity(VECTOR_3D *__return_storage_ptr__,VECTOR_3D param_1,_OBJ76 *param_2)

{
  EULER *pEVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  float *pfVar4;
  EULER local_f4;
  float local_ac [6];
  float local_94;
  float local_90;
  float local_8c;
  VECTOR_3D local_88 [3];
  VECTOR_3D local_64;
  VECTOR_3D local_58;
  VECTOR_3D local_4c;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_10 = 0.0;
  local_c = 0.0;
  local_8 = 0.0;
  __return_storage_ptr__->x = 0.0;
  __return_storage_ptr__->y = 0.0;
  __return_storage_ptr__->z = 0.0;
  for (; param_2 != (_OBJ76 *)0x0; param_2 = obj_get_parent(param_2)) {
    pEVar1 = ClassGetEuler(&local_f4,param_2);
    pfVar4 = local_ac;
    for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = pEVar1->mass;
      pEVar1 = (EULER *)&pEVar1->mass_inv;
      pfVar4 = pfVar4 + 1;
    }
    pVVar2 = Cross_Product(&local_64,&param_1,local_88);
    local_10 = __return_storage_ptr__->x;
    local_c = __return_storage_ptr__->y;
    local_8 = __return_storage_ptr__->z;
    local_40 = pVVar2->x;
    local_3c = pVVar2->y;
    local_38 = pVVar2->z;
    local_4c.x = local_10 + local_40;
    local_4c.y = local_c + local_3c;
    local_4c.z = local_8 + local_38;
    local_34 = local_4c.x;
    local_30 = local_4c.y;
    local_2c = local_4c.z;
    pVVar2 = Vector_Rotate(&local_58,&local_4c,&param_2->transform);
    local_28 = pVVar2->x;
    local_24 = pVVar2->y;
    local_20 = pVVar2->z;
    local_1c = local_94 + local_28;
    local_18 = local_90 + local_24;
    local_14 = local_8c + local_20;
    __return_storage_ptr__->x = local_1c;
    __return_storage_ptr__->y = local_18;
    __return_storage_ptr__->z = local_14;
    Vector_Transform(&param_1,&param_1,1,&param_2->transform);
  }
  return __return_storage_ptr__;
}
