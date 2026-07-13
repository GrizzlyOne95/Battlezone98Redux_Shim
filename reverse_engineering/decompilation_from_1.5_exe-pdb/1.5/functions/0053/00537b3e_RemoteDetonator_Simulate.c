/*
 * Entry: 00537b3e
 * Name: RemoteDetonator::Simulate
 * Namespace: RemoteDetonator
 * Signature: void Simulate(RemoteDetonator * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall RemoteDetonator::Simulate(RemoteDetonator *this,float param_1)

{
  _OBJ76 *p_Var1;
  bool bVar2;
  Ordnance **ppOVar3;
  Ordnance **ppOVar4;
  MAT_3D *pMVar5;
  Ordnance *pOVar6;
  uint uVar7;
  int iVar8;
  MAT_3D *pMVar9;
  MAT_3D local_a8;
  GAS_PREP_INFO local_68;
  uint local_4c;
  undefined1 local_48 [36];
  undefined4 local_24;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  ppOVar4 = this->ordnance;
  this->_padding_ = (int)(param_1 + (float)this->_padding_);
  uVar7 = 0;
  iVar8 = 4;
  ppOVar3 = ppOVar4;
  do {
    if (*ppOVar3 != (Ordnance *)0x0) {
      if (((*ppOVar3)->obj->flags >> 9 & 1) == 0) {
        uVar7 = uVar7 + 1;
      }
      else {
        *ppOVar3 = (Ordnance *)0x0;
      }
    }
    ppOVar3 = ppOVar3 + 1;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  if (((*(byte *)(this->_padding_ + 0x14) & 0x10) == 0) || (command_controls.cmd_multi == '\0')) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if ((this->armed == false) || (bVar2)) {
    this->_padding_ = *(int *)(this->_padding_ + 0x68);
    if ((char)this->_padding_ == '\0') {
      if (0 < (int)uVar7) {
        this->armed = true;
      }
    }
    else if ((((uVar7 < (!bVar2 - 1 & 3) + 1) &&
              (*(int *)(this->_padding_ + 0x48) <=
               (int)(*(uint *)(this->_padding_ + 0x208) ^ 0x33333333))) &&
             (0.0 < (float)this->_padding_)) &&
            (bVar2 = Weapon::PermissionToFire((Weapon *)this), bVar2)) {
      local_4c = 0;
      do {
        if (*ppOVar4 == (Ordnance *)0x0) {
          if (*(char *)(this->_padding_ + 0x58) != '\0') {
            InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
            local_24 = 0x800;
            InitGASPrep(&local_68);
            if ((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) {
              local_68.pri = 0x41;
            }
            StartGASEvent((char *)(this->_padding_ + 0x58),(_OBJ76 *)this->_padding_,
                          (GAS_CTRL *)(local_48 + 0x14),&local_68);
          }
          (**(code **)(*(int *)this->_padding_ + 0x18))(-*(int *)(this->_padding_ + 0x48));
          pMVar5 = Matrix_Multiply((MAT_3D *)local_48,(MAT_3D *)(this->_padding_ + 0x20),
                                   (MAT_3D *)&this->_padding_);
          p_Var1 = (_OBJ76 *)this->_padding_;
          pMVar9 = &local_a8;
          for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
            pMVar9->right_x = pMVar5->right_x;
            pMVar5 = (MAT_3D *)&pMVar5->right_y;
            pMVar9 = (MAT_3D *)&pMVar9->right_y;
          }
          pOVar6 = OrdnanceClass::Build((OrdnanceClass *)this->_padding_,&local_a8,p_Var1);
          this->ordnance[local_4c] = pOVar6;
          pOVar6->dt = (float)this->_padding_ - param_1;
          this->_padding_ = (int)((float)this->_padding_ - *(float *)(this->_padding_ + 0x78));
          break;
        }
        local_4c = local_4c + 1;
        ppOVar4 = ppOVar4 + 1;
      } while (local_4c < 4);
    }
  }
  else {
    this->_padding_ = *(int *)(this->_padding_ + 0x80);
    if ((char)this->_padding_ == '\0') {
      if (uVar7 == 0) {
        this->armed = false;
      }
    }
    else {
      Detonate(this);
    }
  }
  if (0.0 < (float)this->_padding_) {
    this->_padding_ = 0;
  }
  *(undefined1 *)&this->_padding_ = 0;
  return;
}
