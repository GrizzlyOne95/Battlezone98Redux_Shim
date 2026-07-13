/*
 * Entry: 00477857
 * Name: Draw_Sky
 * Namespace: Global
 * Signature: void Draw_Sky(CAMERA * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Draw_Sky(CAMERA *param_1,long param_2,long param_3)

{
  MAT_3D *pMVar1;
  CAMERA *pCVar2;
  long lVar3;
  int iVar4;
  POLYGON_SKIN PVar5;
  POINT_3D *pPVar6;
  CAMERA *pCVar7;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar8;
  CAMERA *pCVar9;
  float10 fVar10;
  float fVar11;
  CAMERA local_388;
  MAT_3D local_170;
  POINT_3D local_130;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_10;
  POLYGON_SKIN local_c;
  CAMERA *local_8;
  
  local_c.Color = 0;
  local_8 = (CAMERA *)(uint)(useD3D == 0);
  if (FogDirection != 0) {
    local_c.Color._1_3_ = 0;
    local_c.Color._0_1_ = Luminance_Table[0][param_2];
  }
  local_10 = FarClip;
  pCVar7 = (CAMERA *)&stack0xfffffe50;
  pCVar2 = param_1;
  pCVar9 = &Old_Camera;
  for (iVar4 = 0x76; iVar4 != 0; iVar4 = iVar4 + -1) {
    pCVar9->Orig_x = pCVar2->Orig_x;
    pCVar2 = (CAMERA *)&pCVar2->Orig_y;
    pCVar9 = (CAMERA *)&pCVar9->Orig_y;
  }
  pMVar1 = Matrix_Inverse((MAT_3D *)pCVar7,unaff_EDI);
  pMVar8 = &local_170;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar8->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
  }
  FarClip = 1200.0;
  pCVar2 = Camera_Init(&local_388,param_1->Buffer,param_1->View_Angle,param_1->Aspect,1200.0,
                       param_1->Zoom_Factor);
  pCVar9 = param_1;
  for (iVar4 = 0x76; iVar4 != 0; iVar4 = iVar4 + -1) {
    pCVar9->Orig_x = pCVar2->Orig_x;
    pCVar2 = (CAMERA *)&pCVar2->Orig_y;
    pCVar9 = (CAMERA *)&pCVar9->Orig_y;
  }
  fVar11 = sign(Old_Camera.Const_x);
  param_1->Const_x = ABS(param_1->Const_x) * fVar11;
  fVar11 = sign(Old_Camera.Const_y);
  param_1->Const_y = ABS(param_1->Const_y) * fVar11;
  Camera_Set_Matrix(param_1,&local_170);
  if (param_3 == 1) {
    if (FogDirection == 0) goto LAB_00477bbd;
    pCVar2 = (CAMERA *)((float)param_1->View_Pyramid[0].y + 900.0);
    lVar3 = Get_Solid_Horizon(&local_130,pCVar2,(float)pCVar7);
    if (lVar3 != 0) {
      PVar5.Color._1_3_ = 0;
      PVar5.Color._0_1_ = Luminance_Table[0][param_2];
      if (useD3D == 0) {
        __Camera_Software_Draw_polygon__(param_1,&local_130,lVar3,PVar5,8);
      }
      else {
        __Camera_Hardware_Draw_polygon__(param_1,&local_130,lVar3,PVar5,8);
      }
    }
    local_8 = (CAMERA *)((float)pCVar2 + 400.0);
    lVar3 = Get_Shaded_Sky((POINT_3D *)param_1,pCVar2,(float)local_8,(float)pCVar7);
    if (lVar3 != 0) {
      if (useD3D == 0) {
        __Camera_Software_Draw_polygon__(param_1,&local_130,lVar3,(POLYGON_SKIN)param_2,9);
      }
      else {
        __Camera_Hardware_Draw_polygon__(param_1,&local_130,lVar3,(POLYGON_SKIN)param_2,9);
      }
    }
    lVar3 = Get_Top_Sky(&local_130,local_8,(float)pCVar7);
    if (lVar3 != 0) goto LAB_00477be6;
  }
  else {
    if ((1 < param_3) && (param_3 < 4)) {
      if (local_8 == (CAMERA *)0x0) {
        Get_Solid_Horizon(&local_130,(CAMERA *)0x461c4000,(float)pCVar7);
        if (useD3D == 0) {
          __Camera_Software_Draw_polygon__(param_1,&local_130,4,local_c,8);
        }
        else {
          __Camera_Hardware_Draw_polygon__(param_1,&local_130,4,local_c,8);
        }
      }
      else {
        (*Device.Refresh.BlitFill)(&Device,local_c.Color);
      }
      if (Sky_Texture.Color != 0) {
        if (SkyType == 0) {
          local_8 = (CAMERA *)TimeStep();
          lVar3 = Get_Tiled_Sky(&local_130,param_1,
                                (float)param_1->View_Pyramid[0].y + (float)SkyHeight);
          if (lVar3 != 0) {
            if (useD3D == 0) {
              __Camera_Software_Draw_polygon__(param_1,&local_130,lVar3,Sky_Texture,0x17);
            }
            else {
              __Camera_Hardware_Draw_polygon__(param_1,&local_130,lVar3,Sky_Texture,0x17);
            }
          }
          local_8 = (CAMERA *)((float)local_8 * 0.03);
          fVar10 = (float10)__CIfmod();
          Sky_Texture_U_Offset = (double)fVar10;
          fVar10 = (float10)__CIfmod();
          Sky_Texture_V_Offset = (double)fVar10;
        }
        else {
          if (useD3D == 0) {
            local_8 = (CAMERA *)TerrainIntensity;
          }
          else {
            local_8 = (CAMERA *)CONCAT22(local_8._2_2_,0xff00);
            local_8 = (CAMERA *)CONCAT31(local_8._1_3_,0xff);
          }
          local_130.Texel.field2_0x8 = (TEXEL_u_8)local_8;
          local_118 = (float)param_1->View_Pyramid[0].x;
          pPVar6 = &local_130;
          local_130.Vector.y = (float)param_1->View_Pyramid[0].y + (float)SkyHeight;
          local_f8 = (float)param_1->View_Pyramid[0].z;
          local_130.Vector.x = local_118 - radius;
          local_130.Vector.z = local_f8 - radius;
          local_130.Texel.u = 0.0;
          local_130.Texel.v = 0.0;
          local_118 = radius + local_118;
          local_10c = 1.0;
          local_108 = 0.0;
          local_f8 = radius + local_f8;
          local_f4 = 1.0;
          local_f0 = 1.0;
          local_d8 = 1.0;
          local_dc = 0.0;
          local_8 = (CAMERA *)0x4;
          local_114 = local_130.Vector.y;
          local_110 = local_130.Vector.z;
          local_100 = local_118;
          local_fc = local_130.Vector.y;
          local_e8 = local_130.Vector.x;
          local_e4 = local_130.Vector.y;
          local_e0 = local_f8;
          do {
            Vector_Transform(&pPVar6->Vector,&pPVar6->Vector,1,&param_1->Matrix);
            pPVar6 = pPVar6 + 1;
            local_8 = (CAMERA *)((int)&local_8[-1].View_Pyramid[4].z + 7);
          } while (local_8 != (CAMERA *)0x0);
          if (useD3D == 0) {
            __Camera_Software_Draw_polygon__(param_1,&local_130,4,Sky_Texture,0x56);
          }
          else {
            __Camera_Hardware_Draw_polygon__(param_1,&local_130,4,Sky_Texture,0x56);
          }
        }
      }
      Draw_Moon_Sun(pCVar7);
      if (2 < param_3) {
        Submit_AnimatedSky(param_1);
        Submit_Stars(param_1);
        Submit_Clouds(param_1);
        Submit_SkyBackdrop(pCVar7);
      }
      goto LAB_00477c08;
    }
LAB_00477bbd:
    if (local_8 == (CAMERA *)0x0) {
      Get_Solid_Horizon(&local_130,(CAMERA *)0x461c4000,(float)pCVar7);
      lVar3 = 4;
      param_2 = local_c.Color;
LAB_00477be6:
      if (useD3D == 0) {
        __Camera_Software_Draw_polygon__(param_1,&local_130,lVar3,(POLYGON_SKIN)param_2,8);
      }
      else {
        __Camera_Hardware_Draw_polygon__(param_1,&local_130,lVar3,(POLYGON_SKIN)param_2,8);
      }
    }
    else {
      (*Device.Refresh.BlitFill)(&Device,local_c.Color);
    }
  }
  Draw_Moon_Sun(pCVar7);
LAB_00477c08:
  pCVar7 = &Old_Camera;
  for (iVar4 = 0x76; iVar4 != 0; iVar4 = iVar4 + -1) {
    param_1->Orig_x = pCVar7->Orig_x;
    pCVar7 = (CAMERA *)&pCVar7->Orig_y;
    param_1 = (CAMERA *)&param_1->Orig_y;
  }
  FarClip = local_10;
  return;
}
