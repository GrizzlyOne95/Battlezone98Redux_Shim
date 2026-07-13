/*
 * Entry: 00486d70
 * Name: Craft::DoCollision
 * Namespace: Craft
 * Signature: bool DoCollision(Craft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Craft::DoCollision(Craft *this,float param_1)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
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
  char cVar19;
  ulong uVar20;
  MAT_3D *pMVar21;
  VECTOR_3D *pVVar22;
  uint uVar23;
  int iVar24;
  float *pfVar25;
  float *pfVar26;
  float fVar27;
  MAT_3D local_100;
  float local_c0 [16];
  VECTOR_3D local_80;
  VECTOR_3D local_74;
  float local_68;
  VECTOR_3D local_64;
  VECTOR_3D *local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  VECTOR_3D local_3c;
  float local_30;
  float local_2c;
  float local_28;
  CLSN_INFO *local_24;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_24 = &this->vhcl->clsn_info;
  VVar14.x = (float)this->_padding_;
  VVar14.y = (float)this->_padding_;
  VVar14.z = (float)this->_padding_;
  fVar27 = VecLen(VVar14);
  this->_padding_ = (int)fVar27;
  if (fVar27 <= 0.0) {
    fVar27 = 1e+30;
  }
  else {
    fVar27 = 1.0 / fVar27;
  }
  this->_padding_ = (int)fVar27;
  uVar20 = Get_Time_Long();
  if (uVar20 < this->_padding_ + 1000U) {
    ClearCollision(local_24);
  }
  if ((local_24->collided == 0) &&
     (cVar19 = (**(code **)(this->_padding_ + 0x9c))(local_24,param_1), cVar19 == '\0')) {
    *(double *)(this->_padding_ + 0x48) =
         (double)(param_1 * (float)this->_padding_ + (float)*(double *)(this->_padding_ + 0x48));
    *(double *)(this->_padding_ + 0x50) =
         (double)((float)this->_padding_ * param_1 + (float)*(double *)(this->_padding_ + 0x50));
    *(double *)(this->_padding_ + 0x58) =
         (double)((float)this->_padding_ * param_1 + (float)*(double *)(this->_padding_ + 0x58));
    VVar15.x = (float)this->_padding_;
    VVar15.y = (float)this->_padding_;
    VVar15.z = (float)this->_padding_;
    pMVar21 = Spinner(&local_100,(MAT_3D *)(this->_padding_ + 0x20),VVar15,param_1);
    pfVar25 = local_c0;
    for (iVar24 = 0x10; iVar24 != 0; iVar24 = iVar24 + -1) {
      *pfVar25 = pMVar21->right_x;
      pMVar21 = (MAT_3D *)&pMVar21->right_y;
      pfVar25 = pfVar25 + 1;
    }
    pfVar25 = local_c0;
    pfVar26 = (float *)(this->_padding_ + 0x20);
    for (iVar24 = 0x10; iVar24 != 0; iVar24 = iVar24 + -1) {
      *pfVar26 = *pfVar25;
      pfVar25 = pfVar25 + 1;
      pfVar26 = pfVar26 + 1;
    }
    return false;
  }
  local_10 = (float)this->_padding_;
  local_c = (float)this->_padding_;
  local_8 = (float)this->_padding_;
  local_20.x = (local_24->normal).x;
  local_20.y = (local_24->normal).y;
  local_20.z = (local_24->normal).z;
  local_48 = 0.0;
  local_44 = 0.0;
  local_40 = 0.0;
  iVar24 = this->_padding_;
  local_3c.x = *(float *)(iVar24 + 8);
  local_3c.y = *(float *)(iVar24 + 0xc);
  local_3c.z = *(float *)(iVar24 + 0x10);
  local_30 = (local_24->point).x;
  local_2c = (local_24->point).y;
  local_28 = (local_24->point).z;
  local_80.x = local_30 - local_3c.x;
  local_80.y = local_2c - local_3c.y;
  local_80.z = local_28 - local_3c.z;
  local_68 = local_24->t;
  local_54 = local_80.x;
  local_50 = local_80.y;
  local_4c = local_80.z;
  if (0.0 <= local_68) {
    if (param_1 < local_68) {
      local_68 = param_1;
    }
    *(double *)(this->_padding_ + 0x48) =
         (double)(local_68 * (float)this->_padding_ + (float)*(double *)(this->_padding_ + 0x48));
    *(double *)(this->_padding_ + 0x50) =
         (double)((float)this->_padding_ * local_68 + (float)*(double *)(this->_padding_ + 0x50));
    *(double *)(this->_padding_ + 0x58) =
         (double)((float)this->_padding_ * local_68 + (float)*(double *)(this->_padding_ + 0x58));
    VVar16.x = (float)this->_padding_;
    VVar16.y = (float)this->_padding_;
    VVar16.z = (float)this->_padding_;
    pMVar21 = Spinner(&local_100,(MAT_3D *)(this->_padding_ + 0x20),VVar16,local_68);
    pfVar25 = local_c0;
    for (iVar24 = 0x10; iVar24 != 0; iVar24 = iVar24 + -1) {
      *pfVar25 = pMVar21->right_x;
      pMVar21 = (MAT_3D *)&pMVar21->right_y;
      pfVar25 = pfVar25 + 1;
    }
    pfVar25 = local_c0;
    pfVar26 = (float *)(this->_padding_ + 0x20);
    for (iVar24 = 0x10; iVar24 != 0; iVar24 = iVar24 + -1) {
      *pfVar26 = *pfVar25;
      pfVar25 = pfVar25 + 1;
      pfVar26 = pfVar26 + 1;
    }
  }
  else {
    local_68 = (local_20.x * (local_24->vel).x +
               (local_24->vel).y * local_20.y + (local_24->vel).z * local_20.z) * local_68;
    *(double *)(this->_padding_ + 0x48) =
         (double)((float)*(double *)(this->_padding_ + 0x48) - local_20.x * local_68);
    *(double *)(this->_padding_ + 0x50) =
         (double)((float)*(double *)(this->_padding_ + 0x50) - local_20.y * local_68);
    *(double *)(this->_padding_ + 0x58) =
         (double)((float)*(double *)(this->_padding_ + 0x58) - local_68 * local_20.z);
    local_68 = 0.0;
  }
  if ((local_24->obj == (_OBJ76 *)0x0) || ((local_24->euler).mass == 0.0)) {
    if ((float)this->_padding_ <= 0.0001) {
      local_14 = 1.0;
    }
    else {
      fVar27 = (local_c * local_20.y + local_10 * local_20.x + local_8 * local_20.z) *
               (float)this->_padding_;
      local_14 = 1.0 - fVar27 * fVar27 * 0.75;
    }
    VVar3.y = local_c;
    VVar3.x = local_10;
    VVar3.z = local_8;
    VVar6.y = local_20.y;
    VVar6.x = local_20.x;
    VVar6.z = local_20.z;
    pVVar22 = AddMultVectors(&local_64,VVar3,
                             ((local_24->vel).x * local_20.x +
                             (local_24->vel).y * local_20.y + (local_24->vel).z * local_20.z) -
                             (local_c * local_20.y + local_10 * local_20.x + local_8 * local_20.z),
                             VVar6);
    local_10 = pVVar22->x;
    local_c = pVVar22->y;
    local_8 = pVVar22->z;
    fVar27 = local_10 * local_10 + local_8 * local_8 + local_c * local_c;
    if (0.0001 < fVar27) {
      local_14 = (1.0 - ((local_c * local_c) / fVar27) * 0.9) * local_14;
    }
    uVar20 = Get_Time_Long();
    uVar23 = uVar20 - this->lastCollideTime;
    if (uVar23 < 100) {
      local_14 = 1.0;
    }
    else if (uVar23 < 500) {
      local_58 = (VECTOR_3D *)(uVar23 - 100);
      fVar27 = (float)(int)local_58;
      if ((int)local_58 < 0) {
        fVar27 = fVar27 + 4.2949673e+09;
      }
      local_14 = 1.0 - fVar27 * (1.0 - local_14) * 0.0025;
    }
    VVar7.y = local_c;
    VVar7.x = local_10;
    VVar7.z = local_8;
    pVVar22 = ScaleVector(&local_64,local_14,VVar7);
    local_10 = pVVar22->x;
    local_c = pVVar22->y;
    local_8 = pVVar22->z;
    if ((25.0 < local_c * local_c + local_10 * local_10 + local_8 * local_8) &&
       (local_24->obj == (_OBJ76 *)0x0)) {
      Damage_Resolve((_OBJ76 *)this->_padding_,(_OBJ76 *)0x0,&local_24->vel,&local_20,
                     &local_24->point);
    }
  }
  else {
    local_58 = (VECTOR_3D *)this->_padding_;
    local_14 = (local_24->euler).mass;
    VVar1.y = local_c;
    VVar1.x = local_10;
    VVar1.z = local_8;
    pVVar22 = CombineVectors(&local_74,(float)local_58,VVar1,local_14,(local_24->euler).v);
    local_58 = ScaleVector(&local_64,1.0 / (local_14 + (float)local_58),*pVVar22);
    local_3c.x = local_58->x;
    local_3c.y = local_58->y;
    local_3c.z = local_58->z;
    local_30 = local_10 - local_3c.x;
    local_2c = local_c - local_3c.y;
    local_28 = local_8 - local_3c.z;
    VVar2.y = local_2c;
    VVar2.x = local_30;
    VVar2.z = local_28;
    VVar4.y = local_20.y;
    VVar4.x = local_20.x;
    VVar4.z = local_20.z;
    pVVar22 = CombineVectors(&local_3c,0.5,VVar2,
                             -(local_30 * local_20.x + local_2c * local_20.y + local_28 * local_20.z
                              ),VVar4);
    local_10 = pVVar22->x;
    local_c = pVVar22->y;
    local_8 = pVVar22->z;
    if (local_c * local_c + local_10 * local_10 + local_8 * local_8 < 25.0) {
      VVar5.y = local_20.y;
      VVar5.x = local_20.x;
      VVar5.z = local_20.z;
      pVVar22 = ScaleVector(&local_3c,5.0,VVar5);
      local_10 = pVVar22->x;
      local_c = pVVar22->y;
      local_8 = pVVar22->z;
    }
    local_3c.x = local_58->x;
    local_3c.y = local_58->y;
    local_3c.z = local_58->z;
    local_30 = local_3c.x + local_10;
    local_2c = local_3c.y + local_c;
    local_28 = local_8 + local_3c.z;
    local_10 = local_30;
    local_c = local_2c;
    local_8 = local_28;
  }
  VVar8.y = local_50;
  VVar8.x = local_54;
  VVar8.z = local_4c;
  iVar24 = ZeroVector(VVar8);
  if (iVar24 == 0) {
    pVVar22 = Vector_Unrotate(&local_64,&local_24->vel,(MAT_3D *)(this->_padding_ + 0x20));
    local_3c.x = pVVar22->x;
    local_3c.y = pVVar22->y;
    local_3c.z = pVVar22->z;
    pVVar22 = Cross_Product(&local_64,&local_3c,&local_80);
    pVVar22 = ScaleVector(&local_74,
                          0.2 / (local_54 * local_54 + local_50 * local_50 + local_4c * local_4c),
                          *pVVar22);
    local_48 = pVVar22->x;
    local_44 = pVVar22->y;
    local_40 = pVVar22->z;
  }
  if ((this->vhcl->flags & 0x200) != 0) goto LAB_004874b9;
  if (local_48 <= 1.5707964) {
    if (local_48 < -1.5707964) {
      fVar27 = -1.5707964 / local_48;
      goto LAB_004873a6;
    }
  }
  else {
    fVar27 = 1.5707964 / local_48;
LAB_004873a6:
    VVar9.y = local_44;
    VVar9.x = local_48;
    VVar9.z = local_40;
    pVVar22 = ScaleVector(&local_64,fVar27,VVar9);
    local_48 = pVVar22->x;
    local_44 = pVVar22->y;
    local_40 = pVVar22->z;
  }
  if (local_44 <= 3.1415927) {
    if (local_44 < -3.1415927) {
      fVar27 = -3.1415927 / local_44;
      goto LAB_004873f8;
    }
  }
  else {
    fVar27 = 3.1415927 / local_44;
LAB_004873f8:
    VVar10.y = local_44;
    VVar10.x = local_48;
    VVar10.z = local_40;
    pVVar22 = ScaleVector(&local_64,fVar27,VVar10);
    local_48 = pVVar22->x;
    local_44 = pVVar22->y;
    local_40 = pVVar22->z;
  }
  if (local_40 <= 0.7853982) {
    if (local_40 < -0.7853982) {
      fVar27 = -0.7853982 / local_40;
      goto LAB_0048744a;
    }
  }
  else {
    fVar27 = 0.7853982 / local_40;
LAB_0048744a:
    VVar11.y = local_44;
    VVar11.x = local_48;
    VVar11.z = local_40;
    pVVar22 = ScaleVector(&local_64,fVar27,VVar11);
    local_48 = pVVar22->x;
    local_44 = pVVar22->y;
    local_40 = pVVar22->z;
  }
  local_3c.x = (float)this->_padding_;
  local_3c.y = (float)this->_padding_;
  local_3c.z = (float)this->_padding_;
  local_30 = local_3c.x + local_48;
  local_2c = local_3c.y + local_44;
  local_28 = local_3c.z + local_40;
  this->_padding_ = (int)local_30;
  this->_padding_ = (int)local_2c;
  this->_padding_ = (int)local_28;
LAB_004874b9:
  fVar27 = (float)this->_padding_ * local_20.x +
           (float)this->_padding_ * local_20.y + (float)this->_padding_ * local_20.z;
  if (fVar27 < 0.0) {
    VVar17.x = (float)this->_padding_;
    VVar17.y = (float)this->_padding_;
    VVar17.z = (float)this->_padding_;
    VVar12.y = local_20.y;
    VVar12.x = local_20.x;
    VVar12.z = local_20.z;
    pVVar22 = AddMultVectors(&local_64,VVar17,-fVar27,VVar12);
    this->_padding_ = (int)pVVar22->x;
    this->_padding_ = (int)pVVar22->y;
    this->_padding_ = (int)pVVar22->z;
  }
  this->_padding_ = (int)local_10;
  this->_padding_ = (int)local_c;
  this->_padding_ = (int)local_8;
  VVar13.y = local_c;
  VVar13.x = local_10;
  VVar13.z = local_8;
  fVar27 = VecLen(VVar13);
  this->_padding_ = (int)fVar27;
  if (fVar27 <= 0.0) {
    fVar27 = 1e+30;
  }
  else {
    fVar27 = 1.0 / fVar27;
  }
  this->_padding_ = (int)fVar27;
  fVar27 = param_1 - local_68;
  *(double *)(this->_padding_ + 0x48) =
       (double)(fVar27 * (float)this->_padding_ + (float)*(double *)(this->_padding_ + 0x48));
  *(double *)(this->_padding_ + 0x50) =
       (double)((float)this->_padding_ * fVar27 + (float)*(double *)(this->_padding_ + 0x50));
  *(double *)(this->_padding_ + 0x58) =
       (double)((float)this->_padding_ * fVar27 + (float)*(double *)(this->_padding_ + 0x58));
  VVar18.x = (float)this->_padding_;
  VVar18.y = (float)this->_padding_;
  VVar18.z = (float)this->_padding_;
  pMVar21 = Spinner(&local_100,(MAT_3D *)(this->_padding_ + 0x20),VVar18,fVar27);
  pfVar25 = local_c0;
  for (iVar24 = 0x10; iVar24 != 0; iVar24 = iVar24 + -1) {
    *pfVar25 = pMVar21->right_x;
    pMVar21 = (MAT_3D *)&pMVar21->right_y;
    pfVar25 = pfVar25 + 1;
  }
  pfVar25 = local_c0;
  pfVar26 = (float *)(this->_padding_ + 0x20);
  for (iVar24 = 0x10; iVar24 != 0; iVar24 = iVar24 + -1) {
    *pfVar26 = *pfVar25;
    pfVar25 = pfVar25 + 1;
    pfVar26 = pfVar26 + 1;
  }
  ClearCollision(local_24);
  uVar20 = Get_Time_Long();
  this->lastCollideTime = uVar20;
  if ((*(uint *)(this->_padding_ + 0x14) & 0x200) != 0) {
    this->vhcl->timer = 0.0;
  }
  return true;
}
