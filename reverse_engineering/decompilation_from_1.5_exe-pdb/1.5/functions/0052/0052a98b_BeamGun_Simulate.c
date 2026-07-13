/*
 * Entry: 0052a98b
 * Name: BeamGun::Simulate
 * Namespace: BeamGun
 * Signature: void Simulate(BeamGun * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall BeamGun::Simulate(BeamGun *this,float param_1)

{
  Carrier *this_00;
  float fVar1;
  bool bVar2;
  _gas_object *p_Var3;
  MAT_3D *pMVar4;
  Ordnance *pOVar5;
  BeamGun *pBVar6;
  int iVar7;
  MAT_3D *pMVar8;
  int iVar9;
  MAT_3D local_b4;
  GAS_PREP_INFO local_74;
  uint local_58;
  float local_54;
  undefined8 local_50;
  undefined1 local_48 [36];
  undefined4 local_24;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if ((this->triggered == false) ||
     (((*(int *)(this->_padding_ + 0x48) != 0 && ((int)(this->carrier->curAmmo ^ 0x33333333U) < 1))
      || (bVar2 = Weapon::PermissionToFire((Weapon *)this), !bVar2)))) {
    if (this->go != (_gas_object *)0x0) {
      p_Var3 = FindGASObject((char *)0x0,(_OBJ76 *)this->_padding_);
      this->go = p_Var3;
      if (p_Var3 != (_gas_object *)0x0) {
        StopGASEvent(p_Var3);
        this->go = (_gas_object *)0x0;
      }
    }
    pOVar5 = this->ordnance;
    if (pOVar5 != (Ordnance *)0x0) {
      if (pOVar5->ordnanceClass->sig == 0x4245414d) {
        pOVar5[1].euler.v_mag = -NAN;
      }
      this->ordnance = (Ordnance *)0x0;
    }
  }
  else {
    iVar9 = *(int *)(this->_padding_ + 0x48);
    local_54 = param_1;
    local_50 = (double)CONCAT44(iVar9,(int)local_50);
    if (0 < iVar9) {
      local_58 = this->carrier->curAmmo ^ 0x33333333;
      if ((float)(int)local_58 / (float)iVar9 < param_1) {
        local_54 = (float)(int)local_58 / (float)iVar9;
      }
    }
    if ((*(char *)(this->_padding_ + 0x58) != '\0') && (this->go == (_gas_object *)0x0)) {
      InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
      local_24 = 0x801;
      InitGASPrep(&local_74);
      local_74.loopMode = 1;
      if ((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) {
        local_74.pri = 0x41;
      }
      p_Var3 = StartGASEvent((char *)(this->_padding_ + 0x58),(_OBJ76 *)this->_padding_,
                             (GAS_CTRL *)(local_48 + 0x14),&local_74);
      this->go = p_Var3;
    }
    pMVar4 = Matrix_Multiply((MAT_3D *)local_48,(MAT_3D *)(this->_padding_ + 0x20),
                             (MAT_3D *)&this->_padding_);
    iVar9 = this->_padding_;
    pMVar8 = &local_b4;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      pMVar8->right_x = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
    }
    fVar1 = (float)*(int *)(iVar9 + 0x48) * param_1 + this->fraction;
    local_50 = (double)((float)Float2Int + fVar1);
    this->fraction = fVar1 - (float)(int)local_50;
    (**(code **)(this->carrier->_padding_ + 0x18))(-(int)local_50);
    bVar2 = DistributedObject::IsRemote((DistributedObject *)&this->carrier->_padding_);
    if ((!bVar2) &&
       ((this->ordnance == (Ordnance *)0x0 || ((this->ordnance->obj->flags & 0x200) != 0)))) {
      pOVar5 = OrdnanceClass::Build
                         ((OrdnanceClass *)this->_padding_,&local_b4,(_OBJ76 *)this->_padding_);
      this->ordnance = pOVar5;
      local_50 = (double)CONCAT44(pOVar5,(int)local_50);
      if (pOVar5->ordnanceClass->sig == 0x4245414d) {
        this_00 = this->carrier->carrier;
        iVar9 = 0;
        do {
          if ((this_00 != (Carrier *)0x0) &&
             (pBVar6 = (BeamGun *)Carrier::GetWeapon(this_00,iVar9), pBVar6 == this)) {
            *(int *)(local_50._4_4_ + 0xfc) = iVar9;
            break;
          }
          iVar9 = iVar9 + 1;
        } while (iVar9 < 5);
      }
      this->ordnance->dt = local_54 - param_1;
    }
  }
  if ((this->carrier == (GameObject *)0x0) ||
     (bVar2 = DistributedObject::IsRemote((DistributedObject *)&this->carrier->_padding_), !bVar2))
  {
    this->triggered = false;
  }
  return;
}
