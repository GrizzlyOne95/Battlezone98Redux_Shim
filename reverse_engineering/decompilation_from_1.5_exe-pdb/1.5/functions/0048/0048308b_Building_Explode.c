/*
 * Entry: 0048308b
 * Name: Building::Explode
 * Namespace: Building
 * Signature: void Explode(Building * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Building::Explode(Building *this)

{
  VECTOR_3D VVar1;
  bool bVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  uint uVar3;
  int iVar4;
  int iVar5;
  ExplosionClass *this_00;
  float *pfVar6;
  MAT_3D *pMVar7;
  MAT_3D *pMVar8;
  float fVar9;
  MAT_3D local_64;
  VECTOR_3D local_24;
  undefined1 local_18 [8];
  float local_10;
  float local_c;
  long local_8;
  
  obj_set_flag((_OBJ76 *)this->_padding_,0x200);
  BettyVoice::BuildingLost(&bettyVoice,(GameObject *)&this[-1]._padding_);
  if (this->_padding_ == this->_padding_) {
    fVar9 = (float)this->_padding_;
    pfVar6 = (float *)(this->_padding_ + 0x20);
    pMVar7 = &local_64;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar7->right_x = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pMVar7 = (MAT_3D *)&pMVar7->right_y;
    }
    local_64.posit_x = (double)fVar9;
    local_64.posit_y = (double)(float)this->_padding_;
    local_64.posit_z = (double)(float)this->_padding_;
    if (*(float *)(this->_padding_ + 0x14) <= 5.0) {
      this_00 = xplVehicle;
      if (*(float *)(this->_padding_ + 0x14) <= 2.0) {
        this_00 = xplSecondary;
      }
      ExplosionClass::Build(this_00,&local_64,(_OBJ76 *)0x0);
    }
    else {
      ExplosionClass::Build(xplBuilding,&local_64,(_OBJ76 *)0x0);
      if ((xplGround != (ExplosionClass *)0x0) && (*(int *)(this->_padding_ + 0x28) == 2)) {
        fVar9 = (float)this->_padding_;
        pMVar7 = &Identity_Matrix;
        pMVar8 = &local_64;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          pMVar8->right_x = pMVar7->right_x;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
          pMVar8 = (MAT_3D *)&pMVar8->right_y;
        }
        local_64.posit_x = (double)fVar9;
        fVar9 = Terrain_FindFloor((double)(float)this->_padding_,(double)(float)this->_padding_);
        local_64.posit_y = (double)fVar9;
        local_64.posit_z = (double)(float)this->_padding_;
        ExplosionClass::Build(xplGround,&local_64,(_OBJ76 *)0x0);
      }
      if (((byte)useD3D & 4) != 0) {
        iVar5 = this->_padding_;
        local_18._0_4_ = *(float *)(iVar5 + 8);
        local_18._4_4_ = *(float *)(iVar5 + 0xc);
        local_10 = *(float *)(iVar5 + 0x10);
        local_c = *(float *)(iVar5 + 0x14);
        Vector_Transform((VECTOR_3D *)local_18,(VECTOR_3D *)local_18,1,
                         (MAT_3D *)(this->_padding_ + 0x20));
        Vector_Transform((VECTOR_3D *)local_18,(VECTOR_3D *)local_18,1,&View_Record.MainCam.Matrix);
        local_8 = Camera_Bounding_Sphere_Test(&View_Record.MainCam,(VECTOR_3D *)local_18,local_c);
        if ((double)local_8 < 0.0 != ((double)local_8 == 0.0)) {
          fVar9 = (local_c / local_10) * 3.0;
          ColorFade::SetGlare(&colorFade,fVar9 * fVar9);
        }
      }
    }
    _ftol2_sse();
    for (iVar5 = extraout_EAX; iVar5 != 0; iVar5 = iVar5 + -1) {
      uVar3 = Rand_Counter + 1U & 0xff;
      local_18._4_4_ = Pseudo_Rand_Number[uVar3] * 20.0 + (float)this->_padding_;
      uVar3 = (uVar3 + 1 & 0xff) + 1;
      Rand_Counter = uVar3 & 0xff;
      local_10 = *(float *)(&DAT_00c9021c + uVar3 * 4) * 15.0 + (float)this->_padding_ + 5.0;
      local_c = Pseudo_Rand_Number[Rand_Counter] * 20.0 + (float)this->_padding_;
      ParticleEffect::AddParticle
                (&particleEffect,(VECTOR_3D *)&this->_padding_,(VECTOR_3D *)(local_18 + 4));
    }
    if (((byte)useD3D & 4) != 0) {
      _ftol2_sse();
      for (iVar5 = extraout_EAX_00; iVar5 != 0; iVar5 = iVar5 + -1) {
        uVar3 = Rand_Counter + 1U & 0xff;
        local_18._4_4_ = Pseudo_Rand_Number[uVar3] * 40.0 + (float)this->_padding_;
        uVar3 = (uVar3 + 1 & 0xff) + 1;
        Rand_Counter = uVar3 & 0xff;
        local_10 = *(float *)(&DAT_00c9021c + uVar3 * 4) * 30.0 + (float)this->_padding_ + 10.0;
        local_c = Pseudo_Rand_Number[Rand_Counter] * 40.0 + (float)this->_padding_;
        FireballEffect::AddFireball
                  (&fireballEffect,(VECTOR_3D *)&this->_padding_,(VECTOR_3D *)(local_18 + 4));
      }
    }
    if ((((_OBJ76 *)this->_padding_)->flags & 0x800) != 0) {
      Remove_Light_Source((_OBJ76 *)this->_padding_);
    }
    if (((byte)useD3D & 4) != 0) {
      VVar1.x = (float)this->_padding_;
      VVar1.y = (float)this->_padding_;
      VVar1.z = (float)this->_padding_;
      ChunkEffect::FullFragmentObject(&chunkEffect,(_OBJ76 *)this->_padding_,VVar1,true);
      Cache_Invalidate_Bsp((tagENTITY *)this->_padding_);
    }
    local_24.x = (float)this->_padding_;
    local_24.y = (float)this->_padding_;
    local_24.z = (float)this->_padding_;
    iVar5 = 0;
    if ((*(byte *)(this->_padding_ + 0x14) & 0x80) == 0) {
      iVar4 = Net_IsNetGame();
      if (iVar4 == 0) {
        iVar5 = *(int *)(this->_padding_ + 0x54);
      }
      else {
        bVar2 = Net::IsDeathMatch();
        if (!bVar2) {
          bVar2 = DistributedObject::IsLocal((DistributedObject *)this);
          if (bVar2) {
            iVar4 = *(int *)(this->_padding_ + 0x54);
            iVar5 = (*(int *)(this->_padding_ + 0x50) + 2) / 2;
            if (iVar4 <= iVar5) {
              iVar5 = iVar4;
            }
          }
        }
      }
    }
    (**(code **)(this->_padding_ + 0x10))();
    if (0 < iVar5) {
      MakeScrapField(&local_24,iVar5);
    }
  }
  return;
}
