/*
 * Entry: 0053b465
 * Name: TargetingGun::Simulate
 * Namespace: TargetingGun
 * Signature: void Simulate(TargetingGun * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall TargetingGun::Simulate(TargetingGun *this,float param_1)

{
  float fVar1;
  _OBJ76 *p_Var2;
  EULER *pEVar3;
  bool bVar4;
  MAT_3D *pMVar5;
  _gas_object *p_Var6;
  Missile *this_00;
  LeaderRound *pLVar7;
  int iVar8;
  MAT_3D *pMVar9;
  MAT_3D local_e8;
  MAT_3D local_a8;
  GAS_PREP_INFO local_68;
  EULER *local_4c;
  undefined1 local_48 [36];
  undefined4 local_24;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_a8.posit_y;
  this->shotTimer = param_1 + this->shotTimer;
  if ((this->salvoCount < 1) || (bVar4 = Weapon::PermissionToFire((Weapon *)this), !bVar4)) {
    if ((this->triggered == false) || (bVar4 = Weapon::PermissionToFire((Weapon *)this), !bVar4)) {
      p_Var6 = this->go;
      if (p_Var6 != (_gas_object *)0x0) {
        StopGASEvent(p_Var6);
        this->go = (_gas_object *)0x0;
      }
    }
    else {
      p_Var6 = this->go;
      if (p_Var6 != (_gas_object *)0x0) {
        StopGASEvent(p_Var6);
        this->go = (_gas_object *)0x0;
      }
      if (((this->leaderObj == (LeaderRound *)0x0) && (0.0 < this->shotTimer)) &&
         (this->leaderClass->ammoCost <= (int)(this->carrier->curAmmo ^ 0x33333333U))) {
        if (*(char *)(this->_padding_ + 0x78) != '\0') {
          InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
          local_24 = 0x800;
          InitGASPrep(&local_68);
          if ((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) {
            local_68.pri = 0x41;
          }
          StartGASEvent((char *)(this->_padding_ + 0x78),(_OBJ76 *)this->_padding_,
                        (GAS_CTRL *)(local_48 + 0x14),&local_68);
        }
        (**(code **)(this->carrier->_padding_ + 0x18))(-this->leaderClass->ammoCost);
        pMVar5 = Matrix_Multiply(&local_a8,(MAT_3D *)(this->_padding_ + 0x20),
                                 (MAT_3D *)&this->_padding_);
        p_Var2 = (_OBJ76 *)this->_padding_;
        pMVar9 = &local_e8;
        for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
          pMVar9->right_x = pMVar5->right_x;
          pMVar5 = (MAT_3D *)&pMVar5->right_y;
          pMVar9 = (MAT_3D *)&pMVar9->right_y;
        }
        pLVar7 = (LeaderRound *)OrdnanceClass::Build(this->leaderClass,&local_e8,p_Var2);
        this->leaderObj = pLVar7;
        pLVar7->launcherObj = this;
        this->leaderObj->_padding_ = (int)(this->shotTimer - param_1);
        this->shotTimer = this->shotTimer - *(float *)(this->_padding_ + 0x8c);
      }
    }
    this->triggered = false;
  }
  else {
    pMVar5 = obj_rel_parent_matrix(&local_a8,(_OBJ76 *)this->_padding_,(_OBJ76 *)this->_padding_);
    pMVar9 = &local_e8;
    for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
      pMVar9->right_x = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
    }
    while( true ) {
      if ((this->salvoCount < 1) || (this->shotTimer <= 0.0)) goto LAB_0053b65a;
      if ((int)(this->carrier->curAmmo ^ 0x33333333U) < *(int *)(this->_padding_ + 0x48)) break;
      if ((*(char *)(this->_padding_ + 0x58) != '\0') && (this->go == (_gas_object *)0x0)) {
        InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
        local_24 = 0x801;
        InitGASPrep(&local_68);
        local_68.loopMode = 1;
        if ((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) {
          local_68.pri = 0x41;
        }
        p_Var6 = StartGASEvent((char *)(this->_padding_ + 0x58),(_OBJ76 *)this->_padding_,
                               (GAS_CTRL *)(local_48 + 0x14),&local_68);
        this->go = p_Var6;
      }
      (**(code **)(this->carrier->_padding_ + 0x18))(-*(int *)(this->_padding_ + 0x48));
      local_4c = &this->carrier->euler;
      pMVar5 = Spinner((MAT_3D *)local_48,(MAT_3D *)(this->_padding_ + 0x20),
                       (this->carrier->euler).omega,-this->shotTimer);
      pEVar3 = local_4c;
      pMVar9 = &local_a8;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        pMVar9->right_x = pMVar5->right_x;
        pMVar5 = (MAT_3D *)&pMVar5->right_y;
        pMVar9 = (MAT_3D *)&pMVar9->right_y;
      }
      local_a8.posit_x = (double)((float)local_a8.posit_x - (pEVar3->v).x * this->shotTimer);
      local_a8.posit_y = (double)((float)local_a8.posit_y - (pEVar3->v).y * this->shotTimer);
      local_a8.posit_z = (double)((float)local_a8.posit_z - (pEVar3->v).z * this->shotTimer);
      pMVar5 = Matrix_Multiply((MAT_3D *)local_48,&local_e8,&local_a8);
      p_Var2 = (_OBJ76 *)this->_padding_;
      pMVar9 = &local_a8;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        pMVar9->right_x = pMVar5->right_x;
        pMVar5 = (MAT_3D *)&pMVar5->right_y;
        pMVar9 = (MAT_3D *)&pMVar9->right_y;
      }
      this_00 = (Missile *)OrdnanceClass::Build((OrdnanceClass *)this->_padding_,&local_a8,p_Var2);
      Missile::SetTarget(this_00,this->lockTarget);
      this_00->_padding_ = (int)(this->shotTimer - param_1);
      fVar1 = *(float *)(this->_padding_ + 0x94);
      this->salvoCount = this->salvoCount + -1;
      this->shotTimer = this->shotTimer - fVar1;
    }
    this->salvoCount = 0;
LAB_0053b65a:
    if (this->salvoCount == 0) {
      this->shotTimer = this->shotTimer - *(float *)(this->_padding_ + 0x8c);
    }
  }
  if (0.0 < this->shotTimer) {
    this->shotTimer = 0.0;
  }
  return;
}
