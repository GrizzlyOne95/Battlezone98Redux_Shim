/*
 * Entry: 0045f205
 * Name: GetPositionNear
 * Namespace: Global
 * Signature: VECTOR_3D * GetPositionNear(VECTOR_3D * __return_storage_ptr__, VECTOR_3D * param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
GetPositionNear(VECTOR_3D *__return_storage_ptr__,VECTOR_3D *param_1,float param_2,float param_3)

{
  float fVar1;
  bool bVar2;
  VECTOR_3D *pVVar3;
  VECTOR_3D local_5c;
  VECTOR_3D local_50;
  float local_44;
  float local_40;
  float local_3c;
  VECTOR_3D local_38;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  int local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_24 = max<float>(3.0,param_3 * 0.5);
  local_38.x = param_1->x;
  local_38.y = param_1->y;
  local_38.z = param_1->z;
  local_38.y = Terrain_FindFloor((double)local_38.x,(double)local_38.z);
  local_14 = 0;
  local_20 = 9999.0;
  __return_storage_ptr__->x = local_38.x;
  __return_storage_ptr__->y = local_38.y;
  bVar2 = false;
  __return_storage_ptr__->z = local_38.z;
  AiUtil_GetExtents((float *)&param_1,&local_c,&local_8,&local_10);
  param_1 = (VECTOR_3D *)((float)param_1 + 10.0);
  local_c = local_c + 10.0;
  local_8 = local_8 - 10.0;
  local_10 = local_10 - 10.0;
  local_28 = param_3 - param_2;
  local_2c = local_24 + local_24;
  do {
    local_18 = RandFloat(6.2831855);
    local_1c = RandFloat(local_28);
    local_1c = local_1c + param_2;
    param_3 = 0.0;
    do {
      pVVar3 = GetCircularPos(&local_50,&local_38,param_3 * local_1c,local_18);
      local_44 = pVVar3->x;
      local_40 = pVVar3->y;
      local_3c = pVVar3->z;
      if (local_2c < ABS(local_40 - local_38.y)) goto LAB_0045f3c9;
      param_3 = param_3 + 0.05;
    } while (param_3 <= 0.9);
    pVVar3 = GetCircularPos(&local_5c,&local_38,local_1c,local_18);
    local_44 = pVVar3->x;
    local_40 = pVVar3->y;
    local_3c = pVVar3->z;
    if (((((float)param_1 <= local_44) && (local_8 < local_44 == (local_8 == local_44))) &&
        (local_c <= local_3c)) && (local_10 < local_3c == (local_10 == local_3c))) {
      fVar1 = ABS(local_40 - local_38.y);
      if (fVar1 < local_20) {
        __return_storage_ptr__->x = pVVar3->x;
        __return_storage_ptr__->y = pVVar3->y;
        __return_storage_ptr__->z = pVVar3->z;
        local_20 = fVar1;
      }
      if (fVar1 < local_24) {
        __return_storage_ptr__->x = pVVar3->x;
        __return_storage_ptr__->y = pVVar3->y;
        __return_storage_ptr__->z = pVVar3->z;
        bVar2 = true;
      }
    }
LAB_0045f3c9:
    local_14 = local_14 + 1;
    if ((bVar2) || (0xff < local_14)) {
      return __return_storage_ptr__;
    }
  } while( true );
}
