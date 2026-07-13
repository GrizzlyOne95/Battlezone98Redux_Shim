
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall HoverCraft::Simulate(HoverCraft *this,float param_1)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  HoverInterface *pHVar4;
  VECTOR_3D_LONG VVar5;
  VECTOR_3D_LONG VVar6;
  VECTOR_3D_LONG VVar7;
  VECTOR_3D_LONG VVar8;
  VECTOR_3D VVar9;
  VECTOR_3D_LONG VVar10;
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
  VECTOR_3D VVar24;
  VECTOR_3D VVar25;
  VECTOR_3D VVar26;
  VECTOR_3D VVar27;
  VECTOR_3D VVar28;
  VECTOR_3D VVar29;
  VECTOR_3D VVar30;
  VECTOR_3D VVar31;
  VECTOR_3D VVar32;
  VECTOR_3D VVar33;
  VECTOR_3D VVar34;
  VECTOR_3D VVar35;
  VECTOR_3D VVar36;
  VECTOR_3D VVar37;
  VECTOR_3D VVar38;
  bool bVar39;
  char cVar40;
  VECTOR_3D_LONG *pVVar41;
  VECTOR_3D *pVVar42;
  int iVar43;
  undefined4 unaff_EDI;
  undefined4 *puVar44;
  float10 fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float fVar49;
  double dVar50;
  double dVar51;
  double dVar52;
  float *pfVar53;
  float fVar54;
  VECTOR_3D local_d8;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  VECTOR_3D local_9c;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  VECTOR_3D local_78;
  float local_6c;
  float local_68;
  float local_64;
  float *local_60;
  VECTOR_3D local_5c;
  float local_50;
  float local_4c;
  undefined1 local_48 [12];
  VECTOR_3D local_3c;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  char local_16;
  char local_15;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar43 = this->_padding_;
  local_14 = *(float *)(iVar43 + 0x38);
  local_60 = (float *)(iVar43 + 0x20);
  local_10 = *(float *)(iVar43 + 0x3c);
  iVar3 = this->_padding_;
  local_16 = *(int *)(iVar3 + 0xd4) != 0;
  local_c = *(float *)(iVar43 + 0x40);
  local_90 = *local_60;
  local_8c = *(float *)(iVar43 + 0x24);
  local_88 = *(float *)(iVar43 + 0x28);
  local_d8.x = *(float *)(iVar43 + 0x2c);
  local_d8.y = *(float *)(iVar43 + 0x30);
  local_d8.z = *(float *)(iVar43 + 0x34);
  local_80 = *(float *)(iVar3 + 0xc4);
  local_a0 = *(float *)(iVar3 + 200);
  local_1c = ___real_40000000;
  if (!(bool)local_16) {
    local_1c = *(float *)(iVar3 + 0xd0);
  }
  local_15 = *(int *)(iVar3 + 0xd8) != 0;
  local_50 = *(float *)(iVar3 + 0xcc);
  local_2c = 0.0;
  local_7c = ___real_7149f2ca;
  if (param_1 != 0.0) {
    local_7c = 1.0 / param_1;
  }
  iVar3 = this->_padding_;
  local_9c.x = (float)*(double *)(iVar43 + 0x48);
  local_9c.y = (float)*(double *)(iVar43 + 0x50);
  local_9c.z = (float)*(double *)(iVar43 + 0x58);
  local_8 = *(float *)(iVar3 + 0x324);
  local_6c = *(float *)(iVar3 + 0x328);
  local_c8 = *(float *)(iVar3 + 0x32c);
  local_a8 = *(float *)(iVar3 + 0x330);
  local_28 = *(float *)(iVar3 + 0x338);
  local_20 = *(float *)(iVar3 + 0x334);
  local_ac = *(float *)(iVar3 + 0x33c);
  local_c4 = *(float *)(iVar3 + 0x340);
  local_b4 = *(float *)(iVar3 + 0x344);
  fVar46 = GetPerformance((float)this->_padding_);
  pfVar53 = local_60;
  local_84 = *(float *)(iVar3 + 0x300) * fVar46;
  local_b0 = *(float *)(iVar3 + 0x304) * fVar46;
  local_b8 = *(float *)(iVar3 + 0x308) * fVar46;
  local_30 = *(float *)(iVar3 + 0x30c) * fVar46;
  fVar49 = *(float *)(iVar3 + 0x310);
  local_a4 = *(float *)(iVar3 + 0x314) * fVar46;
  fVar2 = *(float *)(iVar3 + 0x318);
  local_bc = *(float *)(iVar3 + 0x31c) * fVar46;
  local_cc = fVar46 * *(float *)(iVar3 + 800);
  this->_padding_ = (int)GravityVector.x;
  this->_padding_ = (int)GravityVector.y;
  this->_padding_ = (int)GravityVector.z;
  if ((this->_padding_ == 0) || ((*(uint *)(this->_padding_ + 0x14) & 0x200) != 0)) {
    if ((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0) {
      *(undefined4 *)(this->_padding_ + 0xc4) = 0;
      *(undefined4 *)(this->_padding_ + 200) = 0;
      *(undefined4 *)(this->_padding_ + 0xcc) = 0;
      *(undefined4 *)(this->_padding_ + 0xd0) = 0;
      *(undefined4 *)(this->_padding_ + 0xd4) = 0;
      *(undefined4 *)(this->_padding_ + 0xd8) = 0;
      VVar8.y._4_4_ = (int)((ulonglong)*(undefined8 *)(local_60 + 0xc) >> 0x20);
      VVar8._0_12_ = *(undefined1 (*) [12])(local_60 + 10);
      VVar8.z._0_4_ = (int)*(undefined8 *)(local_60 + 0xe);
      VVar8.z._4_4_ = (int)((ulonglong)*(undefined8 *)(local_60 + 0xe) >> 0x20);
      Floor_GetFloor(VVar8,&local_8,&local_3c);
      local_8 = ((*(float *)(this->_padding_ + 0xdc) + (float)*(double *)(pfVar53 + 0xc)) -
                (float)___real_3fc99999a0000000) - local_8;
      if (local_8 <= 0.0) {
        local_30 = 1.0;
      }
      else {
        local_30 = ___real_3f666666 / (local_8 * local_8 * ___real_3e800000 + ___real_3f800000) +
                   ___real_3dcccccd;
      }
      fVar49 = (___real_411ccccd - local_3c.y * local_8 * ___real_40400000) +
               (((float)this->_padding_ * local_3c.z * ___real_c0000000 -
                (float)this->_padding_ * local_3c.y * ___real_40000000) -
               (float)this->_padding_ * local_3c.x * ___real_40000000);
      if (0.0 < fVar49) {
        VVar26.x = (float)this->_padding_;
        VVar26.y = (float)this->_padding_;
        VVar26.z = (float)this->_padding_;
        VVar17.y = local_3c.y;
        VVar17.x = local_3c.x;
        VVar17.z = local_3c.z;
        pVVar42 = AddMultVectors(&local_9c,VVar26,fVar49,VVar17);
        this->_padding_ = (int)pVVar42->x;
        this->_padding_ = (int)pVVar42->y;
        this->_padding_ = (int)pVVar42->z;
      }
      VVar28.x = (float)this->_padding_;
      VVar28.y = (float)this->_padding_;
      VVar28.z = (float)this->_padding_;
      VVar27.x = (float)this->_padding_;
      VVar27.y = (float)this->_padding_;
      VVar27.z = (float)this->_padding_;
      pVVar42 = AddMultVectors(&local_9c,VVar27,param_1,VVar28);
      local_14 = pVVar42->x;
      local_c = pVVar42->z;
      local_10 = pVVar42->y * ___real_3dcccccd;
      local_2c = ___real_40000000;
      if ((local_8 <= ___real_3dcccccd) && (local_2c = ___real_41400000, 0.0 < local_8)) {
        local_2c = ___real_41400000 - local_8 * ___real_42c80000;
      }
      dVar50 = rsqrt((double)(local_10 * local_10 + local_14 * local_14 + local_c * local_c));
      fVar49 = min<float>(local_7c,(float)dVar50 * local_2c);
      VVar29.x = (float)this->_padding_;
      VVar29.y = (float)this->_padding_;
      VVar29.z = (float)this->_padding_;
      VVar18.y = local_10;
      VVar18.x = local_14;
      VVar18.z = local_c;
      pVVar42 = AddMultVectors(&local_9c,VVar29,-fVar49,VVar18);
      this->_padding_ = (int)pVVar42->x;
      fVar49 = -(local_30 * local_28);
      this->_padding_ = (int)pVVar42->y;
      this->_padding_ = (int)pVVar42->z;
      piVar1 = &this->_padding_;
      *piVar1 = (int)(fVar49 * (float)this->_padding_);
      this->_padding_ = (int)((float)this->_padding_ * fVar49);
      this->_padding_ = (int)(fVar49 * (float)this->_padding_);
      fVar49 = *local_60;
      fVar2 = local_60[1];
      fVar46 = local_60[2];
      *piVar1 = (int)((float)*piVar1 -
                     (local_60[8] * local_3c.z + local_60[7] * local_3c.y + local_60[6] * local_3c.x
                     ) * local_30 * local_20);
      this->_padding_ =
           (int)((fVar46 * local_3c.z + fVar2 * local_3c.y + fVar49 * local_3c.x) *
                 local_30 * local_20 + (float)this->_padding_);
      this->throttle = ___real_bf000000;
      this->airBorne = 0.0;
    }
  }
  else {
    piVar1 = &this->_padding_;
    local_68 = local_10 * (float)this->_padding_ +
               local_c * (float)this->_padding_ + (float)*piVar1 * local_14;
    local_c0 = local_8c * (float)this->_padding_ +
               local_88 * (float)this->_padding_ + (float)*piVar1 * local_90;
    VVar6.y._4_4_ = (int)((ulonglong)*(undefined8 *)(local_60 + 0xc) >> 0x20);
    VVar6._0_12_ = *(undefined1 (*) [12])(local_60 + 10);
    VVar6.z._0_4_ = (int)*(undefined8 *)(local_60 + 0xe);
    VVar6.z._4_4_ = (int)((ulonglong)*(undefined8 *)(local_60 + 0xe) >> 0x20);
    Floor_GetFloor(VVar6,&local_64,&local_5c);
    local_64 = (float)*(double *)(pfVar53 + 0xc) - local_64;
    if (___real_38d1b717 < (float)this->_padding_) {
      local_3c.x = (float)*piVar1;
      local_3c.y = (float)this->_padding_;
      local_3c.z = (float)this->_padding_;
      dVar50 = (double)local_3c.x;
      dVar52 = (double)local_3c.y;
      dVar51 = (double)(*(float *)(this->_padding_ + 0x14) * (float)this->_padding_ +
                       ___real_3f000000);
      VVar5.x._4_4_ = (int)*(undefined8 *)(local_60 + 0xc);
      VVar5.x._0_4_ = (int)((ulonglong)*(undefined8 *)(local_60 + 10) >> 0x20);
      VVar5.y._0_4_ = (int)((ulonglong)*(undefined8 *)(local_60 + 0xc) >> 0x20);
      VVar5.y._4_4_ = (int)*(undefined8 *)(local_60 + 0xe);
      VVar5.z._0_4_ = (int)((ulonglong)*(undefined8 *)(local_60 + 0xe) >> 0x20);
      VVar5.z._4_4_ = SUB84(dVar51,0);
      VVar10.x._4_4_ = SUB84(dVar52,0);
      VVar10.x._0_4_ = (int)((ulonglong)dVar50 >> 0x20);
      VVar10.y._0_4_ = (int)((ulonglong)dVar52 >> 0x20);
      VVar10.y._4_4_ = SUB84((double)local_3c.z,0);
      VVar10.z._0_4_ = (int)((ulonglong)(double)local_3c.z >> 0x20);
      VVar10.z._4_4_ = unaff_EDI;
      pVVar41 = V3DL_AddMult((VECTOR_3D_LONG *)local_48,VVar5,
                             (double)CONCAT44(SUB84(dVar50,0),(int)((ulonglong)dVar51 >> 0x20)),
                             VVar10);
      pfVar53 = &local_24;
      iVar43 = 6;
      puVar44 = (undefined4 *)&stack0xfffffef4;
      pVVar42 = &local_78;
      while( true ) {
        if (iVar43 == 0) break;
        iVar43 = iVar43 + -1;
        *puVar44 = *(undefined4 *)&pVVar41->x;
        pVVar41 = (VECTOR_3D_LONG *)((int)&pVVar41->x + 4);
        puVar44 = puVar44 + 1;
      }
      VVar7.y._0_4_ = SUB84(dVar50,0);
      VVar7.x = dVar51;
      VVar7.y._4_4_ = (int)((ulonglong)dVar50 >> 0x20);
      VVar7.z._0_4_ = SUB84(dVar52,0);
      VVar7.z._4_4_ = (int)((ulonglong)dVar52 >> 0x20);
      Floor_GetFloor(VVar7,pfVar53,pVVar42);
      local_24 = (float)*(double *)(local_60 + 0xc) - local_24;
      local_5c.x = local_78.x + local_5c.x;
      local_5c.y = local_78.y + local_5c.y;
      local_5c.z = local_78.z + local_5c.z;
      local_3c.x = local_5c.x;
      local_3c.y = local_5c.y;
      local_3c.z = local_5c.z;
      pVVar42 = Normalize_Vector(&local_3c,&local_5c);
      local_5c.x = pVVar42->x;
      local_5c.y = pVVar42->y;
      local_5c.z = pVVar42->z;
      local_64 = min<float>(local_64,local_24);
    }
    if (local_64 <= 0.0) {
      local_8 = 0.0;
      fVar48 = local_8;
    }
    else {
      fVar48 = ___real_40000000;
      if (0.0 < local_8) {
        fVar48 = (local_5c.y / local_8) * local_64;
      }
    }
    local_8 = fVar48;
    if (local_8 <= 1.0) {
      this->thrustRatio = 1.0;
    }
    else {
      this->thrustRatio =
           ___real_3f666666 / ((local_8 - 1.0) * (local_8 - 1.0) * ___real_3e800000 + 1.0) +
           ___real_3dcccccd;
    }
    fVar48 = (___real_411ccccd - (local_8 - 1.0) * local_5c.y * LIFT_SPRING) +
             ((float)this->_padding_ * local_5c.x +
             (float)this->_padding_ * local_5c.y + (float)this->_padding_ * local_5c.z) *
             this->thrustRatio * ___real_c09ccccd;
    if (0.0 < fVar48) {
      VVar19.x = (float)this->_padding_;
      VVar19.y = (float)this->_padding_;
      VVar19.z = (float)this->_padding_;
      VVar11.y = local_5c.y;
      VVar11.x = local_5c.x;
      VVar11.z = local_5c.z;
      pVVar42 = AddMultVectors(&local_78,VVar19,fVar48,VVar11);
      this->_padding_ = (int)pVVar42->x;
      this->_padding_ = (int)pVVar42->y;
      this->_padding_ = (int)pVVar42->z;
    }
    this->_padding_ = (int)-((float)this->_padding_ * local_28);
    this->_padding_ = (int)-((float)this->_padding_ * local_28);
    local_3c.x = local_5c.x;
    local_3c.y = local_5c.y + ___real_40000000;
    local_3c.z = local_5c.z;
    pVVar42 = Normalize_Vector(&local_78,&local_3c);
    local_28 = local_20 * this->thrustRatio;
    local_3c.x = pVVar42->x;
    local_3c.y = pVVar42->y;
    local_3c.z = pVVar42->z;
    piVar1 = &this->_padding_;
    *piVar1 = (int)((float)*piVar1 -
                   (local_10 * local_3c.y + local_c * local_3c.z + local_14 * local_3c.x) * local_28
                   );
    this->_padding_ =
         (int)((local_8c * local_3c.y + local_88 * local_3c.z + local_90 * local_3c.x) * local_28 +
              (float)this->_padding_);
    if ((((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) &&
        ((UserProfilePtr->playOption & 0x10) != 0)) ||
       ((bVar39 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_), bVar39 &&
        ((*(uint *)(this->_padding_ + 0x10c) & 0x1000) != 0)))) {
      fVar48 = (1.0 - this->thrustRatio) * local_20;
      *piVar1 = (int)((float)*piVar1 - local_10 * fVar48);
      this->_padding_ = (int)(fVar48 * local_8c + (float)this->_padding_);
    }
    local_4c = min<float>(1.0,local_1c * local_1c + local_50 * local_50);
    fVar48 = ___real_40400000;
    if ((local_15 == '\0') && (fVar48 = ___real_40000000, local_16 == '\0')) {
      fVar48 = local_80 * local_80 * ___real_3f000000 + local_4c;
    }
    this->throttle = fVar48;
    if (0.0 < local_30) {
      fVar47 = Clamp(-((float)this->_padding_ * local_4c * local_68) / local_30,___real_bf800000,1.0
                    );
      fVar48 = local_50;
      if (0.0 < local_50) {
        fVar48 = -local_50;
      }
      local_50 = local_50 + (fVar48 + ___real_3f800000) * fVar47;
    }
    fVar48 = local_b0;
    if (0.0 < local_1c) {
      fVar48 = local_84;
    }
    VVar9.y = local_10;
    VVar9.x = local_14;
    VVar9.z = local_c;
    VVar12.y = local_8c;
    VVar12.x = local_90;
    VVar12.z = local_88;
    pVVar42 = CombineVectors(&local_78,fVar48 * local_1c - local_68,VVar9,
                             local_b8 * local_50 - local_c0,VVar12);
    local_14 = pVVar42->x;
    local_10 = pVVar42->y;
    local_c = pVVar42->z;
    pVVar42 = ScaleVector(&local_78,local_7c,*pVVar42);
    local_3c.x = pVVar42->x;
    local_3c.y = pVVar42->y;
    local_3c.z = pVVar42->z;
    fVar48 = local_3c.y * local_5c.y + local_3c.z * local_5c.z + local_3c.x * local_5c.x;
    if (fVar48 < 0.0) {
      VVar13.y = local_5c.y;
      VVar13.x = local_5c.x;
      VVar13.z = local_5c.z;
      pVVar42 = AddMultVectors(&local_78,*pVVar42,-fVar48,VVar13);
      local_3c.x = pVVar42->x;
      local_3c.y = pVVar42->y;
      local_3c.z = pVVar42->z;
    }
    fVar48 = 0.0;
    local_68 = local_3c.z * local_3c.z + local_3c.y * local_3c.y + local_3c.x * local_3c.x;
    if (0.0 < local_84) {
      fVar48 = Clamp((float)this->_padding_ / local_84,0.0,1.0);
    }
    local_24 = (local_4c * local_5c.y * local_30 +
               (1.0 - local_4c) * ((local_c8 - local_6c) * fVar48 + local_6c)) * this->thrustRatio;
    if (local_68 <= local_24 * local_24) {
      local_78.x = (float)this->_padding_;
      local_78.y = (float)this->_padding_;
      local_78.z = (float)this->_padding_;
      local_14 = local_78.x + local_3c.x;
      local_10 = local_3c.y + local_78.y;
      local_c = local_3c.z + local_78.z;
      this->_padding_ = (int)local_14;
      this->_padding_ = (int)local_10;
      this->_padding_ = (int)local_c;
    }
    else {
      fVar48 = local_3c.x;
      fVar47 = local_3c.y;
      fVar54 = local_3c.z;
      dVar50 = rsqrt((double)local_68);
      VVar20.x = (float)this->_padding_;
      VVar20.y = (float)this->_padding_;
      VVar20.z = (float)this->_padding_;
      VVar14.y = fVar47;
      VVar14.x = fVar48;
      VVar14.z = fVar54;
      pVVar42 = AddMultVectors(&local_78,VVar20,(float)dVar50 * local_24,VVar14);
      bVar39 = ___real_3c23d70a < local_4c;
      this->_padding_ = (int)pVVar42->x;
      this->_padding_ = (int)pVVar42->y;
      this->_padding_ = (int)pVVar42->z;
      if (((bVar39) &&
          (fVar48 = (local_c * local_c + local_10 * local_10 + local_14 * local_14) *
                    (float)this->_padding_ * (float)this->_padding_, 1.0 < fVar48)) &&
         (local_6c = local_c * (float)this->_padding_ +
                     local_10 * (float)this->_padding_ + (float)this->_padding_ * local_14,
         local_6c < 0.0)) {
        dVar50 = rsqrt((double)fVar48);
        local_2c = max<float>(0.0,-((float)dVar50 * local_6c * local_4c));
      }
    }
    VVar22.x = (float)this->_padding_;
    VVar22.y = (float)this->_padding_;
    VVar22.z = (float)this->_padding_;
    VVar21.x = (float)this->_padding_;
    VVar21.y = (float)this->_padding_;
    VVar21.z = (float)this->_padding_;
    pVVar42 = AddMultVectors(&local_78,VVar21,param_1,VVar22);
    local_14 = pVVar42->x;
    local_10 = pVVar42->y;
    local_c = pVVar42->z;
    dVar50 = rsqrt((double)(local_14 * local_14 + local_10 * local_10 + local_c * local_c));
    fVar49 = min<float>(local_7c,(float)dVar50 * fVar49 * fVar46 * local_2c * this->thrustRatio);
    VVar23.x = (float)this->_padding_;
    VVar23.y = (float)this->_padding_;
    VVar23.z = (float)this->_padding_;
    VVar15.y = local_10;
    VVar15.x = local_14;
    VVar15.z = local_c;
    pVVar42 = AddMultVectors(&local_78,VVar23,-fVar49,VVar15);
    this->_padding_ = (int)pVVar42->x;
    this->_padding_ = (int)pVVar42->y;
    this->_padding_ = (int)pVVar42->z;
    if (local_15 != '\0') {
      VVar16.y = local_d8.y;
      VVar16.x = local_d8.x;
      VVar16.z = local_d8.z;
      pVVar42 = AddMultVectors(&local_d8,*pVVar42,local_cc * this->thrustRatio,VVar16);
      this->_padding_ = (int)pVVar42->x;
      this->_padding_ = (int)pVVar42->y;
      this->_padding_ = (int)pVVar42->z;
    }
    if (1.0 < local_1c) {
      local_1c = (local_1c - 1.0) * ___real_3f000000 + 1.0;
    }
    this->_padding_ =
         (int)((local_ac * local_20 * local_a0 - local_28 * local_c4 * local_1c) +
              (float)this->_padding_);
    this->_padding_ = (int)(local_28 * local_b4 * local_50 + (float)this->_padding_);
    fVar49 = (fVar2 * fVar46 - local_a4) * local_4c + local_a4;
    if (fVar49 <= 0.0) {
      this->_padding_ = 0;
    }
    else {
      fVar49 = Clamp(local_80 - (float)this->_padding_ / fVar49,___real_bf800000,1.0);
      this->_padding_ = (int)(fVar49 * local_bc);
    }
    fVar49 = Clamp(1.0 - this->thrustRatio,0.0,1.0);
    this->airBorne = fVar49;
    VVar25.x = (float)this->_padding_;
    VVar25.y = (float)this->_padding_;
    VVar25.z = (float)this->_padding_;
    VVar24.x = (float)this->_padding_;
    VVar24.y = (float)this->_padding_;
    VVar24.z = (float)this->_padding_;
    pVVar42 = AddMultVectors(&local_d8,VVar24,-((float)this->_padding_ * local_a8),VVar25);
    this->_padding_ = (int)pVVar42->x;
    this->_padding_ = (int)pVVar42->y;
    this->_padding_ = (int)pVVar42->z;
    if (this->hi != (HoverInterface *)0x0) {
      this->hi->throt = local_1c;
      this->hi->steer = local_80;
      this->hi->pitch = local_a0;
      this->hi->straf = local_50;
      this->hi->brake = local_2c;
      pHVar4 = this->hi;
      (pHVar4->pos).x = local_9c.x;
      (pHVar4->pos).y = local_9c.y;
      (pHVar4->pos).z = local_9c.z;
      pHVar4 = this->hi;
      (pHVar4->vel).x = (float)this->_padding_;
      (pHVar4->vel).y = (float)this->_padding_;
      (pHVar4->vel).z = (float)this->_padding_;
      pHVar4 = this->hi;
      (pHVar4->accel).x = (float)this->_padding_;
      (pHVar4->accel).y = (float)this->_padding_;
      (pHVar4->accel).z = (float)this->_padding_;
      pHVar4 = this->hi;
      (pHVar4->omg).x = (float)this->_padding_;
      (pHVar4->omg).y = (float)this->_padding_;
      (pHVar4->omg).z = (float)this->_padding_;
      pHVar4 = this->hi;
      (pHVar4->alpha).x = (float)this->_padding_;
      (pHVar4->alpha).y = (float)this->_padding_;
      (pHVar4->alpha).z = (float)this->_padding_;
      pHVar4 = this->hi;
      (pHVar4->normal).x = local_5c.x;
      (pHVar4->normal).y = local_5c.y;
      (pHVar4->normal).z = local_5c.z;
      this->hi->accelLimit = local_24;
      this->hi->heightRatio = local_8;
      this->hi->thrustRatio = local_5c.y * this->thrustRatio;
      this->hi->trackRatio = this->thrustRatio;
      this->hi->dt = param_1;
      fVar45 = (float10)(**(code **)(this->_padding_ + 0x1c))();
      this->hi->health = (float)fVar45;
      this->hi->name = (char *)this->_padding_;
    }
  }
  local_20 = param_1 * ___real_3f000000;
  VVar31.x = (float)this->_padding_;
  VVar31.y = (float)this->_padding_;
  VVar31.z = (float)this->_padding_;
  VVar30.x = (float)this->_padding_;
  VVar30.y = (float)this->_padding_;
  VVar30.z = (float)this->_padding_;
  pVVar42 = AddMultVectors(&local_9c,VVar30,local_20,VVar31);
  this->_padding_ = (int)pVVar42->x;
  this->_padding_ = (int)pVVar42->y;
  this->_padding_ = (int)pVVar42->z;
  VVar33.x = (float)this->_padding_;
  VVar33.y = (float)this->_padding_;
  VVar33.z = (float)this->_padding_;
  VVar32.x = (float)this->_padding_;
  VVar32.y = (float)this->_padding_;
  VVar32.z = (float)this->_padding_;
  pVVar42 = AddMultVectors(&local_9c,VVar32,local_20,VVar33);
  this->_padding_ = (int)pVVar42->x;
  this->_padding_ = (int)pVVar42->y;
  this->_padding_ = (int)pVVar42->z;
  cVar40 = (**(code **)(this->_padding_ + 0x98))();
  if (cVar40 == '\0') {
    VVar35.x = (float)this->_padding_;
    VVar35.y = (float)this->_padding_;
    VVar35.z = (float)this->_padding_;
    VVar34.x = (float)this->_padding_;
    VVar34.y = (float)this->_padding_;
    VVar34.z = (float)this->_padding_;
    pVVar42 = AddMultVectors(&local_9c,VVar34,local_20,VVar35);
    this->_padding_ = (int)pVVar42->x;
    this->_padding_ = (int)pVVar42->y;
    this->_padding_ = (int)pVVar42->z;
    VVar37.x = (float)this->_padding_;
    VVar37.y = (float)this->_padding_;
    VVar37.z = (float)this->_padding_;
    VVar36.x = (float)this->_padding_;
    VVar36.y = (float)this->_padding_;
    VVar36.z = (float)this->_padding_;
    pVVar42 = AddMultVectors(&local_9c,VVar36,local_20,VVar37);
    this->_padding_ = (int)pVVar42->x;
    this->_padding_ = (int)pVVar42->y;
    this->_padding_ = (int)pVVar42->z;
    VVar38.x = (float)this->_padding_;
    VVar38.y = (float)this->_padding_;
    VVar38.z = (float)this->_padding_;
    fVar49 = VecLen(VVar38);
    this->_padding_ = (int)fVar49;
  }
  if (*(int *)(this->_padding_ + 0xf4) != 0) {
    UpdateEyepoint(this,param_1);
  }
  this->_padding_ = (int)(*(float *)(this->_padding_ + 200) * ___real_3f000000);
  if ((((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) &&
      ((UserProfilePtr->playOption & 0x10) != 0)) ||
     ((bVar39 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_), bVar39 &&
      ((*(uint *)(this->_padding_ + 0x10c) & 0x1000) != 0)))) {
    this->_padding_ = (int)((float)this->_padding_ - local_60[7]);
  }
  Craft::Simulate((Craft *)this,param_1);
  return;
}


