/*
 * Entry: 004886f7
 * Name: Craft::Explode
 * Namespace: Craft
 * Signature: void Explode(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::Explode(Craft *this)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  bool bVar4;
  int extraout_EAX;
  int extraout_EAX_00;
  uint uVar5;
  int extraout_EAX_01;
  int iVar6;
  int iVar7;
  float *pfVar8;
  MAT_3D *pMVar9;
  MAT_3D *pMVar10;
  float fVar11;
  MAT_3D local_64;
  VECTOR_3D local_24;
  undefined1 local_18 [8];
  float local_10;
  float local_c;
  int local_8;
  
  obj_set_flag((_OBJ76 *)this->_padding_,0x200);
  if (xplDetonate != (ExplosionClass *)0x0) {
    fVar11 = (float)this->_padding_;
    pfVar8 = (float *)(this->_padding_ + 0x20);
    pMVar9 = &local_64;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      pMVar9->right_x = *pfVar8;
      pfVar8 = pfVar8 + 1;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
    }
    local_64.posit_x = (double)fVar11;
    local_64.posit_y = (double)(float)this->_padding_;
    local_64.posit_z = (double)(float)this->_padding_;
    ExplosionClass::Build(xplDetonate,&local_64,(_OBJ76 *)0x0);
  }
  if (xplGround != (ExplosionClass *)0x0) {
    fVar11 = (float)this->_padding_;
    pMVar9 = &Identity_Matrix;
    pMVar10 = &local_64;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      pMVar10->right_x = pMVar9->right_x;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
      pMVar10 = (MAT_3D *)&pMVar10->right_y;
    }
    local_64.posit_x = (double)fVar11;
    fVar11 = Terrain_FindFloor((double)(float)this->_padding_,(double)(float)this->_padding_);
    local_64.posit_y = (double)fVar11;
    local_64.posit_z = (double)(float)this->_padding_;
    ExplosionClass::Build(xplGround,&local_64,(_OBJ76 *)0x0);
  }
  if ((((byte)useD3D & 4) != 0) && (iVar7 = this->_padding_, 5.0 < *(float *)(iVar7 + 0x14))) {
    local_18._0_4_ = *(float *)(iVar7 + 8);
    local_18._4_4_ = *(float *)(iVar7 + 0xc);
    local_10 = *(float *)(iVar7 + 0x10);
    local_c = *(float *)(iVar7 + 0x14);
    Vector_Transform((VECTOR_3D *)local_18,(VECTOR_3D *)local_18,1,
                     (MAT_3D *)(this->_padding_ + 0x20));
    Vector_Transform((VECTOR_3D *)local_18,(VECTOR_3D *)local_18,1,&View_Record.MainCam.Matrix);
    local_8 = Camera_Bounding_Sphere_Test(&View_Record.MainCam,(VECTOR_3D *)local_18,local_c);
    if ((double)local_8 < 0.0 != ((double)local_8 == 0.0)) {
      fVar11 = (local_c / local_10) * 3.0;
      ColorFade::SetGlare(&colorFade,fVar11 * fVar11);
    }
  }
  VVar2.x = (float)this->_padding_;
  VVar2.y = (float)this->_padding_;
  VVar2.z = (float)this->_padding_;
  ChunkEffect::FullFragmentObject
            (&chunkEffect,(_OBJ76 *)this->_padding_,VVar2,((byte)useD3D & 4) != 0);
  Cache_Invalidate_Bsp((tagENTITY *)this->_padding_);
  _ftol2_sse();
  for (iVar7 = extraout_EAX; iVar7 != 0; iVar7 = iVar7 + -1) {
    uVar5 = Rand_Counter + 1U & 0xff;
    local_18._4_4_ = Pseudo_Rand_Number[uVar5] * 20.0 + (float)this->_padding_;
    uVar5 = (uVar5 + 1 & 0xff) + 1;
    Rand_Counter = uVar5 & 0xff;
    local_10 = *(float *)(&DAT_00c9021c + uVar5 * 4) * 15.0 + (float)this->_padding_ + 5.0;
    local_c = Pseudo_Rand_Number[Rand_Counter] * 20.0 + (float)this->_padding_;
    ParticleEffect::AddParticle
              (&particleEffect,(VECTOR_3D *)&this->_padding_,(VECTOR_3D *)(local_18 + 4));
  }
  if (((byte)useD3D & 4) != 0) {
    _ftol2_sse();
    for (iVar7 = extraout_EAX_00; iVar7 != 0; iVar7 = iVar7 + -1) {
      uVar5 = Rand_Counter + 1U & 0xff;
      local_18._4_4_ = Pseudo_Rand_Number[uVar5] * 40.0 + (float)this->_padding_;
      uVar5 = (uVar5 + 1 & 0xff) + 1;
      Rand_Counter = uVar5 & 0xff;
      local_10 = *(float *)(&DAT_00c9021c + uVar5 * 4) * 30.0 + (float)this->_padding_ + 10.0;
      local_c = Pseudo_Rand_Number[Rand_Counter] * 40.0 + (float)this->_padding_;
      FireballEffect::AddFireball
                (&fireballEffect,(VECTOR_3D *)&this->_padding_,(VECTOR_3D *)(local_18 + 4));
    }
    _ftol2_sse();
    local_8 = extraout_EAX_01;
    while (local_8 != 0) {
      local_18._4_4_ = this->_padding_;
      local_8 = local_8 + -1;
      local_10 = (float)this->_padding_ + 10.0;
      local_c = (float)this->_padding_;
      VVar3.x = (float)this->_padding_;
      VVar3.y = (float)this->_padding_;
      VVar3.z = (float)this->_padding_;
      VVar1.y = local_10;
      VVar1.x = (float)local_18._4_4_;
      VVar1.z = local_c;
      ChunkEffect::CreateChunklet(&chunkEffect,VVar3,VVar1,true);
    }
  }
  local_24.x = (float)this->_padding_;
  local_24.y = (float)this->_padding_;
  local_24.z = (float)this->_padding_;
  iVar7 = 0;
  if ((*(byte *)(this->_padding_ + 0x14) & 0x80) == 0) {
    iVar6 = Net_IsNetGame();
    if (iVar6 == 0) {
      iVar7 = *(int *)(this->_padding_ + 0x54);
    }
    else {
      bVar4 = Net::IsDeathMatch();
      if ((!bVar4) && (bVar4 = DistributedObject::IsLocal((DistributedObject *)this), bVar4)) {
        iVar6 = *(int *)(this->_padding_ + 0x54);
        iVar7 = (*(int *)(this->_padding_ + 0x50) + 2) / 2;
        if (iVar6 <= iVar7) {
          iVar7 = iVar6;
        }
      }
    }
  }
  (**(code **)(this->_padding_ + 0x10))();
  if (0 < iVar7) {
    MakeScrapField(&local_24,iVar7);
  }
  return;
}
