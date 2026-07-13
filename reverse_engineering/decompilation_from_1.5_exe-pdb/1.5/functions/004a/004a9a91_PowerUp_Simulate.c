/*
 * Entry: 004a9a91
 * Name: PowerUp::Simulate
 * Namespace: PowerUp
 * Signature: void Simulate(PowerUp * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUp::Simulate(PowerUp *this,float param_1)

{
  int *piVar1;
  CLSN_INFO *pCVar2;
  uint uVar3;
  VEHICLE *pVVar4;
  VECTOR_3D_LONG VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  VECTOR_3D VVar8;
  VECTOR_3D VVar9;
  VECTOR_3D VVar10;
  VECTOR_3D VVar11;
  VECTOR_3D VVar12;
  VECTOR_3D VVar13;
  VECTOR_3D VVar14;
  VECTOR_3D VVar15;
  VECTOR_3D VVar16;
  VECTOR_3D VVar17;
  VECTOR_3D VVar18;
  VECTOR_3D VVar19;
  VECTOR_3D VVar20;
  VECTOR_3D VVar21;
  VECTOR_3D VVar22;
  VECTOR_3D VVar23;
  PowerUp *pPVar24;
  bool bVar25;
  VECTOR_3D *pVVar26;
  MAT_3D *pMVar27;
  ulong *puVar28;
  int iVar29;
  int iVar30;
  MAT_3D *pMVar31;
  PowerUp *pPVar32;
  MAT_3D *pMVar33;
  float10 fVar34;
  float fVar35;
  double dVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  MAT_3D local_a0;
  float local_60;
  VECTOR_3D local_5c;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  CLSN_INFO *local_34;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  VECTOR_3D local_18;
  float local_c;
  PowerUp *local_8;
  
  piVar1 = &this->_padding_;
  local_8 = this;
  bVar25 = DistributedObject::IsRemote((DistributedObject *)piVar1);
  if (!bVar25) {
    uVar3 = *(uint *)(this->_padding_ + 0x14);
    if ((uVar3 & 0x1000000) != 0) {
      (**(code **)(*piVar1 + 0x14))();
      return;
    }
    if ((uVar3 & 0x200) != 0) {
      (**(code **)(*piVar1 + 0x10))();
      return;
    }
  }
  iVar29 = this->_padding_;
  local_18.x = 0.0;
  local_18.y = 0.0;
  this->_padding_ = (int)0.0;
  local_18.z = 0.0;
  this->_padding_ = (int)-9.8;
  this->_padding_ = (int)0.0;
  pMVar31 = (MAT_3D *)(iVar29 + 0x20);
  local_4c = 0.0;
  local_48 = 0.0;
  local_44 = 0.0;
  VVar5.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar29 + 0x50) >> 0x20);
  VVar5._0_12_ = *(undefined1 (*) [12])(iVar29 + 0x48);
  VVar5.z._0_4_ = (int)*(undefined8 *)(iVar29 + 0x58);
  VVar5.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar29 + 0x58) >> 0x20);
  Floor_GetFloor(VVar5,&local_60,&local_5c);
  local_18.x = pMVar31->right_x;
  pVVar4 = local_8->vhcl;
  uVar3 = pVVar4->flags;
  local_18.y = *(float *)(iVar29 + 0x24);
  local_18.z = *(float *)(iVar29 + 0x28);
  local_40 = *(float *)(iVar29 + 0x38);
  local_3c = *(float *)(iVar29 + 0x3c);
  local_38 = *(float *)(iVar29 + 0x40);
  if ((uVar3 & 4) == 0) {
    local_50 = (pVVar4->control).steer;
    local_30.x = local_5c.x;
    local_30.y = local_5c.y + 2.0;
    local_30.z = local_5c.z;
    local_24.x = local_5c.x;
    local_24.z = local_5c.z;
    local_24.y = local_30.y;
    pVVar26 = Normalize_Vector(&local_30,&local_24);
    local_24.x = pVVar26->x;
    local_24.y = pVVar26->y;
    local_48 = local_48 - (float)local_8->_padding_ * 10.0;
    local_24.z = pVVar26->z;
    local_4c = (float)local_8->_padding_ * -10.0 -
               (local_24.x * local_40 + local_24.y * local_3c + local_24.z * local_38) * 25.0;
    local_44 = (local_44 - (float)local_8->_padding_ * 10.0) +
               (local_24.x * local_18.x + local_24.y * local_18.y + local_24.z * local_18.z) * 25.0;
    fVar34 = (float10)9.800000190734863 -
             (((float10)*(double *)(iVar29 + 0x50) - (float10)1.0) - (float10)local_60) *
             (float10)local_5c.y * (float10)19.600000381469727;
    if ((float10)0 < fVar34) {
      VVar13.x = (float)local_8->_padding_;
      VVar13.y = (float)local_8->_padding_;
      VVar13.z = (float)local_8->_padding_;
      VVar10.y = local_5c.y;
      VVar10.x = local_5c.x;
      VVar10.z = local_5c.z;
      pVVar26 = AddMultVectors(&local_30,VVar13,(float)fVar34,VVar10);
      local_8->_padding_ = (int)pVVar26->x;
      local_8->_padding_ = (int)pVVar26->y;
      local_8->_padding_ = (int)pVVar26->z;
    }
    local_8->_padding_ = (int)((float)local_8->_padding_ - (float)local_8->_padding_ * 5.0);
    local_8->_padding_ = (int)((float)local_8->_padding_ - (float)local_8->_padding_ * 5.0);
    local_8->_padding_ = (int)((float)local_8->_padding_ - (float)local_8->_padding_ * 5.0);
    local_48 = local_50 * 20.0 + local_48;
  }
  else if ((uVar3 & 1) == 0) {
    if (((uVar3 & 8) != 0) && ((float)local_8->_padding_ < 0.0)) {
      pVVar4->flags = pVVar4->flags & 0xfffffff7;
      puVar28 = &local_8->vhcl->flags;
      *puVar28 = *puVar28 | 1;
    }
  }
  else {
    local_34 = (CLSN_INFO *)(pVVar4->control).steer;
    if ((pVVar4->control).turbo == 0) {
      local_c = (pVVar4->control).braccel;
    }
    else {
      local_c = 2.0;
    }
    local_50 = (pVVar4->control).strafe;
    fVar35 = local_c * local_c + local_50 * local_50;
    if (1.0 < fVar35) {
      fVar35 = 1.0;
    }
    local_4c = (-(float)local_8->_padding_ - local_3c * 5.0) - local_c;
    local_44 = local_18.y * 5.0 + (local_44 - (float)local_8->_padding_) + local_50;
    fVar35 = Clamp((float)local_34 - (float)local_8->_padding_ / (fVar35 * 0.5 + 2.0),-1.0,1.0);
    local_48 = fVar35 + fVar35 + local_48;
    if (local_c <= 0.0) {
      fVar35 = 10.0;
    }
    else {
      fVar35 = 15.0;
    }
    VVar6.y = local_3c;
    VVar6.x = local_40;
    VVar6.z = local_38;
    VVar7.y = local_18.y;
    VVar7.x = local_18.x;
    VVar7.z = local_18.z;
    pVVar26 = CombineVectors(&local_30,fVar35 * local_c,VVar6,local_50 * 10.0,VVar7);
    local_40 = (float)local_8->_padding_;
    local_3c = (float)local_8->_padding_;
    local_38 = (float)local_8->_padding_;
    local_18.x = pVVar26->x;
    local_18.y = pVVar26->y;
    local_18.z = pVVar26->z;
    local_30.x = local_18.x - local_40;
    local_24.y = local_18.y - local_3c;
    local_30.z = local_18.z - local_38;
    local_30.y = 0.0;
    VVar8.y = 0.0;
    VVar8.x = local_30.x;
    VVar8.z = local_30.z;
    local_24.x = local_30.x;
    local_24.z = local_30.z;
    pVVar26 = ScaleVector(&local_30,1.0 / param_1,VVar8);
    local_24.x = pVVar26->x;
    local_24.y = pVVar26->y;
    local_24.z = pVVar26->z;
    fVar35 = local_24.x * local_24.x + local_24.z * local_24.z + local_24.y * local_24.y;
    if (25.0 < fVar35) {
      fVar37 = pVVar26->x;
      fVar38 = pVVar26->y;
      fVar39 = pVVar26->z;
      dVar36 = rsqrt((double)fVar35);
      VVar9.y = fVar38;
      VVar9.x = fVar37;
      VVar9.z = fVar39;
      pVVar26 = ScaleVector(&local_30,(float)((float10)dVar36 * (float10)5.0),VVar9);
      local_24.x = pVVar26->x;
      local_24.y = pVVar26->y;
      local_24.z = pVVar26->z;
    }
    local_18.x = (float)local_8->_padding_;
    local_18.y = (float)local_8->_padding_;
    local_18.z = (float)local_8->_padding_;
    local_40 = local_18.x + local_24.x;
    local_3c = local_24.y + local_18.y;
    local_38 = local_24.z + local_18.z;
    local_8->_padding_ = (int)local_40;
    local_8->_padding_ = (int)local_3c;
    local_8->_padding_ = (int)local_38;
    if ((float)local_8->_padding_ < 0.0) {
      fVar35 = (float)local_8->_padding_;
      local_8->_padding_ = (int)(fVar35 * fVar35 * 0.1 + (float)local_8->_padding_);
    }
  }
  local_c = param_1 * 0.5;
  VVar15.x = (float)local_8->_padding_;
  VVar15.y = (float)local_8->_padding_;
  VVar15.z = (float)local_8->_padding_;
  VVar14.x = (float)local_8->_padding_;
  VVar14.y = (float)local_8->_padding_;
  VVar14.z = (float)local_8->_padding_;
  pVVar26 = AddMultVectors(&local_18,VVar14,local_c,VVar15);
  local_30.x = pVVar26->x;
  local_30.y = pVVar26->y;
  local_30.z = pVVar26->z;
  local_8->_padding_ = (int)local_30.x;
  local_8->_padding_ = (int)local_30.y;
  local_8->_padding_ = (int)local_30.z;
  VVar16.x = (float)local_8->_padding_;
  VVar16.y = (float)local_8->_padding_;
  VVar16.z = (float)local_8->_padding_;
  VVar11.y = local_48;
  VVar11.x = local_4c;
  VVar11.z = local_44;
  pVVar26 = AddMultVectors(&local_18,VVar16,local_c,VVar11);
  local_8->_padding_ = (int)pVVar26->x;
  local_8->_padding_ = (int)pVVar26->y;
  local_8->_padding_ = (int)pVVar26->z;
  VVar12.y = local_30.y;
  VVar12.x = local_30.x;
  VVar12.z = local_30.z;
  fVar35 = VecLen(VVar12);
  pPVar32 = local_8;
  local_8->_padding_ = (int)fVar35;
  if (fVar35 <= 0.0) {
    fVar35 = 1e+30;
  }
  else {
    fVar35 = 1.0 / fVar35;
  }
  pVVar4 = local_8->vhcl;
  local_8->_padding_ = (int)fVar35;
  pCVar2 = &pVVar4->clsn_info;
  local_34 = pCVar2;
  if ((pVVar4->flags & 4) != 0) {
    GroundCheck(local_8,pCVar2,param_1);
  }
  if (pCVar2->collided == 0) {
    *(double *)(iVar29 + 0x48) =
         (double)((float)pPVar32->_padding_ * param_1 + (float)*(double *)(iVar29 + 0x48));
    *(double *)(iVar29 + 0x50) =
         (double)((float)pPVar32->_padding_ * param_1 + (float)*(double *)(iVar29 + 0x50));
    fVar35 = (float)pPVar32->_padding_ * param_1;
  }
  else {
    if ((pVVar4->clsn_info).t < 0.0) {
      (pVVar4->clsn_info).t = 0.0;
    }
    *(double *)(iVar29 + 0x48) =
         (double)((float)pPVar32->_padding_ * (pVVar4->clsn_info).t +
                 (float)*(double *)(iVar29 + 0x48));
    *(double *)(iVar29 + 0x50) =
         (double)((pVVar4->clsn_info).t * (float)pPVar32->_padding_ +
                 (float)*(double *)(iVar29 + 0x50));
    pVVar26 = &(pVVar4->clsn_info).normal;
    *(double *)(iVar29 + 0x58) =
         (double)((pVVar4->clsn_info).t * (float)pPVar32->_padding_ +
                 (float)*(double *)(iVar29 + 0x58));
    VVar17.x = (float)pPVar32->_padding_;
    VVar17.y = (float)pPVar32->_padding_;
    VVar17.z = (float)pPVar32->_padding_;
    pVVar26 = AddMultVectors(&local_30,VVar17,
                             (pVVar26->x * (float)pPVar32->_padding_ +
                             (float)pPVar32->_padding_ * (pVVar4->clsn_info).normal.y +
                             (float)pPVar32->_padding_ * (pVVar4->clsn_info).normal.z) * -1.5,
                             *pVVar26);
    local_8->_padding_ = (int)pVVar26->x;
    local_8->_padding_ = (int)pVVar26->y;
    local_8->_padding_ = (int)pVVar26->z;
    *(double *)(iVar29 + 0x48) =
         (double)((param_1 - local_34->t) * (float)local_8->_padding_ +
                 (float)*(double *)(iVar29 + 0x48));
    *(double *)(iVar29 + 0x50) =
         (double)((param_1 - local_34->t) * (float)local_8->_padding_ +
                 (float)*(double *)(iVar29 + 0x50));
    fVar35 = (param_1 - local_34->t) * (float)local_8->_padding_;
    pPVar32 = local_8;
  }
  *(double *)(iVar29 + 0x58) = (double)(fVar35 + (float)*(double *)(iVar29 + 0x58));
  if ((pPVar32->vhcl->flags & 4) == 0) {
    VVar19.x = (float)pPVar32->_padding_;
    VVar19.y = (float)pPVar32->_padding_;
    VVar19.z = (float)pPVar32->_padding_;
    pMVar27 = Spinner(&local_a0,pMVar31,VVar19,param_1);
    for (iVar30 = 0x10; iVar30 != 0; iVar30 = iVar30 + -1) {
      pMVar31->right_x = pMVar27->right_x;
      pMVar27 = (MAT_3D *)&pMVar27->right_y;
      pMVar31 = (MAT_3D *)&pMVar31->right_y;
    }
  }
  else {
    pVVar26 = Vector_Rotate(&local_30,(VECTOR_3D *)(pPVar32->_padding_ + 8),pMVar31);
    local_18.x = pVVar26->x;
    local_18.y = pVVar26->y;
    local_18.z = pVVar26->z;
    *(double *)(iVar29 + 0x48) = (double)(local_18.x + (float)*(double *)(iVar29 + 0x48));
    *(double *)(iVar29 + 0x50) = (double)(local_18.y + (float)*(double *)(iVar29 + 0x50));
    *(double *)(iVar29 + 0x58) = (double)(local_18.z + (float)*(double *)(iVar29 + 0x58));
    VVar18.x = (float)local_8->_padding_;
    VVar18.y = (float)local_8->_padding_;
    VVar18.z = (float)local_8->_padding_;
    pMVar27 = Spinner(&local_a0,pMVar31,VVar18,param_1);
    pMVar33 = pMVar31;
    for (iVar30 = 0x10; iVar30 != 0; iVar30 = iVar30 + -1) {
      pMVar33->right_x = pMVar27->right_x;
      pMVar27 = (MAT_3D *)&pMVar27->right_y;
      pMVar33 = (MAT_3D *)&pMVar33->right_y;
    }
    pVVar26 = Vector_Rotate(&local_30,(VECTOR_3D *)(local_8->_padding_ + 8),pMVar31);
    local_18.x = pVVar26->x;
    local_18.y = pVVar26->y;
    local_18.z = pVVar26->z;
    *(double *)(iVar29 + 0x48) = (double)((float)*(double *)(iVar29 + 0x48) - local_18.x);
    *(double *)(iVar29 + 0x50) = (double)((float)*(double *)(iVar29 + 0x50) - local_18.y);
    *(double *)(iVar29 + 0x58) = (double)((float)*(double *)(iVar29 + 0x58) - local_18.z);
  }
  pPVar32 = local_8;
  pCVar2 = local_34;
  if ((local_8->vhcl->flags & 4) != 0) {
    if (local_34->collided == 0) {
      Terrain_GetHeightAndNormal
                (*(double *)(iVar29 + 0x48),*(double *)(iVar29 + 0x58),&param_1,&local_30);
      if ((float)*(double *)(iVar29 + 0x50) < param_1) {
        pCVar2->collided = 1;
      }
      if (pCVar2->collided == 0) goto LAB_004aa2c5;
    }
    puVar28 = &pPVar32->vhcl->flags;
    if ((*puVar28 & 1) != 0) {
      *puVar28 = *puVar28 & 0xfffffff6;
    }
    puVar28 = &pPVar32->vhcl->flags;
    *puVar28 = *puVar28 & 0xfffffffb;
    iVar29 = Net_IsNetGame();
    if (iVar29 != 0) {
      piVar1 = &pPVar32->_padding_;
      bVar25 = DistributedObject::IsLocal((DistributedObject *)piVar1);
      if ((bVar25) && (iVar29 = (**(code **)*piVar1)(), *(int *)(iVar29 + 0x20) != 0x5752434b)) {
        DistributedObject::UpdatePermState((DistributedObject *)piVar1);
      }
    }
  }
  if (pCVar2->collided != 0) {
    ClearCollision(pCVar2);
  }
LAB_004aa2c5:
  pPVar24 = local_8;
  VVar21.x = (float)pPVar32->_padding_;
  VVar21.y = (float)pPVar32->_padding_;
  VVar21.z = (float)pPVar32->_padding_;
  VVar20.x = (float)local_8->_padding_;
  VVar20.y = (float)local_8->_padding_;
  VVar20.z = (float)local_8->_padding_;
  pVVar26 = AddMultVectors(&local_30,VVar20,local_c,VVar21);
  pPVar24->_padding_ = (int)pVVar26->x;
  pPVar24->_padding_ = (int)pVVar26->y;
  pPVar24->_padding_ = (int)pVVar26->z;
  VVar23.x = (float)pPVar24->_padding_;
  VVar23.y = (float)pPVar24->_padding_;
  VVar23.z = (float)pPVar24->_padding_;
  VVar22.x = (float)pPVar24->_padding_;
  VVar22.y = (float)pPVar24->_padding_;
  VVar22.z = (float)pPVar24->_padding_;
  pVVar26 = AddMultVectors(&local_18,VVar22,local_c,VVar23);
  local_30.x = pVVar26->x;
  local_30.y = pVVar26->y;
  local_30.z = pVVar26->z;
  VVar10 = *pVVar26;
  pPVar24->_padding_ = (int)local_30.x;
  pPVar24->_padding_ = (int)local_30.y;
  pPVar24->_padding_ = (int)local_30.z;
  fVar35 = VecLen(VVar10);
  local_8->_padding_ = (int)fVar35;
  if (fVar35 <= 0.0) {
    fVar35 = 1e+30;
  }
  else {
    fVar35 = 1.0 / fVar35;
  }
  local_8->_padding_ = (int)fVar35;
  GameObject::UpdatePosition((GameObject *)local_8);
  return;
}
