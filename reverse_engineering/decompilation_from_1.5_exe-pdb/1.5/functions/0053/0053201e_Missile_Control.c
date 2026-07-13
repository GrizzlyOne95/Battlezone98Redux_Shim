/*
 * Entry: 0053201e
 * Name: Missile::Control
 * Namespace: Missile
 * Signature: void Control(Missile * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Missile::Control(Missile *this,float param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  VECTOR_3D *pVVar5;
  double dVar6;
  VECTOR_3D local_24;
  VECTOR_3D local_18;
  float local_c;
  float local_8;
  
  if ((*(byte *)(this->_padding_ + 0x14) & 8) != 0) {
    iVar3 = (**(code **)(this->_padding_ + 0x24))();
    if (iVar3 == 0) {
      this->_padding_ = 0;
      this->_padding_ = 0;
    }
    else {
      pfVar4 = (float *)(**(code **)(*(int *)(iVar3 + 0x20) + 0xc))();
      iVar3 = this->_padding_;
      local_18.x = *pfVar4 - (float)*(double *)(iVar3 + 0x48);
      local_18.y = pfVar4[1] - (float)*(double *)(iVar3 + 0x50);
      local_18.z = pfVar4[2] - (float)*(double *)(iVar3 + 0x58);
      pVVar5 = Normalize_Vector(&local_24,&local_18);
      iVar3 = this->_padding_;
      local_18.x = pVVar5->x;
      local_18.y = pVVar5->y;
      local_18.z = pVVar5->z;
      local_8 = (*(float *)(iVar3 + 0x20) * local_18.x +
                *(float *)(iVar3 + 0x24) * local_18.y + *(float *)(iVar3 + 0x28) * local_18.z) *
                (1.0 / param_1);
      local_c = (*(float *)(iVar3 + 0x2c) * local_18.x +
                *(float *)(iVar3 + 0x30) * local_18.y + *(float *)(iVar3 + 0x34) * local_18.z) *
                (1.0 / param_1);
      fVar2 = local_8 * local_8 + local_c * local_c;
      fVar1 = *(float *)(this->_padding_ + 0xb0);
      if (fVar1 * fVar1 < fVar2) {
        dVar6 = rsqrt((double)fVar2);
        local_8 = local_8 * (float)dVar6 * fVar1;
        local_c = (float)dVar6 * fVar1 * local_c;
      }
      this->_padding_ = (int)local_c;
      this->_padding_ = (int)-local_8;
    }
    this->_padding_ = 0;
  }
  return;
}
