/*
 * Entry: 00408023
 * Name: AddCliffForce
 * Namespace: Global
 * Signature: bool AddCliffForce(GameObject * param_1, VECTOR_3D * param_2, float param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AddCliffForce(GameObject *param_1,VECTOR_3D *param_2,float param_3,VECTOR_3D *param_4)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  uint uVar3;
  char cVar4;
  bool bVar5;
  byte bVar6;
  float *pfVar7;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar8;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  int extraout_EAX_04;
  int iVar9;
  VECTOR_3D *pVVar10;
  int iVar11;
  float fVar12;
  double dVar13;
  float fVar14;
  float fVar15;
  VECTOR_3D local_78;
  float local_6c;
  float local_68;
  float local_64;
  VECTOR_3D local_60;
  float local_54;
  float fStack_50;
  float local_4c;
  VECTOR_3D local_48;
  float local_3c;
  float local_38;
  int local_34;
  int local_30;
  int local_2c;
  uint local_28;
  float local_24;
  int local_20;
  int local_1c;
  uint local_18;
  float local_14;
  int local_10;
  int local_c;
  char local_5;
  
  local_5 = '\0';
  pfVar7 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  local_54 = *pfVar7;
  fStack_50 = pfVar7[1];
  local_4c = pfVar7[2];
  local_60.x = (param_1->euler).v.x;
  local_60.y = (param_1->euler).v.y;
  local_60.z = (param_1->euler).v.z;
  floor((double)(Terrain.Grid_Scale * local_54));
  _ftol2_sse();
  local_c = extraout_EAX;
  floor((double)(Terrain.Grid_Scale * local_4c));
  _ftol2_sse();
  local_68 = param_2->y;
  fVar12 = param_2->x - local_54;
  fVar14 = param_2->z - local_4c;
  local_18 = 0;
  local_48.x = 0.0;
  local_48.y = 0.0;
  local_48.z = 0.0;
  local_6c = ((float)local_c + 0.5) * Terrain.Grid_Size - local_54;
  local_64 = Terrain.Grid_Size * ((float)extraout_EAX_00 + 0.5) - local_4c;
  if (ABS(fVar12) <= ABS(fVar14)) {
    if (fVar14 <= 0.0) {
      param_2 = (VECTOR_3D *)0x2;
    }
    else {
      param_2 = (VECTOR_3D *)0x0;
    }
  }
  else if (fVar12 <= 0.0) {
    param_2 = (VECTOR_3D *)0x3;
  }
  else {
    param_2 = (VECTOR_3D *)0x1;
  }
  local_30 = extraout_EAX_00;
  iVar8 = (**(code **)(param_1->_padding_ + 0x2c))();
  fVar12 = Min(0.0,local_60.x);
  floor((double)((fVar12 + *(float *)(iVar8 + 0x44)) * Terrain.Grid_Scale));
  _ftol2_sse();
  local_34 = extraout_EAX_01;
  if (local_c + -1 <= extraout_EAX_01) {
    local_34 = local_c + -1;
  }
  fVar12 = Min(0.0,local_60.z);
  floor((double)((fVar12 + *(float *)(iVar8 + 0x4c)) * Terrain.Grid_Scale));
  _ftol2_sse();
  iVar9 = local_30;
  iVar11 = extraout_EAX_02;
  if (local_30 + -1 <= extraout_EAX_02) {
    iVar11 = local_30 + -1;
  }
  fVar12 = Max(0.0,local_60.x);
  floor((double)((fVar12 + *(float *)(iVar8 + 0x50)) * Terrain.Grid_Scale));
  _ftol2_sse();
  local_2c = extraout_EAX_03;
  if (extraout_EAX_03 <= local_c + 1) {
    local_2c = local_c + 1;
  }
  fVar12 = Max(0.0,local_60.z);
  floor((double)((fVar12 + *(float *)(iVar8 + 0x58)) * Terrain.Grid_Scale));
  _ftol2_sse();
  iVar8 = local_30 + 1;
  local_30 = extraout_EAX_04;
  if (extraout_EAX_04 <= iVar8) {
    local_30 = iVar8;
  }
  local_10 = iVar11;
  if (iVar11 <= local_30) {
    local_1c = iVar11 - iVar9;
    local_20 = local_1c * 2;
    do {
      local_38 = (float)local_34;
      if (local_34 <= local_2c) {
        local_28 = local_34 - local_c;
        local_3c = (float)local_10 + 0.5;
        local_60.y = 0.0;
        iVar8 = local_34;
        do {
          local_60.x = local_54 - ((float)iVar8 + 0.5) * Terrain.Grid_Size;
          local_60.z = local_4c - Terrain.Grid_Size * local_3c;
          local_14 = local_60.x * local_60.x + local_60.z * local_60.z;
          if ((0.0001 < local_14) && (local_14 <= param_3 * param_3)) {
            iVar9 = (local_28 ^ (int)local_28 >> 0x1f) - ((int)local_28 >> 0x1f);
            if (local_1c < iVar9 * 2) {
              if (local_20 < iVar9) {
                if (-iVar9 < local_20) {
                  cVar4 = (iVar8 <= local_c) * '\x04' + '\x02';
                }
                else if (iVar9 * -2 < local_1c) {
                  cVar4 = (iVar8 <= local_c) * '\x02' + '\x03';
                }
                else {
                  cVar4 = '\x04';
                }
              }
              else {
                cVar4 = ((iVar8 <= local_c) - 1U & 0xfa) + 7;
              }
            }
            else {
              cVar4 = '\0';
            }
            local_38 = (float)iVar8;
            bVar5 = CellIsBlocked(iVar8,local_10);
            if (bVar5) {
              local_18 = local_18 | 1 << (cVar4 + (char)param_2 * -2 & 7U);
            }
            bVar6 = CellType(iVar8,local_10);
            iVar9 = Material((uint)bVar6);
            local_24 = sAvoidForceMaterial[iVar9];
            if (local_24 != 0.0) {
              fVar12 = Max(param_1->collisionRadius,7.0);
              local_38 = local_24;
              if (fVar12 * fVar12 < local_14) {
                local_38 = ((fVar12 * fVar12) / local_14) * local_24;
              }
              fVar12 = local_60.x;
              fVar14 = local_60.y;
              fVar15 = local_60.z;
              dVar13 = rsqrt((double)local_14);
              VVar1.y = local_48.y;
              VVar1.x = local_48.x;
              VVar1.z = local_48.z;
              VVar2.y = fVar14;
              VVar2.x = fVar12;
              VVar2.z = fVar15;
              pVVar10 = AddMultVectors(&local_78,VVar1,(float)dVar13 * local_38,VVar2);
              local_48.x = pVVar10->x;
              local_48.y = pVVar10->y;
              local_48.z = pVVar10->z;
              local_5 = '\x01';
            }
          }
          iVar8 = iVar8 + 1;
          local_28 = local_28 + 1;
          local_38 = (float)iVar8;
        } while (iVar8 <= local_2c);
      }
      local_10 = local_10 + 1;
      local_1c = local_1c + 1;
      local_20 = local_20 + 2;
    } while (local_10 <= local_30);
  }
  if ((local_18 != 0) || (local_5 != '\0')) {
    bVar5 = WallCheck(local_18,0x83,4,~DIR_UP,(DirType)param_2,param_1,&local_48);
    uVar3 = local_18;
    if ((bVar5) ||
       (((bVar5 = WallCheck(local_18,0x81,0x46,~DIR_UP,(DirType)param_2,param_1,&local_48), bVar5 ||
         (bVar5 = WallCheck(uVar3,3,0xc4,~DIR_UP,(DirType)param_2,param_1,&local_48), bVar5)) ||
        (bVar5 = WallCheck(uVar3,0x82,1,DIR_UP,(DirType)param_2,param_1,&local_48), bVar5)))) {
LAB_00408570:
      local_5 = '\x01';
      if (225.0 <= param_3 * param_3) {
        pVVar10 = &local_48;
        local_48.z = local_64 + local_48.z;
        local_48.x = local_6c + local_48.x;
        goto LAB_00408508;
      }
    }
    else {
      bVar5 = WallCheck(uVar3,6,0xc1,DIR_LEFT,(DirType)param_2,param_1,&local_48);
      if ((bVar5) ||
         (bVar5 = WallCheck(uVar3,0xc0,7,DIR_RIGHT,(DirType)param_2,param_1,&local_48), bVar5)) {
        local_5 = '\x01';
      }
      else {
        bVar5 = WallCheck(uVar3,0x80,3,DIR_UP,(DirType)param_2,param_1,&local_48);
        if ((bVar5) ||
           (bVar5 = WallCheck(uVar3,2,0x81,DIR_UP,(DirType)param_2,param_1,&local_48), bVar5))
        goto LAB_00408570;
      }
    }
  }
  pVVar10 = &local_60;
  local_60.x = param_4->x + local_48.x;
  local_60.y = param_4->y + local_48.y;
  local_60.z = param_4->z + local_48.z;
LAB_00408508:
  param_4->x = pVVar10->x;
  param_4->y = pVVar10->y;
  param_4->z = pVVar10->z;
  return (bool)local_5;
}
