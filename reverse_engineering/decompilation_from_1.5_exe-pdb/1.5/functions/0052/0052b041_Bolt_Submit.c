/*
 * Entry: 0052b041
 * Name: Bolt::Submit
 * Namespace: Bolt
 * Signature: void Submit(Bolt * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Bolt::Submit(Bolt *this,CAMERA *param_1)

{
  uint *puVar1;
  float fVar2;
  float fVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  _ZSORTING *p_Var7;
  float fVar8;
  float fVar9;
  float fVar10;
  MAT_3D *pMVar11;
  VECTOR_3D *pVVar12;
  uint uVar13;
  long lVar14;
  int iVar15;
  int iVar16;
  float *pfVar17;
  MAT_3D *pMVar18;
  float fVar19;
  MAT_3D local_148;
  VECTOR_3D local_108;
  float local_fc;
  POLYGON_SKIN local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  _ZSORTING *local_d0;
  VECTOR_3D local_cc;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  _ZSORTING *local_9c;
  float local_98;
  POLYGON_SKIN local_94;
  float local_90;
  POLYGON_SKIN local_8c;
  float local_88;
  float local_84;
  float local_80;
  _ZSORTING *local_7c;
  _ZSORTING *local_78;
  float local_74;
  POLYGON_SKIN local_70;
  long local_68;
  MAT_3D local_64;
  float local_24;
  _ZSORTING *local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pfVar17 = (float *)(this->_padding_ + 0x20);
  pMVar11 = &local_64;
  for (iVar15 = 0x10; iVar15 != 0; iVar15 = iVar15 + -1) {
    pMVar11->right_x = *pfVar17;
    pfVar17 = pfVar17 + 1;
    pMVar11 = (MAT_3D *)&pMVar11->right_y;
  }
  local_24 = (float)(((float10)local_64.posit_z - (float10)(this->origin).z) *
                     (float10)local_64.front_z +
                     (float10)local_64.front_y *
                     ((float10)local_64.posit_y - (float10)(this->origin).y) +
                    (float10)local_64.front_x *
                    ((float10)local_64.posit_x - (float10)(this->origin).x));
  local_64.posit_x = (this->origin).x;
  local_64.posit_y = (this->origin).y;
  local_64.posit_z = (this->origin).z;
  pMVar11 = Matrix_Multiply(&local_148,&local_64,&param_1->Matrix);
  iVar15 = this->_padding_;
  pMVar18 = &local_64;
  for (iVar16 = 0x10; iVar16 != 0; iVar16 = iVar16 + -1) {
    pMVar18->right_x = pMVar11->right_x;
    pMVar11 = (MAT_3D *)&pMVar11->right_y;
    pMVar18 = (MAT_3D *)&pMVar18->right_y;
  }
  local_10 = (float)local_64.posit_x;
  local_c = (float)local_64.posit_y;
  local_8 = (float)local_64.posit_z;
  local_20 = *(_ZSORTING **)(iVar15 + 0x70);
  pfVar17 = (float *)(iVar15 + 0x80);
  if (0.0 < *pfVar17) {
    local_20 = (_ZSORTING *)(((float)this->_padding_ / *pfVar17) * (float)local_20);
  }
  local_1c = local_64.up_x;
  local_18 = local_64.up_y;
  local_14 = local_64.up_z;
  VVar4.y = local_64.up_y;
  VVar4.x = local_64.up_x;
  VVar4.z = local_64.up_z;
  pVVar12 = ScaleVector(&local_cc,(float)local_20,VVar4);
  local_c0 = pVVar12->x;
  local_1c = local_64.right_x;
  local_18 = local_64.right_y;
  local_bc = pVVar12->y;
  local_14 = local_64.right_z;
  local_b8 = pVVar12->z;
  VVar5.y = local_64.right_y;
  VVar5.x = local_64.right_x;
  VVar5.z = local_64.right_z;
  pVVar12 = ScaleVector(&local_cc,(float)local_20,VVar5);
  local_f0 = pVVar12->x;
  local_ec = pVVar12->y;
  local_e8 = pVVar12->z;
  local_68 = Rand_Counter;
  fVar19 = local_1c;
  fVar2 = local_18;
  fVar3 = local_14;
  fVar8 = local_10;
  fVar9 = local_c;
  fVar10 = local_8;
  if (0.0 < *(float *)(this->_padding_ + 0x78)) {
    uVar13 = (uint)*(ushort *)((int)&this->_padding_ + 2);
    uVar13 = uVar13 ^ uVar13 << 0xd;
    uVar13 = uVar13 ^ (int)uVar13 >> 0x11;
    Rand_Counter = (uVar13 << 5 ^ uVar13) & 0xff;
    fVar8 = local_10;
    fVar9 = local_c;
    fVar10 = local_8;
  }
  while (local_14 = fVar10, local_18 = fVar9, local_1c = fVar8, 0.0 < local_24) {
    iVar15 = this->_padding_;
    if (local_24 <= *(float *)(iVar15 + 0x74)) {
      local_10 = local_64.front_x * local_24 + (float)local_64.posit_x;
      local_64.posit_x = (double)local_10;
      local_c = local_64.front_y * local_24 + (float)local_64.posit_y;
      local_64.posit_y = (double)local_c;
      local_8 = local_64.front_z * local_24 + (float)local_64.posit_z;
      local_64.posit_z = (double)local_8;
      fVar19 = local_24;
    }
    else {
      fVar19 = *(float *)(iVar15 + 0x74);
      local_10 = local_64.front_x * fVar19 + (float)local_64.posit_x;
      local_64.posit_x = (double)local_10;
      local_c = local_64.front_y * fVar19 + (float)local_64.posit_y;
      local_64.posit_y = (double)local_c;
      local_8 = local_64.front_z * fVar19 + (float)local_64.posit_z;
      local_64.posit_z = (double)local_8;
      if (0.0 < *(float *)(iVar15 + 0x78)) {
        uVar13 = Rand_Counter + 1U & 0xff;
        fVar2 = Pseudo_Rand_Number[uVar13] * *(float *)(this->_padding_ + 0x78);
        Rand_Counter = uVar13 + 1 & 0xff;
        fVar3 = Pseudo_Rand_Number[Rand_Counter] * *(float *)(this->_padding_ + 0x78);
        local_10 = local_64.right_x * fVar2 + local_64.up_x * fVar3 + local_10;
        local_c = local_64.right_y * fVar2 + local_64.up_y * fVar3 + local_c;
        local_8 = fVar3 * local_64.up_z + local_64.right_z * fVar2 + local_8;
      }
    }
    local_24 = local_24 - fVar19;
    local_a8 = local_1c + local_10;
    local_a4 = local_18 + local_c;
    local_a0 = local_14 + local_8;
    VVar6.y = local_a4;
    VVar6.x = local_a8;
    VVar6.z = local_a0;
    pVVar12 = ScaleVector(&local_108,0.5,VVar6);
    local_cc.x = pVVar12->x;
    local_cc.y = pVVar12->y;
    local_cc.z = pVVar12->z;
    lVar14 = Camera_Bounding_Sphere_Test(param_1,&local_cc,this->radius);
    p_Var7 = SortingTableCurrent;
    fVar19 = local_1c;
    fVar2 = local_18;
    fVar3 = local_14;
    fVar8 = local_10;
    fVar9 = local_c;
    fVar10 = local_8;
    if (lVar14 < 1) {
      SortingTableCurrent->vcnt = 0;
      local_90 = local_1c + local_f0;
      p_Var7->Type = 10;
      p_Var7->Bitmap_Operation = 4;
      local_8c = (POLYGON_SKIN)(local_18 + local_ec);
      p_Var7->Skin_Color = *(POLYGON_SKIN *)(this->_padding_ + 0x7c);
      local_20 = p_Var7;
      local_88 = local_14 + local_e8;
      p_Var7[1].vcnt = (long)local_90;
      local_d8 = local_f0 + local_10;
      p_Var7[1].Skin_Color = local_8c;
      p_Var7[1].Bitmap_Operation = (long)local_88;
      local_d4 = local_ec + local_c;
      local_d0 = (_ZSORTING *)(local_8 + local_e8);
      p_Var7[1].Type = (long)local_d8;
      local_78 = (_ZSORTING *)(local_10 - local_f0);
      p_Var7[1].Z_Value = local_d4;
      p_Var7[1].Next = local_d0;
      local_74 = local_c - local_ec;
      local_70 = (POLYGON_SKIN)(local_8 - local_e8);
      p_Var7[1].Previous = local_78;
      local_e4 = local_1c - local_f0;
      p_Var7[2].vcnt = (long)local_74;
      p_Var7[2].Skin_Color = local_70;
      local_e0 = local_18 - local_ec;
      local_dc = local_14 - local_e8;
      p_Var7[2].Bitmap_Operation = (long)local_e4;
      p_Var7[2].Type = (long)local_e0;
      p_Var7[2].Z_Value = local_dc;
      fVar19 = VectGetMin((VECTOR_3D *)(p_Var7 + 1),4);
      local_20->Z_Value = fVar19;
      ZSORTAdd(fVar19);
      local_20 = SortingTableCurrent;
      SortingTableCurrent->vcnt = 0;
      local_20->Type = 10;
      local_fc = local_1c + local_c0;
      local_20->Bitmap_Operation = 4;
      local_20->Skin_Color = *(POLYGON_SKIN *)(this->_padding_ + 0x7c);
      local_f8 = (POLYGON_SKIN)(local_18 + local_bc);
      local_f4 = local_14 + local_b8;
      local_20[1].vcnt = (long)local_fc;
      local_84 = local_c0 + local_10;
      local_20[1].Skin_Color = local_f8;
      local_20[1].Bitmap_Operation = (long)local_f4;
      local_80 = local_bc + local_c;
      local_7c = (_ZSORTING *)(local_8 + local_b8);
      local_20[1].Type = (long)local_84;
      local_9c = (_ZSORTING *)(local_10 - local_c0);
      local_20[1].Z_Value = local_80;
      local_20[1].Next = local_7c;
      local_98 = local_c - local_bc;
      local_94 = (POLYGON_SKIN)(local_8 - local_b8);
      local_20[1].Previous = local_9c;
      local_b4 = local_1c - local_c0;
      local_20[2].vcnt = (long)local_98;
      local_20[2].Skin_Color = local_94;
      local_b0 = local_18 - local_bc;
      local_ac = local_14 - local_b8;
      local_20[2].Bitmap_Operation = (long)local_b4;
      local_20[2].Type = (long)local_b0;
      local_20[2].Z_Value = local_ac;
      fVar19 = VectGetMin((VECTOR_3D *)(local_20 + 1),4);
      local_20->Z_Value = fVar19;
      ZSORTAdd(fVar19);
      fVar19 = local_1c;
      fVar2 = local_18;
      fVar3 = local_14;
      fVar8 = local_10;
      fVar9 = local_c;
      fVar10 = local_8;
    }
  }
  Rand_Counter = local_68;
  local_10 = local_1c;
  local_1c = fVar19;
  local_c = local_18;
  local_18 = fVar2;
  local_8 = local_14;
  local_14 = fVar3;
  iVar15 = UserPref_arcadeMode();
  if (iVar15 == 0) {
    fVar19 = TimeStepLocal();
    this->_padding_ = (int)((float)this->_padding_ - fVar19);
  }
  if ((float)this->_padding_ <= 0.0) {
    puVar1 = (uint *)(this->_padding_ + 0x14);
    *puVar1 = *puVar1 | 0x200;
  }
  return;
}
