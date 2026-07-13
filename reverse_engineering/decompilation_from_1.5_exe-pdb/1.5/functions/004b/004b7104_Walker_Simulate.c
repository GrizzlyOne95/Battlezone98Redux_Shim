/*
 * Entry: 004b7104
 * Name: Walker::Simulate
 * Namespace: Walker
 * Signature: void Simulate(Walker * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Walker::Simulate(Walker *this,float param_1)

{
  int iVar1;
  uint uVar2;
  VECTOR_3D_LONG VVar3;
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
  VECTOR_3D VVar19;
  VECTOR_3D VVar20;
  VECTOR_3D VVar21;
  VECTOR_3D VVar22;
  VECTOR_3D VVar23;
  VECTOR_3D VVar24;
  VECTOR_3D VVar25;
  bool bVar26;
  long lVar27;
  VECTOR_3D *pVVar28;
  int *piVar29;
  MAT_3D *pMVar30;
  uint *puVar31;
  int iVar32;
  float *pfVar33;
  MAT_3D *pMVar34;
  float fVar35;
  float fVar36;
  double dVar37;
  float fVar38;
  float fVar39;
  GAS_PREP_INFO local_100;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  VECTOR_3D local_c4;
  int local_b8;
  float local_b4;
  MAT_3D *local_b0;
  VECTOR_3D local_ac;
  float *local_a0;
  float local_9c;
  float local_98;
  VECTOR_3D local_94;
  VECTOR_3D local_88;
  tagANIMOBJ_ACTIVE_LIST *local_7c;
  float local_78;
  char local_71;
  float local_70;
  float local_6c;
  char local_65;
  VECTOR_3D local_64;
  VECTOR_3D local_58;
  float local_4c;
  undefined1 local_48 [36];
  undefined4 local_24;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_78;
  local_b8 = this->_padding_;
  iVar32 = this->_padding_;
  if (param_1 == 0.0) {
    local_6c = 1e+30;
  }
  else {
    local_6c = 1.0 / param_1;
  }
  VVar3.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar32 + 0x50) >> 0x20);
  VVar3._0_12_ = *(undefined1 (*) [12])(iVar32 + 0x48);
  VVar3.z._0_4_ = (int)*(undefined8 *)(iVar32 + 0x58);
  VVar3.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar32 + 0x58) >> 0x20);
  local_b0 = (MAT_3D *)(iVar32 + 0x20);
  Floor_GetFloor(VVar3,&local_dc,&local_ac);
  iVar1 = this->_padding_;
  local_c8 = *(float *)(iVar1 + 0xc4);
  local_e0 = *(float *)(iVar1 + 200);
  if (*(int *)(iVar1 + 0xd4) < 1) {
    local_70 = *(float *)(iVar1 + 0xd0);
  }
  else {
    local_70 = 2.0;
  }
  local_78 = *(float *)(iVar1 + 0xcc);
  local_71 = 0 < *(int *)(iVar1 + 0xd8);
  local_65 = this->_padding_ == 0;
  local_9c = local_70 * local_70 + local_78 * local_78;
  if (1.0 < local_9c) {
    local_9c = 1.0;
  }
  local_94.x = ((MAT_3D *)(iVar32 + 0x20))->right_x;
  local_94.y = *(float *)(iVar32 + 0x24);
  local_94.z = *(float *)(iVar32 + 0x28);
  local_c4.x = *(float *)(iVar32 + 0x2c);
  local_c4.y = *(float *)(iVar32 + 0x30);
  local_c4.z = *(float *)(iVar32 + 0x34);
  local_64.x = *(float *)(iVar32 + 0x38);
  local_64.y = *(float *)(iVar32 + 0x3c);
  local_64.z = *(float *)(iVar32 + 0x40);
  piVar29 = &this->animHandle;
  local_98 = local_64.x * (float)this->_padding_ +
             (float)this->_padding_ * local_64.y + (float)this->_padding_ * local_64.z;
  local_b4 = (float)this->_padding_ * local_94.x +
             (float)this->_padding_ * local_94.y + (float)this->_padding_ * local_94.z;
  if ((-1 < *piVar29) &&
     ((((*(uint *)(this->_padding_ + 0x14) & 0x200) != 0 ||
       (lVar27 = AnimObj_Status(*piVar29,&local_7c), lVar27 != 0)) || (local_7c->status != 1)))) {
    AnimObj_Stop(*piVar29);
    *piVar29 = -1;
  }
  iVar32 = this->_padding_;
  local_4c = -1e+30;
  lVar27 = this->curAnim;
  if (iVar32 == 0) {
    if ((*(byte *)(this->_padding_ + 0x10c) & 0x80) == 0) {
      local_4c = 0.0;
    }
    else if (local_65 == '\0') {
      if ((float)this->_padding_ <= 0.1) {
LAB_004b72d6:
        lVar27 = 2;
      }
      else if (ABS(local_98) <= ABS(local_b4)) {
        local_4c = local_b4 * *(float *)(this->_padding_ + 0x3cc);
        if (local_b4 <= 0.0) {
          lVar27 = 6;
          goto LAB_004b7438;
        }
        lVar27 = 7;
      }
      else {
        local_4c = local_98 * *(float *)(this->_padding_ + 0x3cc);
        if (local_98 <= 0.0) {
          lVar27 = 5;
LAB_004b7438:
          local_4c = -local_4c;
        }
        else {
          lVar27 = 4;
        }
      }
    }
    else {
      lVar27 = 0;
      this->_padding_ = 1;
    }
  }
  else if (iVar32 == 1) {
    if (*piVar29 == -1) {
      lVar27 = 3;
      this->_padding_ = 2;
    }
    else {
      lVar27 = 0;
    }
  }
  else if (iVar32 == 2) {
    if (local_65 == '\0') {
      lVar27 = 1;
      this->_padding_ = 3;
    }
    else {
      lVar27 = 3;
    }
  }
  else if (iVar32 == 3) {
    if (*piVar29 == -1) {
      this->_padding_ = 0;
      goto LAB_004b72d6;
    }
    lVar27 = 1;
  }
  if (this->curAnim != lVar27) {
    if (-1 < *piVar29) {
      AnimObj_Stop(*piVar29);
    }
    this->curAnim = lVar27;
    AnimObj_Start((void *)this->_padding_,lVar27,piVar29);
  }
  if ((-1 < *piVar29) && (!NAN(local_4c) && 0.0 < local_4c != (local_4c == 0.0))) {
    AnimObj_SetRate(*piVar29,local_4c);
  }
  iVar32 = local_b8;
  if ((-1 < *piVar29) &&
     (AnimObj_Status(*piVar29,&local_7c), iVar32 = local_b8, local_7c->loopsToDo < 0)) {
    local_98 = (float)(local_7c->lastFrame + local_7c->startFrame);
    bVar26 = (float)(int)local_98 * 0.5 < local_7c->curFrame;
    if (this->cycleState != bVar26) {
      this->cycleState = bVar26;
      InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
      local_24 = 0x2000;
      InitGASPrep(&local_100);
      iVar32 = local_b8;
      local_100.pri = (-(uint)((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) & 0x14) + 0x2d;
      StartGASEvent((char *)(local_b8 + 0x3bc),(_OBJ76 *)this->_padding_,
                    (GAS_CTRL *)(local_48 + 0x14),&local_100);
    }
  }
  if ((*(byte *)(this->_padding_ + 0x10c) & 0x80) == 0) {
    pfVar33 = (float *)(iVar32 + 0x368);
  }
  else if (this->_padding_ == 0) {
    pfVar33 = (float *)(iVar32 + 0x334);
  }
  else {
    pfVar33 = (float *)(iVar32 + 0x300);
  }
  local_a0 = pfVar33;
  fVar35 = GetPerformance((float)this->_padding_);
  local_e4 = pfVar33[1] * fVar35;
  fVar36 = *pfVar33;
  local_b4 = pfVar33[5] * fVar35;
  local_98 = pfVar33[6] * fVar35;
  local_7c = (tagANIMOBJ_ACTIVE_LIST *)(pfVar33[7] * fVar35);
  local_4c = pfVar33[8] * fVar35;
  local_d8 = pfVar33[9] * fVar35;
  local_cc = pfVar33[10] * fVar35;
  local_d0 = pfVar33[0xb] * fVar35;
  local_d4 = pfVar33[0xc];
  this->_padding_ = (int)0.0;
  local_d4 = local_d4 * fVar35;
  this->_padding_ = (int)-9.8;
  this->_padding_ = (int)0.0;
  uVar2 = *(uint *)(this->_padding_ + 0x10c);
  if ((char)uVar2 < '\0') {
    fVar36 = -(fVar35 * fVar36);
    this->_padding_ = (int)((float)this->_padding_ * fVar36);
    this->_padding_ = (int)(fVar36 * (float)this->_padding_);
    local_58.x = local_ac.x;
    local_88.y = local_ac.y + 2.0;
    local_58.z = local_ac.z;
    local_88.x = local_ac.x;
    local_88.z = local_ac.z;
    local_58.y = local_88.y;
    pVVar28 = Normalize_Vector(&local_58,&local_88);
    local_88.x = pVVar28->x;
    local_88.y = pVVar28->y;
    local_88.z = pVVar28->z;
    piVar29 = &this->_padding_;
    fVar36 = (float)*piVar29 -
             (local_88.x * local_64.x + local_88.y * local_64.y + local_88.z * local_64.z) *
             local_e4;
    *piVar29 = (int)fVar36;
    fVar35 = (local_88.y * local_94.y + local_88.z * local_94.z + local_88.x * local_94.x) *
             local_e4 + (float)this->_padding_;
    this->_padding_ = (int)fVar35;
    *piVar29 = (int)((local_a0[2] * local_e4 * local_e0 - local_a0[3] * local_e4 * local_70) +
                    fVar36);
    this->_padding_ = (int)(local_a0[4] * local_e4 * local_78 + fVar35);
    fVar36 = (local_cc - local_d8) * local_9c + local_d8;
    if (0.0 < fVar36) {
      fVar36 = Clamp(local_c8 - (float)this->_padding_ / fVar36,-1.0,1.0);
      this->_padding_ = (int)(fVar36 * local_d0);
    }
    fVar36 = local_98;
    if (0.0 < local_70) {
      fVar36 = local_b4;
    }
    VVar4.y = local_64.y;
    VVar4.x = local_64.x;
    VVar4.z = local_64.z;
    VVar6.y = local_94.y;
    VVar6.x = local_94.x;
    VVar6.z = local_94.z;
    pVVar28 = CombineVectors(&local_64,fVar36 * local_70,VVar4,(float)local_7c * local_78,VVar6);
    local_58.x = pVVar28->x;
    local_58.y = pVVar28->y;
    local_58.z = pVVar28->z;
    VVar7.y = local_ac.y;
    VVar7.x = local_ac.x;
    VVar7.z = local_ac.z;
    pVVar28 = AddMultVectors(&local_94,*pVVar28,
                             -(local_58.x * local_ac.x +
                              local_58.z * local_ac.z + local_58.y * local_ac.y),VVar7);
    local_64.x = (float)this->_padding_;
    local_64.y = (float)this->_padding_;
    local_64.z = (float)this->_padding_;
    local_58.x = pVVar28->x;
    local_58.y = pVVar28->y;
    local_58.z = pVVar28->z;
    local_94.x = local_58.x - local_64.x;
    local_94.y = local_58.y - local_64.y;
    local_94.z = local_58.z - local_64.z;
    VVar8.y = local_94.y;
    VVar8.x = local_94.x;
    VVar8.z = local_94.z;
    pVVar28 = ScaleVector(&local_58,local_6c,VVar8);
    local_64.x = pVVar28->x;
    local_64.y = pVVar28->y;
    local_64.z = pVVar28->z;
    fVar36 = local_64.x * local_64.x + local_64.z * local_64.z + local_64.y * local_64.y;
    if (local_4c * local_4c < fVar36) {
      fVar35 = pVVar28->x;
      fVar38 = pVVar28->y;
      fVar39 = pVVar28->z;
      dVar37 = rsqrt((double)fVar36);
      VVar9.y = fVar38;
      VVar9.x = fVar35;
      VVar9.z = fVar39;
      pVVar28 = ScaleVector(&local_58,(float)dVar37 * local_4c,VVar9);
      local_64.x = pVVar28->x;
      local_64.y = pVVar28->y;
      local_64.z = pVVar28->z;
    }
    local_58.x = (float)this->_padding_;
    local_58.y = (float)this->_padding_;
    local_58.z = (float)this->_padding_;
    local_94.x = local_58.x + local_64.x;
    local_94.y = local_64.y + local_58.y;
    local_94.z = local_64.z + local_58.z;
    this->_padding_ = (int)local_94.x;
    this->_padding_ = (int)local_94.y;
    this->_padding_ = (int)local_94.z;
    if ((local_71 == '\0') || (local_d4 <= 0.0)) goto LAB_004b7b43;
    DoAudioNew((char *)(local_b8 + 0x39c),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
    fVar36 = local_d4 * local_6c;
    pVVar28 = (VECTOR_3D *)&this->_padding_;
    fVar35 = local_88.x;
    fVar38 = local_88.y;
    fVar39 = local_88.z;
  }
  else {
    if ((uVar2 & 4) == 0) {
      piVar29 = (int *)(this->_padding_ + 0xdc);
      if (*piVar29 != 0) {
        *piVar29 = 0;
        puVar31 = (uint *)(this->_padding_ + 0x10c);
        *puVar31 = *puVar31 | 8;
      }
      puVar31 = (uint *)(this->_padding_ + 0x10c);
      if (((*(byte *)puVar31 & 8) != 0) && ((float)this->_padding_ < 0.0)) {
        *puVar31 = *puVar31 & 0xfffffff7;
        puVar31 = (uint *)(this->_padding_ + 0x10c);
        *puVar31 = *puVar31 | 4;
      }
      this->_padding_ = 0;
      this->_padding_ = 0;
      fVar36 = (local_cc - local_d8) * local_9c + local_d8;
      if (0.0 < fVar36) {
        fVar36 = Clamp(local_c8 - (float)this->_padding_ / fVar36,-1.0,1.0);
        this->_padding_ = (int)(fVar36 * local_d0);
      }
      goto LAB_004b7b43;
    }
    fVar36 = -(fVar35 * fVar36);
    fVar35 = (float)this->_padding_ * fVar36 - local_64.y * local_e4;
    this->_padding_ = (int)fVar35;
    fVar36 = local_94.y * local_e4 + (float)this->_padding_ * fVar36;
    this->_padding_ = (int)fVar36;
    this->_padding_ =
         (int)((local_a0[2] * local_e4 * local_e0 - local_a0[3] * local_e4 * local_70) + fVar35);
    this->_padding_ = (int)(local_a0[4] * local_e4 * local_78 + fVar36);
    fVar36 = (local_cc - local_d8) * local_9c + local_d8;
    if (0.0 < fVar36) {
      fVar36 = Clamp(local_c8 - (float)this->_padding_ / fVar36,-1.0,1.0);
      this->_padding_ = (int)(fVar36 * local_d0);
    }
    fVar36 = local_98;
    if (0.0 < local_70) {
      fVar36 = local_b4;
    }
    VVar5.y = local_64.y;
    VVar5.x = local_64.x;
    VVar5.z = local_64.z;
    VVar10.y = local_94.y;
    VVar10.x = local_94.x;
    VVar10.z = local_94.z;
    pVVar28 = CombineVectors(&local_64,fVar36 * local_70,VVar5,(float)local_7c * local_78,VVar10);
    local_88.x = (float)this->_padding_;
    local_88.y = (float)this->_padding_;
    local_88.z = (float)this->_padding_;
    local_64.x = pVVar28->x - local_88.x;
    local_64.y = pVVar28->y - local_88.y;
    local_64.z = pVVar28->z - local_88.z;
    local_58.y = 0.0;
    VVar11.y = 0.0;
    VVar11.x = local_64.x;
    VVar11.z = local_64.z;
    local_58.x = local_64.x;
    local_58.z = local_64.z;
    pVVar28 = ScaleVector(&local_58,local_6c,VVar11);
    local_64.x = pVVar28->x;
    local_64.y = pVVar28->y;
    local_64.z = pVVar28->z;
    fVar36 = local_64.x * local_64.x + local_64.z * local_64.z + local_64.y * local_64.y;
    if (local_4c * local_4c < fVar36) {
      fVar35 = pVVar28->x;
      fVar38 = pVVar28->y;
      fVar39 = pVVar28->z;
      dVar37 = rsqrt((double)fVar36);
      VVar12.y = fVar38;
      VVar12.x = fVar35;
      VVar12.z = fVar39;
      pVVar28 = ScaleVector(&local_58,(float)dVar37 * local_4c,VVar12);
      local_64.x = pVVar28->x;
      local_64.y = pVVar28->y;
      local_64.z = pVVar28->z;
    }
    local_58.x = (float)this->_padding_;
    local_58.y = (float)this->_padding_;
    local_58.z = (float)this->_padding_;
    local_88.x = local_58.x + local_64.x;
    local_88.y = local_64.y + (float)this->_padding_;
    local_88.z = local_64.z + (float)this->_padding_;
    this->_padding_ = (int)local_88.x;
    this->_padding_ = (int)local_88.y;
    this->_padding_ = (int)local_88.z;
    fVar36 = (local_c4.x * (float)this->_padding_ +
             (float)this->_padding_ * local_c4.y + (float)this->_padding_ * local_c4.z) *
             (float)this->_padding_ * -0.1;
    if (fVar36 <= 0.0) goto LAB_004b7b43;
    pVVar28 = &local_88;
    fVar35 = local_c4.x;
    fVar38 = local_c4.y;
    fVar39 = local_c4.z;
  }
  VVar13.y = fVar38;
  VVar13.x = fVar35;
  VVar13.z = fVar39;
  pVVar28 = AddMultVectors(&local_58,*pVVar28,fVar36,VVar13);
  this->_padding_ = (int)pVVar28->x;
  this->_padding_ = (int)pVVar28->y;
  this->_padding_ = (int)pVVar28->z;
LAB_004b7b43:
  local_6c = param_1 * 0.5;
  VVar17.x = (float)this->_padding_;
  VVar17.y = (float)this->_padding_;
  VVar17.z = (float)this->_padding_;
  VVar16.x = (float)this->_padding_;
  VVar16.y = (float)this->_padding_;
  VVar16.z = (float)this->_padding_;
  pVVar28 = AddMultVectors(&local_88,VVar16,local_6c,VVar17);
  pMVar34 = local_b0;
  local_58.x = pVVar28->x;
  local_58.y = pVVar28->y;
  local_58.z = pVVar28->z;
  VVar5 = *pVVar28;
  this->_padding_ = (int)local_58.x;
  this->_padding_ = (int)local_58.y;
  this->_padding_ = (int)local_58.z;
  pMVar30 = Spinner((MAT_3D *)local_48,local_b0,VVar5,param_1);
  for (iVar32 = 0x10; iVar32 != 0; iVar32 = iVar32 + -1) {
    pMVar34->right_x = pMVar30->right_x;
    pMVar30 = (MAT_3D *)&pMVar30->right_y;
    pMVar34 = (MAT_3D *)&pMVar34->right_y;
  }
  VVar19.x = (float)this->_padding_;
  VVar19.y = (float)this->_padding_;
  VVar19.z = (float)this->_padding_;
  VVar18.x = (float)this->_padding_;
  VVar18.y = (float)this->_padding_;
  VVar18.z = (float)this->_padding_;
  pVVar28 = AddMultVectors(&local_58,VVar18,local_6c,VVar19);
  this->_padding_ = (int)pVVar28->x;
  this->_padding_ = (int)pVVar28->y;
  this->_padding_ = (int)pVVar28->z;
  VVar21.x = (float)this->_padding_;
  VVar21.y = (float)this->_padding_;
  VVar21.z = (float)this->_padding_;
  VVar20.x = (float)this->_padding_;
  VVar20.y = (float)this->_padding_;
  VVar20.z = (float)this->_padding_;
  pVVar28 = AddMultVectors(&local_58,VVar20,local_6c,VVar21);
  this->_padding_ = (int)pVVar28->x;
  this->_padding_ = (int)pVVar28->y;
  this->_padding_ = (int)pVVar28->z;
  local_b0->posit_x = (double)((float)this->_padding_ * param_1 + (float)local_b0->posit_x);
  local_b0->posit_y = (double)((float)this->_padding_ * param_1 + (float)local_b0->posit_y);
  local_b0->posit_z = (double)((float)this->_padding_ * param_1 + (float)local_b0->posit_z);
  VVar23.x = (float)this->_padding_;
  VVar23.y = (float)this->_padding_;
  VVar23.z = (float)this->_padding_;
  VVar22.x = (float)this->_padding_;
  VVar22.y = (float)this->_padding_;
  VVar22.z = (float)this->_padding_;
  pVVar28 = AddMultVectors(&local_88,VVar22,local_6c,VVar23);
  local_58.x = pVVar28->x;
  local_58.y = pVVar28->y;
  local_58.z = pVVar28->z;
  VVar5 = *pVVar28;
  this->_padding_ = (int)local_58.x;
  this->_padding_ = (int)local_58.y;
  this->_padding_ = (int)local_58.z;
  if (local_dc < (float)local_b0->posit_y) {
    puVar31 = (uint *)(this->_padding_ + 0x10c);
    *puVar31 = *puVar31 & 0xffffff7f;
  }
  else {
    VVar14.y = local_c4.y;
    VVar14.x = local_c4.x;
    VVar14.z = local_c4.z;
    pVVar28 = AddMultVectors(&local_58,VVar5,5.0,VVar14);
    local_c4.x = pVVar28->x;
    local_c4.y = pVVar28->y;
    local_c4.z = pVVar28->z;
    if (local_c4.x * local_ac.x + local_c4.z * local_ac.z + local_c4.y * local_ac.y < 0.0) {
      Damage_Resolve((_OBJ76 *)this->_padding_,(_OBJ76 *)0x0,&local_c4,&local_ac,(VECTOR_3D *)0x0);
    }
    puVar31 = (uint *)(this->_padding_ + 0x10c);
    if (-1 < (char)*puVar31) {
      if ((*puVar31 & 4) == 0) {
        *puVar31 = *puVar31 & 0xfffffff7;
      }
      else {
        *puVar31 = *puVar31 & 0xfffffff3;
      }
      puVar31 = (uint *)(this->_padding_ + 0x10c);
      *puVar31 = *puVar31 | 0x80;
    }
    VVar24.x = (float)this->_padding_;
    VVar24.y = (float)this->_padding_;
    VVar24.z = (float)this->_padding_;
    VVar15.y = local_ac.y;
    VVar15.x = local_ac.x;
    VVar15.z = local_ac.z;
    pVVar28 = AddMultVectors(&local_58,VVar24,
                             -((float)this->_padding_ * local_ac.x +
                              (float)this->_padding_ * local_ac.z +
                              (float)this->_padding_ * local_ac.y),VVar15);
    this->_padding_ = (int)pVVar28->x;
    this->_padding_ = (int)pVVar28->y;
    this->_padding_ = (int)pVVar28->z;
    local_b0->posit_y = (double)local_dc;
  }
  VVar25.x = (float)this->_padding_;
  VVar25.y = (float)this->_padding_;
  VVar25.z = (float)this->_padding_;
  fVar36 = VecLen(VVar25);
  this->_padding_ = (int)fVar36;
  this->_padding_ = (int)(*(float *)(this->_padding_ + 200) * 0.5);
  if ((((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) &&
      ((UserProfilePtr->playOption & 0x10) != 0)) ||
     ((bVar26 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_), bVar26 &&
      ((*(uint *)(this->_padding_ + 0x10c) & 0x1000) != 0)))) {
    this->_padding_ = (int)((float)this->_padding_ - *(float *)(this->_padding_ + 0x3c));
  }
  Craft::Simulate((Craft *)this,param_1);
  return;
}
