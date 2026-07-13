/*
 * Entry: 004b7e4d
 * Name: Walker::RegCollision
 * Namespace: Walker
 * Signature: bool RegCollision(Walker * this, _OBJ76 * param_1, CLSN_INFO * param_2, CLSN_INFO * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
Walker::RegCollision(Walker *this,_OBJ76 *param_1,CLSN_INFO *param_2,CLSN_INFO *param_3)

{
  float fVar1;
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
  bool bVar13;
  _OBJ76 *p_Var14;
  EULER *pEVar15;
  VECTOR_3D *pVVar16;
  VECTOR_3D *pVVar17;
  MAT_3D *pMVar18;
  int iVar19;
  float *pfVar20;
  float *pfVar21;
  float fVar22;
  EULER local_108;
  float local_c0 [2];
  MAT_3D local_b8;
  VECTOR_3D local_78;
  VECTOR_3D local_6c;
  VECTOR_3D local_60;
  float local_54;
  float local_50;
  VECTOR_3D local_4c;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  bVar13 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
  if ((bVar13) ||
     ((((char)this->_padding_ != '\0' && (this->_padding_ != 0)) &&
      (p_Var14 = (_OBJ76 *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0x30))(),
      param_1 == p_Var14)))) {
    return false;
  }
  pEVar15 = ClassGetEuler(&local_108,param_1);
  pfVar20 = local_c0;
  for (iVar19 = 0x12; iVar19 != 0; iVar19 = iVar19 + -1) {
    *pfVar20 = pEVar15->mass;
    pEVar15 = (EULER *)&pEVar15->mass_inv;
    pfVar20 = pfVar20 + 1;
  }
  local_28 = (float)this->_padding_;
  local_24 = (float)this->_padding_;
  local_20 = (float)this->_padding_;
  local_78.x = local_b8.up_y - local_28;
  local_78.y = local_b8.up_z - local_24;
  local_78.z = local_b8.front_x - local_20;
  local_10 = local_78.x;
  local_c = local_78.y;
  local_8 = local_78.z;
  Damage_Resolve((_OBJ76 *)this->_padding_,param_1,&local_78,&param_2->normal,&param_2->point);
  if (param_1->class_id == CLASS_ID_POWERUP) {
    return false;
  }
  local_54 = TimeStep();
  VVar11.x = (float)this->_padding_;
  VVar11.y = (float)this->_padding_;
  VVar11.z = (float)this->_padding_;
  fVar22 = VecLen(VVar11);
  this->_padding_ = (int)fVar22;
  if (fVar22 == 0.0) {
    fVar1 = 1e+30;
  }
  else {
    fVar1 = 1.0 / fVar22;
  }
  this->_padding_ = (int)fVar1;
  local_1c = (float)this->_padding_;
  local_18 = (float)this->_padding_;
  local_14 = (float)this->_padding_;
  local_40.x = (param_2->normal).x;
  local_40.y = (param_2->normal).y;
  local_40.z = (param_2->normal).z;
  iVar19 = this->_padding_;
  local_34.x = *(float *)(iVar19 + 8);
  local_34.y = *(float *)(iVar19 + 0xc);
  local_34.z = *(float *)(iVar19 + 0x10);
  local_28 = (param_2->point).x;
  local_24 = (param_2->point).y;
  local_20 = (param_2->point).z;
  local_60.x = local_28 - local_34.x;
  local_60.y = local_24 - local_34.y;
  local_60.z = local_20 - local_34.z;
  if (fVar22 <= 0.0001) {
    param_1 = (_OBJ76 *)0x3f800000;
  }
  else {
    fVar1 = (local_40.y * local_18 + local_40.x * local_1c + local_40.z * local_14) * fVar1;
    param_1 = (_OBJ76 *)(1.0 - fVar1 * fVar1 * 0.75);
  }
  local_10 = local_60.x;
  local_c = local_60.y;
  local_8 = local_60.z;
  iVar19 = dynamic_object(param_2->obj);
  if ((iVar19 == 0) || ((param_2->euler).mass < 0.0001)) {
    VVar4.y = local_18;
    VVar4.x = local_1c;
    VVar4.z = local_14;
    VVar7.y = local_40.y;
    VVar7.x = local_40.x;
    VVar7.z = local_40.z;
    pVVar16 = AddMultVectors(&local_4c,VVar4,
                             (local_40.y * local_18 + local_40.x * local_1c + local_40.z * local_14)
                             * -2.0,VVar7);
    local_1c = pVVar16->x;
    local_18 = pVVar16->y;
    local_14 = pVVar16->z;
    if (0.0001 < (float)this->_padding_) {
      param_1 = (_OBJ76 *)
                ((1.0 - (float)this->_padding_ * (float)this->_padding_ * local_18 * local_18 * 0.9)
                * (float)param_1);
    }
    pVVar16 = ScaleVector(&local_4c,(float)param_1,*pVVar16);
    local_1c = pVVar16->x;
    local_18 = pVVar16->y;
    local_14 = pVVar16->z;
    if ((25.0 < local_18 * local_18 + local_1c * local_1c + local_14 * local_14) &&
       (param_2->obj == (_OBJ76 *)0x0)) {
      Damage_Resolve((_OBJ76 *)this->_padding_,(_OBJ76 *)0x0,&param_2->vel,&local_40,&param_2->point
                    );
    }
    param_1 = (_OBJ76 *)this->_padding_;
  }
  else {
    local_50 = (float)this->_padding_;
    fVar22 = (param_2->euler).mass;
    VVar2.y = local_18;
    VVar2.x = local_1c;
    VVar2.z = local_14;
    pVVar16 = CombineVectors(&local_6c,local_50,VVar2,fVar22,(param_2->euler).v);
    pVVar16 = ScaleVector(&local_4c,1.0 / (fVar22 + local_50),*pVVar16);
    local_34.x = pVVar16->x;
    local_34.y = pVVar16->y;
    local_34.z = pVVar16->z;
    local_28 = local_1c - local_34.x;
    local_24 = local_18 - local_34.y;
    local_20 = local_14 - local_34.z;
    VVar3.y = local_24;
    VVar3.x = local_28;
    VVar3.z = local_20;
    VVar5.y = local_40.y;
    VVar5.x = local_40.x;
    VVar5.z = local_40.z;
    pVVar17 = CombineVectors(&local_34,0.5,VVar3,
                             -(local_20 * local_40.z + local_24 * local_40.y + local_28 * local_40.x
                              ),VVar5);
    local_1c = pVVar17->x;
    local_18 = pVVar17->y;
    local_14 = pVVar17->z;
    if (local_18 * local_18 + local_1c * local_1c + local_14 * local_14 < 25.0) {
      VVar6.y = local_40.y;
      VVar6.x = local_40.x;
      VVar6.z = local_40.z;
      pVVar17 = ScaleVector(&local_34,5.0,VVar6);
      local_1c = pVVar17->x;
      local_18 = pVVar17->y;
      local_14 = pVVar17->z;
    }
    local_34.x = pVVar16->x;
    local_34.y = pVVar16->y;
    param_1 = (_OBJ76 *)this->_padding_;
    local_34.z = pVVar16->z;
    local_28 = local_34.x + local_1c;
    local_24 = local_34.y + local_18;
    local_20 = local_34.z + local_14;
    local_1c = local_28;
    local_18 = local_24;
    local_14 = local_20;
  }
  pVVar16 = Vector_Unrotate(&local_4c,&param_2->vel,&param_1->transform);
  local_34.x = pVVar16->x;
  local_34.y = pVVar16->y;
  local_34.z = pVVar16->z;
  pVVar16 = Cross_Product(&local_4c,&local_34,&local_60);
  pVVar16 = ScaleVector(&local_6c,
                        0.2 / (local_c * local_c + local_8 * local_8 + local_10 * local_10),*pVVar16
                       );
  local_10 = pVVar16->x;
  local_c = pVVar16->y;
  local_8 = pVVar16->z;
  if ((*(uint *)(this->_padding_ + 0x10c) & 0x200) != 0) goto LAB_004b8403;
  if (local_10 <= 1.5707964) {
    if (local_10 < -1.5707964) {
      fVar22 = -1.5707964 / local_10;
      goto LAB_004b82f0;
    }
  }
  else {
    fVar22 = 1.5707964 / local_10;
LAB_004b82f0:
    pVVar16 = ScaleVector(&local_4c,fVar22,*pVVar16);
    local_10 = pVVar16->x;
    local_c = pVVar16->y;
    local_8 = pVVar16->z;
  }
  if (local_c <= 3.1415927) {
    if (local_c < -3.1415927) {
      fVar22 = -3.1415927 / local_c;
      goto LAB_004b8342;
    }
  }
  else {
    fVar22 = 3.1415927 / local_c;
LAB_004b8342:
    VVar8.y = local_c;
    VVar8.x = local_10;
    VVar8.z = local_8;
    pVVar16 = ScaleVector(&local_4c,fVar22,VVar8);
    local_10 = pVVar16->x;
    local_c = pVVar16->y;
    local_8 = pVVar16->z;
  }
  if (local_8 <= 0.7853982) {
    if (local_8 < -0.7853982) {
      fVar22 = -0.7853982 / local_8;
      goto LAB_004b8394;
    }
  }
  else {
    fVar22 = 0.7853982 / local_8;
LAB_004b8394:
    VVar9.y = local_c;
    VVar9.x = local_10;
    VVar9.z = local_8;
    pVVar16 = ScaleVector(&local_4c,fVar22,VVar9);
    local_10 = pVVar16->x;
    local_c = pVVar16->y;
    local_8 = pVVar16->z;
  }
  local_34.x = (float)this->_padding_;
  local_34.y = (float)this->_padding_;
  local_34.z = (float)this->_padding_;
  local_28 = local_34.x + local_10;
  local_24 = local_34.y + local_c;
  local_20 = local_34.z + local_8;
  this->_padding_ = (int)local_28;
  this->_padding_ = (int)local_24;
  this->_padding_ = (int)local_20;
LAB_004b8403:
  this->_padding_ = (int)local_1c;
  this->_padding_ = (int)local_18;
  this->_padding_ = (int)local_14;
  VVar10.y = local_18;
  VVar10.x = local_1c;
  VVar10.z = local_14;
  fVar22 = VecLen(VVar10);
  this->_padding_ = (int)fVar22;
  if (fVar22 <= 0.0) {
    fVar22 = 1e+30;
  }
  else {
    fVar22 = 1.0 / fVar22;
  }
  this->_padding_ = (int)fVar22;
  (param_1->transform).posit_x = (double)(local_1c * local_54 + (float)(param_1->transform).posit_x)
  ;
  *(double *)(this->_padding_ + 0x50) =
       (double)(local_18 * local_54 + (float)*(double *)(this->_padding_ + 0x50));
  *(double *)(this->_padding_ + 0x58) =
       (double)(local_14 * local_54 + (float)*(double *)(this->_padding_ + 0x58));
  VVar12.x = (float)this->_padding_;
  VVar12.y = (float)this->_padding_;
  VVar12.z = (float)this->_padding_;
  pMVar18 = Spinner(&local_b8,(MAT_3D *)(this->_padding_ + 0x20),VVar12,local_54);
  pfVar20 = &local_108.v_mag;
  for (iVar19 = 0x10; iVar19 != 0; iVar19 = iVar19 + -1) {
    *pfVar20 = pMVar18->right_x;
    pMVar18 = (MAT_3D *)&pMVar18->right_y;
    pfVar20 = pfVar20 + 1;
  }
  pfVar20 = &local_108.v_mag;
  pfVar21 = (float *)(this->_padding_ + 0x20);
  for (iVar19 = 0x10; iVar19 != 0; iVar19 = iVar19 + -1) {
    *pfVar21 = *pfVar20;
    pfVar20 = pfVar20 + 1;
    pfVar21 = pfVar21 + 1;
  }
  return true;
}
