/*
 * Entry: 004cd7b3
 * Name: EngineFlame::Submit
 * Namespace: EngineFlame
 * Signature: void Submit(EngineFlame * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EngineFlame::Submit(EngineFlame *this,CAMERA *param_1)

{
  VECTOR_3D VVar1;
  _ZSORTING *p_Var2;
  MAT_3D *pMVar3;
  VECTOR_3D *pVVar4;
  long lVar5;
  int iVar6;
  Flame *pFVar7;
  float *pfVar8;
  bool bVar9;
  float fVar10;
  MAT_3D local_130;
  VECTOR_3D local_f0;
  VECTOR_3D local_e4;
  float local_d8 [4];
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  double local_b0;
  double local_a8;
  double local_a0;
  float local_98;
  POLYGON_SKIN local_94;
  float local_90;
  float local_8c;
  POLYGON_SKIN local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  _ZSORTING *local_54;
  _ZSORTING *local_50;
  float local_4c;
  POLYGON_SKIN local_48;
  float local_44;
  float local_40;
  _ZSORTING *local_3c;
  _ZSORTING *local_38;
  float local_34;
  POLYGON_SKIN local_30;
  float local_2c;
  Flame *local_28;
  EngineFlame *local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pFVar7 = this->flameList;
  bVar9 = pFVar7 < this->flamePtr;
  local_24 = this;
  while (bVar9) {
    local_28 = pFVar7;
    pMVar3 = Matrix_Multiply(&local_130,&pFVar7->transform,&param_1->Matrix);
    local_8 = pFVar7->scale;
    fVar10 = local_24->flameLength * local_8;
    pfVar8 = local_d8;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar8 = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pfVar8 = pfVar8 + 1;
    }
    local_2c = fVar10 + fVar10;
    local_14 = (float)local_b0;
    local_10 = (float)local_a8;
    local_c = (float)local_a0;
    local_20 = local_c0 * local_2c + (float)local_b0;
    local_1c = local_bc * local_2c + (float)local_a8;
    local_18 = local_2c * local_b8 + (float)local_a0;
    local_80 = local_20 + local_14;
    local_7c = local_1c + local_10;
    local_78 = local_18 + local_c;
    VVar1.y = local_7c;
    VVar1.x = local_80;
    VVar1.z = local_78;
    pVVar4 = ScaleVector(&local_f0,0.5,VVar1);
    local_e4.x = pVVar4->x;
    local_e4.y = pVVar4->y;
    local_e4.z = pVVar4->z;
    lVar5 = Camera_Bounding_Sphere_Test(param_1,&local_e4,local_2c * 0.5);
    p_Var2 = SortingTableCurrent;
    if (lVar5 < 1) {
      local_74 = local_d8[0] * local_8;
      SortingTableCurrent->vcnt = 0;
      local_70 = local_d8[1] * local_8;
      p_Var2->Type = 10;
      local_6c = local_d8[2] * local_8;
      p_Var2->Bitmap_Operation = 4;
      local_98 = local_74 + local_14;
      (p_Var2->Skin_Color).Texture = (TEXTURE *)(local_24->flameTexture + local_24->flameIndex);
      local_94 = (POLYGON_SKIN)(local_70 + local_10);
      local_90 = local_c + local_6c;
      p_Var2[1].vcnt = (long)local_98;
      local_5c = local_74 + local_20;
      p_Var2[1].Skin_Color = local_94;
      p_Var2[1].Bitmap_Operation = (long)local_90;
      local_58 = local_70 + local_1c;
      local_54 = (_ZSORTING *)(local_18 + local_6c);
      p_Var2[1].Type = (long)local_5c;
      local_38 = (_ZSORTING *)(local_20 - local_74);
      p_Var2[1].Z_Value = local_58;
      p_Var2[1].Next = local_54;
      local_34 = local_1c - local_70;
      local_30 = (POLYGON_SKIN)(local_18 - local_6c);
      p_Var2[1].Previous = local_38;
      local_74 = local_14 - local_74;
      p_Var2[2].vcnt = (long)local_34;
      p_Var2[2].Skin_Color = local_30;
      local_70 = local_10 - local_70;
      local_6c = local_c - local_6c;
      p_Var2[2].Bitmap_Operation = (long)local_74;
      p_Var2[2].Type = (long)local_70;
      p_Var2[2].Z_Value = local_6c;
      fVar10 = VectGetMin((VECTOR_3D *)(p_Var2 + 1),4);
      p_Var2->Z_Value = fVar10;
      ZSORTAdd(fVar10);
      p_Var2 = SortingTableCurrent;
      local_68 = local_d8[3] * local_8;
      local_64 = local_c8 * local_8;
      SortingTableCurrent->vcnt = 0;
      local_60 = local_c4 * local_8;
      p_Var2->Type = 10;
      p_Var2->Bitmap_Operation = 4;
      local_8c = local_68 + local_14;
      (p_Var2->Skin_Color).Texture = (TEXTURE *)(local_24->flameTexture + local_24->flameIndex);
      local_88 = (POLYGON_SKIN)(local_64 + local_10);
      local_84 = local_c + local_60;
      p_Var2[1].vcnt = (long)local_8c;
      local_44 = local_68 + local_20;
      p_Var2[1].Skin_Color = local_88;
      p_Var2[1].Bitmap_Operation = (long)local_84;
      local_40 = local_64 + local_1c;
      local_3c = (_ZSORTING *)(local_18 + local_60);
      p_Var2[1].Type = (long)local_44;
      local_50 = (_ZSORTING *)(local_20 - local_68);
      p_Var2[1].Z_Value = local_40;
      p_Var2[1].Next = local_3c;
      local_4c = local_1c - local_64;
      local_48 = (POLYGON_SKIN)(local_18 - local_60);
      p_Var2[1].Previous = local_50;
      local_68 = local_14 - local_68;
      p_Var2[2].vcnt = (long)local_4c;
      p_Var2[2].Skin_Color = local_48;
      local_64 = local_10 - local_64;
      local_60 = local_c - local_60;
      p_Var2[2].Bitmap_Operation = (long)local_68;
      p_Var2[2].Type = (long)local_64;
      p_Var2[2].Z_Value = local_60;
      fVar10 = VectGetMin((VECTOR_3D *)(p_Var2 + 1),4);
      p_Var2->Z_Value = fVar10;
      ZSORTAdd(fVar10);
      pFVar7 = local_28;
    }
    pFVar7 = pFVar7 + 1;
    bVar9 = pFVar7 < local_24->flamePtr;
  }
  return;
}
