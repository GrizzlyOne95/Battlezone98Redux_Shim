/*
 * Entry: 0053c924
 * Name: Torpedo::Simulate
 * Namespace: Torpedo
 * Signature: void Simulate(Torpedo * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Torpedo::Simulate(Torpedo *this,float param_1)

{
  uint *puVar1;
  VECTOR_3D_LONG VVar2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D_LONG VVar4;
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
  char cVar23;
  bool bVar24;
  GameObject *this_00;
  _OBJ76 *p_Var25;
  int iVar26;
  SPHERE *pSVar27;
  SPHERE *pSVar28;
  VECTOR_3D *pVVar29;
  VECTOR_3D *pVVar30;
  VECTOR_3D_LONG *pVVar31;
  MAT_3D *pMVar32;
  uint uVar33;
  uint uVar34;
  CLSN_INFO *pCVar35;
  int *piVar36;
  float *pfVar37;
  undefined4 unaff_EDI;
  undefined4 *puVar38;
  int *piVar39;
  MAT_3D *pMVar40;
  float fVar41;
  double dVar42;
  undefined4 uVar43;
  undefined4 uVar44;
  double dVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  MAT_3D local_b4;
  VECTOR_3D local_74;
  float local_68;
  float local_64;
  undefined1 local_60 [12];
  VECTOR_3D local_54;
  float local_48;
  float local_44;
  float local_40;
  CLSN_INFO *local_3c;
  VECTOR_3D local_38;
  float local_2c;
  VECTOR_3D local_28;
  MAT_3D *local_1c;
  VECTOR_3D local_18;
  float local_c;
  float local_8;
  
  if (this->lifeTimer < param_1) {
    puVar1 = (uint *)(this->_padding_ + 0x14);
    *puVar1 = *puVar1 | 0x200;
    *(undefined4 *)(this->_padding_ + 0x108) = 0;
  }
  this_00 = GameObject::GetObj(this->_padding_);
  if (this_00 != (GameObject *)0x0) {
    if ((this_00->obj->flags & 1) != 0) {
      this->_padding_ = 0;
    }
    piVar39 = &this_00->_padding_;
    p_Var25 = (_OBJ76 *)(**(code **)(*piVar39 + 0x30))();
    iVar26 = IsBuilding(p_Var25);
    if (iVar26 == 0) {
      p_Var25 = (_OBJ76 *)(**(code **)(*piVar39 + 0x30))();
      iVar26 = IsCraft(p_Var25);
      if ((iVar26 == 0) || (cVar23 = (**(code **)(this_00->_padding_ + 0x68))(), cVar23 != '\0'))
      goto LAB_0053ca36;
    }
    pSVar27 = GameObject::GetSphere(this_00);
    pSVar28 = GameObject::GetSphere((GameObject *)this);
    local_8 = pSVar27->radius + pSVar28->radius;
    pVVar29 = (VECTOR_3D *)(**(code **)(*piVar39 + 0xc))();
    pVVar30 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
    fVar41 = Dist3D_Squared(*pVVar30,*pVVar29);
    if (fVar41 < local_8 * local_8 * 0.5) {
      puVar1 = (uint *)(this->_padding_ + 0x14);
      *puVar1 = *puVar1 | 0x200;
      *(undefined4 *)(this->_padding_ + 0x108) = 0;
    }
  }
LAB_0053ca36:
  local_1c = (MAT_3D *)(this->_padding_ + 0x20);
  this->lifeTimer = this->lifeTimer - param_1;
  this->_padding_ = (int)0.0;
  this->_padding_ = (int)-9.8;
  local_28.x = 0.0;
  local_28.y = 0.0;
  local_28.z = 0.0;
  this->_padding_ = (int)0.0;
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->_padding_ = 0;
  local_68 = GetPerformance((float)this->_padding_);
  pMVar40 = local_1c;
  iVar26 = this->_padding_;
  local_64 = *(float *)(iVar26 + 0x174) * local_68;
  local_44 = *(float *)(iVar26 + 0x178) * local_68;
  local_8 = *(float *)(iVar26 + 0x17c) * local_68;
  local_3c = (CLSN_INFO *)(*(float *)(iVar26 + 0x180) * local_68);
  local_48 = *(float *)(iVar26 + 0x184) * local_68;
  local_68 = local_68 * *(float *)(iVar26 + 0x188);
  VVar3.y._4_4_ = (int)((ulonglong)local_1c->posit_y >> 0x20);
  VVar3._0_12_ = *(undefined1 (*) [12])&local_1c->posit_x;
  VVar3.z._0_4_ = SUB84(local_1c->posit_z,0);
  VVar3.z._4_4_ = (int)((ulonglong)local_1c->posit_z >> 0x20);
  Floor_GetFloor(VVar3,&local_2c,&local_38);
  local_2c = (float)pMVar40->posit_y - local_2c;
  local_28.x = (float)this->_padding_;
  local_28.y = (float)this->_padding_;
  local_28.z = (float)this->_padding_;
  dVar42 = (double)local_28.x;
  dVar45 = (double)local_28.y;
  uVar43 = 0;
  uVar44 = 0x3fe00000;
  VVar2.x._4_4_ = SUB84(local_1c->posit_y,0);
  VVar2.x._0_4_ = (int)((ulonglong)local_1c->posit_x >> 0x20);
  VVar2.y._0_4_ = (int)((ulonglong)local_1c->posit_y >> 0x20);
  VVar2.y._4_4_ = SUB84(local_1c->posit_z,0);
  VVar2.z._0_4_ = (int)((ulonglong)local_1c->posit_z >> 0x20);
  VVar2.z._4_4_ = 0;
  VVar5.x._4_4_ = SUB84(dVar45,0);
  VVar5.x._0_4_ = (int)((ulonglong)dVar42 >> 0x20);
  VVar5.y._0_4_ = (int)((ulonglong)dVar45 >> 0x20);
  VVar5.y._4_4_ = SUB84((double)local_28.z,0);
  VVar5.z._0_4_ = (int)((ulonglong)(double)local_28.z >> 0x20);
  VVar5.z._4_4_ = unaff_EDI;
  pVVar31 = V3DL_AddMult((VECTOR_3D_LONG *)local_60,VVar2,
                         (double)CONCAT44(SUB84(dVar42,0),0x3fe00000),VVar5);
  pVVar29 = &local_74;
  pfVar37 = &local_40;
  iVar26 = 6;
  puVar38 = (undefined4 *)&stack0xffffff20;
  while( true ) {
    if (iVar26 == 0) break;
    iVar26 = iVar26 + -1;
    *puVar38 = *(undefined4 *)&pVVar31->x;
    pVVar31 = (VECTOR_3D_LONG *)((int)&pVVar31->x + 4);
    puVar38 = puVar38 + 1;
  }
  VVar4.x._4_4_ = uVar44;
  VVar4.x._0_4_ = uVar43;
  VVar4.y._0_4_ = SUB84(dVar42,0);
  VVar4.y._4_4_ = (int)((ulonglong)dVar42 >> 0x20);
  VVar4.z._0_4_ = SUB84(dVar45,0);
  VVar4.z._4_4_ = (int)((ulonglong)dVar45 >> 0x20);
  Floor_GetFloor(VVar4,pfVar37,pVVar29);
  local_40 = (float)local_1c->posit_y - local_40;
  local_38.x = local_74.x + local_38.x;
  local_38.y = local_74.y + local_38.y;
  local_38.z = local_74.z + local_38.z;
  local_28.x = local_38.x;
  local_28.y = local_38.y;
  local_28.z = local_38.z;
  pVVar29 = Normalize_Vector(&local_54,&local_38);
  local_38.x = pVVar29->x;
  local_38.y = pVVar29->y;
  local_38.z = pVVar29->z;
  local_2c = min<float>(local_2c,local_40);
  fVar41 = *(float *)(this->_padding_ + 0x170);
  fVar46 = 0.0;
  if (0.0 < local_2c) {
    if (fVar41 <= 0.0) {
      fVar46 = 2.0;
    }
    else {
      fVar46 = (local_38.y / fVar41) * local_2c;
    }
  }
  if (fVar46 <= 1.0) {
    local_c = 1.0;
  }
  else {
    local_c = 0.9 / ((fVar46 - 1.0) * (fVar46 - 1.0) * 0.25 + 1.0) + 0.1;
  }
  fVar41 = (9.8 - (fVar46 - 1.0) * local_38.y * 19.6) +
           ((float)this->_padding_ * local_38.x +
           (float)this->_padding_ * local_38.y + (float)this->_padding_ * local_38.z) * local_c *
           -4.9;
  if (0.0 < fVar41) {
    VVar13.x = (float)this->_padding_;
    VVar13.y = (float)this->_padding_;
    VVar13.z = (float)this->_padding_;
    VVar6.y = local_38.y;
    VVar6.x = local_38.x;
    VVar6.z = local_38.z;
    pVVar29 = AddMultVectors(&local_54,VVar13,fVar41,VVar6);
    this->_padding_ = (int)pVVar29->x;
    this->_padding_ = (int)pVVar29->y;
    this->_padding_ = (int)pVVar29->z;
  }
  this->_padding_ = (int)-(local_44 * (float)this->_padding_);
  this->_padding_ = (int)-((float)this->_padding_ * local_44);
  local_18.x = local_38.x;
  local_18.y = local_38.y + 2.0;
  local_18.z = local_38.z;
  pVVar29 = Normalize_Vector(&local_54,&local_18);
  pMVar40 = local_1c;
  local_18.x = pVVar29->x;
  local_18.y = pVVar29->y;
  local_18.z = pVVar29->z;
  this->_padding_ =
       (int)((float)this->_padding_ -
            (local_1c->front_x * local_18.x +
            local_18.y * local_1c->front_y + local_18.z * local_1c->front_z) * local_c * local_64);
  this->_padding_ =
       (int)((local_1c->right_x * local_18.x +
             local_1c->right_y * local_18.y + local_1c->right_z * local_18.z) * local_c * local_64 +
            (float)this->_padding_);
  if (0.0 < local_48) {
    fVar41 = Clamp(*(float *)(this->_padding_ + 0xc4) - (float)this->_padding_ / local_48,-1.0,1.0);
    this->_padding_ = (int)(fVar41 * local_68);
  }
  local_28.x = pMVar40->front_x * local_8 - (float)this->_padding_;
  local_28.y = local_8 * pMVar40->front_y - (float)this->_padding_;
  local_28.z = local_8 * pMVar40->front_z - (float)this->_padding_;
  if (param_1 == 0.0) {
    fVar41 = 1e+30;
  }
  else {
    fVar41 = 1.0 / param_1;
  }
  VVar7.y = local_28.y;
  VVar7.x = local_28.x;
  VVar7.z = local_28.z;
  pVVar29 = ScaleVector(&local_54,fVar41,VVar7);
  local_18.x = pVVar29->x;
  local_18.y = pVVar29->y;
  local_18.z = pVVar29->z;
  fVar41 = local_18.y * local_38.y + local_18.z * local_38.z + local_18.x * local_38.x;
  if (fVar41 < 0.0) {
    VVar8.y = local_38.y;
    VVar8.x = local_38.x;
    VVar8.z = local_38.z;
    pVVar29 = AddMultVectors(&local_54,*pVVar29,-fVar41,VVar8);
    local_18.x = pVVar29->x;
    local_18.y = pVVar29->y;
    local_18.z = pVVar29->z;
  }
  local_8 = local_c * (float)local_3c;
  fVar41 = local_18.x * local_18.x + local_18.z * local_18.z + local_18.y * local_18.y;
  if (local_8 * local_8 < fVar41) {
    fVar46 = local_18.x;
    fVar47 = local_18.y;
    fVar48 = local_18.z;
    dVar42 = rsqrt((double)fVar41);
    VVar9.y = fVar47;
    VVar9.x = fVar46;
    VVar9.z = fVar48;
    pVVar29 = ScaleVector(&local_54,(float)dVar42 * local_8,VVar9);
    local_18.x = pVVar29->x;
    local_18.y = pVVar29->y;
    local_18.z = pVVar29->z;
  }
  local_54.x = (float)this->_padding_;
  local_54.y = (float)this->_padding_;
  local_54.z = (float)this->_padding_;
  local_28.x = local_54.x + local_18.x;
  local_28.y = local_18.y + local_54.y;
  local_28.z = local_18.z + local_54.z;
  this->_padding_ = (int)local_28.x;
  local_c = param_1 * 0.5;
  this->_padding_ = (int)local_28.y;
  this->_padding_ = (int)local_28.z;
  VVar14.x = (float)this->_padding_;
  VVar14.y = (float)this->_padding_;
  VVar14.z = (float)this->_padding_;
  VVar10.y = local_28.y;
  VVar10.x = local_28.x;
  VVar10.z = local_28.z;
  pVVar29 = AddMultVectors(&local_28,VVar14,local_c,VVar10);
  local_54.x = pVVar29->x;
  local_54.y = pVVar29->y;
  local_54.z = pVVar29->z;
  this->_padding_ = (int)local_54.x;
  this->_padding_ = (int)local_54.y;
  this->_padding_ = (int)local_54.z;
  VVar16.x = (float)this->_padding_;
  VVar16.y = (float)this->_padding_;
  VVar16.z = (float)this->_padding_;
  VVar15.x = (float)this->_padding_;
  VVar15.y = (float)this->_padding_;
  VVar15.z = (float)this->_padding_;
  pVVar29 = AddMultVectors(&local_28,VVar15,local_c,VVar16);
  this->_padding_ = (int)pVVar29->x;
  this->_padding_ = (int)pVVar29->y;
  this->_padding_ = (int)pVVar29->z;
  VVar11.y = local_54.y;
  VVar11.x = local_54.x;
  VVar11.z = local_54.z;
  fVar41 = VecLen(VVar11);
  this->_padding_ = (int)fVar41;
  if (fVar41 <= 0.0) {
    fVar41 = 1e+30;
  }
  else {
    fVar41 = 1.0 / fVar41;
  }
  iVar26 = this->_padding_;
  this->_padding_ = (int)fVar41;
  pCVar35 = (CLSN_INFO *)(iVar26 + 0x4c);
  local_3c = pCVar35;
  PowerUp::GroundCheck((PowerUp *)this,pCVar35,param_1);
  if (pCVar35->collided != 0) {
    if (*(int *)(iVar26 + 0x50) == 0) {
      (**(code **)(this->_padding_ + 0x48))();
    }
    if (pCVar35->collided != 0) {
      if (*(float *)(iVar26 + 0x9c) < 0.0) {
        *(undefined4 *)(iVar26 + 0x9c) = 0;
      }
      local_1c->posit_x =
           (double)(*(float *)(iVar26 + 0x9c) * (float)this->_padding_ + (float)local_1c->posit_x);
      local_1c->posit_y =
           (double)(*(float *)(iVar26 + 0x9c) * (float)this->_padding_ + (float)local_1c->posit_y);
      local_1c->posit_z =
           (double)(*(float *)(iVar26 + 0x9c) * (float)this->_padding_ + (float)local_1c->posit_z);
      VVar17.x = (float)this->_padding_;
      VVar17.y = (float)this->_padding_;
      VVar17.z = (float)this->_padding_;
      pVVar29 = AddMultVectors(&local_54,VVar17,
                               ((float)this->_padding_ * ((VECTOR_3D *)(iVar26 + 0xb8))->x +
                               (float)this->_padding_ * *(float *)(iVar26 + 0xbc) +
                               (float)this->_padding_ * *(float *)(iVar26 + 0xc0)) * -1.5,
                               *(VECTOR_3D *)(iVar26 + 0xb8));
      this->_padding_ = (int)pVVar29->x;
      this->_padding_ = (int)pVVar29->y;
      this->_padding_ = (int)pVVar29->z;
      local_1c->posit_x =
           (double)((param_1 - local_3c->t) * (float)this->_padding_ + (float)local_1c->posit_x);
      local_1c->posit_y =
           (double)((param_1 - local_3c->t) * (float)this->_padding_ + (float)local_1c->posit_y);
      local_1c->posit_z =
           (double)((param_1 - local_3c->t) * (float)this->_padding_ + (float)local_1c->posit_z);
      ClearCollision(local_3c);
      goto LAB_0053d0e4;
    }
  }
  local_1c->posit_x = (double)((float)this->_padding_ * param_1 + (float)local_1c->posit_x);
  local_1c->posit_y = (double)(param_1 * (float)this->_padding_ + (float)local_1c->posit_y);
  local_1c->posit_z = (double)((float)this->_padding_ * param_1 + (float)local_1c->posit_z);
LAB_0053d0e4:
  pMVar40 = local_1c;
  VVar18.x = (float)this->_padding_;
  VVar18.y = (float)this->_padding_;
  VVar18.z = (float)this->_padding_;
  pMVar32 = Spinner(&local_b4,local_1c,VVar18,param_1);
  for (iVar26 = 0x10; iVar26 != 0; iVar26 = iVar26 + -1) {
    pMVar40->right_x = pMVar32->right_x;
    pMVar32 = (MAT_3D *)&pMVar32->right_y;
    pMVar40 = (MAT_3D *)&pMVar40->right_y;
  }
  VVar20.x = (float)this->_padding_;
  VVar20.y = (float)this->_padding_;
  VVar20.z = (float)this->_padding_;
  VVar19.x = (float)this->_padding_;
  VVar19.y = (float)this->_padding_;
  VVar19.z = (float)this->_padding_;
  pVVar29 = AddMultVectors(&local_28,VVar19,local_c,VVar20);
  local_54.x = pVVar29->x;
  local_54.y = pVVar29->y;
  local_54.z = pVVar29->z;
  this->_padding_ = (int)local_54.x;
  this->_padding_ = (int)local_54.y;
  this->_padding_ = (int)local_54.z;
  VVar22.x = (float)this->_padding_;
  VVar22.y = (float)this->_padding_;
  VVar22.z = (float)this->_padding_;
  VVar21.x = (float)this->_padding_;
  VVar21.y = (float)this->_padding_;
  VVar21.z = (float)this->_padding_;
  pVVar29 = AddMultVectors(&local_28,VVar21,local_c,VVar22);
  this->_padding_ = (int)pVVar29->x;
  this->_padding_ = (int)pVVar29->y;
  this->_padding_ = (int)pVVar29->z;
  VVar12.y = local_54.y;
  VVar12.x = local_54.x;
  VVar12.z = local_54.z;
  fVar41 = VecLen(VVar12);
  this->_padding_ = (int)fVar41;
  if (fVar41 <= 0.0) {
    fVar41 = 1e+30;
  }
  else {
    fVar41 = 1.0 / fVar41;
  }
  piVar39 = (int *)this->_padding_;
  this->_padding_ = (int)fVar41;
  piVar36 = &this->_padding_;
  for (iVar26 = 0x12; piVar39 = piVar39 + 1, iVar26 != 0; iVar26 = iVar26 + -1) {
    *piVar39 = *piVar36;
    piVar36 = piVar36 + 1;
  }
  GameObject::UpdatePosition((GameObject *)this);
  if ((*(uint *)(this->_padding_ + 0x14) & 0x1000200) != 0) {
    pfVar37 = (float *)(this->_padding_ + 0x108);
    if (*pfVar37 <= 0.0) {
      bVar24 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
      if (!bVar24) {
        (**(code **)(this->_padding_ + 0x14))();
      }
    }
    else {
      *pfVar37 = *pfVar37 - param_1;
      fVar41 = *(float *)(this->_padding_ + 0x14) * 0.7;
      pfVar37 = (float *)(this->_padding_ + 0x20);
      pMVar40 = &local_b4;
      for (iVar26 = 0x10; iVar26 != 0; iVar26 = iVar26 + -1) {
        pMVar40->right_x = *pfVar37;
        pfVar37 = pfVar37 + 1;
        pMVar40 = (MAT_3D *)&pMVar40->right_y;
      }
      uVar33 = (Rand_Counter + 1U & 0xff) + 1;
      uVar34 = (uVar33 & 0xff) + 1;
      local_b4.posit_x =
           (double)(*(float *)(&DAT_00c9021c + uVar33 * 4) * fVar41 + (float)this->_padding_);
      Rand_Counter = uVar34 & 0xff;
      local_b4.posit_y =
           (double)(*(float *)(&DAT_00c9021c + uVar34 * 4) * fVar41 + (float)this->_padding_);
      local_b4.posit_z =
           (double)(fVar41 * Pseudo_Rand_Number[Rand_Counter] + (float)this->_padding_);
      ExplosionClass::Build(xplSecondary,&local_b4,(_OBJ76 *)0x0);
    }
  }
  return;
}
