/*
 * Entry: 005311e5
 * Name: MachineGun::Simulate
 * Namespace: MachineGun
 * Signature: void Simulate(MachineGun * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall MachineGun::Simulate(MachineGun *this,float param_1)

{
  _OBJ76 *p_Var1;
  bool bVar2;
  char cVar3;
  _gas_object *p_Var4;
  MAT_3D *pMVar5;
  Ordnance *pOVar6;
  int iVar7;
  MAT_3D *pMVar8;
  float *pfVar9;
  MAT_3D local_e8;
  MAT_3D local_a8;
  GAS_PREP_INFO local_68;
  int local_4c;
  undefined1 local_48 [36];
  undefined4 local_24;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_a8.posit_y;
  this->_padding_ = (int)(param_1 + (float)this->_padding_);
  if ((((char)this->_padding_ == '\0') ||
      ((int)(*(uint *)(this->_padding_ + 0x208) ^ 0x33333333) < *(int *)(this->_padding_ + 0x48)))
     || (bVar2 = Weapon::PermissionToFire((Weapon *)this), !bVar2)) {
    if (0.0 < (float)this->_padding_) {
      this->_padding_ = 0;
    }
    if (this->go != (_gas_object *)0x0) {
      p_Var4 = FindGASObject((char *)0x0,(_OBJ76 *)this->_padding_);
      this->go = p_Var4;
      if (p_Var4 != (_gas_object *)0x0) {
        StopGASEvent(p_Var4);
        this->go = (_gas_object *)0x0;
      }
    }
  }
  else {
    if ((*(char *)(this->_padding_ + 0x58) != '\0') && (this->go == (_gas_object *)0x0)) {
      InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
      local_24 = 0x801;
      InitGASPrep(&local_68);
      local_68.loopMode = 1;
      if ((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) {
        local_68.pri = 0x41;
      }
      p_Var4 = StartGASEvent((char *)(this->_padding_ + 0x58),(_OBJ76 *)this->_padding_,
                             (GAS_CTRL *)(local_48 + 0x14),&local_68);
      this->go = p_Var4;
    }
    pMVar5 = obj_rel_parent_matrix
                       ((MAT_3D *)local_48,(_OBJ76 *)this->_padding_,(_OBJ76 *)this->_padding_);
    pMVar8 = &local_a8;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      pMVar8->right_x = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
    }
    while ((0.0 < (float)this->_padding_ &&
           (cVar3 = (**(code **)(this->_padding_ + 4))(), cVar3 != '\0'))) {
      (**(code **)(*(int *)this->_padding_ + 0x18))(-*(int *)(this->_padding_ + 0x48));
      if (((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) &&
         ((*(int *)(this->_padding_ + 8) == 0x63657467 &&
          (*(int *)(this->_padding_ + 0xc) == 0x6f6e68)))) {
        ColorFade::SetFade(&colorFade,1.0,5.0,(uint)RAVE_COLOR[RAVE_POS].r,
                           (uint)RAVE_COLOR[RAVE_POS].g,(uint)RAVE_COLOR[RAVE_POS].b);
        RAVE_POS = RAVE_POS + 1;
        if (RAVE_POS == 0x1e) {
          RAVE_POS = 0;
        }
      }
      local_4c = this->_padding_ + 0x108;
      pMVar5 = Spinner(&local_e8,(MAT_3D *)(this->_padding_ + 0x20),
                       *(VECTOR_3D *)(this->_padding_ + 300),-(float)this->_padding_);
      pfVar9 = (float *)local_48;
      for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
        *pfVar9 = pMVar5->right_x;
        pMVar5 = (MAT_3D *)&pMVar5->right_y;
        pfVar9 = pfVar9 + 1;
      }
      local_20 = (double)((float)local_20 - *(float *)(local_4c + 0x18) * (float)this->_padding_);
      local_18 = (double)((float)local_18 - *(float *)(local_4c + 0x1c) * (float)this->_padding_);
      local_10 = (double)((float)local_10 - *(float *)(local_4c + 0x20) * (float)this->_padding_);
      pMVar5 = Matrix_Multiply(&local_e8,&local_a8,(MAT_3D *)local_48);
      p_Var1 = (_OBJ76 *)this->_padding_;
      pfVar9 = (float *)local_48;
      for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
        *pfVar9 = pMVar5->right_x;
        pMVar5 = (MAT_3D *)&pMVar5->right_y;
        pfVar9 = pfVar9 + 1;
      }
      pOVar6 = OrdnanceClass::Build((OrdnanceClass *)this->_padding_,(MAT_3D *)local_48,p_Var1);
      pOVar6->dt = (float)this->_padding_ - param_1;
      this->_padding_ = (int)((float)this->_padding_ - *(float *)(this->_padding_ + 0x78));
    }
  }
  *(undefined1 *)&this->_padding_ = 0;
  return;
}
