/*
 * Entry: 00537eaf
 * Name: Rocket::Simulate
 * Namespace: Rocket
 * Signature: void Simulate(Rocket * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Rocket::Simulate(Rocket *this,float param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  VECTOR_3D VVar5;
  MAT_3D *pMVar6;
  uint uVar7;
  int iVar8;
  float unaff_EDI;
  float *pfVar9;
  ushort uVar10;
  MAT_3D local_a0;
  float local_60 [4];
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  double local_38;
  double local_30;
  double local_28;
  VECTOR_3D local_20;
  VECTOR_3D local_14;
  float local_8;
  
  Bullet::Simulate((Bullet *)this,param_1);
  iVar8 = this->_padding_;
  if ((*(byte *)(iVar8 + 0x14) & 8) != 0) {
    if (0 < *(int *)(this->_padding_ + 0x7c)) {
      local_20.x = (float)*(double *)(iVar8 + 0x48);
      local_20.y = (float)*(double *)(iVar8 + 0x50);
      local_20.z = (float)*(double *)(iVar8 + 0x58);
      local_14.x = local_20.x;
      local_14.y = local_20.y;
      local_14.z = local_20.z;
      SubmitMissileLight((CAMERA *)&local_20,(VECTOR_3D *)0x41200000,unaff_EDI);
    }
    if ((float)this->_padding_ < param_1) {
      param_1 = (float)this->_padding_;
    }
    if (this->smokeEmitter != (SmokeEmitter *)0x0) {
      local_8 = *(float *)(this->_padding_ + 0x74);
      fVar1 = this->smokeTimer + param_1;
      this->smokeTimer = fVar1;
      uVar10 = (ushort)(0.0 < fVar1) << 8 | (ushort)NAN(fVar1) << 10;
      while ((POPCOUNT((char)(uVar10 >> 8)) & 1U) != 0) {
        VVar5.x = (float)this->_padding_;
        VVar5.y = (float)this->_padding_;
        VVar5.z = (float)this->_padding_;
        pMVar6 = Spinner(&local_a0,(MAT_3D *)(this->_padding_ + 0x20),VVar5,-this->smokeTimer);
        fVar1 = this->smokeTimer;
        fVar2 = (float)this->_padding_;
        pfVar9 = local_60;
        for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
          *pfVar9 = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pfVar9 = pfVar9 + 1;
        }
        local_20.x = (float)local_38 - fVar1 * fVar2;
        local_38 = (double)local_20.x;
        local_20.y = (float)local_30 - this->smokeTimer * (float)this->_padding_;
        local_30 = (double)local_20.y;
        local_20.z = (float)local_28 - this->smokeTimer * (float)this->_padding_;
        local_28 = (double)local_20.z;
        local_20.x = local_20.x - local_48 * local_8;
        local_20.y = local_20.y - local_44 * local_8;
        local_20.z = local_20.z - local_40 * local_8;
        fVar1 = *(float *)(this->_padding_ + 0x94);
        uVar7 = Rand_Counter + 1U & 0xff;
        fVar3 = Pseudo_Rand_Number[uVar7] * *(float *)(this->_padding_ + 0x8c);
        uVar7 = uVar7 + 1 & 0xff;
        fVar2 = Pseudo_Rand_Number[uVar7] * *(float *)(this->_padding_ + 0x8c);
        Rand_Counter = uVar7 + 1 & 0xff;
        fVar4 = Pseudo_Rand_Number[Rand_Counter] * *(float *)(this->_padding_ + 0x90);
        local_14.x = fVar1 * (float)this->_padding_ +
                     fVar4 * local_48 + local_60[0] * fVar3 + local_60[3] * fVar2;
        local_14.y = fVar4 * local_44 +
                     local_60[1] * fVar3 + local_50 * fVar2 + (float)this->_padding_ * fVar1;
        local_14.z = fVar1 * (float)this->_padding_ +
                     fVar4 * local_40 + local_4c * fVar2 + local_60[2] * fVar3;
        SmokeEffect::AddSmoke(&smokeEffect,this->smokeEmitter,&local_20,&local_14,this->smokeTimer);
        this->smokeTimer = this->smokeTimer - *(float *)(this->_padding_ + 0x9c);
        uVar10 = (ushort)(0.0 < this->smokeTimer) << 8 | (ushort)NAN(this->smokeTimer) << 10;
      }
    }
  }
  return;
}
