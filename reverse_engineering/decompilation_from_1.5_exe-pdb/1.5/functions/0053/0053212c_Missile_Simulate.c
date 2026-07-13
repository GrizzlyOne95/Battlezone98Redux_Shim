/*
 * Entry: 0053212c
 * Name: Missile::Simulate
 * Namespace: Missile
 * Signature: void Simulate(Missile * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Missile::Simulate(Missile *this,float param_1)

{
  int *piVar1;
  float fVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  MAT_3D *pMVar5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  float fVar9;
  MAT_3D local_88;
  float local_48 [16];
  MAT_3D *local_8;
  
  iVar6 = this->_padding_;
  if ((*(byte *)(iVar6 + 0x14) & 8) != 0) {
    fVar9 = *(float *)(this->_padding_ + 0x50);
    piVar1 = &this->_padding_;
    local_8 = (MAT_3D *)(iVar6 + 0x20);
    fVar2 = *(float *)(this->_padding_ + 0xb4) * param_1;
    *piVar1 = (int)((*(float *)(iVar6 + 0x38) * fVar9 - (float)*piVar1) * fVar2 + (float)*piVar1);
    this->_padding_ =
         (int)((*(float *)(iVar6 + 0x3c) * fVar9 - (float)this->_padding_) * fVar2 +
              (float)this->_padding_);
    this->_padding_ =
         (int)((*(float *)(iVar6 + 0x40) * fVar9 - (float)this->_padding_) * fVar2 +
              (float)this->_padding_);
    VVar3.x = (float)this->_padding_;
    VVar3.y = (float)this->_padding_;
    VVar3.z = (float)this->_padding_;
    fVar9 = VecLen(VVar3);
    this->_padding_ = (int)fVar9;
    if (fVar9 <= 0.0) {
      fVar9 = 1e+30;
    }
    else {
      fVar9 = 1.0 / fVar9;
    }
    this->_padding_ = (int)fVar9;
    VVar4.x = (float)this->_padding_;
    VVar4.y = (float)this->_padding_;
    VVar4.z = (float)this->_padding_;
    pMVar5 = Spinner(&local_88,local_8,VVar4,param_1);
    pfVar7 = local_48;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar7 = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pfVar7 = pfVar7 + 1;
    }
    pfVar7 = local_48;
    pfVar8 = (float *)(this->_padding_ + 0x20);
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar8 = *pfVar7;
      pfVar7 = pfVar7 + 1;
      pfVar8 = pfVar8 + 1;
    }
  }
  Rocket::Simulate((Rocket *)this,param_1);
  return;
}
