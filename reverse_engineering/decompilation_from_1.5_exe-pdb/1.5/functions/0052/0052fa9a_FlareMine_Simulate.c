/*
 * Entry: 0052fa9a
 * Name: FlareMine::Simulate
 * Namespace: FlareMine
 * Signature: void Simulate(FlareMine * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FlareMine::Simulate(FlareMine *this,float param_1)

{
  _OBJ76 *p_Var1;
  _gas_object *p_Var2;
  MAT_3D *pMVar3;
  MAT_3D *pMVar4;
  Ordnance *pOVar5;
  int iVar6;
  MAT_3D *pMVar7;
  float fVar8;
  MAT_3D local_b4;
  GAS_PREP_INFO local_74;
  MAT_3D *local_58;
  float local_54;
  float local_50;
  OrdnanceClass *local_4c;
  undefined1 local_48 [36];
  undefined4 local_24;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)((int)&local_b4.posit_z + 4U);
  iVar6 = this->_padding_;
  fVar8 = this->shotTimer + param_1;
  local_4c = *(OrdnanceClass **)(iVar6 + 0x168);
  this->shotTimer = fVar8;
  if (!NAN(fVar8) && 0.0 < fVar8 != (fVar8 == 0.0)) {
    do {
      if ((this->_padding_ == 0) && (*(char *)(iVar6 + 0x16c) != '\0')) {
        InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
        local_24 = 0x801;
        InitGASPrep(&local_74);
        local_74.loopMode = 1;
        p_Var2 = StartGASEvent((char *)(this->_padding_ + 0x16c),(_OBJ76 *)this->_padding_,
                               (GAS_CTRL *)(local_48 + 0x14),&local_74);
        this->_padding_ = (int)p_Var2;
      }
      local_58 = (MAT_3D *)(this->_padding_ + 0x20);
      local_54 = *(float *)(this->_padding_ + 0x184);
      Rand_Counter = Rand_Counter + 1U & 0xff;
      local_50 = Pseudo_Rand_Number[Rand_Counter];
      fVar8 = RandFloat(3.1415927);
      pMVar3 = Build_Pitch_Yaw_Matrix((MAT_3D *)local_48,local_50 * local_54 - 1.5707964,fVar8);
      pMVar4 = local_58;
      pMVar7 = &local_b4;
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        pMVar7->right_x = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
      }
      pMVar4 = Matrix_Multiply((MAT_3D *)local_48,&local_b4,pMVar4);
      p_Var1 = (_OBJ76 *)this->_padding_;
      pMVar3 = &local_b4;
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        pMVar3->right_x = pMVar4->right_x;
        pMVar4 = (MAT_3D *)&pMVar4->right_y;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
      }
      pOVar5 = OrdnanceClass::Build(local_4c,&local_b4,p_Var1);
      pOVar5->bSend = 0;
      pOVar5->dt = this->shotTimer - param_1;
      iVar6 = this->_padding_;
      this->shotTimer = this->shotTimer - *(float *)(iVar6 + 0x180);
      fVar8 = this->shotTimer;
    } while (!NAN(fVar8) && 0.0 < fVar8 != (fVar8 == 0.0));
  }
  Mine::Simulate((Mine *)this,param_1);
  return;
}
