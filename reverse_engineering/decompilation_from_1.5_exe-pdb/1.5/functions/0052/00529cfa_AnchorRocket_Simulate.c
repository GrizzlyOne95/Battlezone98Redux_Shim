/*
 * Entry: 00529cfa
 * Name: AnchorRocket::Simulate
 * Namespace: AnchorRocket
 * Signature: void Simulate(AnchorRocket * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnchorRocket::Simulate(AnchorRocket *this,float param_1)

{
  float fVar1;
  VECTOR_3D VVar2;
  MAT_3D *pMVar3;
  VECTOR_3D *pVVar4;
  VECTOR_3D *pVVar5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  float fVar9;
  MAT_3D local_94;
  float local_54 [16];
  VECTOR_3D local_14;
  GameObject *local_8;
  
  if (this->hitObj == 0) {
    Rocket::Simulate((Rocket *)this,param_1);
  }
  else {
    local_8 = GameObject::GetObj(this->hitObj);
    if (local_8 == (GameObject *)0x0) {
      iVar6 = this->_padding_;
    }
    else {
      pMVar3 = Matrix_Multiply(&local_94,&this->offset,&local_8->obj->transform);
      pfVar7 = local_54;
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *pfVar7 = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pfVar7 = pfVar7 + 1;
      }
      pfVar7 = local_54;
      pfVar8 = (float *)(this->_padding_ + 0x20);
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *pfVar8 = *pfVar7;
        pfVar7 = pfVar7 + 1;
        pfVar8 = pfVar8 + 1;
      }
      pVVar5 = &(local_8->euler).v;
      fVar1 = (local_8->euler).v_mag;
      fVar9 = *(float *)(this->_padding_ + 0xb0) * param_1;
      if (fVar1 <= fVar9) {
        pVVar4 = &local_14;
        local_14.x = 0.0;
        local_14.y = 0.0;
        local_14.z = 0.0;
      }
      else {
        pVVar4 = ScaleVector(&local_14,1.0 - fVar9 / fVar1,*pVVar5);
        pVVar5 = &(local_8->euler).v;
      }
      pVVar5->x = pVVar4->x;
      pVVar5->y = pVVar4->y;
      pVVar5->z = pVVar4->z;
      local_8 = (GameObject *)&(local_8->euler).omega;
      fVar9 = VecLen(*(VECTOR_3D *)local_8);
      fVar1 = *(float *)(this->_padding_ + 0xb4) * param_1;
      if (fVar9 <= fVar1) {
        pVVar5 = &local_14;
        local_14.x = 0.0;
        local_14.y = 0.0;
        local_14.z = 0.0;
      }
      else {
        VVar2.x = (float)local_8->_padding_;
        VVar2.y = (float)local_8->_padding_;
        VVar2.z = (float)local_8->_padding_;
        pVVar5 = ScaleVector(&local_14,1.0 - fVar1 / fVar9,VVar2);
      }
      local_8->_padding_ = (int)pVVar5->x;
      local_8->_padding_ = (int)pVVar5->y;
      local_8->_padding_ = (int)pVVar5->z;
      fVar1 = (float)this->_padding_ - param_1;
      this->_padding_ = (int)fVar1;
      iVar6 = this->_padding_;
      if (fVar1 < 0.0 == (fVar1 == 0.0)) {
        *(uint *)(iVar6 + 0x14) = *(uint *)(iVar6 + 0x14) & 0xfffffdff;
        return;
      }
    }
    *(uint *)(iVar6 + 0x14) = *(uint *)(iVar6 + 0x14) | 0x200;
  }
  return;
}
