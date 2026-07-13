/*
 * Entry: 004d0722
 * Name: LensFlare::Render
 * Namespace: LensFlare
 * Signature: void Render(LensFlare * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LensFlare::Render(LensFlare *this)

{
  float fVar1;
  float fVar2;
  _GRAPHIC_BUFFER *p_Var3;
  VECTOR_3D *pVVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  VECTOR_3D local_80;
  float local_74;
  float local_70;
  undefined4 local_6c;
  float local_68;
  float local_64;
  undefined4 local_60;
  float local_5c;
  float local_58;
  undefined4 local_54;
  VECTOR_3D local_50;
  float local_44;
  float local_40;
  float local_3c;
  double local_38;
  int local_30;
  int local_2c;
  double local_28;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  byte *local_10;
  int local_c;
  int local_8;
  
  if (((SunIndex != 0) && (View_Record.Current_View != TWO_D_VIEW)) &&
     (View_Record.Current_View != EDIT_VIEW)) {
    pVVar4 = Vector_Rotate(&local_50,&Sun_Light,&View_Record.MainCam.Matrix);
    p_Var3 = View_Record.MainCam.Buffer;
    local_44 = pVVar4->x;
    local_40 = pVVar4->y;
    local_3c = pVVar4->z;
    if (View_Record.MainCam.View_Frustrum[0].z <= local_3c) {
      iVar8 = ((View_Record.MainCam.Buffer)->Pane).x0;
      iVar6 = ((View_Record.MainCam.Buffer)->Pane).x1;
      local_30 = (iVar8 + iVar6) / 2;
      iVar7 = ((View_Record.MainCam.Buffer)->Pane).y0;
      local_2c = (((View_Record.MainCam.Buffer)->Pane).y1 + iVar7) / 2;
      local_28 = (double)(View_Record.MainCam.Const_x * local_44 * (1.0 / local_3c) +
                          View_Record.MainCam.Orig_x + (float)Float2Int);
      local_38 = (double)(View_Record.MainCam.Const_y * local_40 * (1.0 / local_3c) +
                          View_Record.MainCam.Orig_y + (float)Float2Int);
      if (((iVar8 <= local_28._0_4_) && (local_28._0_4_ <= iVar6)) &&
         ((iVar7 <= local_38._0_4_ && (local_38._0_4_ <= ((View_Record.MainCam.Buffer)->Pane).y1))))
      {
        local_8 = 0;
        iVar8 = local_28._0_4_ + -2;
        if (useD3D == 0) {
          local_c = 0;
          if (-1 < iVar8) {
            local_c = iVar8;
          }
          local_14 = local_28._0_4_ + 2;
          if (iVar6 + -1 <= local_28._0_4_ + 2) {
            local_14 = iVar6 + -1;
          }
          iVar8 = local_38._0_4_ + -2;
          if (iVar8 < 0) {
            iVar8 = 0;
          }
          iVar6 = (View_Record.MainCam.Buffer)->Height + -1;
          if (local_38._0_4_ + 2 < iVar6) {
            iVar6 = local_38._0_4_ + 2;
          }
          if (iVar8 <= iVar6) {
            iVar7 = iVar8 - local_38._0_4_;
            pbVar5 = (View_Record.MainCam.Buffer)->Buffer +
                     local_c + (View_Record.MainCam.Buffer)->Width * iVar8;
            local_1c = (iVar6 - iVar8) + 1;
            do {
              local_20 = iVar7 * iVar7;
              if (local_c <= local_14) {
                local_18 = local_c - local_28._0_4_;
                iVar8 = (local_14 - local_c) + 1;
                local_10 = pbVar5;
                do {
                  if ((local_18 * local_18 + local_20 < 6) &&
                     ((uint)*local_10 == DisplayInterface::colorWhite)) {
                    local_8 = local_8 + 1;
                  }
                  local_18 = local_18 + 1;
                  local_10 = local_10 + 1;
                  iVar8 = iVar8 + -1;
                } while (iVar8 != 0);
              }
              pbVar5 = pbVar5 + (View_Record.MainCam.Buffer)->Width;
              iVar7 = iVar7 + 1;
              local_1c = local_1c + -1;
            } while (local_1c != 0);
            local_1c = 0;
          }
          fVar1 = 0.047;
        }
        else {
          local_80.x = (float)iVar8;
          local_1c = local_38._0_4_ + 3;
          local_80.y = (float)(local_38._0_4_ + -2);
          local_80.z = 1000.0;
          local_74 = (float)(local_28._0_4_ + 3);
          local_6c = 0x447a0000;
          local_64 = (float)local_1c;
          local_60 = 0x447a0000;
          local_54 = 0x447a0000;
          local_70 = local_80.y;
          local_68 = local_74;
          local_5c = local_80.x;
          local_58 = local_64;
          local_8 = D3D_Occlusion_Query(&local_80,4);
          fVar1 = 0.04;
        }
        iVar8 = local_38._0_4_;
        iVar6 = local_28._0_4_;
        if (0 < local_8) {
          fVar2 = local_3c * local_3c * local_3c * local_3c;
          fVar2 = fVar2 * fVar2;
          fVar2 = fVar2 * fVar2;
          ColorFade::SetGlare(&colorFade,fVar2 * fVar2 * (float)local_8 * fVar1);
          iVar8 = local_38._0_4_;
          iVar6 = local_28._0_4_;
        }
        if (local_8 != 0) {
          local_20 = iVar6 - local_30;
          iVar8 = iVar8 - local_2c;
          uVar9 = 0;
          do {
            iVar6 = *(int *)((int)&RING_MAPS[0].fraction + uVar9);
            DrawSprite(p_Var3,*(int *)((int)&RING_MAPS[0].index + uVar9),
                       (iVar6 * local_20 >> 8) + local_30,(iVar6 * iVar8 >> 8) + local_2c,0x250004);
            uVar9 = uVar9 + 0xc;
          } while (uVar9 < 0x48);
        }
      }
    }
  }
  return;
}
