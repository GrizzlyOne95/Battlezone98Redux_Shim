/*
 * Entry: 0054070a
 * Name: __Camera_Hardware_Draw_polygon__
 * Namespace: Global
 * Signature: void __Camera_Hardware_Draw_polygon__(CAMERA * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
__Camera_Hardware_Draw_polygon__
          (CAMERA *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4,long param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  int iVar6;
  _GRAPHIC_BUFFER *p_Var7;
  long lVar8;
  long lVar9;
  int unaff_EDI;
  POINT_3D local_358 [32];
  double local_58;
  tagPOINT local_50;
  int local_48;
  int local_44;
  double local_40;
  uint local_38;
  double local_34;
  float local_2c;
  float local_28;
  float local_24;
  undefined8 local_20;
  int local_18;
  int local_14;
  float local_10;
  float local_c;
  float local_8;
  
  if (1 < param_3) {
    if (param_3 == 2) {
      local_2c = (param_2->Vector).x;
      local_28 = (param_2->Vector).y;
      local_24 = (param_2->Vector).z;
      local_10 = param_2[1].Vector.x;
      local_c = param_2[1].Vector.y;
      local_8 = param_2[1].Vector.z;
      fVar1 = local_24 - param_1->View_Frustrum[0].z;
      uVar5 = ((uint)fVar1 & 0xbfffffff | (uint)(local_8 - param_1->View_Frustrum[0].z) >> 1) >>
              0x1e;
      if (uVar5 != 3) {
        fVar3 = local_28;
        fVar4 = local_2c;
        if (uVar5 != 0) {
          fVar2 = param_1->View_Frustrum[0].z - local_24;
          if (((uint)fVar1 & 0x80000000) == 0) {
            fVar2 = fVar2 / (local_8 - local_24);
            local_8 = param_1->View_Frustrum[0].z;
            local_10 = (local_10 - local_2c) * fVar2 + local_2c;
            local_c = (local_c - local_28) * fVar2 + local_28;
          }
          else {
            fVar2 = fVar2 / (local_8 - local_24);
            local_24 = param_1->View_Frustrum[0].z;
            fVar3 = (local_c - local_28) * fVar2 + local_28;
            fVar4 = (local_10 - local_2c) * fVar2 + local_2c;
          }
        }
        fVar1 = param_1->View_Frustrum[4].z - local_24;
        uVar5 = ((uint)fVar1 & 0xbfffffff | (uint)(param_1->View_Frustrum[4].z - local_8) >> 1) >>
                0x1e;
        if (uVar5 != 3) {
          if (uVar5 != 0) {
            if (((uint)fVar1 & 0x80000000) == 0) {
              fVar1 = fVar1 / (local_8 - local_24);
              local_8 = param_1->View_Frustrum[4].z;
              local_10 = (local_10 - fVar4) * fVar1 + fVar4;
              local_c = (local_c - fVar3) * fVar1 + fVar3;
            }
            else {
              fVar1 = fVar1 / (local_8 - local_24);
              local_24 = param_1->View_Frustrum[4].z;
              fVar4 = (local_10 - fVar4) * fVar1 + fVar4;
              fVar3 = (local_c - fVar3) * fVar1 + fVar3;
            }
          }
          fVar1 = (float)Float2Int;
          local_20 = (double)(fVar4 * (1.0 / local_24) * param_1->Const_x + param_1->Orig_x + fVar1)
          ;
          local_58 = (double)(param_1->Const_y * fVar3 * (1.0 / local_24) + param_1->Orig_y + fVar1)
          ;
          local_40 = (double)(local_10 * (1.0 / local_8) * param_1->Const_x + param_1->Orig_x +
                             fVar1);
          local_34 = (double)(param_1->Const_y * local_c * (1.0 / local_8) + param_1->Orig_y + fVar1
                             );
          if (param_1->Buffer->Status != 0) {
            lVar8 = local_58._0_4_;
            lVar9 = (long)local_20;
            param_5 = ComputeOutputCode((long)local_20,local_58._0_4_,&param_1->Buffer->Pane);
            local_38 = ComputeOutputCode(local_40._0_4_,local_34._0_4_,&param_1->Buffer->Pane);
            local_50.y = lVar8;
            while( true ) {
              fVar1 = spriteZ;
              if (local_38 == 0 && param_5 == 0) break;
              if ((param_5 & local_38) != 0) {
                return;
              }
              param_3 = param_5;
              if (param_5 == 0) {
                param_3 = local_38;
              }
              if ((param_3 & 8U) == 0) {
                if ((param_3 & 4U) == 0) {
                  iVar6 = local_34._0_4_ - local_50.y;
                  local_20 = (double)CONCAT44(iVar6,(long)local_20);
                  if ((param_3 & 2U) == 0) {
                    local_14 = (param_1->Buffer->Pane).y1 - local_50.y;
                    local_18 = local_40._0_4_ - lVar9;
                    iVar6 = (int)(((longlong)local_18 * (longlong)local_14) / (longlong)iVar6) +
                            lVar9;
                    p_Var7 = param_1->Buffer;
                    local_50.y = (p_Var7->Pane).y1;
                  }
                  else {
                    local_14 = (param_1->Buffer->Pane).y0 - local_50.y;
                    local_18 = local_40._0_4_ - lVar9;
                    iVar6 = (int)(((longlong)local_18 * (longlong)local_14) / (longlong)iVar6) +
                            lVar9;
                    p_Var7 = param_1->Buffer;
                    local_50.y = (p_Var7->Pane).y0;
                  }
                }
                else {
                  local_20 = (double)CONCAT44(local_40._0_4_ - lVar9,(long)local_20);
                  local_14 = (param_1->Buffer->Pane).x1 - lVar9;
                  local_18 = local_34._0_4_ - local_50.y;
                  local_50.y = local_50.y +
                               (int)(((longlong)local_18 * (longlong)local_14) /
                                    (longlong)(local_40._0_4_ - lVar9));
                  p_Var7 = param_1->Buffer;
                  iVar6 = (p_Var7->Pane).x1;
                }
              }
              else {
                local_18 = local_40._0_4_ - lVar9;
                local_14 = (param_1->Buffer->Pane).x0 - lVar9;
                local_20 = (double)CONCAT44(local_34._0_4_ - local_50.y,(long)local_20);
                local_50.y = local_50.y +
                             (int)(((longlong)(local_34._0_4_ - local_50.y) * (longlong)local_14) /
                                  (longlong)local_18);
                p_Var7 = param_1->Buffer;
                iVar6 = (p_Var7->Pane).x0;
              }
              if (param_3 == param_5) {
                local_58 = (double)CONCAT44(local_58._4_4_,local_50.y);
                param_5 = ComputeOutputCode(iVar6,local_50.y,&p_Var7->Pane);
                lVar9 = iVar6;
              }
              else {
                local_40 = (double)CONCAT44(local_40._4_4_,iVar6);
                local_34 = (double)CONCAT44(local_34._4_4_,local_50.y);
                local_38 = ComputeOutputCode(iVar6,local_50.y,&p_Var7->Pane);
              }
              local_50.y = local_58._0_4_;
            }
            local_48 = local_40._0_4_;
            local_44 = local_34._0_4_;
            spriteZ = (local_8 + local_24) * 0.5;
            local_50.x = lVar9;
            D3D_PolyLine(&local_50,2,param_4);
            spriteZ = fVar1;
          }
        }
      }
    }
    else {
      lVar8 = (*Clip_D3D_Poly_Vtltbl[param_5 & 0x1ffU])
                        (param_1,local_358,param_2,param_3,param_5 & 0x1ffU);
      if (lVar8 != 0) {
        Set_Rounding(unaff_EDI);
        (*Submit_D3D_TL_Vtltbl[param_5 & 0xff])(local_358,lVar8,param_4);
        Set_Rounding(unaff_EDI);
      }
    }
  }
  return;
}
