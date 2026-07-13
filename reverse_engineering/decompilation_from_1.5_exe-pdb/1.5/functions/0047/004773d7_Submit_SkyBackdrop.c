/*
 * Entry: 004773d7
 * Name: Submit_SkyBackdrop
 * Namespace: Global
 * Signature: void Submit_SkyBackdrop(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_SkyBackdrop(CAMERA *param_1)

{
  TEXEL_u_8 TVar1;
  TEXTURE *pTVar2;
  _ZSORTING *p_Var3;
  MAT_3D *pMVar4;
  int iVar5;
  CAMERA *unaff_EBX;
  float *pfVar6;
  MAT_3D *pMVar7;
  VECTOR_3D *pVVar8;
  TEXEL_u_8 *pTVar9;
  ushort uVar10;
  float10 fVar11;
  float10 fVar12;
  double dVar13;
  MAT_3D local_174;
  MAT_3D local_134;
  POINT_3D local_f4;
  POLYGON_SKIN local_d0;
  float local_cc;
  POLYGON_SKIN local_c8;
  POLYGON_SKIN local_b8;
  POLYGON_SKIN local_b4;
  POLYGON_SKIN local_b0;
  TEXEL_u_8 *local_a0;
  POLYGON_SKIN local_9c;
  POLYGON_SKIN local_98;
  VECTOR_3D local_94;
  float local_88;
  undefined4 local_84;
  undefined4 local_80;
  float local_7c;
  float local_78;
  undefined4 local_74;
  float local_70;
  float local_6c;
  undefined4 local_68;
  double local_34;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  TEXEL_u_8 *local_14;
  POLYGON_SKIN local_10;
  float local_c;
  POLYGON_SKIN local_8;
  
  if (SkyBackdrop.name[0] != '\0') {
    local_8 = (POLYGON_SKIN)
              (float)(((float10)unaff_EBX->View_Pyramid[2].x + (float10)unaff_EBX->View_Pyramid[1].x
                      ) * (float10)0.5 - (float10)unaff_EBX->View_Pyramid[0].x);
    local_c = (float)(((float10)unaff_EBX->View_Pyramid[2].z + (float10)unaff_EBX->View_Pyramid[1].z
                      ) * (float10)0.5 - (float10)unaff_EBX->View_Pyramid[0].z);
    dVar13 = rsqrt((double)((float)local_8 * (float)local_8 + local_c * local_c));
    local_8.Color = (long)(local_8.Color * (float)dVar13 * SkyBackdrop.distance);
    local_c = (float)dVar13 * SkyBackdrop.distance * local_c;
    Rot_Mat.posit_x = unaff_EBX->View_Pyramid[0].x + (double)(float)local_8;
    Rot_Mat.posit_y = (double)SkyBackdrop.base;
    Rot_Mat.posit_z = unaff_EBX->View_Pyramid[0].z + (double)local_c;
    pMVar4 = Matrix_Multiply(&local_174,&Rot_Mat,&unaff_EBX->Matrix);
    pMVar7 = &local_134;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar7->right_x = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pMVar7 = (MAT_3D *)&pMVar7->right_y;
    }
    local_28 = (float)((float10)SkyBackdrop.width * (float10)0.5);
    local_94.y = 0.0;
    local_94.z = 0.0;
    local_84 = 0;
    local_80 = 0;
    local_78 = SkyBackdrop.height;
    local_6c = SkyBackdrop.height;
    local_74 = 0;
    local_68 = 0;
    local_f4.Texel.field2_0x8.luma = TerrainIntensity;
    if (useD3D != 0) {
      local_10.Color._0_2_ = 0xff00;
      local_10.Color._0_1_ = 0xff;
      local_f4.Texel.field2_0x8 = (TEXEL_u_8)local_10;
    }
    fVar12 = (float10)fpatan((float10)local_c,(float10)(float)local_8);
    fVar11 = (fVar12 * (float10)pi2_inv + (float10)0.5) * (float10)4.0;
    local_2c = (float)fVar11;
    local_1c = (float)((float10)SkyBackdrop.width /
                       ((float10)SkyBackdrop.distance + (float10)SkyBackdrop.distance) + fVar11);
    local_24 = (float)((float10)1 / ((float10)local_1c - fVar11));
    local_c = (float)fVar11;
    local_34 = (double)(local_1c - 0.001);
    fVar12 = (float10)(local_1c - 0.001);
    uVar10 = (ushort)(fVar11 < fVar12) << 8 | (ushort)(NAN(fVar11) || NAN(fVar12)) << 10;
    local_c8 = (POLYGON_SKIN)local_f4.Texel.field2_0x8;
    local_b0 = (POLYGON_SKIN)local_f4.Texel.field2_0x8;
    local_98 = (POLYGON_SKIN)local_f4.Texel.field2_0x8;
    while ((POPCOUNT((char)(uVar10 >> 8)) & 1U) != 0) {
      fVar12 = (float10)floor((double)local_c);
      local_14 = (TEXEL_u_8 *)(float)((float10)local_c - fVar12);
      fVar12 = (float10)__CIfmod();
      local_20 = (float)(fVar12 * (float10)0.25);
      fVar12 = (float10)1;
      local_18 = (float)((float10)local_c + fVar12);
      if (local_1c < local_18) {
        fVar12 = (float10)floor((double)local_1c);
        fVar12 = (float10)local_1c - fVar12;
      }
      local_8 = (POLYGON_SKIN)(float)fVar12;
      local_10 = (POLYGON_SKIN)(local_20 + 0.25);
      local_94.x = (local_c - local_2c) * local_24 * SkyBackdrop.width - local_28;
      local_88 = ((float)local_8 - (float)local_14) * local_24 * SkyBackdrop.width + local_94.x;
      local_7c = local_88;
      local_70 = local_94.x;
      fVar12 = (float10)floor();
      p_Var3 = SortingTableCurrent;
      local_c = (float)fVar12;
      if (SkyBackdrop.type == 0) {
        local_f4.Texel.u = (float)local_14;
        pfVar6 = &local_f4.Vector.z;
        pVVar8 = &local_94;
        local_f4.Texel.v = local_20;
        local_18 = 5.60519e-45;
        local_d0 = local_8;
        local_cc = local_20;
        local_b8 = local_8;
        local_b4 = local_10;
        local_a0 = local_14;
        local_9c = local_10;
        do {
          Vector_Transform((VECTOR_3D *)(pfVar6 + -2),pVVar8,1,&local_134);
          *pfVar6 = SkyBackdrop.distance;
          pVVar8 = pVVar8 + 1;
          pfVar6 = pfVar6 + 6;
          local_18 = (float)((int)local_18 + -1);
        } while (local_18 != 0.0);
        if (useD3D == 0) {
          __Camera_Software_Draw_polygon__
                    (unaff_EBX,&local_f4,4,(POLYGON_SKIN)SkyBackdrop.bitmap,0x46);
        }
        else {
          __Camera_Hardware_Draw_polygon__
                    (unaff_EBX,&local_f4,4,(POLYGON_SKIN)SkyBackdrop.bitmap,0x46);
        }
      }
      else {
        local_18 = 5.60519e-45;
        SortingTableCurrent->Type = 8;
        p_Var3->vcnt = 4;
        p_Var3->Bitmap_Operation = 0xc4;
        pTVar2 = SkyBackdrop.bitmap;
        p_Var3[1].Type = (long)local_14;
        (p_Var3->Skin_Color).Texture = pTVar2;
        p_Var3[1].Z_Value = local_20;
        pTVar9 = (TEXEL_u_8 *)&p_Var3[1].Next;
        p_Var3[2].Bitmap_Operation = (long)local_8;
        p_Var3[2].Type = (long)local_20;
        p_Var3[3].Skin_Color = local_8;
        p_Var3[3].Bitmap_Operation = (long)local_10;
        p_Var3[4].vcnt = (long)local_14;
        p_Var3[4].Skin_Color = local_10;
        local_14 = &local_f4.Texel.field2_0x8;
        local_10.Texture = (TEXTURE *)&local_94;
        do {
          Vector_Transform((VECTOR_3D *)&pTVar9[-5].l,(VECTOR_3D *)local_10.Texture,1,&local_134);
          TVar1 = *local_14;
          local_10.Texture = (TEXTURE *)(local_10.Color + 0xc);
          local_14 = local_14 + 6;
          *pTVar9 = TVar1;
          pTVar9[-3].luma = SkyBackdrop.distance;
          pTVar9 = pTVar9 + 6;
          local_18 = (float)((int)local_18 + -1);
        } while (local_18 != 0.0);
        p_Var3->Z_Value = SkyBackdrop.distance;
        ZSORTAdd(SkyBackdrop.distance);
      }
      uVar10 = (ushort)(local_c < (float)local_34) << 8 |
               (ushort)(NAN(local_c) || NAN((float)local_34)) << 10;
    }
  }
  return;
}
