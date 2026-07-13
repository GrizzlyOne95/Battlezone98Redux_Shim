/*
 * Entry: 00487c01
 * Name: Craft::Simulate
 * Namespace: Craft
 * Signature: void Simulate(Craft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::Simulate(Craft *this,float param_1)

{
  ulong *puVar1;
  Carrier *pCVar2;
  undefined4 *puVar3;
  Team *this_00;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  bool bVar8;
  int iVar9;
  VECTOR_3D *pVVar10;
  VECTOR_3D *pVVar11;
  VECTOR_3D *pVVar12;
  long *plVar13;
  Weapon *pWVar14;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  uint uVar15;
  int *piVar16;
  float *pfVar17;
  VEHICLE *pVVar18;
  VECTOR_3D *pVVar19;
  uint uVar20;
  MAT_3D *pMVar21;
  float fVar22;
  double dVar23;
  int iVar24;
  char cVar25;
  MAT_3D local_5c;
  VECTOR_3D local_1c;
  VECTOR_3D *local_10;
  VECTOR_3D *local_c;
  VECTOR_3D *local_8;
  
  if (this->_padding_ == 0) {
    if (this->_padding_ == 0) {
      iVar9 = (**(code **)(this->_padding_ + 0x30))();
      this->_padding_ = iVar9;
    }
  }
  else if ((this->_padding_ != 0) && (*(int *)(this->_padding_ + 0x20) != 0x54554700)) {
    this->_padding_ = 0;
  }
  iVar9 = _isnan((double)(float)this->_padding_);
  if ((((iVar9 == 0) && (iVar9 = _isnan((double)(float)this->_padding_), iVar9 == 0)) &&
      (iVar9 = _isnan((double)(float)this->_padding_), iVar9 == 0)) &&
     (iVar9 = _isnan((double)(float)this->_padding_), iVar9 == 0)) {
    if (1000.0 < (float)this->_padding_) {
      VVar5.x = (float)this->_padding_;
      VVar5.y = (float)this->_padding_;
      VVar5.z = (float)this->_padding_;
      pVVar10 = ScaleVector(&local_1c,1000.0 / (float)this->_padding_,VVar5);
      iVar9 = 0x447a0000;
      goto LAB_00487ce6;
    }
  }
  else {
    iVar9 = 0;
    pVVar10 = &local_1c;
    local_1c.x = 0.0;
    local_1c.y = 0.0;
    local_1c.z = 0.0;
LAB_00487ce6:
    this->_padding_ = (int)pVVar10->x;
    this->_padding_ = (int)pVVar10->y;
    this->_padding_ = (int)pVVar10->z;
    this->_padding_ = iVar9;
  }
  if ((float)this->_padding_ <= 0.0) {
    fVar22 = 1e+30;
  }
  else {
    fVar22 = 1.0 / (float)this->_padding_;
  }
  pVVar18 = this->vhcl;
  this->_padding_ = (int)fVar22;
  piVar16 = &this->_padding_;
  for (iVar9 = 0x12; pVVar18 = (VEHICLE *)&pVVar18->euler, iVar9 != 0; iVar9 = iVar9 + -1) {
    ((EULER *)pVVar18)->mass = (float)*piVar16;
    piVar16 = piVar16 + 1;
  }
  local_8 = (VECTOR_3D *)(this->_padding_ + 0x20);
  iVar9 = _isnan(*(double *)(this->_padding_ + 0x48));
  pVVar10 = local_8;
  if (((iVar9 == 0) && (iVar9 = _isnan(*(double *)(local_8 + 4)), iVar9 == 0)) &&
     (iVar9 = _isnan(*(double *)&pVVar10[4].z), iVar9 == 0)) {
    iVar9 = Terrain_ValidPoint(*(double *)&pVVar10[3].y,*(double *)&pVVar10[4].z);
    if (iVar9 != 0) goto LAB_00487e3a;
    dVar23 = Clamp<double>(*(double *)&pVVar10[3].y,(double)TerMinX,(double)TerMaxX);
    *(double *)&pVVar10[3].y = dVar23;
    dVar23 = Clamp<double>(*(double *)&pVVar10[4].z,(double)TerMinZ,(double)TerMaxZ);
  }
  else {
    *(double *)&pVVar10[3].y = ((double)TerMaxX + (double)TerMinX) * 0.5;
    dVar23 = ((double)TerMaxZ + (double)TerMinZ) * 0.5;
  }
  *(double *)&pVVar10[4].z = dVar23;
  fVar22 = Terrain_FindFloor(*(double *)&pVVar10[3].y,dVar23);
  *(double *)(pVVar10 + 4) = (double)fVar22;
LAB_00487e3a:
  pVVar10 = local_8;
  pVVar19 = local_8 + 2;
  local_c = pVVar19;
  pVVar11 = Normalize_Vector(&local_1c,pVVar19);
  pVVar12 = local_8;
  pVVar19->x = pVVar11->x;
  pVVar10[2].y = pVVar11->y;
  pVVar10[2].z = pVVar11->z;
  local_10 = local_8 + 1;
  pVVar11 = Cross_Product(&local_1c,local_10,local_c);
  pVVar10 = local_8;
  pVVar12->x = pVVar11->x;
  pVVar12->y = pVVar11->y;
  pVVar12->z = pVVar11->z;
  pVVar12 = Normalize_Vector(&local_1c,local_8);
  pVVar10->x = pVVar12->x;
  pVVar10->y = pVVar12->y;
  pVVar10->z = pVVar12->z;
  pVVar10 = Cross_Product(&local_1c,local_c,local_8);
  local_10->x = pVVar10->x;
  fVar22 = local_8->x;
  local_10->y = pVVar10->y;
  local_10->z = pVVar10->z;
  iVar9 = _isnan((double)fVar22);
  pVVar10 = local_8;
  if (((iVar9 != 0) || (iVar9 = _isnan((double)local_8->y), iVar9 != 0)) ||
     ((((iVar9 = _isnan((double)pVVar10->z), iVar9 != 0 ||
        (((iVar9 = _isnan((double)local_10->x), iVar9 != 0 ||
          (iVar9 = _isnan((double)pVVar10[1].y), iVar9 != 0)) ||
         (iVar9 = _isnan((double)pVVar10[1].z), iVar9 != 0)))) ||
       ((iVar9 = _isnan((double)local_c->x), iVar9 != 0 ||
        (iVar9 = _isnan((double)pVVar10[2].y), iVar9 != 0)))) ||
      (iVar9 = _isnan((double)pVVar10[2].z), iVar9 != 0)))) {
    local_8->x = 1.0;
    local_8->y = 0.0;
    local_8->z = 0.0;
    local_10->x = 0.0;
    local_10->y = 1.0;
    local_10->z = 0.0;
    local_1c.x = 0.0;
    local_1c.y = 0.0;
    local_1c.z = 1.0;
    local_c->x = 0.0;
    local_c->y = 0.0;
    local_c->z = 1.0;
  }
  GameObject::UpdatePosition((GameObject *)this);
  UpdateTemperature(this,param_1);
  piVar16 = &this->_padding_;
  local_10 = (VECTOR_3D *)piVar16;
  bVar8 = DistributedObject::IsRemote((DistributedObject *)piVar16);
  if (!bVar8) {
    if (*(char *)((int)&this->_padding_ + 1) != '\0') {
      Team::AddScrap((Team *)this->_padding_,*(long *)(this->_padding_ + 0x54));
      Team::AddPilot((Team *)this->_padding_,*(long *)(this->_padding_ + 0x58));
      (**(code **)(*piVar16 + 0x10))();
      return;
    }
    plVar13 = &(this->vhcl->control).eject;
    if ((*plVar13 != 0) && (this->_padding_ != 0)) {
      *plVar13 = 0;
      this->fPersonEjectRatio = 1.0;
      iVar9 = Net_IsNetGame();
      if (iVar9 != 0) {
        Increment_Player_Deaths();
        Increment_Player_Deaths();
        uVar20 = (uint)(this == (Craft *)GameObject::userObject);
        cVar25 = 'E';
        iVar24 = 0;
        iVar9 = (**(code **)(*(int *)local_10 + 4))();
        KillMessage(iVar9,iVar24,cVar25,uVar20);
      }
      BettyVoice::VehicleLost(&bettyVoice,(GameObject *)this);
      DeadMenDontUseCBs((_OBJ76 *)this->_padding_);
      if (this->_padding_ != 0) {
        local_c = (VECTOR_3D *)0x0;
        local_8 = (VECTOR_3D *)0x18;
        do {
          pCVar2 = (Carrier *)this->_padding_;
          pWVar14 = Carrier::GetWeapon(pCVar2,(int)local_c);
          if (pWVar14 != (Weapon *)0x0) {
            if (local_c < (VECTOR_3D *)0x5) {
              *(undefined4 *)((int)pCVar2->hardpoint + (int)local_8 + -4) = 0;
              pCVar2->existant = pCVar2->existant & ~(1 << ((byte)local_c & 0x1f));
            }
            Weapon::Remove(pWVar14);
          }
          local_8 = (VECTOR_3D *)((int)local_8 + 4);
          local_c = (VECTOR_3D *)((int)&local_c->x + 1);
        } while ((int)local_8 < 0x2c);
        operator_delete((void *)this->_padding_);
        this->_padding_ = 0;
      }
      if ((*(byte *)(this->_padding_ + 0x14) & 0x80) == 0) {
        (**(code **)(this->_padding_ + 0x7c))();
      }
      else {
        puVar3 = (undefined4 *)this->_padding_;
        if (puVar3 != (undefined4 *)0x0) {
          (**(code **)*puVar3)(1);
        }
        this->_padding_ = 0;
      }
      obj_set_flag((_OBJ76 *)this->_padding_,0x200);
      this->_padding_ = 0;
      this->_padding_ = 0;
    }
    plVar13 = &(this->vhcl->control).abandon;
    if ((*plVar13 != 0) && (this->_padding_ != 0)) {
      *plVar13 = 0;
      (**(code **)(this->_padding_ + 0x80))();
    }
  }
  if (this->_padding_ == GameObject::userTeamNumber) {
    (**(code **)(this->_padding_ + 0x58))();
  }
  if (this->_padding_ < 0) {
    this->_padding_ = 0;
  }
  if (this->_padding_ != 0) {
    (**(code **)(this->_padding_ + 0x94))(param_1);
  }
  if ((*(uint *)(this->_padding_ + 0x14) & 0x200) != 0) {
    if ((this->vhcl->flags & 0x8000) == 0) {
      if (xplVehicle != (ExplosionClass *)0x0) {
        fVar22 = (float)this->_padding_;
        pfVar17 = (float *)(this->_padding_ + 0x20);
        pMVar21 = &local_5c;
        for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
          pMVar21->right_x = *pfVar17;
          pfVar17 = pfVar17 + 1;
          pMVar21 = (MAT_3D *)&pMVar21->right_y;
        }
        local_5c.posit_x = (double)fVar22;
        local_5c.posit_y = (double)(float)this->_padding_;
        local_5c.posit_z = (double)(float)this->_padding_;
        ExplosionClass::Build(xplVehicle,&local_5c,(_OBJ76 *)0x0);
      }
      puVar1 = &this->vhcl->flags;
      *puVar1 = *puVar1 | 0x8000;
      if (this->state != DEPLOYED) {
        this->vhcl->timer = 5.0;
      }
      BettyVoice::VehicleLost(&bettyVoice,(GameObject *)this);
      DeadMenDontUseCBs((_OBJ76 *)this->_padding_);
      if ((*(byte *)(this->_padding_ + 0x14) & 0x80) == 0) {
        if (this->_padding_ == 0) {
          puVar3 = (undefined4 *)this->_padding_;
          if (puVar3 != (undefined4 *)0x0) {
            (**(code **)*puVar3)(1);
          }
          this->_padding_ = 0;
          if (this == (Craft *)GameObject::userObject) {
            iVar9 = Net_IsNetGame();
            if (iVar9 != 0) {
              Net_KillPlayer();
            }
            DisableInputs();
            Push_Camera();
            Set_View((tagENTITY *)this->_padding_,GK_FREE_EYE_VIEW);
            eye_controls.track_yaw = 1;
          }
        }
        else {
          (**(code **)(this->_padding_ + 0x7c))();
        }
      }
      else {
        puVar3 = (undefined4 *)this->_padding_;
        if (puVar3 != (undefined4 *)0x0) {
          (**(code **)*puVar3)(1);
        }
        this->_padding_ = 0;
      }
      if (this->_padding_ != 0) {
        uVar20 = 0;
        param_1 = 3.36312e-44;
        do {
          pCVar2 = (Carrier *)this->_padding_;
          pWVar14 = Carrier::GetWeapon(pCVar2,uVar20);
          if (pWVar14 != (Weapon *)0x0) {
            if (uVar20 < 5) {
              *(undefined4 *)((int)pCVar2->hardpoint + (int)param_1 + -4) = 0;
              pCVar2->existant = pCVar2->existant & ~(1 << ((byte)uVar20 & 0x1f));
            }
            Weapon::Remove(pWVar14);
          }
          param_1 = (float)((int)param_1 + 4);
          uVar20 = uVar20 + 1;
        } while ((int)param_1 < 0x2c);
        operator_delete((void *)this->_padding_);
        this->_padding_ = 0;
      }
      Rand_Counter = Rand_Counter + 1U & 0xff;
      this->_padding_ = (int)(Pseudo_Rand_Number[Rand_Counter] * 3.0 + (float)this->_padding_);
      Rand_Counter = Rand_Counter + 1U & 0xff;
      this->_padding_ =
           (int)(Pseudo_Rand_Number[Rand_Counter] * 3.0 + (float)this->_padding_ + 10.0);
      Rand_Counter = Rand_Counter + 1U & 0xff;
      this->_padding_ = (int)(Pseudo_Rand_Number[Rand_Counter] * 3.0 + (float)this->_padding_);
      Rand_Counter = Rand_Counter + 1U & 0xff;
      this->_padding_ = (int)(Pseudo_Rand_Number[Rand_Counter] * 2.0 + (float)this->_padding_);
      Rand_Counter = Rand_Counter + 1U & 0xff;
      this->_padding_ = (int)(Pseudo_Rand_Number[Rand_Counter] * 0.5 + (float)this->_padding_);
      Rand_Counter = Rand_Counter + 1U & 0xff;
      this->_padding_ = (int)(Pseudo_Rand_Number[Rand_Counter] * 2.0 + (float)this->_padding_);
      VVar6.x = (float)this->_padding_;
      VVar6.y = (float)this->_padding_;
      VVar6.z = (float)this->_padding_;
      ChunkEffect::PartialFragmentObject
                (&chunkEffect,(_OBJ76 *)this->_padding_,VVar6,((byte)useD3D & 4) != 0);
      Cache_Invalidate_Bsp((tagENTITY *)this->_padding_);
      _ftol2_sse();
      for (iVar9 = extraout_EAX; iVar9 != 0; iVar9 = iVar9 + -1) {
        uVar20 = Rand_Counter + 1U & 0xff;
        local_1c.x = Pseudo_Rand_Number[uVar20] * 20.0 + (float)this->_padding_;
        uVar20 = (uVar20 + 1 & 0xff) + 1;
        Rand_Counter = uVar20 & 0xff;
        local_1c.y = *(float *)(&DAT_00c9021c + uVar20 * 4) * 15.0 + (float)this->_padding_ + 5.0;
        local_1c.z = Pseudo_Rand_Number[Rand_Counter] * 20.0 + (float)this->_padding_;
        ParticleEffect::AddParticle(&particleEffect,(VECTOR_3D *)&this->_padding_,&local_1c);
      }
      if (((byte)useD3D & 4) != 0) {
        _ftol2_sse();
        for (iVar9 = extraout_EAX_00; iVar9 != 0; iVar9 = iVar9 + -1) {
          uVar20 = Rand_Counter + 1U & 0xff;
          local_1c.x = Pseudo_Rand_Number[uVar20] * 40.0 + (float)this->_padding_;
          uVar20 = (uVar20 + 1 & 0xff) + 1;
          Rand_Counter = uVar20 & 0xff;
          local_1c.y = *(float *)(&DAT_00c9021c + uVar20 * 4) * 30.0 + (float)this->_padding_ + 10.0
          ;
          local_1c.z = Pseudo_Rand_Number[Rand_Counter] * 40.0 + (float)this->_padding_;
          FireballEffect::AddFireball(&fireballEffect,(VECTOR_3D *)&this->_padding_,&local_1c);
        }
        iVar9 = Net_IsNetGame();
        if (iVar9 == 0) {
          _ftol2_sse();
          for (iVar9 = extraout_EAX_01; iVar9 != 0; iVar9 = iVar9 + -1) {
            local_1c.x = (float)this->_padding_;
            local_1c.y = (float)this->_padding_ + 10.0;
            local_1c.z = (float)this->_padding_;
            VVar7.x = (float)this->_padding_;
            VVar7.y = (float)this->_padding_;
            VVar7.z = (float)this->_padding_;
            VVar4.y = local_1c.y;
            VVar4.x = local_1c.x;
            VVar4.z = local_1c.z;
            ChunkEffect::CreateChunklet(&chunkEffect,VVar7,VVar4,true);
          }
        }
      }
    }
    else {
      pfVar17 = &this->vhcl->timer;
      if (*pfVar17 <= 0.0) {
        (**(code **)(*(int *)local_10 + 0x14))();
        return;
      }
      *pfVar17 = *pfVar17 - param_1;
      if ((xplSecondary != (ExplosionClass *)0x0) &&
         (fVar22 = Random(), (fVar22 + 1.0) * 0.5 < param_1 * 5.0)) {
        fVar22 = *(float *)(this->_padding_ + 0x14) * 0.7;
        pfVar17 = (float *)(this->_padding_ + 0x20);
        pMVar21 = &local_5c;
        for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
          pMVar21->right_x = *pfVar17;
          pfVar17 = pfVar17 + 1;
          pMVar21 = (MAT_3D *)&pMVar21->right_y;
        }
        uVar20 = (Rand_Counter + 1U & 0xff) + 1;
        uVar15 = (uVar20 & 0xff) + 1;
        local_5c.posit_x =
             (double)(*(float *)(&DAT_00c9021c + uVar20 * 4) * fVar22 + (float)this->_padding_);
        Rand_Counter = uVar15 & 0xff;
        local_5c.posit_y =
             (double)(*(float *)(&DAT_00c9021c + uVar15 * 4) * fVar22 + (float)this->_padding_);
        local_5c.posit_z =
             (double)(fVar22 * Pseudo_Rand_Number[Rand_Counter] + (float)this->_padding_);
        ExplosionClass::Build(xplSecondary,&local_5c,(_OBJ76 *)0x0);
      }
    }
  }
  if ((this->_padding_ == -1) && (this->_padding_ != 0)) {
    iVar9 = *(int *)(this->_padding_ + 0x144);
    if ((4 < iVar9) && (iVar24 = *(int *)(this->_padding_ + 0x148), 4 < iVar24)) {
      iVar9 = Team::FirstEmptySlot((Team *)this->_padding_,iVar9,iVar24);
      this_00 = (Team *)this->_padding_;
      this->_padding_ = iVar9;
      if ((this_00 != (Team *)0x0) && (iVar9 != -1)) {
        Team::SetSlot(this_00,iVar9,(GameObject *)this);
      }
    }
  }
  return;
}
