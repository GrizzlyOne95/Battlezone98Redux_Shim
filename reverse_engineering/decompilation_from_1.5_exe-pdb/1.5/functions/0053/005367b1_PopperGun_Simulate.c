/*
 * Entry: 005367b1
 * Name: PopperGun::Simulate
 * Namespace: PopperGun
 * Signature: void Simulate(PopperGun * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PopperGun::Simulate(PopperGun *this,float param_1)

{
  _OBJ76 *p_Var1;
  float fVar2;
  MAT_3D *pMVar3;
  Ordnance *pOVar4;
  int iVar5;
  int iVar6;
  MAT_3D *pMVar7;
  MAT_3D local_e4;
  MAT_3D local_a4;
  GAS_PREP_INFO local_64;
  undefined1 local_48 [36];
  undefined4 local_24;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)((int)&local_a4.posit_x + 4U);
  fVar2 = param_1 + this->shotTimer;
  this->shotTimer = fVar2;
  if (this->triggered == false) {
    if (0.0 < fVar2) {
      this->shotTimer = 0.0;
    }
  }
  else {
    if (0.0 < fVar2) {
      if (*(int *)(this->_padding_ + 0x48) <= (int)(this->carrier->curAmmo ^ 0x33333333U)) {
        if (*(char *)(this->_padding_ + 0x58) != '\0') {
          InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
          local_24 = 0x800;
          InitGASPrep(&local_64);
          if ((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) {
            local_64.pri = 0x41;
          }
          StartGASEvent((char *)(this->_padding_ + 0x58),(_OBJ76 *)this->_padding_,
                        (GAS_CTRL *)(local_48 + 0x14),&local_64);
        }
        (**(code **)(this->carrier->_padding_ + 0x18))(-*(int *)(this->_padding_ + 0x48));
        pMVar3 = Matrix_Multiply((MAT_3D *)local_48,(MAT_3D *)(this->_padding_ + 0x20),
                                 (MAT_3D *)&this->_padding_);
        iVar6 = this->_padding_;
        pMVar7 = &local_a4;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          pMVar7->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
        }
        pMVar3 = Build_Pitch_Matrix((MAT_3D *)local_48,-*(float *)(iVar6 + 0x7c));
        pMVar7 = &local_e4;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          pMVar7->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
        }
        pMVar3 = Matrix_Multiply((MAT_3D *)local_48,&local_e4,&local_a4);
        p_Var1 = (_OBJ76 *)this->_padding_;
        pMVar7 = &local_a4;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          pMVar7->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
        }
        pOVar4 = OrdnanceClass::Build((OrdnanceClass *)this->_padding_,&local_a4,p_Var1);
        pOVar4->dt = this->shotTimer - param_1;
      }
      this->shotTimer = this->shotTimer - *(float *)(this->_padding_ + 0x78);
    }
    this->triggered = false;
  }
  return;
}
