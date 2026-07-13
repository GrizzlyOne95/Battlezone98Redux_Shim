/*
 * Entry: 0049a5ba
 * Name: Geizer::Simulate
 * Namespace: Geizer
 * Signature: void Simulate(Geizer * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Geizer::Simulate(Geizer *this,float param_1)

{
  int iVar1;
  float fVar2;
  uint uVar3;
  VECTOR_3D *pVVar4;
  ushort uVar5;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  if (this->isSteamOn != false) {
    iVar1 = this->_padding_;
    fVar2 = param_1 + this->smokeTimer;
    this->smokeTimer = fVar2;
    local_1c.x = (float)*(double *)(iVar1 + 0x48);
    local_1c.y = (float)*(double *)(iVar1 + 0x50);
    local_1c.z = (float)*(double *)(iVar1 + 0x58);
    uVar5 = (ushort)(0.0 < fVar2) << 8 | (ushort)NAN(fVar2) << 10;
    while ((POPCOUNT((char)(uVar5 >> 8)) & 1U) != 0) {
      uVar3 = Rand_Counter + 1U & 0xff;
      Rand_Counter = uVar3 + 1 & 0xff;
      local_10.x = Pseudo_Rand_Number[uVar3] * 2.0;
      local_10.y = 12.0;
      local_10.z = Pseudo_Rand_Number[Rand_Counter] * 2.0;
      pVVar4 = Vector_Rotate(&local_28,&local_10,(MAT_3D *)(this->_padding_ + 0x20));
      local_10.x = pVVar4->x;
      local_10.y = pVVar4->y;
      local_10.z = pVVar4->z;
      SmokeEffect::AddSmoke(&smokeEffect,this->smokeEmitter,&local_1c,&local_10,this->smokeTimer);
      this->smokeTimer = this->smokeTimer - 0.1;
      uVar5 = (ushort)(0.0 < this->smokeTimer) << 8 | (ushort)NAN(this->smokeTimer) << 10;
    }
  }
  return;
}
