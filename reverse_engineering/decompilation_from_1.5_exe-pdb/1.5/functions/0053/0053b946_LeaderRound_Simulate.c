/*
 * Entry: 0053b946
 * Name: LeaderRound::Simulate
 * Namespace: LeaderRound
 * Signature: void Simulate(LeaderRound * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LeaderRound::Simulate(LeaderRound *this,float param_1)

{
  uint *puVar1;
  float fVar2;
  GameObject *pGVar3;
  MAT_3D *pMVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  MAT_3D local_84;
  float local_44 [16];
  
  if (this->hitObj == 0) {
    Rocket::Simulate((Rocket *)this,param_1);
  }
  else {
    pGVar3 = GameObject::GetObj(this->hitObj);
    if ((pGVar3 == (GameObject *)0x0) ||
       (fVar2 = (float)this->_padding_ - param_1, this->_padding_ = (int)fVar2, fVar2 <= 0.0)) {
      puVar1 = (uint *)(this->_padding_ + 0x14);
      *puVar1 = *puVar1 | 0x200;
    }
    else {
      pMVar4 = Matrix_Multiply(&local_84,&this->offset,&pGVar3->obj->transform);
      pfVar6 = local_44;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *pfVar6 = pMVar4->right_x;
        pMVar4 = (MAT_3D *)&pMVar4->right_y;
        pfVar6 = pfVar6 + 1;
      }
      pfVar6 = local_44;
      pfVar7 = (float *)(this->_padding_ + 0x20);
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *pfVar7 = *pfVar6;
        pfVar6 = pfVar6 + 1;
        pfVar7 = pfVar7 + 1;
      }
    }
  }
  return;
}
