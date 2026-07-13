/*
 * Entry: 0052a1d7
 * Name: Beam::Submit
 * Namespace: Beam
 * Signature: void Submit(Beam * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Beam::Submit(Beam *this,CAMERA *param_1)

{
  float fVar1;
  float fVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  _ZSORTING *p_Var6;
  MAT_3D *pMVar7;
  VECTOR_3D *pVVar8;
  uint uVar9;
  long lVar10;
  int iVar11;
  float *pfVar12;
  MAT_3D *pMVar13;
  float fVar14;
  MAT_3D local_140;
  VECTOR_3D local_100;
  float local_f4;
  POLYGON_SKIN local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  _ZSORTING *local_c8;
  VECTOR_3D local_c4;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  _ZSORTING *local_a0;
  float local_9c;
  POLYGON_SKIN local_98;
  _ZSORTING *local_94;
  float local_90;
  POLYGON_SKIN local_8c;
  float local_88;
  POLYGON_SKIN local_84;
  float local_80;
  float local_7c;
  float local_78;
  _ZSORTING *local_74;
  float local_70;
  float local_6c;
  float local_68;
  MAT_3D local_64;
  _ZSORTING *local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pfVar12 = (float *)(this->_padding_ + 0x20);
  pMVar7 = &local_64;
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    pMVar7->right_x = *pfVar12;
    pfVar12 = pfVar12 + 1;
    pMVar7 = (MAT_3D *)&pMVar7->right_y;
  }
  local_20 = (float)(((float10)local_64.posit_z - (float10)(this->origin).z) *
                     (float10)local_64.front_z +
                     (float10)local_64.front_y *
                     ((float10)local_64.posit_y - (float10)(this->origin).y) +
                    (float10)local_64.front_x *
                    ((float10)local_64.posit_x - (float10)(this->origin).x));
  local_64.posit_x = (this->origin).x;
  local_64.posit_y = (this->origin).y;
  local_64.posit_z = (this->origin).z;
  pMVar7 = Matrix_Multiply(&local_140,&local_64,&param_1->Matrix);
  pMVar13 = &local_64;
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    pMVar13->right_x = pMVar7->right_x;
    pMVar7 = (MAT_3D *)&pMVar7->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  local_10 = (float)local_64.posit_x;
  local_c = (float)local_64.posit_y;
  local_8 = (float)local_64.posit_z;
  local_1c = local_64.up_x;
  local_18 = local_64.up_y;
  local_14 = local_64.up_z;
  VVar3.y = local_64.up_y;
  VVar3.x = local_64.up_x;
  VVar3.z = local_64.up_z;
  pVVar8 = ScaleVector(&local_c4,*(float *)(this->_padding_ + 0x70),VVar3);
  local_b8 = pVVar8->x;
  local_1c = local_64.right_x;
  local_18 = local_64.right_y;
  local_b4 = pVVar8->y;
  local_b0 = pVVar8->z;
  local_14 = local_64.right_z;
  VVar4.y = local_64.right_y;
  VVar4.x = local_64.right_x;
  VVar4.z = local_64.right_z;
  pVVar8 = ScaleVector(&local_c4,*(float *)(this->_padding_ + 0x70),VVar4);
  local_e8 = pVVar8->x;
  local_e4 = pVVar8->y;
  local_e0 = pVVar8->z;
  while (local_d4 = local_8, local_d8 = local_c, local_dc = local_10, 0.0 < local_20) {
    local_1c = local_10;
    local_18 = local_c;
    local_14 = local_8;
    if (local_20 <= *(float *)(this->_padding_ + 0x74)) {
      local_10 = local_64.front_x * local_20 + (float)local_64.posit_x;
      local_64.posit_x = (double)local_10;
      local_c = local_64.front_y * local_20 + (float)local_64.posit_y;
      local_64.posit_y = (double)local_c;
      local_8 = local_64.front_z * local_20 + (float)local_64.posit_z;
      local_64.posit_z = (double)local_8;
      fVar14 = local_20;
    }
    else {
      fVar14 = *(float *)(this->_padding_ + 0x74);
      local_10 = local_64.front_x * fVar14 + (float)local_64.posit_x;
      local_64.posit_x = (double)local_10;
      local_c = local_64.front_y * fVar14 + (float)local_64.posit_y;
      local_64.posit_y = (double)local_c;
      local_8 = local_64.front_z * fVar14 + (float)local_64.posit_z;
      local_64.posit_z = (double)local_8;
      if (0.0 < *(float *)(this->_padding_ + 0x78)) {
        uVar9 = Rand_Counter + 1U & 0xff;
        fVar1 = Pseudo_Rand_Number[uVar9] * *(float *)(this->_padding_ + 0x78);
        Rand_Counter = uVar9 + 1 & 0xff;
        fVar2 = Pseudo_Rand_Number[Rand_Counter] * *(float *)(this->_padding_ + 0x78);
        local_10 = local_64.right_x * fVar1 + local_64.up_x * fVar2 + local_10;
        local_c = local_64.right_y * fVar1 + local_64.up_y * fVar2 + local_c;
        local_8 = fVar2 * local_64.up_z + local_64.right_z * fVar1 + local_8;
      }
    }
    local_20 = local_20 - fVar14;
    local_dc = local_dc + local_10;
    local_d8 = local_d8 + local_c;
    local_d4 = local_d4 + local_8;
    VVar5.y = local_d8;
    VVar5.x = local_dc;
    VVar5.z = local_d4;
    pVVar8 = ScaleVector(&local_100,0.5,VVar5);
    local_c4.x = pVVar8->x;
    local_c4.y = pVVar8->y;
    local_c4.z = pVVar8->z;
    lVar10 = Camera_Bounding_Sphere_Test(param_1,&local_c4,this->radius);
    p_Var6 = SortingTableCurrent;
    if (lVar10 < 1) {
      SortingTableCurrent->vcnt = 0;
      local_88 = local_1c + local_e8;
      p_Var6->Type = 10;
      p_Var6->Bitmap_Operation = 4;
      local_84 = (POLYGON_SKIN)(local_18 + local_e4);
      p_Var6->Skin_Color = *(POLYGON_SKIN *)(this->_padding_ + 0x7c);
      local_24 = p_Var6;
      local_80 = local_14 + local_e0;
      p_Var6[1].vcnt = (long)local_88;
      local_d0 = local_e8 + local_10;
      p_Var6[1].Skin_Color = local_84;
      p_Var6[1].Bitmap_Operation = (long)local_80;
      local_cc = local_e4 + local_c;
      local_c8 = (_ZSORTING *)(local_8 + local_e0);
      p_Var6[1].Type = (long)local_d0;
      local_a0 = (_ZSORTING *)(local_10 - local_e8);
      p_Var6[1].Z_Value = local_cc;
      p_Var6[1].Next = local_c8;
      local_9c = local_c - local_e4;
      local_98 = (POLYGON_SKIN)(local_8 - local_e0);
      p_Var6[1].Previous = local_a0;
      local_70 = local_1c - local_e8;
      p_Var6[2].vcnt = (long)local_9c;
      p_Var6[2].Skin_Color = local_98;
      local_6c = local_18 - local_e4;
      local_68 = local_14 - local_e0;
      p_Var6[2].Bitmap_Operation = (long)local_70;
      p_Var6[2].Type = (long)local_6c;
      p_Var6[2].Z_Value = local_68;
      fVar14 = VectGetMin((VECTOR_3D *)(p_Var6 + 1),4);
      local_24->Z_Value = fVar14;
      ZSORTAdd(fVar14);
      local_24 = SortingTableCurrent;
      SortingTableCurrent->vcnt = 0;
      local_24->Type = 10;
      local_f4 = local_1c + local_b8;
      local_24->Bitmap_Operation = 4;
      local_24->Skin_Color = *(POLYGON_SKIN *)(this->_padding_ + 0x7c);
      local_f0 = (POLYGON_SKIN)(local_18 + local_b4);
      local_ec = local_14 + local_b0;
      local_24[1].vcnt = (long)local_f4;
      local_7c = local_b8 + local_10;
      local_24[1].Skin_Color = local_f0;
      local_24[1].Bitmap_Operation = (long)local_ec;
      local_78 = local_b4 + local_c;
      local_74 = (_ZSORTING *)(local_8 + local_b0);
      local_24[1].Type = (long)local_7c;
      local_94 = (_ZSORTING *)(local_10 - local_b8);
      local_24[1].Z_Value = local_78;
      local_24[1].Next = local_74;
      local_90 = local_c - local_b4;
      local_8c = (POLYGON_SKIN)(local_8 - local_b0);
      local_24[1].Previous = local_94;
      local_ac = local_1c - local_b8;
      local_24[2].vcnt = (long)local_90;
      local_24[2].Skin_Color = local_8c;
      local_a8 = local_18 - local_b4;
      local_a4 = local_14 - local_b0;
      local_24[2].Bitmap_Operation = (long)local_ac;
      local_24[2].Type = (long)local_a8;
      local_24[2].Z_Value = local_a4;
      fVar14 = VectGetMin((VECTOR_3D *)(local_24 + 1),4);
      local_24->Z_Value = fVar14;
      ZSORTAdd(fVar14);
    }
  }
  return;
}
