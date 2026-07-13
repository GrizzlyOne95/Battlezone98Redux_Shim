/*
 * Entry: 00474ed6
 * Name: inside_poly
 * Namespace: Global
 * Signature: int inside_poly(_clsn_poly * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl inside_poly(_clsn_poly *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3)

{
  VECTOR_3D *pVVar1;
  float *unaff_EBX;
  VECTOR_3D local_7c;
  VECTOR_3D local_70;
  VECTOR_3D local_64;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
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
  VECTOR_3D *local_10;
  int local_c;
  ushort *local_8;
  
  local_8 = (ushort *)unaff_EBX[5];
  local_c = 0;
  pVVar1 = &(param_1->plane).surf_normal + local_8[(int)unaff_EBX[4] + -1];
  local_1c = pVVar1->x;
  local_18 = pVVar1->y;
  local_14 = pVVar1->z;
  if (0 < (int)unaff_EBX[4]) {
    local_40 = param_2->x;
    local_3c = param_2->y;
    local_38 = param_2->z;
    do {
      local_10 = &(param_1->plane).surf_normal + *local_8;
      local_28 = local_10->x;
      local_24 = local_10->y;
      local_20 = local_10->z;
      local_64.x = local_28 - local_1c;
      local_64.y = local_24 - local_18;
      local_64.z = local_20 - local_14;
      local_70.x = local_40 - local_1c;
      local_70.y = local_3c - local_18;
      local_70.z = local_38 - local_14;
      local_4c = local_70.x;
      local_48 = local_70.y;
      local_44 = local_70.z;
      local_34 = local_64.x;
      local_30 = local_64.y;
      local_2c = local_64.z;
      pVVar1 = Cross_Product(&local_7c,&local_70,&local_64);
      local_58 = pVVar1->x;
      local_54 = pVVar1->y;
      local_50 = pVVar1->z;
      if (local_50 * unaff_EBX[2] + local_54 * unaff_EBX[1] + *unaff_EBX * local_58 < 0.0) {
        return 0;
      }
      local_c = local_c + 1;
      local_8 = local_8 + 1;
      local_1c = local_10->x;
      local_18 = local_10->y;
      local_14 = local_10->z;
    } while (local_c < (int)unaff_EBX[4]);
  }
  return 1;
}
