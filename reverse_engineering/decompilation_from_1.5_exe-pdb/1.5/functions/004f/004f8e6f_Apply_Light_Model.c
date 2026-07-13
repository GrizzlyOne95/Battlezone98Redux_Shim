/*
 * Entry: 004f8e6f
 * Name: Apply_Light_Model
 * Namespace: Global
 * Signature: void Apply_Light_Model(float * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3, MAT_3D * param_4, MAT_3D * param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Apply_Light_Model(float *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3,MAT_3D *param_4,
                 MAT_3D *param_5,long param_6)

{
  DYNAMIC_LIGHT *pDVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  long lVar5;
  VECTOR_3D *pVVar6;
  VECTOR_3D *pVVar7;
  VECTOR_3D *pVVar8;
  float *pfVar9;
  int iVar10;
  float *pfVar11;
  float fVar12;
  float local_80;
  float local_7c [11];
  VECTOR_3D local_50;
  float local_44;
  float local_40;
  float local_3c;
  VECTOR_3D local_38;
  float local_2c;
  float local_28;
  long local_24;
  int local_20;
  float *local_1c;
  int local_18;
  VECTOR_3D *local_14;
  float local_10;
  float local_c;
  int local_8;
  
  lVar5 = Lights_Struct.Apply_Light_Counter;
  local_24 = Lights_Struct.Apply_Light_Counter;
  pVVar7 = Vector_Unrotate(&local_38,&Sun_Light,param_4);
  local_44 = pVVar7->x;
  local_28 = -TOD_tbl[Lights_Struct.TOD_entry].Att;
  local_40 = pVVar7->y;
  local_2c = TOD_tbl[Lights_Struct.TOD_entry].Ambient;
  local_3c = pVVar7->z;
  if (TOD_tbl[Lights_Struct.TOD_entry].Day_Time == 1) {
    if (View_Record.Current_View == OVER_VIEW) {
      if (0 < param_6) {
        for (; param_6 != 0; param_6 = param_6 + -1) {
          *param_1 = 0.3;
          param_1 = param_1 + 1;
        }
      }
    }
    else {
      iVar10 = 0;
      if (0 < param_6) {
        pfVar9 = &param_2->z;
        do {
          fVar12 = Get_Depth_Attenuation(*pfVar9);
          pfVar9 = pfVar9 + 3;
          param_1[iVar10] = fVar12 * 0.7 + 0.3;
          iVar10 = iVar10 + 1;
        } while (iVar10 < param_6);
      }
    }
  }
  else {
    local_8 = 0;
    if (0 < lVar5) {
      local_14 = (VECTOR_3D *)&local_80;
      do {
        pVVar8 = Vector_Unrotate(&local_38,&Lights_Struct.Apply_Lights[local_8]->World_Direction,
                                 param_4);
        pVVar7 = local_14;
        pfVar9 = (float *)((int)local_14 + 4);
        pVVar6 = (VECTOR_3D *)((int)local_14 + 0xc);
        local_14->x = pVVar8->x;
        local_14 = pVVar6;
        iVar10 = local_8 + 1;
        local_8 = iVar10;
        *pfVar9 = pVVar8->y;
        *(float *)((int)pVVar7 + 8) = pVVar8->z;
      } while (iVar10 < lVar5);
    }
    local_8 = 0;
    if (0 < param_6) {
      local_18 = (int)param_3 - (int)param_2;
      local_14 = param_3;
      pfVar9 = &param_2->z;
      do {
        local_c = (*(float *)(local_18 + (int)pfVar9) * local_3c +
                  param_3->x * local_44 + ((float *)(local_18 + (int)pfVar9))[-1] * local_40) *
                  local_28;
        if (local_c < 0.0) {
          local_c = 0.0;
        }
        local_20 = 0;
        local_14 = param_3;
        if (0 < local_24) {
          pfVar11 = local_7c;
          local_1c = pfVar11;
          do {
            pDVar1 = Lights_Struct.Apply_Lights[local_20];
            fVar12 = ((VECTOR_3D *)(pfVar9 + -2))->x - (pDVar1->Camera_Pos).x;
            fVar3 = pfVar9[-1] - (pDVar1->Camera_Pos).y;
            fVar4 = *pfVar9 - (pDVar1->Camera_Pos).z;
            fVar2 = fVar12 * fVar12 + fVar3 * fVar3 + fVar4 * fVar4;
            local_10 = 1.0 / (pDVar1->Att_Dist * fVar2 + 1.0);
            if ((pDVar1->flags & 1) == 0) {
              local_38.z = 1.0 / (SQRT(fVar2) + 0.5);
              local_38.x = local_38.z * fVar12;
              local_38.y = local_38.z * fVar3;
              local_38.z = fVar4 * local_38.z;
              local_1c = pfVar11;
              pVVar7 = Vector_Unrotate(&local_50,&local_38,param_5);
              local_38.x = pVVar7->x;
              local_38.y = pVVar7->y;
              local_38.z = pVVar7->z;
              fVar12 = (local_14->x * pVVar7->x + local_14->y * pVVar7->y + local_14->z * pVVar7->z)
                       * local_10;
              param_3 = local_14;
              if (fVar12 < 0.0) {
                fVar12 = 0.0;
              }
            }
            else {
              local_1c = (float *)-(param_3->y * *pfVar11 +
                                   pfVar11[-1] * param_3->x + param_3->z * pfVar11[1]);
              if ((float)local_1c <= 0.0) {
                local_1c = (float *)0x0;
              }
              else {
                fVar2 = 1.0 / (SQRT(fVar2) + 0.5);
                fVar12 = Pow((double)((1.0 - ((pDVar1->Camera_Direction).z * fVar2 * fVar4 +
                                              (pDVar1->Camera_Direction).y * fVar2 * fVar3 +
                                             (pDVar1->Camera_Direction).x * fVar2 * fVar12)) * 0.5),
                             (double)pDVar1->Cone);
                local_10 = fVar12 * local_10;
              }
              fVar12 = (float)local_1c * local_10 * 1.25;
              local_1c = pfVar11;
            }
            local_20 = local_20 + 1;
            pfVar11 = local_1c + 3;
            local_c = fVar12 + local_c;
            local_1c = pfVar11;
          } while (local_20 < local_24);
        }
        fVar12 = Get_Depth_Attenuation(*pfVar9);
        fVar12 = (local_c + local_2c) * (1.0 - fVar12);
        if (!NAN(fVar12) && 1.0 < fVar12 != (fVar12 == 1.0)) {
          fVar12 = 1.0;
        }
        param_1[local_8] = fVar12;
        local_8 = local_8 + 1;
        param_3 = param_3 + 1;
        pfVar9 = pfVar9 + 3;
        local_14 = param_3;
      } while (local_8 < param_6);
    }
  }
  return;
}
