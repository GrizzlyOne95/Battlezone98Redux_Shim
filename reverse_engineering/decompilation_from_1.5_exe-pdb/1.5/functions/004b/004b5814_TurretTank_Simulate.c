/*
 * Entry: 004b5814
 * Name: TurretTank::Simulate
 * Namespace: TurretTank
 * Signature: void Simulate(TurretTank * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTank::Simulate(TurretTank *this,float param_1)

{
  float fVar1;
  float fVar2;
  _OBJ76 *p_Var3;
  VECTOR_3D_LONG VVar4;
  VECTOR_3D_LONG VVar5;
  VECTOR_3D_LONG VVar6;
  VECTOR_3D_LONG VVar7;
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
  VECTOR_3D VVar39;
  bool bVar40;
  long lVar41;
  int *piVar42;
  VECTOR_3D *pVVar43;
  MAT_3D *pMVar44;
  MAT_3D *pMVar45;
  float *pfVar46;
  int iVar47;
  int iVar48;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar49;
  float fVar50;
  double dVar51;
  MAT_3D local_660;
  MAT_3D local_620;
  MAT_3D local_5e0;
  MAT_3D local_5a0;
  MAT_3D local_560;
  MAT_3D local_520;
  MAT_3D local_4e0;
  MAT_3D local_4a0;
  MAT_3D local_460;
  MAT_3D local_420;
  MAT_3D local_3e0;
  MAT_3D local_3a0;
  MAT_3D local_360;
  MAT_3D local_320;
  MAT_3D local_2e0;
  MAT_3D local_2a0;
  MAT_3D local_260;
  MAT_3D local_220;
  MAT_3D local_1e0;
  VECTOR_3D local_1a0;
  VECTOR_3D local_194;
  VECTOR_3D local_188;
  VECTOR_3D local_17c;
  VECTOR_3D local_170;
  VECTOR_3D local_164;
  VECTOR_3D local_158;
  VECTOR_3D local_14c;
  VECTOR_3D local_140;
  VECTOR_3D local_134;
  VECTOR_3D local_128;
  VECTOR_3D local_11c;
  VECTOR_3D local_110;
  VECTOR_3D local_104;
  VECTOR_3D local_f8;
  VECTOR_3D local_ec;
  VECTOR_3D local_e0;
  VECTOR_3D local_d4;
  VECTOR_3D local_c8;
  MAT_3D local_bc;
  MAT_3D local_7c;
  float local_3c;
  VECTOR_3D local_38;
  MAT_3D *local_2c;
  SINCOS local_28;
  MAT_3D *local_20;
  MAT_3D *local_1c;
  VECTOR_3D local_18;
  MAT_3D *local_c;
  float local_8;
  
  if ((-1 < this->animHandle) &&
     ((((*(uint *)(this->_padding_ + 0x14) & 0x200) != 0 ||
       (lVar41 = AnimObj_Status(this->animHandle,(tagANIMOBJ_ACTIVE_LIST **)&local_20), lVar41 != 0)
       ) || (local_20->right_x != 1.4013e-45)))) {
    AnimObj_Stop(this->animHandle);
    this->animHandle = -1;
  }
  if ((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0) {
    piVar42 = (int *)(this->_padding_ + 0xe0);
    if (*piVar42 != 0) {
      *piVar42 = 0;
      this->change_state = 1;
    }
    if ((this->change_state != 0) && (this->animHandle < 0)) {
      piVar42 = &this->_padding_;
      if (*piVar42 == 1) {
        *piVar42 = 2;
      }
      else if (*piVar42 == 3) {
        *piVar42 = 0;
      }
    }
  }
  else if (this->_padding_ != 0) {
    pfVar46 = (float *)(this->_padding_ + 0x108);
    this->_padding_ = 0;
    if (*pfVar46 == -1e+30) {
      *pfVar46 = 5.0;
    }
    ClearHazard(this);
  }
  iVar47 = this->_padding_;
  if (iVar47 == 0) {
    if (this->change_state != 0) {
      this->change_state = 0;
      this->_padding_ = 1;
      DoAudioNew((char *)(this->_padding_ + 0x39c),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
      AnimObj_Start((void *)this->_padding_,0,&this->animHandle);
      piVar42 = &this->_padding_;
      this->delayTimer = *(float *)(this->_padding_ + 0x3c4);
      *(undefined4 *)(*piVar42 + 0xd0) = 0;
      *(undefined4 *)(*piVar42 + 0xc4) = 0;
      *(undefined4 *)(*piVar42 + 0xcc) = 0;
      *(undefined4 *)(*piVar42 + 200) = 0;
      this->prevYaw = (float)this->_padding_;
    }
  }
  else if (iVar47 == 1) {
    iVar47 = this->_padding_;
    VVar7.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar47 + 0x50) >> 0x20);
    VVar7._0_12_ = *(undefined1 (*) [12])(iVar47 + 0x48);
    VVar7.z._0_4_ = (int)*(undefined8 *)(iVar47 + 0x58);
    VVar7.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar47 + 0x58) >> 0x20);
    fVar50 = FindFloor(VVar7);
    if ((float)*(double *)(iVar47 + 0x50) < fVar50 + 0.5) {
      this->delayTimer = this->delayTimer - param_1;
    }
    if (this->delayTimer <= 0.0) {
      this->_padding_ = 2;
      this->_padding_ = 0;
      SetHazard(this);
    }
  }
  else if (iVar47 == 2) {
    if (this->change_state != 0) {
      this->change_state = 0;
      this->_padding_ = 3;
      DoAudioNew((char *)(this->_padding_ + 0x3ac),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
      piVar42 = &this->_padding_;
      this->delayTimer = *(float *)(this->_padding_ + 0x3c8);
      *(undefined4 *)(*piVar42 + 0xd0) = 0;
      *(undefined4 *)(*piVar42 + 0xc4) = 0;
      *(undefined4 *)(*piVar42 + 0xcc) = 0;
      *(undefined4 *)(*piVar42 + 200) = 0;
      if (this->turretAligned != false) {
        AnimObj_Start((void *)this->_padding_,1,&this->animHandle);
      }
      ClearHazard(this);
    }
  }
  else if (iVar47 == 3) {
    if (this->turretAligned != false) {
      this->delayTimer = this->delayTimer - param_1;
    }
    if (this->delayTimer <= 0.0) {
      this->_padding_ = 0;
      this->_padding_ = 0;
    }
  }
  iVar47 = this->_padding_;
  if (iVar47 != 0) {
    if (this->_padding_ == 2) {
      *(undefined4 *)(iVar47 + 0x34) = *(undefined4 *)(iVar47 + 0x2c);
    }
    else {
      *(undefined4 *)(iVar47 + 0x34) = 0;
    }
  }
  iVar47 = this->_padding_;
  if (iVar47 == 0) {
    HoverCraft::Simulate((HoverCraft *)this,param_1);
    return;
  }
  if (iVar47 == 1) {
    fVar50 = GetPerformance((float)this->_padding_);
    iVar47 = this->_padding_;
    local_2c = (MAT_3D *)(*(float *)(iVar47 + 0x310) * fVar50);
    local_1c = (MAT_3D *)(*(float *)(iVar47 + 0x338) * fVar50);
    local_20 = (MAT_3D *)(fVar50 * *(float *)(iVar47 + 0x334));
    this->_padding_ = (int)0.0;
    this->_padding_ = (int)-9.8;
    this->_padding_ = (int)0.0;
    iVar47 = this->_padding_;
    local_28.Cos = (float)(iVar47 + 0x20);
    VVar6.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar47 + 0x50) >> 0x20);
    VVar6._0_12_ = *(undefined1 (*) [12])(iVar47 + 0x48);
    VVar6.z._0_4_ = (int)*(undefined8 *)(iVar47 + 0x58);
    VVar6.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar47 + 0x58) >> 0x20);
    Floor_GetFloor(VVar6,(float *)&local_c,&local_38);
    local_c = (MAT_3D *)((float)*(double *)(iVar47 + 0x50) - (float)local_c);
    fVar50 = (9.8 - local_38.y * (float)local_c * 19.6) +
             (((float)this->_padding_ * local_38.y * -6.86 -
              (float)this->_padding_ * local_38.z * 6.86) -
             local_38.x * (float)this->_padding_ * 6.86);
    if (0.0 < fVar50) {
      VVar28.x = (float)this->_padding_;
      VVar28.y = (float)this->_padding_;
      VVar28.z = (float)this->_padding_;
      VVar10.y = local_38.y;
      VVar10.x = local_38.x;
      VVar10.z = local_38.z;
      pVVar43 = AddMultVectors(&local_140,VVar28,fVar50,VVar10);
      this->_padding_ = (int)pVVar43->x;
      this->_padding_ = (int)pVVar43->y;
      this->_padding_ = (int)pVVar43->z;
    }
    VVar30.x = (float)this->_padding_;
    VVar30.y = (float)this->_padding_;
    VVar30.z = (float)this->_padding_;
    VVar29.x = (float)this->_padding_;
    VVar29.y = (float)this->_padding_;
    VVar29.z = (float)this->_padding_;
    pVVar43 = AddMultVectors(&local_1a0,VVar29,param_1,VVar30);
    local_18.x = pVVar43->x;
    local_18.z = pVVar43->z;
    local_18.y = pVVar43->y * 0.1;
    fVar50 = local_18.y * local_18.y + local_18.x * local_18.x + local_18.z * local_18.z;
    if (0.0 < fVar50) {
      dVar51 = rsqrt((double)fVar50);
      fVar50 = min<float>(1.0 / param_1,(float)dVar51 * (float)local_2c);
      VVar31.x = (float)this->_padding_;
      VVar31.y = (float)this->_padding_;
      VVar31.z = (float)this->_padding_;
      VVar11.y = local_18.y;
      VVar11.x = local_18.x;
      VVar11.z = local_18.z;
      pVVar43 = AddMultVectors(&local_ec,VVar31,-fVar50,VVar11);
      this->_padding_ = (int)pVVar43->x;
      this->_padding_ = (int)pVVar43->y;
      this->_padding_ = (int)pVVar43->z;
    }
    this->_padding_ = (int)-((float)this->_padding_ * (float)local_1c);
    this->_padding_ = (int)-((float)this->_padding_ * (float)local_1c);
    this->_padding_ = (int)-((float)this->_padding_ * (float)local_1c);
    local_18.x = local_38.x;
    local_18.y = local_38.y + 2.0;
    local_18.z = local_38.z;
    pVVar43 = Normalize_Vector(&local_104,&local_18);
    local_18.x = pVVar43->x;
    fVar50 = *(float *)local_28.Cos;
    local_18.y = pVVar43->y;
    fVar1 = *(float *)((int)local_28.Cos + 4);
    fVar2 = *(float *)((int)local_28.Cos + 8);
    local_18.z = pVVar43->z;
    VVar33.x = (float)this->_padding_;
    VVar33.y = (float)this->_padding_;
    VVar33.z = (float)this->_padding_;
    this->_padding_ =
         (int)((float)this->_padding_ -
              (local_18.z * *(float *)((int)local_28.Cos + 0x20) +
               local_18.y * *(float *)((int)local_28.Cos + 0x1c) +
              local_18.x * *(float *)((int)local_28.Cos + 0x18)) * (float)local_20);
    this->_padding_ =
         (int)((fVar2 * local_18.z + local_18.y * fVar1 + local_18.x * fVar50) * (float)local_20 +
              (float)this->_padding_);
    local_8 = param_1 * 0.5;
    VVar32.x = (float)this->_padding_;
    VVar32.y = (float)this->_padding_;
    VVar32.z = (float)this->_padding_;
    pVVar43 = AddMultVectors(&local_c8,VVar32,local_8,VVar33);
    this->_padding_ = (int)pVVar43->x;
    this->_padding_ = (int)pVVar43->y;
    this->_padding_ = (int)pVVar43->z;
    *(double *)((int)local_28.Cos + 0x28) =
         (double)((float)this->_padding_ * param_1 + (float)*(double *)((int)local_28.Cos + 0x28));
    *(double *)((int)local_28.Cos + 0x30) =
         (double)((float)this->_padding_ * param_1 + (float)*(double *)((int)local_28.Cos + 0x30));
    *(double *)((int)local_28.Cos + 0x38) =
         (double)((float)this->_padding_ * param_1 + (float)*(double *)((int)local_28.Cos + 0x38));
    VVar35.x = (float)this->_padding_;
    VVar35.y = (float)this->_padding_;
    VVar35.z = (float)this->_padding_;
    VVar34.x = (float)this->_padding_;
    VVar34.y = (float)this->_padding_;
    VVar34.z = (float)this->_padding_;
    pVVar43 = AddMultVectors(&local_134,VVar34,local_8,VVar35);
    this->_padding_ = (int)pVVar43->x;
    this->_padding_ = (int)pVVar43->y;
    this->_padding_ = (int)pVVar43->z;
    VVar37.x = (float)this->_padding_;
    VVar37.y = (float)this->_padding_;
    VVar37.z = (float)this->_padding_;
    VVar36.x = (float)this->_padding_;
    VVar36.y = (float)this->_padding_;
    VVar36.z = (float)this->_padding_;
    pVVar43 = AddMultVectors(&local_14c,VVar36,local_8,VVar37);
    pMVar45 = (MAT_3D *)local_28.Cos;
    local_18.x = pVVar43->x;
    local_18.y = pVVar43->y;
    local_18.z = pVVar43->z;
    VVar10 = *pVVar43;
    this->_padding_ = (int)local_18.x;
    this->_padding_ = (int)local_18.y;
    this->_padding_ = (int)local_18.z;
    pMVar44 = Spinner(&local_660,(MAT_3D *)local_28.Cos,VVar10,param_1);
    for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
      pMVar45->right_x = pMVar44->right_x;
      pMVar44 = (MAT_3D *)&pMVar44->right_y;
      pMVar45 = (MAT_3D *)&pMVar45->right_y;
    }
    VVar39.x = (float)this->_padding_;
    VVar39.y = (float)this->_padding_;
    VVar39.z = (float)this->_padding_;
    VVar38.x = (float)this->_padding_;
    VVar38.y = (float)this->_padding_;
    VVar38.z = (float)this->_padding_;
    pVVar43 = AddMultVectors(&local_164,VVar38,local_8,VVar39);
    this->_padding_ = (int)pVVar43->x;
    this->_padding_ = (int)pVVar43->y;
    this->_padding_ = (int)pVVar43->z;
    this->_padding_ = -0x41000000;
    this->_padding_ = 0;
  }
  else {
    if (iVar47 == 2) {
      fVar50 = GetPerformance((float)this->_padding_);
      iVar47 = this->_padding_;
      iVar48 = this->_padding_;
      local_c = (MAT_3D *)(*(float *)(iVar47 + 0x338) * fVar50);
      local_1c = (MAT_3D *)(iVar48 + 0x20);
      local_20 = (MAT_3D *)(*(float *)(iVar47 + 0x334) * fVar50);
      local_28.Cos = fVar50 * *(float *)(iVar47 + 0x3c0);
      VVar5.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar48 + 0x50) >> 0x20);
      VVar5._0_12_ = *(undefined1 (*) [12])(iVar48 + 0x48);
      VVar5.z._0_4_ = (int)*(undefined8 *)(iVar48 + 0x58);
      VVar5.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar48 + 0x58) >> 0x20);
      Floor_GetFloor(VVar5,(float *)&local_2c,&local_38);
      *(double *)(iVar48 + 0x50) = (double)(float)local_2c;
      this->_padding_ = (int)-((float)local_c * (float)this->_padding_);
      this->_padding_ = (int)-((float)local_c * (float)this->_padding_);
      this->_padding_ = (int)-((float)local_c * (float)this->_padding_);
      local_18.x = local_38.x;
      local_18.y = local_38.y + 2.0;
      local_18.z = local_38.z;
      pVVar43 = Normalize_Vector(&local_188,&local_18);
      local_18.x = pVVar43->x;
      fVar50 = local_1c->right_x;
      local_18.y = pVVar43->y;
      fVar1 = local_1c->right_y;
      fVar2 = local_1c->right_z;
      local_18.z = pVVar43->z;
      this->_padding_ =
           (int)((float)this->_padding_ -
                (local_18.z * local_1c->front_z + local_18.y * local_1c->front_y +
                local_18.x * local_1c->front_x) * (float)local_20);
      this->_padding_ =
           (int)((fVar2 * local_18.z + local_18.y * fVar1 + local_18.x * fVar50) * (float)local_20 +
                (float)this->_padding_);
      local_8 = param_1 * 0.5;
      VVar25.x = (float)this->_padding_;
      VVar25.y = (float)this->_padding_;
      VVar25.z = (float)this->_padding_;
      VVar24.x = (float)this->_padding_;
      VVar24.y = (float)this->_padding_;
      VVar24.z = (float)this->_padding_;
      pVVar43 = AddMultVectors(&local_128,VVar24,local_8,VVar25);
      this->_padding_ = (int)pVVar43->x;
      this->_padding_ = (int)pVVar43->y;
      this->_padding_ = (int)pVVar43->z;
      pMVar45 = Build_Position_Rotation_Matrix
                          (&local_620,-((float)this->_padding_ * param_1),
                           -(param_1 * (float)this->_padding_),-(param_1 * (float)this->_padding_),
                           0.0,0.0,0.0);
      fVar50 = local_8;
      pMVar44 = &local_bc;
      for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
        pMVar44->right_x = pMVar45->right_x;
        pMVar45 = (MAT_3D *)&pMVar45->right_y;
        pMVar44 = (MAT_3D *)&pMVar44->right_y;
      }
      VVar27.x = (float)this->_padding_;
      VVar27.y = (float)this->_padding_;
      VVar27.z = (float)this->_padding_;
      VVar26.x = (float)this->_padding_;
      VVar26.y = (float)this->_padding_;
      VVar26.z = (float)this->_padding_;
      pVVar43 = AddMultVectors(&local_170,VVar26,fVar50,VVar27);
      pMVar45 = local_1c;
      this->_padding_ = (int)pVVar43->x;
      this->_padding_ = (int)pVVar43->y;
      this->_padding_ = (int)pVVar43->z;
      pMVar44 = Matrix_Multiply(&local_260,&local_bc,local_1c);
      for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
        pMVar45->right_x = pMVar44->right_x;
        pMVar44 = (MAT_3D *)&pMVar44->right_y;
        pMVar45 = (MAT_3D *)&pMVar45->right_y;
      }
      local_20 = *(MAT_3D **)(this->_padding_ + 200);
      fVar50 = -(*(float *)(this->_padding_ + 0xc4) * local_28.Cos);
      this->_padding_ = (int)((1.0 / param_1) * (fVar50 - this->prevYaw) + (float)this->_padding_);
      this->prevYaw = fVar50;
      pMVar45 = Build_Yaw_Matrix(&local_2e0,fVar50 * param_1);
      pMVar44 = &local_7c;
      for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
        pMVar44->right_x = pMVar45->right_x;
        pMVar45 = (MAT_3D *)&pMVar45->right_y;
        pMVar44 = (MAT_3D *)&pMVar44->right_y;
      }
      pMVar45 = Matrix_Inverse(&local_360,unaff_EDI);
      pMVar44 = &local_1e0;
      for (iVar47 = 0x10; pMVar49 = local_1c, iVar47 != 0; iVar47 = iVar47 + -1) {
        pMVar44->right_x = pMVar45->right_x;
        pMVar45 = (MAT_3D *)&pMVar45->right_y;
        pMVar44 = (MAT_3D *)&pMVar44->right_y;
      }
      pMVar45 = Matrix_Multiply(&local_3e0,&local_7c,local_1c);
      for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
        pMVar49->right_x = pMVar45->right_x;
        pMVar45 = (MAT_3D *)&pMVar45->right_y;
        pMVar49 = (MAT_3D *)&pMVar49->right_y;
      }
      if (this->turretYObj != (_OBJ76 *)0x0) {
        Cache_Invalidate_Bsp((tagENTITY *)this->_padding_);
        this->turretAligned = false;
        local_c = *(MAT_3D **)(this->_padding_ + 0xa8);
        while (local_c != (MAT_3D *)0x0) {
          pfVar46 = &local_c->front_z;
          pMVar45 = Matrix_Multiply(&local_460,(MAT_3D *)pfVar46,&local_1e0);
          local_c = *(MAT_3D **)&local_c[2].field_0x24;
          for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
            *pfVar46 = pMVar45->right_x;
            pMVar45 = (MAT_3D *)&pMVar45->right_y;
            pfVar46 = pfVar46 + 1;
          }
        }
        pMVar44 = &this->turretYObj->transform;
        pMVar45 = Matrix_Multiply(&local_4e0,&local_7c,pMVar44);
        for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
          pMVar44->right_x = pMVar45->right_x;
          pMVar45 = (MAT_3D *)&pMVar45->right_y;
          pMVar44 = (MAT_3D *)&pMVar44->right_y;
        }
      }
      if (0 < this->turretXCount) {
        Cache_Invalidate_Bsp((tagENTITY *)this->_padding_);
        this->turretAligned = false;
        local_28 = SinCos((float)local_20 * -0.5);
        local_18.y = -local_28.Sin;
        local_1c = (MAT_3D *)0x0;
        if (0 < this->turretXCount) {
          local_c = (MAT_3D *)this->turretXObj;
          do {
            p_Var3 = (_OBJ76 *)local_c->right_x;
            local_20 = &p_Var3->transform;
            pMVar45 = Build_Pitch_Matrix(&local_560,
                                         ((p_Var3->transform).up_y * local_18.y +
                                         (p_Var3->transform).up_z * local_28.Cos) * param_1 * -5.0);
            pMVar44 = &local_220;
            for (iVar47 = 0x10; pMVar49 = local_20, iVar47 != 0; iVar47 = iVar47 + -1) {
              pMVar44->right_x = pMVar45->right_x;
              pMVar45 = (MAT_3D *)&pMVar45->right_y;
              pMVar44 = (MAT_3D *)&pMVar44->right_y;
            }
            pMVar45 = Matrix_Multiply(&local_5e0,&local_220,local_20);
            local_c = (MAT_3D *)&local_c->right_y;
            local_1c = (MAT_3D *)((int)&local_1c->right_x + 1);
            for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
              pMVar49->right_x = pMVar45->right_x;
              pMVar45 = (MAT_3D *)&pMVar45->right_y;
              pMVar49 = (MAT_3D *)&pMVar49->right_y;
            }
          } while ((int)local_1c < this->turretXCount);
        }
      }
      this->_padding_ = 0;
      this->_padding_ = 0;
      this->_padding_ = 0;
      this->_padding_ = 0;
      this->_padding_ = 0;
      this->_padding_ = 0;
      this->_padding_ = 0;
      iVar47 = -0x41000000;
    }
    else {
      if (iVar47 != 3) goto LAB_004b6140;
      fVar50 = GetPerformance((float)this->_padding_);
      iVar47 = this->_padding_;
      local_2c = (MAT_3D *)(*(float *)(iVar47 + 0x310) * fVar50);
      local_8 = *(float *)(iVar47 + 0x338) * fVar50;
      local_1c = (MAT_3D *)(fVar50 * *(float *)(iVar47 + 0x334));
      this->_padding_ = (int)0.0;
      this->_padding_ = (int)-9.8;
      local_20 = (MAT_3D *)(1.0 / param_1);
      this->_padding_ = (int)0.0;
      iVar47 = this->_padding_;
      local_28.Cos = (float)(iVar47 + 0x20);
      VVar4.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar47 + 0x50) >> 0x20);
      VVar4._0_12_ = *(undefined1 (*) [12])(iVar47 + 0x48);
      VVar4.z._0_4_ = (int)*(undefined8 *)(iVar47 + 0x58);
      VVar4.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar47 + 0x58) >> 0x20);
      local_c = local_20;
      Floor_GetFloor(VVar4,&local_3c,&local_38);
      local_3c = ((float)*(double *)(iVar47 + 0x50) - local_3c) -
                 *(float *)(this->_padding_ + 0x324);
      fVar50 = (9.8 - local_38.y * local_3c * 19.6) +
               (((float)this->_padding_ * local_38.y * -6.86 -
                (float)this->_padding_ * local_38.z * 6.86) -
               local_38.x * (float)this->_padding_ * 6.86);
      if (0.0 < fVar50) {
        VVar12.x = (float)this->_padding_;
        VVar12.y = (float)this->_padding_;
        VVar12.z = (float)this->_padding_;
        VVar8.y = local_38.y;
        VVar8.x = local_38.x;
        VVar8.z = local_38.z;
        pVVar43 = AddMultVectors(&local_11c,VVar12,fVar50,VVar8);
        this->_padding_ = (int)pVVar43->x;
        this->_padding_ = (int)pVVar43->y;
        this->_padding_ = (int)pVVar43->z;
      }
      VVar14.x = (float)this->_padding_;
      VVar14.y = (float)this->_padding_;
      VVar14.z = (float)this->_padding_;
      VVar13.x = (float)this->_padding_;
      VVar13.y = (float)this->_padding_;
      VVar13.z = (float)this->_padding_;
      pVVar43 = AddMultVectors(&local_17c,VVar13,param_1,VVar14);
      local_18.x = pVVar43->x;
      local_18.z = pVVar43->z;
      local_18.y = pVVar43->y * 0.1;
      fVar50 = local_18.z * local_18.z + local_18.y * local_18.y + local_18.x * local_18.x;
      if (0.0 < fVar50) {
        dVar51 = rsqrt((double)fVar50);
        fVar50 = min<float>((float)local_c,(float)dVar51 * (float)local_2c);
        VVar15.x = (float)this->_padding_;
        VVar15.y = (float)this->_padding_;
        VVar15.z = (float)this->_padding_;
        VVar9.y = local_18.y;
        VVar9.x = local_18.x;
        VVar9.z = local_18.z;
        pVVar43 = AddMultVectors(&local_d4,VVar15,-fVar50,VVar9);
        this->_padding_ = (int)pVVar43->x;
        this->_padding_ = (int)pVVar43->y;
        this->_padding_ = (int)pVVar43->z;
      }
      this->_padding_ = (int)-(local_8 * (float)this->_padding_);
      this->_padding_ = (int)-((float)this->_padding_ * local_8);
      this->_padding_ = (int)-((float)this->_padding_ * local_8);
      local_18.x = local_38.x;
      local_18.y = local_38.y + 2.0;
      local_18.z = local_38.z;
      pVVar43 = Normalize_Vector(&local_e0,&local_18);
      local_18.x = pVVar43->x;
      fVar50 = *(float *)local_28.Cos;
      local_18.y = pVVar43->y;
      fVar1 = *(float *)((int)local_28.Cos + 4);
      fVar2 = *(float *)((int)local_28.Cos + 8);
      local_18.z = pVVar43->z;
      VVar17.x = (float)this->_padding_;
      VVar17.y = (float)this->_padding_;
      VVar17.z = (float)this->_padding_;
      this->_padding_ =
           (int)((float)this->_padding_ -
                (local_18.x * *(float *)((int)local_28.Cos + 0x18) +
                 local_18.z * *(float *)((int)local_28.Cos + 0x20) +
                local_18.y * *(float *)((int)local_28.Cos + 0x1c)) * (float)local_1c);
      this->_padding_ =
           (int)((fVar1 * local_18.y + local_18.x * fVar50 + local_18.z * fVar2) * (float)local_1c +
                (float)this->_padding_);
      local_8 = param_1 * 0.5;
      VVar16.x = (float)this->_padding_;
      VVar16.y = (float)this->_padding_;
      VVar16.z = (float)this->_padding_;
      pVVar43 = AddMultVectors(&local_194,VVar16,local_8,VVar17);
      this->_padding_ = (int)pVVar43->x;
      this->_padding_ = (int)pVVar43->y;
      this->_padding_ = (int)pVVar43->z;
      *(double *)((int)local_28.Cos + 0x28) =
           (double)((float)this->_padding_ * param_1 + (float)*(double *)((int)local_28.Cos + 0x28))
      ;
      *(double *)((int)local_28.Cos + 0x30) =
           (double)((float)this->_padding_ * param_1 + (float)*(double *)((int)local_28.Cos + 0x30))
      ;
      *(double *)((int)local_28.Cos + 0x38) =
           (double)((float)this->_padding_ * param_1 + (float)*(double *)((int)local_28.Cos + 0x38))
      ;
      VVar19.x = (float)this->_padding_;
      VVar19.y = (float)this->_padding_;
      VVar19.z = (float)this->_padding_;
      VVar18.x = (float)this->_padding_;
      VVar18.y = (float)this->_padding_;
      VVar18.z = (float)this->_padding_;
      pVVar43 = AddMultVectors(&local_f8,VVar18,local_8,VVar19);
      this->_padding_ = (int)pVVar43->x;
      this->_padding_ = (int)pVVar43->y;
      this->_padding_ = (int)pVVar43->z;
      VVar21.x = (float)this->_padding_;
      VVar21.y = (float)this->_padding_;
      VVar21.z = (float)this->_padding_;
      VVar20.x = (float)this->_padding_;
      VVar20.y = (float)this->_padding_;
      VVar20.z = (float)this->_padding_;
      pVVar43 = AddMultVectors(&local_158,VVar20,local_8,VVar21);
      pMVar45 = (MAT_3D *)local_28.Cos;
      local_18.x = pVVar43->x;
      local_18.y = pVVar43->y;
      local_18.z = pVVar43->z;
      VVar10 = *pVVar43;
      this->_padding_ = (int)local_18.x;
      this->_padding_ = (int)local_18.y;
      this->_padding_ = (int)local_18.z;
      pMVar44 = Spinner(&local_2a0,(MAT_3D *)local_28.Cos,VVar10,param_1);
      for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
        pMVar45->right_x = pMVar44->right_x;
        pMVar44 = (MAT_3D *)&pMVar44->right_y;
        pMVar45 = (MAT_3D *)&pMVar45->right_y;
      }
      VVar23.x = (float)this->_padding_;
      VVar23.y = (float)this->_padding_;
      VVar23.z = (float)this->_padding_;
      VVar22.x = (float)this->_padding_;
      VVar22.y = (float)this->_padding_;
      VVar22.z = (float)this->_padding_;
      pVVar43 = AddMultVectors(&local_110,VVar22,local_8,VVar23);
      this->_padding_ = (int)pVVar43->x;
      this->_padding_ = (int)pVVar43->y;
      this->_padding_ = (int)pVVar43->z;
      if (this->turretAligned == false) {
        Cache_Invalidate_Bsp((tagENTITY *)this->_padding_);
        p_Var3 = this->turretYObj;
        local_8 = 0.0;
        local_c = (MAT_3D *)0x0;
        if (p_Var3 != (_OBJ76 *)0x0) {
          fVar50 = GetPerformance((float)this->_padding_);
          fVar50 = fVar50 * *(float *)(this->_padding_ + 0x3c0);
          if ((p_Var3->transform).front_z <= 0.0) {
            if ((p_Var3->transform).front_x <= 0.0) {
              fVar50 = -fVar50;
            }
          }
          else {
            fVar50 = Clamp((p_Var3->transform).front_x * (float)local_20,-fVar50,fVar50);
          }
          this->_padding_ =
               (int)((fVar50 - this->prevYaw) * (float)local_20 + (float)this->_padding_);
          this->prevYaw = fVar50;
          local_8 = fVar50;
          pMVar45 = Build_Yaw_Matrix(&local_4a0,-(fVar50 * param_1));
          pMVar44 = &local_7c;
          for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
            pMVar44->right_x = pMVar45->right_x;
            pMVar45 = (MAT_3D *)&pMVar45->right_y;
            pMVar44 = (MAT_3D *)&pMVar44->right_y;
          }
          pMVar45 = Matrix_Inverse(&local_320,unaff_EDI);
          iVar47 = this->_padding_;
          pMVar44 = &local_1e0;
          for (iVar48 = 0x10; iVar48 != 0; iVar48 = iVar48 + -1) {
            pMVar44->right_x = pMVar45->right_x;
            pMVar45 = (MAT_3D *)&pMVar45->right_y;
            pMVar44 = (MAT_3D *)&pMVar44->right_y;
          }
          local_28.Cos = *(float *)(iVar47 + 0xa8);
          while ((MAT_3D *)local_28.Cos != (MAT_3D *)0x0) {
            pfVar46 = &((MAT_3D *)local_28.Cos)->front_z;
            pMVar45 = Matrix_Multiply(&local_5a0,(MAT_3D *)pfVar46,&local_1e0);
            local_28.Cos = *(float *)&((MAT_3D *)((int)local_28.Cos + 0x80))->field_0x24;
            for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
              *pfVar46 = pMVar45->right_x;
              pMVar45 = (MAT_3D *)&pMVar45->right_y;
              pfVar46 = pfVar46 + 1;
            }
          }
          pMVar45 = Matrix_Multiply(&local_3a0,&local_7c,&this->turretYObj->transform);
          pMVar44 = &local_bc;
          for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
            pMVar44->right_x = pMVar45->right_x;
            pMVar45 = (MAT_3D *)&pMVar45->right_y;
            pMVar44 = (MAT_3D *)&pMVar44->right_y;
          }
          pMVar45 = &local_bc;
          pMVar44 = &this->turretYObj->transform;
          for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
            pMVar44->right_x = pMVar45->right_x;
            pMVar45 = (MAT_3D *)&pMVar45->right_y;
            pMVar44 = (MAT_3D *)&pMVar44->right_y;
          }
        }
        if ((0 < this->turretXCount) && (local_1c = (MAT_3D *)0x0, 0 < this->turretXCount)) {
          local_28.Cos = (float)this->turretXObj;
          do {
            local_2c = &(*(_OBJ76 **)local_28.Cos)->transform;
            local_c = (MAT_3D *)(((*(_OBJ76 **)local_28.Cos)->transform).up_z * param_1 * -5.0);
            pMVar45 = Build_Pitch_Matrix(&local_520,(float)local_c);
            pMVar44 = &local_bc;
            for (iVar47 = 0x10; pMVar49 = local_2c, iVar47 != 0; iVar47 = iVar47 + -1) {
              pMVar44->right_x = pMVar45->right_x;
              pMVar45 = (MAT_3D *)&pMVar45->right_y;
              pMVar44 = (MAT_3D *)&pMVar44->right_y;
            }
            pMVar45 = Matrix_Multiply(&local_420,&local_bc,local_2c);
            local_28.Cos = (float)((int)local_28.Cos + 4);
            local_1c = (MAT_3D *)((int)&local_1c->right_x + 1);
            for (iVar47 = 0x10; iVar47 != 0; iVar47 = iVar47 + -1) {
              pMVar49->right_x = pMVar45->right_x;
              pMVar45 = (MAT_3D *)&pMVar45->right_y;
              pMVar49 = (MAT_3D *)&pMVar49->right_y;
            }
          } while ((int)local_1c < this->turretXCount);
        }
        if ((ABS(local_8) < 0.01) && (ABS((float)local_c) < 0.01)) {
          this->turretAligned = true;
          AnimObj_Start((void *)this->_padding_,1,&this->animHandle);
        }
      }
      iVar47 = 0;
    }
    this->_padding_ = iVar47;
  }
LAB_004b6140:
  if (*(int *)(this->_padding_ + 0xf4) != 0) {
    HoverCraft::UpdateEyepoint((HoverCraft *)this,param_1);
  }
  this->_padding_ = (int)(*(float *)(this->_padding_ + 200) * 0.5);
  if (((*(byte *)(this->_padding_ + 0x14) & 0x10) == 0) ||
     ((UserProfilePtr->playOption & 0x10) == 0)) {
    bVar40 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
    if ((!bVar40) || ((*(uint *)(this->_padding_ + 0x10c) & 0x1000) == 0)) goto LAB_004b61be;
  }
  this->_padding_ = (int)((float)this->_padding_ - *(float *)(this->_padding_ + 0x3c));
LAB_004b61be:
  Craft::Simulate((Craft *)this,param_1);
  return;
}
