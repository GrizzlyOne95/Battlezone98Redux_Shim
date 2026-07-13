/*
 * Entry: 004a56ba
 * Name: Person::Simulate
 * Namespace: Person
 * Signature: void Simulate(Person * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Person::Simulate(Person *this,float param_1)

{
  int *piVar1;
  Carrier *pCVar2;
  int iVar3;
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
  char *pcVar33;
  bool bVar34;
  char cVar35;
  Weapon *pWVar36;
  int iVar37;
  long lVar38;
  VECTOR_3D *pVVar39;
  MAT_3D *pMVar40;
  uint *puVar41;
  AiMission *pAVar42;
  char *pcVar43;
  GameObject *this_00;
  DistributedObject *this_01;
  undefined4 *puVar44;
  uint uVar45;
  MAT_3D *pMVar46;
  undefined4 *puVar47;
  float fVar48;
  double dVar49;
  float fVar50;
  float fVar51;
  float fVar52;
  GAS_PREP_INFO local_108;
  VECTOR_3D local_ec;
  int local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  DistributedObject *local_c8;
  undefined4 local_c4;
  GameObjectClass *local_c0;
  float local_bc;
  float local_b8;
  float *local_b4;
  VECTOR_3D local_b0;
  float local_a4;
  VECTOR_3D local_a0;
  float local_94;
  float local_90;
  VECTOR_3D local_8c;
  MAT_3D *local_80;
  CLSN_INFO *local_7c;
  float local_78;
  float local_74;
  float local_70;
  char local_6a;
  bool local_69;
  VECTOR_3D local_68;
  VECTOR_3D local_5c;
  char local_4d;
  float local_4c;
  undefined1 local_48 [36];
  undefined4 local_24;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_78;
  this_01 = (DistributedObject *)&this->_padding_;
  local_c8 = this_01;
  bVar34 = DistributedObject::IsRemote(this_01);
  if ((!bVar34) && ((*(uint *)(this->_padding_ + 0x14) & 0x1000200) != 0)) {
    uVar45 = 0;
    if (this->_padding_ != 0) {
      local_70 = 3.36312e-44;
      do {
        pCVar2 = (Carrier *)this->_padding_;
        pWVar36 = Carrier::GetWeapon(pCVar2,uVar45);
        if (pWVar36 != (Weapon *)0x0) {
          if (uVar45 < 5) {
            *(undefined4 *)((int)pCVar2->hardpoint + (int)local_70 + -4) = 0;
            pCVar2->existant = pCVar2->existant & ~(1 << ((byte)uVar45 & 0x1f));
          }
          Weapon::Remove(pWVar36);
        }
        local_70 = (float)((int)local_70 + 4);
        uVar45 = uVar45 + 1;
      } while ((int)local_70 < 0x2c);
      operator_delete((void *)this->_padding_);
      this->_padding_ = 0;
      this_01 = local_c8;
    }
    if (this == (Person *)GameObject::userObject) {
      iVar37 = Net_IsNetGame();
      if (iVar37 != 0) {
        playerVehicleHandle = 0;
        Net_KillPlayer();
      }
      DisableInputs();
      Push_Camera();
      Set_View((tagENTITY *)this->_padding_,GK_FREE_EYE_VIEW);
      eye_controls.track_yaw = 1;
    }
    if ((*(uint *)(this->_padding_ + 0x14) & 0x1000000) != 0) {
      (**(code **)(this_01->_padding_ + 0x14))();
      return;
    }
    (**(code **)(this_01->_padding_ + 0x10))();
    return;
  }
  local_e0 = this->_padding_;
  if (param_1 == 0.0) {
    local_b8 = 1e+30;
  }
  else {
    local_b8 = 1.0 / param_1;
  }
  iVar37 = this->_padding_;
  VVar4.y._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar37 + 0x50) >> 0x20);
  VVar4._0_12_ = *(undefined1 (*) [12])(iVar37 + 0x48);
  VVar4.z._0_4_ = (int)*(undefined8 *)(iVar37 + 0x58);
  VVar4.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar37 + 0x58) >> 0x20);
  local_80 = (MAT_3D *)(iVar37 + 0x20);
  Floor_GetFloor(VVar4,&local_cc,&local_b0);
  local_6a = this->_padding_ == 0;
  local_4d = '\0';
  if ((bool)local_6a) {
    local_90 = 0.0;
    local_69 = false;
    local_78 = 0.0;
    local_d4 = 0.0;
    local_74 = 0.0;
  }
  else {
    iVar3 = this->_padding_;
    local_78 = *(float *)(iVar3 + 0xc4);
    local_d4 = *(float *)(iVar3 + 200);
    if (*(int *)(iVar3 + 0xd4) == 0) {
      local_74 = *(float *)(iVar3 + 0xd0);
    }
    else {
      local_74 = 2.0;
    }
    local_90 = *(float *)(iVar3 + 0xcc);
    local_69 = 0 < *(int *)(iVar3 + 0xd8);
  }
  pCVar2 = (Carrier *)this->_padding_;
  local_4c = 0.0;
  do {
    if (((pCVar2->selected & 1 << (SUB41(local_4c,0) & 0x1f)) != 0) &&
       (pWVar36 = Carrier::GetWeapon(pCVar2,(int)local_4c), pWVar36->weaponClass->sig == 0x534e4950)
       ) {
      local_4d = '\x01';
    }
    local_4c = (float)((int)local_4c + 1);
  } while ((int)local_4c < 5);
  local_70 = local_74 * local_74 + local_90 * local_90;
  if (1.0 < local_70) {
    local_70 = 1.0;
  }
  local_a0.x = ((MAT_3D *)(iVar37 + 0x20))->right_x;
  local_a0.y = *(float *)(iVar37 + 0x24);
  local_a0.z = *(float *)(iVar37 + 0x28);
  local_ec.x = *(float *)(iVar37 + 0x2c);
  local_ec.y = *(float *)(iVar37 + 0x30);
  local_ec.z = *(float *)(iVar37 + 0x34);
  local_5c.x = *(float *)(iVar37 + 0x38);
  local_5c.y = *(float *)(iVar37 + 0x3c);
  local_5c.z = *(float *)(iVar37 + 0x40);
  piVar1 = &this->animHandle;
  local_a4 = local_5c.x * (float)this->_padding_ +
             (float)this->_padding_ * local_5c.y + (float)this->_padding_ * local_5c.z;
  local_bc = local_a0.x * (float)this->_padding_ +
             (float)this->_padding_ * local_a0.y + (float)this->_padding_ * local_a0.z;
  if ((-1 < *piVar1) &&
     ((((*(uint *)(this->_padding_ + 0x14) & 0x200) != 0 ||
       (lVar38 = AnimObj_Status(*piVar1,(tagANIMOBJ_ACTIVE_LIST **)&local_7c), lVar38 != 0)) ||
      (local_7c->collided != 1)))) {
    AnimObj_Stop(*piVar1);
    *piVar1 = -1;
    if ((this->curAnim == 8) && (bVar34 = DistributedObject::IsRemote(local_c8), !bVar34)) {
      puVar41 = (uint *)(this->_padding_ + 0x14);
      *puVar41 = *puVar41 | 0x200;
    }
  }
  lVar38 = this->curAnim;
  local_4c = -1e+30;
  if (local_6a != '\0') {
    lVar38 = 8;
    goto LAB_004a59f7;
  }
  iVar37 = this->_padding_;
  if (iVar37 == 0) {
    if ((*(byte *)(this->_padding_ + 0x10c) & 0x80) == 0) {
      local_4c = 0.0;
      goto LAB_004a59f7;
    }
    if (local_4d != '\0') {
      lVar38 = 0;
      this->_padding_ = 1;
      goto LAB_004a59f7;
    }
    if (0.1 < (float)this->_padding_) {
      if (ABS(local_a4) <= ABS(local_bc)) {
        local_4c = local_bc * *(float *)(this->_padding_ + 0x4ac);
        if (0.0 < local_bc) {
          lVar38 = 7;
          goto LAB_004a59f7;
        }
        lVar38 = 6;
      }
      else {
        local_4c = local_a4 * *(float *)(this->_padding_ + 0x4ac);
        if (0.0 < local_a4) {
          lVar38 = 4;
          goto LAB_004a59f7;
        }
        lVar38 = 5;
      }
      local_4c = -local_4c;
      goto LAB_004a59f7;
    }
  }
  else {
    if (iVar37 == 1) {
      if (*piVar1 == -1) {
        lVar38 = 3;
        this->_padding_ = 2;
      }
      else {
        lVar38 = 0;
      }
      goto LAB_004a59f7;
    }
    if (iVar37 == 2) {
      if (local_4d == '\0') {
        lVar38 = 1;
        this->_padding_ = 3;
      }
      else {
        lVar38 = 3;
      }
      goto LAB_004a59f7;
    }
    if (iVar37 != 3) goto LAB_004a59f7;
    if (*piVar1 != -1) {
      lVar38 = 1;
      goto LAB_004a59f7;
    }
    this->_padding_ = 0;
  }
  lVar38 = 2;
LAB_004a59f7:
  if (this->curAnim != lVar38) {
    if (-1 < *piVar1) {
      AnimObj_Stop(*piVar1);
    }
    this->curAnim = lVar38;
    AnimObj_Start((void *)this->_padding_,lVar38,piVar1);
  }
  if ((-1 < *piVar1) && (!NAN(local_4c) && 0.0 < local_4c != (local_4c == 0.0))) {
    AnimObj_SetRate(*piVar1,local_4c);
  }
  if ((-1 < *piVar1) &&
     (AnimObj_Status(*piVar1,(tagANIMOBJ_ACTIVE_LIST **)&local_7c), (int)(local_7c->euler).k_i < 0))
  {
    local_a4 = (float)((int)(local_7c->euler).v_mag_inv + (int)(local_7c->euler).v_mag);
    bVar34 = (float)(int)local_a4 * 0.5 < (local_7c->euler).mass_inv;
    if (this->cycleState != bVar34) {
      this->cycleState = bVar34;
      InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
      local_24 = 0x2000;
      InitGASPrep(&local_108);
      local_108.pri = (-(uint)((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) & 0x14) + 0x2d;
      StartGASEvent((char *)(local_e0 + 0x49c),(_OBJ76 *)this->_padding_,
                    (GAS_CTRL *)(local_48 + 0x14),&local_108);
    }
  }
  iVar37 = this->_padding_;
  iVar3 = this->_padding_;
  if ((*(byte *)(iVar37 + 0x10c) & 0x80) == 0) {
    local_b4 = (float *)(iVar3 + 0x368);
  }
  else if (this->_padding_ == 0) {
    local_b4 = (float *)(iVar3 + 0x334);
  }
  else {
    local_b4 = (float *)(iVar3 + 0x300);
  }
  local_c0 = (GameObjectClass *)local_b4[1];
  fVar48 = *local_b4;
  local_bc = local_b4[5];
  local_a4 = local_b4[6];
  local_7c = (CLSN_INFO *)local_b4[7];
  local_4c = local_b4[8];
  local_dc = local_b4[9];
  local_d0 = local_b4[10];
  local_94 = local_b4[0xb];
  local_d8 = local_b4[0xc];
  this->_padding_ = (int)0.0;
  this->_padding_ = (int)-9.8;
  this->_padding_ = (int)0.0;
  if ((char)*(uint *)(iVar37 + 0x10c) < '\0') {
    fVar48 = -fVar48;
    this->_padding_ = (int)((float)this->_padding_ * fVar48);
    this->_padding_ = (int)(fVar48 * (float)this->_padding_);
    local_68.x = local_b0.x;
    local_8c.y = local_b0.y + 2.0;
    local_68.z = local_b0.z;
    local_8c.x = local_b0.x;
    local_8c.z = local_b0.z;
    local_68.y = local_8c.y;
    pVVar39 = Normalize_Vector(&local_68,&local_8c);
    local_8c.x = pVVar39->x;
    local_8c.y = pVVar39->y;
    local_8c.z = pVVar39->z;
    piVar1 = &this->_padding_;
    fVar48 = (float)*piVar1 -
             (local_8c.y * local_5c.y + local_8c.z * local_5c.z + local_8c.x * local_5c.x) *
             (float)local_c0;
    *piVar1 = (int)fVar48;
    fVar50 = (local_8c.y * local_a0.y + local_8c.z * local_a0.z + local_8c.x * local_a0.x) *
             (float)local_c0 + (float)this->_padding_;
    this->_padding_ = (int)fVar50;
    *piVar1 = (int)((local_b4[2] * (float)local_c0 * local_d4 -
                    local_b4[3] * (float)local_c0 * local_74) + fVar48);
    this->_padding_ = (int)(local_b4[4] * (float)local_c0 * local_90 + fVar50);
    fVar48 = (local_d0 - local_dc) * local_70 + local_dc;
    if (0.0 < fVar48) {
      fVar48 = Clamp(local_78 - (float)this->_padding_ / fVar48,-1.0,1.0);
      this->_padding_ = (int)(fVar48 * local_94);
    }
    fVar48 = local_a4;
    if (0.0 < local_74) {
      fVar48 = local_bc;
    }
    VVar6.y = local_5c.y;
    VVar6.x = local_5c.x;
    VVar6.z = local_5c.z;
    VVar8.y = local_a0.y;
    VVar8.x = local_a0.x;
    VVar8.z = local_a0.z;
    pVVar39 = CombineVectors(&local_5c,fVar48 * local_74,VVar6,(float)local_7c * local_90,VVar8);
    local_68.x = pVVar39->x;
    local_68.y = pVVar39->y;
    local_68.z = pVVar39->z;
    VVar9.y = local_b0.y;
    VVar9.x = local_b0.x;
    VVar9.z = local_b0.z;
    pVVar39 = AddMultVectors(&local_a0,*pVVar39,
                             -(local_b0.z * local_68.z +
                              local_b0.y * local_68.y + local_68.x * local_b0.x),VVar9);
    local_5c.x = (float)this->_padding_;
    local_5c.y = (float)this->_padding_;
    local_5c.z = (float)this->_padding_;
    local_68.x = pVVar39->x;
    local_68.y = pVVar39->y;
    local_68.z = pVVar39->z;
    local_a0.x = local_68.x - local_5c.x;
    local_a0.y = local_68.y - local_5c.y;
    local_a0.z = local_68.z - local_5c.z;
    VVar10.y = local_a0.y;
    VVar10.x = local_a0.x;
    VVar10.z = local_a0.z;
    pVVar39 = ScaleVector(&local_68,local_b8,VVar10);
    local_5c.x = pVVar39->x;
    local_5c.y = pVVar39->y;
    local_5c.z = pVVar39->z;
    fVar48 = local_5c.x * local_5c.x + local_5c.z * local_5c.z + local_5c.y * local_5c.y;
    if (local_4c * local_4c < fVar48) {
      fVar50 = pVVar39->x;
      fVar51 = pVVar39->y;
      fVar52 = pVVar39->z;
      dVar49 = rsqrt((double)fVar48);
      VVar11.y = fVar51;
      VVar11.x = fVar50;
      VVar11.z = fVar52;
      pVVar39 = ScaleVector(&local_68,(float)dVar49 * local_4c,VVar11);
      local_5c.x = pVVar39->x;
      local_5c.y = pVVar39->y;
      local_5c.z = pVVar39->z;
    }
    local_68.x = (float)this->_padding_;
    local_68.y = (float)this->_padding_;
    local_68.z = (float)this->_padding_;
    local_a0.x = local_68.x + local_5c.x;
    local_a0.y = local_5c.y + local_68.y;
    local_a0.z = local_5c.z + local_68.z;
    this->_padding_ = (int)local_a0.x;
    this->_padding_ = (int)local_a0.y;
    this->_padding_ = (int)local_a0.z;
    if ((local_69 != false) && (0.0 < local_d8)) {
      DoAudioNew((char *)(local_e0 + 0x47c),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
      VVar19.x = (float)this->_padding_;
      VVar19.y = (float)this->_padding_;
      VVar19.z = (float)this->_padding_;
      VVar12.y = local_8c.y;
      VVar12.x = local_8c.x;
      VVar12.z = local_8c.z;
      pVVar39 = AddMultVectors(&local_68,VVar19,local_d8 * local_b8,VVar12);
      this->_padding_ = (int)pVVar39->x;
      this->_padding_ = (int)pVVar39->y;
      this->_padding_ = (int)pVVar39->z;
    }
  }
  else if ((*(uint *)(iVar37 + 0x10c) & 4) == 0) {
    if ((float)this->_padding_ < 0.0) {
      *(uint *)(iVar37 + 0x10c) = *(uint *)(iVar37 + 0x10c) | 4;
    }
    this->_padding_ = 0;
    this->_padding_ = 0;
    fVar48 = (local_d0 - local_dc) * local_70 + local_dc;
    if (0.0 < fVar48) {
      fVar48 = Clamp(local_78 - (float)this->_padding_ / fVar48,-1.0,1.0);
      this->_padding_ = (int)(fVar48 * local_94);
    }
  }
  else {
    fVar48 = -fVar48;
    fVar50 = (float)this->_padding_ * fVar48 - (float)local_c0 * local_5c.y;
    this->_padding_ = (int)fVar50;
    fVar48 = (float)local_c0 * local_a0.y + (float)this->_padding_ * fVar48;
    this->_padding_ = (int)fVar48;
    this->_padding_ =
         (int)((local_b4[2] * (float)local_c0 * local_d4 - local_b4[3] * (float)local_c0 * local_74)
              + fVar50);
    this->_padding_ = (int)(local_b4[4] * (float)local_c0 * local_90 + fVar48);
    fVar48 = (local_d0 - local_dc) * local_70 + local_dc;
    if (0.0 < fVar48) {
      fVar48 = Clamp(local_78 - (float)this->_padding_ / fVar48,-1.0,1.0);
      this->_padding_ = (int)(fVar48 * local_94);
    }
    fVar48 = local_a4;
    if (0.0 < local_74) {
      fVar48 = local_bc;
    }
    VVar7.y = local_5c.y;
    VVar7.x = local_5c.x;
    VVar7.z = local_5c.z;
    VVar13.y = local_a0.y;
    VVar13.x = local_a0.x;
    VVar13.z = local_a0.z;
    pVVar39 = CombineVectors(&local_5c,fVar48 * local_74,VVar7,(float)local_7c * local_90,VVar13);
    local_8c.x = (float)this->_padding_;
    local_8c.y = (float)this->_padding_;
    local_8c.z = (float)this->_padding_;
    local_68.x = pVVar39->x - local_8c.x;
    local_5c.y = pVVar39->y - local_8c.y;
    local_68.z = pVVar39->z - local_8c.z;
    local_68.y = 0.0;
    VVar14.y = 0.0;
    VVar14.x = local_68.x;
    VVar14.z = local_68.z;
    local_5c.x = local_68.x;
    local_5c.z = local_68.z;
    pVVar39 = ScaleVector(&local_68,local_b8,VVar14);
    local_5c.x = pVVar39->x;
    local_5c.y = pVVar39->y;
    local_5c.z = pVVar39->z;
    fVar48 = local_5c.x * local_5c.x + local_5c.z * local_5c.z + local_5c.y * local_5c.y;
    if (local_4c * local_4c < fVar48) {
      fVar50 = pVVar39->x;
      fVar51 = pVVar39->y;
      fVar52 = pVVar39->z;
      dVar49 = rsqrt((double)fVar48);
      VVar15.y = fVar51;
      VVar15.x = fVar50;
      VVar15.z = fVar52;
      pVVar39 = ScaleVector(&local_68,(float)dVar49 * local_4c,VVar15);
      local_5c.x = pVVar39->x;
      local_5c.y = pVVar39->y;
      local_5c.z = pVVar39->z;
    }
    local_68.x = (float)this->_padding_;
    local_68.y = (float)this->_padding_;
    local_68.z = (float)this->_padding_;
    local_8c.x = local_68.x + local_5c.x;
    local_8c.y = local_5c.y + local_68.y;
    local_8c.z = local_5c.z + local_68.z;
    this->_padding_ = (int)local_8c.x;
    this->_padding_ = (int)local_8c.y;
    this->_padding_ = (int)local_8c.z;
    if ((float)this->_padding_ < 0.0) {
      fVar48 = (float)this->_padding_;
      this->_padding_ = (int)(fVar48 * fVar48 * 0.1 + (float)this->_padding_);
    }
  }
  local_78 = param_1 * 0.5;
  VVar21.x = (float)this->_padding_;
  VVar21.y = (float)this->_padding_;
  VVar21.z = (float)this->_padding_;
  VVar20.x = (float)this->_padding_;
  VVar20.y = (float)this->_padding_;
  VVar20.z = (float)this->_padding_;
  pVVar39 = AddMultVectors(&local_8c,VVar20,local_78,VVar21);
  local_68.x = pVVar39->x;
  local_68.y = pVVar39->y;
  local_68.z = pVVar39->z;
  this->_padding_ = (int)local_68.x;
  this->_padding_ = (int)local_68.y;
  this->_padding_ = (int)local_68.z;
  VVar23.x = (float)this->_padding_;
  VVar23.y = (float)this->_padding_;
  VVar23.z = (float)this->_padding_;
  VVar22.x = (float)this->_padding_;
  VVar22.y = (float)this->_padding_;
  VVar22.z = (float)this->_padding_;
  pVVar39 = AddMultVectors(&local_8c,VVar22,local_78,VVar23);
  this->_padding_ = (int)pVVar39->x;
  this->_padding_ = (int)pVVar39->y;
  this->_padding_ = (int)pVVar39->z;
  VVar16.y = local_68.y;
  VVar16.x = local_68.x;
  VVar16.z = local_68.z;
  fVar48 = VecLen(VVar16);
  this->_padding_ = (int)fVar48;
  if (fVar48 <= 0.0) {
    fVar48 = 1e+30;
  }
  else {
    fVar48 = 1.0 / fVar48;
  }
  iVar37 = this->_padding_;
  local_7c = (CLSN_INFO *)(iVar37 + 0x4c);
  this->_padding_ = (int)fVar48;
  if (local_7c->collided == 0) {
    local_80->posit_x = (double)((float)this->_padding_ * param_1 + (float)local_80->posit_x);
    local_80->posit_y = (double)((float)this->_padding_ * param_1 + (float)local_80->posit_y);
    local_80->posit_z = (double)((float)this->_padding_ * param_1 + (float)local_80->posit_z);
  }
  else {
    local_94 = *(float *)(iVar37 + 0x9c);
    if (0.0 <= local_94) {
      if (param_1 < local_94) {
        local_94 = param_1;
      }
      local_80->posit_x = (double)(local_94 * (float)this->_padding_ + (float)local_80->posit_x);
      local_80->posit_y = (double)((float)this->_padding_ * local_94 + (float)local_80->posit_y);
      local_80->posit_z = (double)(local_94 * (float)this->_padding_ + (float)local_80->posit_z);
    }
    else {
      local_94 = (*(float *)(iVar37 + 0xac) * *(float *)(iVar37 + 0xb8) +
                 *(float *)(iVar37 + 0xb0) * *(float *)(iVar37 + 0xbc) +
                 *(float *)(iVar37 + 0xb4) * *(float *)(iVar37 + 0xc0)) * local_94;
      local_80->posit_x = (double)((float)local_80->posit_x - local_94 * *(float *)(iVar37 + 0xb8));
      local_80->posit_y = (double)((float)local_80->posit_y - *(float *)(iVar37 + 0xbc) * local_94);
      local_80->posit_z = (double)((float)local_80->posit_z - local_94 * *(float *)(iVar37 + 0xc0));
      local_94 = 0.0;
    }
    VVar24.x = (float)this->_padding_;
    VVar24.y = (float)this->_padding_;
    VVar24.z = (float)this->_padding_;
    pVVar39 = AddMultVectors(&local_68,VVar24,
                             ((float)this->_padding_ * ((VECTOR_3D *)(iVar37 + 0xb8))->x +
                             (float)this->_padding_ * *(float *)(iVar37 + 0xbc) +
                             (float)this->_padding_ * *(float *)(iVar37 + 0xc0)) * -1.5,
                             *(VECTOR_3D *)(iVar37 + 0xb8));
    fVar48 = param_1 - local_94;
    this->_padding_ = (int)pVVar39->x;
    this->_padding_ = (int)pVVar39->y;
    this->_padding_ = (int)pVVar39->z;
    local_80->posit_x = (double)(fVar48 * (float)this->_padding_ + (float)local_80->posit_x);
    local_80->posit_y = (double)((float)this->_padding_ * fVar48 + (float)local_80->posit_y);
    local_80->posit_z = (double)(fVar48 * (float)this->_padding_ + (float)local_80->posit_z);
    ClearCollision(local_7c);
  }
  VVar25.x = (float)this->_padding_;
  VVar25.y = (float)this->_padding_;
  VVar25.z = (float)this->_padding_;
  pMVar40 = Spinner((MAT_3D *)local_48,local_80,VVar25,param_1);
  pMVar46 = local_80;
  for (iVar37 = 0x10; iVar37 != 0; iVar37 = iVar37 + -1) {
    pMVar46->right_x = pMVar40->right_x;
    pMVar40 = (MAT_3D *)&pMVar40->right_y;
    pMVar46 = (MAT_3D *)&pMVar46->right_y;
  }
  VVar27.x = (float)this->_padding_;
  VVar27.y = (float)this->_padding_;
  VVar27.z = (float)this->_padding_;
  VVar26.x = (float)this->_padding_;
  VVar26.y = (float)this->_padding_;
  VVar26.z = (float)this->_padding_;
  pVVar39 = AddMultVectors(&local_68,VVar26,local_78,VVar27);
  this->_padding_ = (int)pVVar39->x;
  this->_padding_ = (int)pVVar39->y;
  this->_padding_ = (int)pVVar39->z;
  VVar29.x = (float)this->_padding_;
  VVar29.y = (float)this->_padding_;
  VVar29.z = (float)this->_padding_;
  VVar28.x = (float)this->_padding_;
  VVar28.y = (float)this->_padding_;
  VVar28.z = (float)this->_padding_;
  pVVar39 = AddMultVectors(&local_68,VVar28,local_78,VVar29);
  pMVar40 = local_80;
  this->_padding_ = (int)pVVar39->x;
  this->_padding_ = (int)pVVar39->y;
  this->_padding_ = (int)pVVar39->z;
  VVar5.y._4_4_ = (int)((ulonglong)local_80->posit_y >> 0x20);
  VVar5._0_12_ = *(undefined1 (*) [12])&local_80->posit_x;
  VVar5.z._0_4_ = SUB84(local_80->posit_z,0);
  VVar5.z._4_4_ = (int)((ulonglong)local_80->posit_z >> 0x20);
  Floor_GetFloor(VVar5,&local_cc,&local_b0);
  if ((local_cc < (float)pMVar40->posit_y) ||
     (1.1920929e-07 <=
      (float)this->_padding_ * local_b0.x +
      (float)this->_padding_ * local_b0.z + (float)this->_padding_ * local_b0.y)) {
    puVar41 = (uint *)(this->_padding_ + 0x10c);
    *puVar41 = *puVar41 & 0xffffff7f;
  }
  else {
    VVar30.x = (float)this->_padding_;
    VVar30.y = (float)this->_padding_;
    VVar30.z = (float)this->_padding_;
    VVar17.y = local_ec.y;
    VVar17.x = local_ec.x;
    VVar17.z = local_ec.z;
    pVVar39 = AddMultVectors(&local_ec,VVar30,5.0,VVar17);
    local_8c.x = pVVar39->x;
    local_8c.y = pVVar39->y;
    local_8c.z = pVVar39->z;
    if (local_b0.z * local_8c.z + local_b0.x * local_8c.x + local_b0.y * local_8c.y < 0.0) {
      Damage_Resolve((_OBJ76 *)this->_padding_,(_OBJ76 *)0x0,&local_8c,&local_b0,(VECTOR_3D *)0x0);
    }
    puVar41 = (uint *)(this->_padding_ + 0x10c);
    if (-1 < (char)*puVar41) {
      if ((*puVar41 & 4) != 0) {
        *puVar41 = *puVar41 & 0xfffffffb;
        pAVar42 = AiMission::GetCurrent();
        if ((((((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0) &&
              (this == (Person *)GameObject::userObject)) && (bVar34 = Net::IsNetGame(), bVar34)) &&
            (((char)this->_padding_ != '\0' && (pAVar42 != (AiMission *)0x0)))) &&
           ((cVar35 = (**(code **)(pAVar42->_padding_ + 0x3c))(), cVar35 != '\0' &&
            ((iVar37 = strncmp("suser",Net::odfName + 1,5), iVar37 != 0 &&
             (iVar37 = strncmp("spilo",Net::odfName + 1,5), iVar37 != 0)))))) {
          local_c4 = 0;
          local_c0 = (GameObjectClass *)0x0;
          *(undefined1 *)&this->_padding_ = 0;
          pcVar33 = Net::odfName;
          do {
            pcVar43 = pcVar33;
            pcVar33 = pcVar43 + 1;
          } while (*pcVar43 != '\0');
          memcpy(&local_c4,Net::odfName,pcVar43 + -0x62a994);
          local_c0 = GameObjectClass::Find(CONCAT44(local_c0,local_c4));
          puVar44 = (undefined4 *)(this->_padding_ + 0x20);
          puVar47 = (undefined4 *)local_48;
          for (iVar37 = 0x10; iVar37 != 0; iVar37 = iVar37 + -1) {
            *puVar47 = *puVar44;
            puVar44 = puVar44 + 1;
            puVar47 = puVar47 + 1;
          }
          uVar45 = Rand_Counter + 1U & 0xff;
          local_20 = Clamp((double)(Pseudo_Rand_Number[uVar45] * 30.0 + (float)local_20),
                           (double)(edgeMinX + 15.0),(double)(edgeMaxX - 15.0));
          Rand_Counter = uVar45 + 1 & 0xff;
          local_10 = Clamp((double)(Pseudo_Rand_Number[Rand_Counter] * 30.0 + (float)local_10),
                           (double)(edgeMinZ + 15.0),(double)(edgeMaxZ - 15.0));
          fVar48 = Terrain_FindFloor(local_20,local_10);
          local_18 = (double)fVar48;
          fVar48 = Terrain_FindFloor(local_20 - 5.0,local_10 - 5.0);
          if ((float)local_18 < fVar48) {
            local_18 = (double)fVar48;
          }
          fVar48 = Terrain_FindFloor(local_20 - 5.0,local_10 + 5.0);
          if ((float)local_18 < fVar48) {
            local_18 = (double)fVar48;
          }
          fVar48 = Terrain_FindFloor(local_20 + 5.0,local_10 + 5.0);
          if ((float)local_18 < fVar48) {
            local_18 = (double)fVar48;
          }
          fVar48 = Terrain_FindFloor(local_20 + 5.0,local_10 - 5.0);
          if ((float)local_18 < fVar48) {
            local_18 = (double)fVar48;
          }
          local_18 = local_18 + 10.0;
          this_00 = GameObjectClass::Build(local_c0,(MAT_3D *)local_48,0,0,-1,(char *)0x0);
          if (this_00 == (GameObject *)0x0) {
            playerVehicleHandle = 0;
          }
          else {
            if (this_00->carrier != (Carrier *)0x0) {
              Carrier::SetSelected(this_00->carrier,0);
            }
            playerVehicleHandle = GameObject::GetHandle(this_00);
          }
          DistributedObject::SetLocal((DistributedObject *)&this_00->_padding_);
        }
      }
      puVar41 = (uint *)(this->_padding_ + 0x10c);
      *puVar41 = *puVar41 | 0x80;
    }
    VVar31.x = (float)this->_padding_;
    VVar31.y = (float)this->_padding_;
    VVar31.z = (float)this->_padding_;
    VVar18.y = local_b0.y;
    VVar18.x = local_b0.x;
    VVar18.z = local_b0.z;
    pVVar39 = AddMultVectors(&local_ec,VVar31,
                             -((float)this->_padding_ * local_b0.x +
                              (float)this->_padding_ * local_b0.z +
                              (float)this->_padding_ * local_b0.y),VVar18);
    this->_padding_ = (int)pVVar39->x;
    this->_padding_ = (int)pVVar39->y;
    this->_padding_ = (int)pVVar39->z;
    local_80->posit_y = (double)local_cc;
  }
  VVar32.x = (float)this->_padding_;
  VVar32.y = (float)this->_padding_;
  VVar32.z = (float)this->_padding_;
  fVar48 = VecLen(VVar32);
  this->_padding_ = (int)fVar48;
  if (fVar48 <= 0.0) {
    fVar48 = 1e+30;
  }
  else {
    fVar48 = 1.0 / fVar48;
  }
  this->_padding_ = (int)fVar48;
  Craft::UpdateTemperature((Craft *)this,param_1);
  GameObject::UpdatePosition((GameObject *)this);
  this->_padding_ = (int)(*(float *)(this->_padding_ + 200) * 0.5);
  if ((((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) &&
      ((UserProfilePtr->playOption & 0x10) != 0)) ||
     ((bVar34 = DistributedObject::IsRemote(local_c8), bVar34 &&
      ((*(uint *)(this->_padding_ + 0x10c) & 0x1000) != 0)))) {
    this->_padding_ = (int)((float)this->_padding_ - *(float *)(this->_padding_ + 0x3c));
  }
  (**(code **)(this->_padding_ + 0x94))(param_1);
  return;
}
