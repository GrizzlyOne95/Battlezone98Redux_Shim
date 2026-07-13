/*
 * Entry: 004abb7b
 * Name: Producer::Simulate
 * Namespace: Producer
 * Signature: void Simulate(Producer * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Producer::Simulate(Producer *this,float param_1)

{
  undefined1 (*pauVar1) [12];
  Geizer *this_00;
  SmokeState SVar2;
  float fVar3;
  VECTOR_3D_LONG VVar4;
  VECTOR_3D_LONG VVar5;
  VECTOR_3D_LONG VVar6;
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
  bool bVar35;
  long lVar36;
  VECTOR_3D *pVVar37;
  MAT_3D *pMVar38;
  int *piVar39;
  MAT_3D *pMVar40;
  char *pcVar41;
  _gas_object *p_Var42;
  uint uVar43;
  int iVar44;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  float *pfVar45;
  ushort uVar46;
  float fVar47;
  double dVar48;
  undefined1 local_390 [472];
  MAT_3D local_1b8;
  MAT_3D local_178;
  VECTOR_3D local_138;
  VECTOR_3D local_12c;
  VECTOR_3D local_120;
  VECTOR_3D local_114;
  VECTOR_3D local_108;
  VECTOR_3D local_fc;
  VECTOR_3D local_f0;
  VECTOR_3D local_e4;
  VECTOR_3D local_d8;
  VECTOR_3D local_cc;
  VECTOR_3D local_c0;
  VECTOR_3D local_b4;
  VECTOR_3D local_a8;
  VECTOR_3D local_9c;
  GAS_PREP_INFO local_90;
  float *local_74;
  float local_70;
  VECTOR_3D local_6c;
  VECTOR_3D local_60;
  MAT_3D *local_54;
  tagANIMOBJ_ACTIVE_LIST *local_50;
  float local_4c;
  undefined1 local_48 [36];
  undefined4 local_24;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_90.sampleRate;
  piVar39 = &this->animHandle;
  if ((-1 < *piVar39) &&
     ((lVar36 = AnimObj_Status(*piVar39,&local_50), lVar36 != 0 || (local_50->status != 1)))) {
    AnimObj_Stop(*piVar39);
    *piVar39 = -1;
    fVar47 = get_obj_radius((_OBJ76 *)this->_padding_,*(VECTOR_3D *)(this->_padding_ + 8));
    *(float *)(this->_padding_ + 0x14) = fVar47;
    GameObject::UpdatePosition((GameObject *)this);
  }
  if (((*(uint *)(this->_padding_ + 0x14) & 0x200) != 0) && (bVar35 = IsBusy(this), bVar35)) {
    CancelBuild(this);
  }
  HasPower(this);
  if (this->_padding_ == 2) {
    KickEnemys((Craft *)this);
  }
  iVar44 = this->_padding_;
  if (iVar44 == 0) {
    piVar39 = (int *)(this->_padding_ + 0xe0);
    if (*piVar39 != 0) {
      this->_padding_ = 1;
      *piVar39 = 0;
      DoAudioNew((char *)(this->_padding_ + 0x39c),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
      AnimObj_Start((void *)this->_padding_,0,&this->animHandle);
      this->delayTimer = *(float *)(this->_padding_ + 0x3c0);
      *(undefined4 *)(this->_padding_ + 0xd0) = 0;
      *(undefined4 *)(this->_padding_ + 0xc4) = 0;
      *(undefined4 *)(this->_padding_ + 0xcc) = 0;
      *(undefined4 *)(this->_padding_ + 200) = 0;
      this_00 = this->powerSource;
      if (this_00 != (Geizer *)0x0) {
        Geizer::Lock(this_00);
        iVar44 = GameObject::GetHandle((GameObject *)this->powerSource);
        this->powerHandle = iVar44;
      }
    }
    HoverCraft::Simulate((HoverCraft *)this,param_1);
  }
  else {
    if (iVar44 == 1) {
      fVar47 = this->delayTimer - param_1;
      this->delayTimer = fVar47;
      if (fVar47 < 0.0 != (fVar47 == 0.0)) {
        this->_padding_ = 2;
        AnimObj_Start((void *)this->_padding_,4,&this->animHandle);
        if (this->powerHandle == 0) {
          if (this->deployedBuilder != false) {
            *(undefined4 *)(this->_padding_ + 0xe0) = 1;
          }
        }
        else {
          Geizer::StopSteam(this->powerSource);
          BlockCells((GameObject *)this,true);
        }
      }
      fVar47 = GetPerformance((float)this->_padding_);
      iVar44 = this->_padding_;
      local_4c = *(float *)(iVar44 + 0x334) * fVar47;
      local_70 = *(float *)(iVar44 + 0x338) * fVar47;
      local_74 = (float *)(fVar47 * *(float *)(iVar44 + 0x310));
      iVar44 = this->_padding_;
      this->_padding_ = (int)0.0;
      this->_padding_ = (int)-9.8;
      local_54 = (MAT_3D *)(iVar44 + 0x20);
      this->_padding_ = (int)0.0;
      VVar6.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar44 + 0x50) >> 0x20);
      VVar6._0_12_ = *(undefined1 (*) [12])(iVar44 + 0x48);
      VVar6.z._0_4_ = (int)*(undefined8 *)(iVar44 + 0x58);
      VVar6.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar44 + 0x58) >> 0x20);
      Floor_GetFloor(VVar6,(float *)&local_50,&local_6c);
      local_50 = (tagANIMOBJ_ACTIVE_LIST *)((float)local_54->posit_y - (float)local_50);
      fVar47 = (9.8 - local_6c.y * (float)local_50 * 19.6) +
               (((float)this->_padding_ * local_6c.z * -6.86 -
                (float)this->_padding_ * local_6c.y * 6.86) -
               local_6c.x * (float)this->_padding_ * 6.86);
      if (0.0 < fVar47) {
        VVar24.x = (float)this->_padding_;
        VVar24.y = (float)this->_padding_;
        VVar24.z = (float)this->_padding_;
        VVar10.y = local_6c.y;
        VVar10.x = local_6c.x;
        VVar10.z = local_6c.z;
        pVVar37 = AddMultVectors(&local_120,VVar24,fVar47,VVar10);
        this->_padding_ = (int)pVVar37->x;
        this->_padding_ = (int)pVVar37->y;
        this->_padding_ = (int)pVVar37->z;
      }
      VVar26.x = (float)this->_padding_;
      VVar26.y = (float)this->_padding_;
      VVar26.z = (float)this->_padding_;
      VVar25.x = (float)this->_padding_;
      VVar25.y = (float)this->_padding_;
      VVar25.z = (float)this->_padding_;
      pVVar37 = AddMultVectors(&local_f0,VVar25,param_1,VVar26);
      local_60.x = pVVar37->x;
      local_60.z = pVVar37->z;
      local_60.y = pVVar37->y * 0.1;
      fVar47 = local_60.x * local_60.x + local_60.z * local_60.z + local_60.y * local_60.y;
      if (0.0 < fVar47) {
        dVar48 = rsqrt((double)fVar47);
        fVar47 = min<float>(1.0 / param_1,(float)dVar48 * (float)local_74);
        VVar27.x = (float)this->_padding_;
        VVar27.y = (float)this->_padding_;
        VVar27.z = (float)this->_padding_;
        VVar11.y = local_60.y;
        VVar11.x = local_60.x;
        VVar11.z = local_60.z;
        pVVar37 = AddMultVectors(&local_12c,VVar27,-fVar47,VVar11);
        this->_padding_ = (int)pVVar37->x;
        this->_padding_ = (int)pVVar37->y;
        this->_padding_ = (int)pVVar37->z;
      }
      fVar3 = -(local_70 * (float)this->_padding_);
      this->_padding_ = (int)fVar3;
      this->_padding_ = (int)-((float)this->_padding_ * local_70);
      fVar47 = -((float)this->_padding_ * local_70);
      this->_padding_ = (int)fVar47;
      this->_padding_ =
           (int)(fVar3 - (local_6c.x * local_54->front_x +
                         local_54->front_z * local_6c.z + local_54->front_y * local_6c.y) * local_4c
                );
      this->_padding_ =
           (int)((local_6c.x * local_54->right_x +
                 local_54->right_y * local_6c.y + local_54->right_z * local_6c.z) * local_4c +
                fVar47);
      local_4c = param_1 * 0.5;
      VVar28.x = (float)this->_padding_;
      VVar28.y = (float)this->_padding_;
      VVar28.z = (float)this->_padding_;
      VVar12.y = (float)this->_padding_;
      VVar12.x = (float)this->_padding_;
      VVar12.z = (float)this->_padding_;
      pVVar37 = AddMultVectors(&local_108,VVar28,local_4c,VVar12);
      this->_padding_ = (int)pVVar37->x;
      this->_padding_ = (int)pVVar37->y;
      this->_padding_ = (int)pVVar37->z;
      local_54->posit_x = (double)((float)this->_padding_ * param_1 + (float)local_54->posit_x);
      local_54->posit_y = (double)((float)this->_padding_ * param_1 + (float)local_54->posit_y);
      local_54->posit_z = (double)(param_1 * (float)this->_padding_ + (float)local_54->posit_z);
      VVar30.x = (float)this->_padding_;
      VVar30.y = (float)this->_padding_;
      VVar30.z = (float)this->_padding_;
      VVar29.x = (float)this->_padding_;
      VVar29.y = (float)this->_padding_;
      VVar29.z = (float)this->_padding_;
      pVVar37 = AddMultVectors(&local_c0,VVar29,local_4c,VVar30);
      local_60.x = pVVar37->x;
      local_60.y = pVVar37->y;
      local_60.z = pVVar37->z;
      VVar10 = *pVVar37;
      this->_padding_ = (int)local_60.x;
      this->_padding_ = (int)local_60.y;
      this->_padding_ = (int)local_60.z;
      fVar47 = VecLen(VVar10);
      this->_padding_ = (int)fVar47;
      VVar32.x = (float)this->_padding_;
      VVar32.y = (float)this->_padding_;
      VVar32.z = (float)this->_padding_;
      VVar31.x = (float)this->_padding_;
      VVar31.y = (float)this->_padding_;
      VVar31.z = (float)this->_padding_;
      pVVar37 = AddMultVectors(&local_cc,VVar31,local_4c,VVar32);
      pMVar40 = local_54;
      local_60.x = pVVar37->x;
      local_60.y = pVVar37->y;
      local_60.z = pVVar37->z;
      VVar10 = *pVVar37;
      this->_padding_ = (int)local_60.x;
      this->_padding_ = (int)local_60.y;
      this->_padding_ = (int)local_60.z;
      pMVar38 = Spinner(&local_178,local_54,VVar10,param_1);
      for (iVar44 = 0x10; iVar44 != 0; iVar44 = iVar44 + -1) {
        pMVar40->right_x = pMVar38->right_x;
        pMVar38 = (MAT_3D *)&pMVar38->right_y;
        pMVar40 = (MAT_3D *)&pMVar40->right_y;
      }
      VVar34.x = (float)this->_padding_;
      VVar34.y = (float)this->_padding_;
      VVar34.z = (float)this->_padding_;
      VVar33.x = (float)this->_padding_;
      VVar33.y = (float)this->_padding_;
      VVar33.z = (float)this->_padding_;
      pVVar37 = AddMultVectors(&local_a8,VVar33,local_4c,VVar34);
      iVar44 = -0x41000000;
LAB_004ac5f9:
      this->_padding_ = (int)pVVar37->x;
      this->_padding_ = (int)pVVar37->y;
      this->_padding_ = (int)pVVar37->z;
      this->_padding_ = iVar44;
      HoverCraft::UpdateSound((HoverCraft *)this,param_1);
    }
    else {
      if (iVar44 != 2) {
        if (iVar44 != 3) goto LAB_004ac6f2;
        fVar47 = this->delayTimer - param_1;
        this->delayTimer = fVar47;
        if (fVar47 < 0.0 != (fVar47 == 0.0)) {
          this->_padding_ = 0;
          if (this->powerHandle != 0) {
            Geizer::Unlock(this->powerSource);
            this->powerHandle = 0;
          }
        }
        local_70 = GetPerformance((float)this->_padding_);
        iVar44 = this->_padding_;
        local_4c = *(float *)(iVar44 + 0x334) * local_70;
        local_74 = (float *)(*(float *)(iVar44 + 0x338) * local_70);
        local_70 = local_70 * *(float *)(iVar44 + 0x310);
        iVar44 = this->_padding_;
        this->_padding_ = (int)0.0;
        this->_padding_ = (int)-9.8;
        local_54 = (MAT_3D *)(iVar44 + 0x20);
        this->_padding_ = (int)0.0;
        VVar4.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar44 + 0x50) >> 0x20);
        VVar4._0_12_ = *(undefined1 (*) [12])(iVar44 + 0x48);
        VVar4.z._0_4_ = (int)*(undefined8 *)(iVar44 + 0x58);
        VVar4.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar44 + 0x58) >> 0x20);
        Floor_GetFloor(VVar4,(float *)&local_50,&local_6c);
        local_50 = (tagANIMOBJ_ACTIVE_LIST *)
                   (((float)local_54->posit_y - (float)local_50) -
                   *(float *)(this->_padding_ + 0x324));
        fVar47 = (9.8 - local_6c.y * (float)local_50 * 19.6) +
                 (((float)this->_padding_ * local_6c.z * -6.86 -
                  (float)this->_padding_ * local_6c.y * 6.86) -
                 local_6c.x * (float)this->_padding_ * 6.86);
        if (0.0 < fVar47) {
          VVar13.x = (float)this->_padding_;
          VVar13.y = (float)this->_padding_;
          VVar13.z = (float)this->_padding_;
          VVar7.y = local_6c.y;
          VVar7.x = local_6c.x;
          VVar7.z = local_6c.z;
          pVVar37 = AddMultVectors(&local_9c,VVar13,fVar47,VVar7);
          this->_padding_ = (int)pVVar37->x;
          this->_padding_ = (int)pVVar37->y;
          this->_padding_ = (int)pVVar37->z;
        }
        VVar15.x = (float)this->_padding_;
        VVar15.y = (float)this->_padding_;
        VVar15.z = (float)this->_padding_;
        VVar14.x = (float)this->_padding_;
        VVar14.y = (float)this->_padding_;
        VVar14.z = (float)this->_padding_;
        pVVar37 = AddMultVectors(&local_138,VVar14,param_1,VVar15);
        local_60.x = pVVar37->x;
        local_60.z = pVVar37->z;
        local_60.y = pVVar37->y * 0.1;
        fVar47 = local_60.x * local_60.x + local_60.z * local_60.z + local_60.y * local_60.y;
        if (0.0 < fVar47) {
          dVar48 = rsqrt((double)fVar47);
          fVar47 = min<float>(1.0 / param_1,(float)dVar48 * local_70);
          VVar16.x = (float)this->_padding_;
          VVar16.y = (float)this->_padding_;
          VVar16.z = (float)this->_padding_;
          VVar8.y = local_60.y;
          VVar8.x = local_60.x;
          VVar8.z = local_60.z;
          pVVar37 = AddMultVectors(&local_e4,VVar16,-fVar47,VVar8);
          this->_padding_ = (int)pVVar37->x;
          this->_padding_ = (int)pVVar37->y;
          this->_padding_ = (int)pVVar37->z;
        }
        fVar3 = -((float)local_74 * (float)this->_padding_);
        this->_padding_ = (int)fVar3;
        this->_padding_ = (int)-((float)this->_padding_ * (float)local_74);
        fVar47 = -((float)this->_padding_ * (float)local_74);
        this->_padding_ = (int)fVar47;
        this->_padding_ =
             (int)(fVar3 - (local_6c.x * local_54->front_x +
                           local_54->front_z * local_6c.z + local_54->front_y * local_6c.y) *
                           local_4c);
        this->_padding_ =
             (int)((local_6c.x * local_54->right_x +
                   local_54->right_z * local_6c.z + local_54->right_y * local_6c.y) * local_4c +
                  fVar47);
        local_4c = param_1 * 0.5;
        VVar17.x = (float)this->_padding_;
        VVar17.y = (float)this->_padding_;
        VVar17.z = (float)this->_padding_;
        VVar9.y = (float)this->_padding_;
        VVar9.x = (float)this->_padding_;
        VVar9.z = (float)this->_padding_;
        pVVar37 = AddMultVectors(&local_fc,VVar17,local_4c,VVar9);
        this->_padding_ = (int)pVVar37->x;
        this->_padding_ = (int)pVVar37->y;
        this->_padding_ = (int)pVVar37->z;
        local_54->posit_x = (double)((float)this->_padding_ * param_1 + (float)local_54->posit_x);
        local_54->posit_y = (double)((float)this->_padding_ * param_1 + (float)local_54->posit_y);
        local_54->posit_z = (double)(param_1 * (float)this->_padding_ + (float)local_54->posit_z);
        VVar19.x = (float)this->_padding_;
        VVar19.y = (float)this->_padding_;
        VVar19.z = (float)this->_padding_;
        VVar18.x = (float)this->_padding_;
        VVar18.y = (float)this->_padding_;
        VVar18.z = (float)this->_padding_;
        pVVar37 = AddMultVectors(&local_114,VVar18,local_4c,VVar19);
        local_60.x = pVVar37->x;
        local_60.y = pVVar37->y;
        local_60.z = pVVar37->z;
        VVar10 = *pVVar37;
        this->_padding_ = (int)local_60.x;
        this->_padding_ = (int)local_60.y;
        this->_padding_ = (int)local_60.z;
        fVar47 = VecLen(VVar10);
        this->_padding_ = (int)fVar47;
        VVar21.x = (float)this->_padding_;
        VVar21.y = (float)this->_padding_;
        VVar21.z = (float)this->_padding_;
        VVar20.x = (float)this->_padding_;
        VVar20.y = (float)this->_padding_;
        VVar20.z = (float)this->_padding_;
        pVVar37 = AddMultVectors(&local_b4,VVar20,local_4c,VVar21);
        pMVar40 = local_54;
        local_60.x = pVVar37->x;
        local_60.y = pVVar37->y;
        local_60.z = pVVar37->z;
        VVar10 = *pVVar37;
        this->_padding_ = (int)local_60.x;
        this->_padding_ = (int)local_60.y;
        this->_padding_ = (int)local_60.z;
        pMVar38 = Spinner((MAT_3D *)local_48,local_54,VVar10,param_1);
        for (iVar44 = 0x10; iVar44 != 0; iVar44 = iVar44 + -1) {
          pMVar40->right_x = pMVar38->right_x;
          pMVar38 = (MAT_3D *)&pMVar38->right_y;
          pMVar40 = (MAT_3D *)&pMVar40->right_y;
        }
        VVar23.x = (float)this->_padding_;
        VVar23.y = (float)this->_padding_;
        VVar23.z = (float)this->_padding_;
        VVar22.x = (float)this->_padding_;
        VVar22.y = (float)this->_padding_;
        VVar22.z = (float)this->_padding_;
        pVVar37 = AddMultVectors(&local_d8,VVar22,local_4c,VVar23);
        iVar44 = 0;
        goto LAB_004ac5f9;
      }
      piVar39 = (int *)(this->_padding_ + 0xe0);
      if (*piVar39 != 0) {
        this->_padding_ = 3;
        *piVar39 = 0;
        DoAudioNew((char *)(this->_padding_ + 0x3ac),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
        piVar39 = &this->animHandle;
        if (-1 < *piVar39) {
          AnimObj_Stop(*piVar39);
          *piVar39 = -1;
        }
        AnimObj_Start((void *)this->_padding_,1,piVar39);
        this->delayTimer = *(float *)(this->_padding_ + 0x3c4);
        if (this->powerHandle != 0) {
          if (this->powerSource != (Geizer *)0x0) {
            Geizer::StartSteam(this->powerSource);
          }
          BlockCells((GameObject *)this,false);
        }
      }
      iVar44 = this->_padding_;
      local_6c.x = *(float *)(iVar44 + 0x38);
      local_74 = (float *)(iVar44 + 0x20);
      local_6c.y = *(float *)(iVar44 + 0x3c);
      local_6c.z = *(float *)(iVar44 + 0x40);
      pauVar1 = (undefined1 (*) [12])(iVar44 + 0x48);
      local_90.pri = *(long *)((int)pauVar1 + 0);
      local_90.maxCopies = *(long *)((int)pauVar1 + 4);
      local_90._20_8_ = *(undefined8 *)(iVar44 + 0x58);
      VVar5.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar44 + 0x50) >> 0x20);
      VVar5._0_12_ = *pauVar1;
      VVar5.z._0_4_ = local_90.random;
      VVar5.z._4_4_ = local_90.sampleRate;
      local_60.x = local_6c.x;
      local_60.y = local_6c.y;
      local_60.z = local_6c.z;
      Floor_GetFloor(VVar5,&local_70,&local_60);
      pMVar40 = Build_Orthogonal_Matrix(&local_1b8,unaff_EDI,unaff_ESI);
      pfVar45 = local_74;
      for (iVar44 = 0x10; iVar44 != 0; iVar44 = iVar44 + -1) {
        *pfVar45 = pMVar40->right_x;
        pMVar40 = (MAT_3D *)&pMVar40->right_y;
        pfVar45 = pfVar45 + 1;
      }
      local_74[10] = (float)local_90.pri;
      local_74[0xb] = (float)local_90.maxCopies;
      *(double *)(local_74 + 0xc) = (double)local_70;
      local_74[0xe] = (float)local_90.random;
      local_74[0xf] = (float)local_90.sampleRate;
      this->_padding_ = 0;
      this->_padding_ = 0;
      this->_padding_ = 0;
      this->_padding_ = 0;
      this->_padding_ = 0;
      this->_padding_ = 0;
      this->_padding_ = 0;
      bVar35 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
      if (((!bVar35) && (this->powerSource != (Geizer *)0x0)) &&
         (local_50 = (tagANIMOBJ_ACTIVE_LIST *)Get_TimeLocal(), this->nextRepair < (float)local_50))
      {
        (**(code **)(this->_padding_ + 0x28))(*(undefined4 *)(this->_padding_ + 0x3cc));
        this->nextRepair = *(float *)(this->_padding_ + 0x3c8) + (float)local_50;
      }
      bVar35 = IsBusy(this);
      if (bVar35) {
        UpdateBuild(this,param_1);
      }
    }
    Craft::Simulate((Craft *)this,param_1);
  }
LAB_004ac6f2:
  iVar44 = this->_padding_;
  if (iVar44 != 0) {
    if (this->_padding_ == 2) {
      *(undefined4 *)(iVar44 + 0x34) = *(undefined4 *)(iVar44 + 0x2c);
    }
    else {
      *(undefined4 *)(iVar44 + 0x34) = 0;
    }
  }
  if ((((_OBJ76 *)this->_padding_)->flags & 0x200) != 0) {
    return;
  }
  SVar2 = this->smoke;
  if (SVar2 == SMOKE_OFF) {
    if (this->_padding_ != 2) {
      return;
    }
    if (this->buildClass == (GameObjectClass *)0x0) {
      return;
    }
    this->smoke = SMOKE_START;
  }
  else if (SVar2 != SMOKE_START) {
    if (SVar2 != SMOKE_ON) {
      if (SVar2 != SMOKE_STOP) {
        return;
      }
      pcVar41 = (char *)(this->_padding_ + 0x3fc);
      if ((*pcVar41 != '\0') &&
         (p_Var42 = FindGASObject(pcVar41,(_OBJ76 *)this->_padding_), p_Var42 != (_gas_object *)0x0)
         ) {
        StopGASEvent(p_Var42);
      }
      this->smoke = SMOKE_OFF;
      return;
    }
    goto LAB_004ac7ef;
  }
  this->smokeTimer = 0.0;
  if (*(char *)(this->_padding_ + 0x3fc) != '\0') {
    InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
    local_24 = 1;
    InitGASPrep(&local_90);
    local_90.loopMode = 1;
    StartGASEvent((char *)(this->_padding_ + 0x3fc),(_OBJ76 *)this->_padding_,
                  (GAS_CTRL *)(local_48 + 0x14),&local_90);
  }
  this->smoke = SMOKE_ON;
LAB_004ac7ef:
  local_4c = 0.0;
  if (0 < this->smokeCount) {
    local_54 = (MAT_3D *)local_390;
    local_50 = (tagANIMOBJ_ACTIVE_LIST *)this->smokeList;
    do {
      pMVar38 = obj_rel_parent_matrix(&local_178,(_OBJ76 *)local_50->status,(_OBJ76 *)0x0);
      pMVar40 = local_54;
      local_50 = (tagANIMOBJ_ACTIVE_LIST *)&local_50->animHeader;
      local_4c = (float)((int)local_4c + 1);
      pfVar45 = &local_54[-1].front_x;
      for (iVar44 = 0x10; iVar44 != 0; iVar44 = iVar44 + -1) {
        *pfVar45 = pMVar38->right_x;
        pMVar38 = (MAT_3D *)&pMVar38->right_y;
        pfVar45 = pfVar45 + 1;
      }
      *(double *)local_54 = (double)(*(float *)&local_54[-1].posit_y + (float)*(double *)local_54);
      *(double *)&local_54->right_z =
           (double)(*(float *)((int)&local_54[-1].posit_y + 4) +
                   (float)*(double *)&local_54->right_z);
      pMVar38 = local_54 + -1;
      pfVar45 = &local_54->up_y;
      local_54 = local_54 + 1;
      *(double *)&pMVar40->up_y = (double)(*(float *)&pMVar38->posit_z + (float)*(double *)pfVar45);
    } while ((int)local_4c < this->smokeCount);
  }
  fVar47 = this->smokeTimer + param_1;
  this->smokeTimer = fVar47;
  uVar46 = (ushort)(0.0 < fVar47) << 8 | (ushort)NAN(fVar47) << 10;
  while ((POPCOUNT((char)(uVar46 >> 8)) & 1U) != 0) {
    local_4c = 0.0;
    if (0 < this->smokeCount) {
      local_50 = (tagANIMOBJ_ACTIVE_LIST *)(local_390 + 8);
      do {
        local_9c.x = (float)*(double *)&local_50[-1].framesToDo;
        local_6c.x = local_9c.x;
        local_9c.y = (float)*(double *)local_50;
        local_6c.y = local_9c.y;
        local_9c.z = (float)*(double *)&local_50->frameRate;
        uVar43 = (Rand_Counter + 1U & 0xff) + 1;
        Rand_Counter = uVar43 & 0xff;
        local_60.x = *(float *)(&DAT_00c9021c + uVar43 * 4) * 2.5;
        local_60.y = Pseudo_Rand_Number[Rand_Counter] * 2.5;
        local_60.z = 8.0;
        local_6c.z = local_9c.z;
        pVVar37 = Vector_Rotate(&local_a8,&local_60,(MAT_3D *)&local_50[-2].startFrame);
        local_60.x = pVVar37->x;
        local_60.y = pVVar37->y;
        local_60.z = pVVar37->z;
        SmokeEffect::AddSmoke(&smokeEffect,this->smokeEmitter,&local_9c,&local_60,this->smokeTimer);
        local_4c = (float)((int)local_4c + 1);
        local_50 = local_50 + 2;
      } while ((int)local_4c < this->smokeCount);
    }
    this->smokeTimer = this->smokeTimer - 0.2;
    uVar46 = (ushort)(0.0 < this->smokeTimer) << 8 | (ushort)NAN(this->smokeTimer) << 10;
  }
  if (this->buildClass == (GameObjectClass *)0x0) {
    this->smoke = SMOKE_STOP;
  }
  return;
}
