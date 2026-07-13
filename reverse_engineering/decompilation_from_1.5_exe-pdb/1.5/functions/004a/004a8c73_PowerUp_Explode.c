/*
 * Entry: 004a8c73
 * Name: PowerUp::Explode
 * Namespace: PowerUp
 * Signature: void Explode(PowerUp * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUp::Explode(PowerUp *this)

{
  float fVar1;
  VECTOR_3D VVar2;
  int extraout_EAX;
  uint uVar3;
  int iVar4;
  ExplosionClass *this_00;
  float *pfVar5;
  MAT_3D *pMVar6;
  int iVar7;
  MAT_3D local_50;
  VECTOR_3D local_10;
  
  obj_set_flag((_OBJ76 *)this->_padding_,0x200);
  fVar1 = (float)this->_padding_;
  iVar7 = this->_padding_;
  pfVar5 = (float *)(this->_padding_ + 0x20);
  pMVar6 = &local_50;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar6->right_x = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
  }
  local_50.posit_x = (double)fVar1;
  local_50.posit_y = (double)(float)this->_padding_;
  local_50.posit_z = (double)(float)this->_padding_;
  this_00 = xplVehicle;
  if (*(float *)(iVar7 + 0x14) <= 3.0) {
    this_00 = xplSecondary;
  }
  ExplosionClass::Build(this_00,&local_50,(_OBJ76 *)0x0);
  _ftol2_sse();
  for (iVar7 = extraout_EAX; iVar7 != 0; iVar7 = iVar7 + -1) {
    uVar3 = Rand_Counter + 1U & 0xff;
    local_10.x = Pseudo_Rand_Number[uVar3] * 20.0 + (float)this->_padding_;
    uVar3 = (uVar3 + 1 & 0xff) + 1;
    Rand_Counter = uVar3 & 0xff;
    local_10.y = *(float *)(&DAT_00c9021c + uVar3 * 4) * 15.0 + (float)this->_padding_ + 5.0;
    local_10.z = Pseudo_Rand_Number[Rand_Counter] * 20.0 + (float)this->_padding_;
    ParticleEffect::AddParticle(&particleEffect,(VECTOR_3D *)&this->_padding_,&local_10);
  }
  VVar2.x = (float)this->_padding_;
  VVar2.y = (float)this->_padding_;
  VVar2.z = (float)this->_padding_;
  ChunkEffect::FullFragmentObject(&chunkEffect,(_OBJ76 *)this->_padding_,VVar2,false);
  Cache_Invalidate_Bsp((tagENTITY *)this->_padding_);
  (**(code **)(this->_padding_ + 0x10))();
  return;
}
