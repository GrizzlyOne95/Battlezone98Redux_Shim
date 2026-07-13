/*
 * Entry: 004b445b
 * Name: TurretCraft::Simulate
 * Namespace: TurretCraft
 * Signature: void Simulate(TurretCraft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::Simulate(TurretCraft *this,float param_1)

{
  float fVar1;
  float fVar2;
  _OBJ76 *p_Var3;
  VECTOR_3D_LONG VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  VECTOR_3D VVar8;
  bool bVar9;
  int iVar10;
  VECTOR_3D *pVVar11;
  MAT_3D *pMVar12;
  MAT_3D *pMVar13;
  MAT_3D *unaff_EDI;
  float *pfVar14;
  MAT_3D *pMVar15;
  float fVar16;
  MAT_3D local_178;
  MAT_3D local_138;
  MAT_3D local_f8;
  MAT_3D local_b8;
  MAT_3D local_78;
  VECTOR_3D local_38;
  VECTOR_3D local_2c;
  float local_20;
  MAT_3D *local_1c;
  undefined1 local_18 [8];
  float local_10;
  MAT_3D *local_c;
  float local_8;
  
  iVar10 = ClosestPower(this);
  this->powerSource = iVar10;
  if (iVar10 == 0) {
    ClearHazard(this);
  }
  else {
    GameObject::SetCurAmmo((GameObject *)this,this->_padding_ ^ 0x33333333);
    SetHazard(this);
  }
  iVar10 = this->_padding_;
  local_c = (MAT_3D *)(iVar10 + 0x20);
  VVar4.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar10 + 0x50) >> 0x20);
  VVar4._0_12_ = *(undefined1 (*) [12])(iVar10 + 0x48);
  VVar4.z._0_4_ = (int)*(undefined8 *)(iVar10 + 0x58);
  VVar4.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar10 + 0x58) >> 0x20);
  Floor_GetFloor(VVar4,&local_20,&local_38);
  *(double *)(iVar10 + 0x50) = (double)local_20;
  fVar16 = GetPerformance((float)this->_padding_);
  iVar10 = this->_padding_;
  local_1c = (MAT_3D *)(*(float *)(iVar10 + 0x300) * fVar16);
  local_8 = *(float *)(iVar10 + 0x304) * fVar16;
  fVar16 = fVar16 * *(float *)(iVar10 + 0x308);
  this->_padding_ = (int)-((float)this->_padding_ * fVar16);
  this->_padding_ = (int)-(fVar16 * (float)this->_padding_);
  this->_padding_ = (int)-(fVar16 * (float)this->_padding_);
  local_18._0_4_ = local_38.x;
  local_18._4_4_ = local_38.y + 2.0;
  local_10 = local_38.z;
  pVVar11 = Normalize_Vector(&local_2c,(VECTOR_3D *)local_18);
  local_18._0_4_ = pVVar11->x;
  fVar16 = local_c->right_x;
  local_18._4_4_ = pVVar11->y;
  fVar1 = local_c->right_y;
  fVar2 = local_c->right_z;
  local_10 = pVVar11->z;
  this->_padding_ =
       (int)((float)this->_padding_ -
            (local_c->front_x * (float)local_18._0_4_ +
            local_c->front_y * (float)local_18._4_4_ + local_c->front_z * local_10) * local_8);
  this->_padding_ =
       (int)((fVar16 * (float)local_18._0_4_ + fVar1 * (float)local_18._4_4_ + fVar2 * local_10) *
             local_8 + (float)this->_padding_);
  local_8 = param_1 * 0.5;
  VVar6.x = (float)this->_padding_;
  VVar6.y = (float)this->_padding_;
  VVar6.z = (float)this->_padding_;
  VVar5.x = (float)this->_padding_;
  VVar5.y = (float)this->_padding_;
  VVar5.z = (float)this->_padding_;
  pVVar11 = AddMultVectors(&local_2c,VVar5,local_8,VVar6);
  this->_padding_ = (int)pVVar11->x;
  this->_padding_ = (int)pVVar11->y;
  this->_padding_ = (int)pVVar11->z;
  pMVar12 = Build_Position_Rotation_Matrix
                      (&local_78,-((float)this->_padding_ * param_1),
                       -(param_1 * (float)this->_padding_),-((float)this->_padding_ * param_1),0.0,
                       0.0,0.0);
  fVar16 = local_8;
  pMVar13 = &local_138;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar13->right_x = pMVar12->right_x;
    pMVar12 = (MAT_3D *)&pMVar12->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  VVar8.x = (float)this->_padding_;
  VVar8.y = (float)this->_padding_;
  VVar8.z = (float)this->_padding_;
  VVar7.x = (float)this->_padding_;
  VVar7.y = (float)this->_padding_;
  VVar7.z = (float)this->_padding_;
  pVVar11 = AddMultVectors(&local_2c,VVar7,fVar16,VVar8);
  pMVar12 = local_c;
  this->_padding_ = (int)pVVar11->x;
  this->_padding_ = (int)pVVar11->y;
  this->_padding_ = (int)pVVar11->z;
  pMVar13 = Matrix_Multiply(&local_78,&local_138,local_c);
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar12->right_x = pMVar13->right_x;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
    pMVar12 = (MAT_3D *)&pMVar12->right_y;
  }
  Cache_Invalidate_Bsp((tagENTITY *)this->_padding_);
  local_8 = *(float *)(this->_padding_ + 200);
  fVar16 = -(*(float *)(this->_padding_ + 0xc4) * (float)local_1c);
  this->_padding_ = (int)((1.0 / param_1) * (fVar16 - this->prevYaw) + (float)this->_padding_);
  this->prevYaw = fVar16;
  pMVar12 = Build_Yaw_Matrix(&local_78,fVar16 * param_1);
  pMVar13 = &local_b8;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar13->right_x = pMVar12->right_x;
    pMVar12 = (MAT_3D *)&pMVar12->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  pMVar12 = Matrix_Inverse(&local_78,unaff_EDI);
  pMVar13 = &local_f8;
  for (iVar10 = 0x10; pMVar15 = local_c, iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar13->right_x = pMVar12->right_x;
    pMVar12 = (MAT_3D *)&pMVar12->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  pMVar12 = Matrix_Multiply(&local_78,&local_b8,local_c);
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar15->right_x = pMVar12->right_x;
    pMVar12 = (MAT_3D *)&pMVar12->right_y;
    pMVar15 = (MAT_3D *)&pMVar15->right_y;
  }
  if (this->turretYObj != (_OBJ76 *)0x0) {
    local_c = *(MAT_3D **)(this->_padding_ + 0xa8);
    while (local_c != (MAT_3D *)0x0) {
      pfVar14 = &local_c->front_z;
      pMVar12 = Matrix_Multiply(&local_78,(MAT_3D *)pfVar14,&local_f8);
      local_c = *(MAT_3D **)&local_c[2].field_0x24;
      for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
        *pfVar14 = pMVar12->right_x;
        pMVar12 = (MAT_3D *)&pMVar12->right_y;
        pfVar14 = pfVar14 + 1;
      }
    }
    pMVar13 = &this->turretYObj->transform;
    pMVar12 = Matrix_Multiply(&local_78,&local_b8,pMVar13);
    for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
      pMVar13->right_x = pMVar12->right_x;
      pMVar12 = (MAT_3D *)&pMVar12->right_y;
      pMVar13 = (MAT_3D *)&pMVar13->right_y;
    }
  }
  if (0 < this->turretXCount) {
    join_0x00000008_0x00000000_ = SinCos(local_8 * -0.5);
    local_2c.y = -local_18._4_4_;
    local_8 = 0.0;
    if (0 < this->turretXCount) {
      local_c = (MAT_3D *)this->turretXObj;
      do {
        p_Var3 = *(_OBJ76 **)local_c;
        local_1c = &p_Var3->transform;
        pMVar12 = Build_Pitch_Matrix(&local_178,
                                     ((p_Var3->transform).up_y * local_2c.y +
                                     (p_Var3->transform).up_z * local_10) * param_1 * -5.0);
        pMVar13 = &local_78;
        for (iVar10 = 0x10; pMVar15 = local_1c, iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar13->right_x = pMVar12->right_x;
          pMVar12 = (MAT_3D *)&pMVar12->right_y;
          pMVar13 = (MAT_3D *)&pMVar13->right_y;
        }
        pMVar12 = Matrix_Multiply(&local_178,&local_78,local_1c);
        local_c = (MAT_3D *)((int)local_c + 4);
        local_8 = (float)((int)local_8 + 1);
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar15->right_x = pMVar12->right_x;
          pMVar12 = (MAT_3D *)&pMVar12->right_y;
          pMVar15 = (MAT_3D *)&pMVar15->right_y;
        }
      } while ((int)local_8 < this->turretXCount);
    }
  }
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->_padding_ = (int)(*(float *)(this->_padding_ + 200) * 0.5);
  if (((*(byte *)(this->_padding_ + 0x14) & 0x10) == 0) ||
     ((UserProfilePtr->playOption & 0x10) == 0)) {
    bVar9 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
    if ((!bVar9) || ((*(uint *)(this->_padding_ + 0x10c) & 0x1000) == 0)) goto LAB_004b48d0;
  }
  this->_padding_ = (int)((float)this->_padding_ - *(float *)(this->_padding_ + 0x3c));
LAB_004b48d0:
  Craft::Simulate((Craft *)this,param_1);
  return;
}
