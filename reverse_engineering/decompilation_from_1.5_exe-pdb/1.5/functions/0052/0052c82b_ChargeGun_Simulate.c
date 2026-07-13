/*
 * Entry: 0052c82b
 * Name: ChargeGun::Simulate
 * Namespace: ChargeGun
 * Signature: void Simulate(ChargeGun * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall ChargeGun::Simulate(ChargeGun *this,float param_1)

{
  ulong *puVar1;
  float fVar2;
  _OBJ76 *p_Var3;
  OrdnanceData *pOVar4;
  OrdnanceData *pOVar5;
  bool bVar6;
  MAT_3D *pMVar7;
  Ordnance *pOVar8;
  char *pcVar9;
  _gas_object *p_Var10;
  OrdnanceClass *pOVar11;
  int iVar12;
  MAT_3D *pMVar13;
  float *pfVar14;
  MAT_3D local_ec;
  MAT_3D local_ac;
  GAS_PREP_INFO local_6c;
  long local_50;
  int iStack_4c;
  undefined1 local_48 [36];
  undefined4 local_24;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)((int)&local_ac.posit_y + 4U);
  if ((this->salvoCount < 1) || (bVar6 = Weapon::PermissionToFire((Weapon *)this), !bVar6)) {
    if ((char)this->_padding_ != '\0') {
      pOVar4 = this->chargeLevel;
      pOVar5 = this->fullLevel;
      if (pOVar4 < pOVar5) {
        pOVar11 = pOVar4[1].ordnanceClass;
        if ((pOVar11 == (OrdnanceClass *)0x0) ||
           (pOVar11->ammoCost <= (int)(*(uint *)(this->_padding_ + 0x208) ^ 0x33333333))) {
          this->_padding_ = (int)((float)this->_padding_ + param_1);
        }
        fVar2 = pOVar4[1].shotDelay;
        if (fVar2 < (float)this->_padding_ != (fVar2 == (float)this->_padding_)) {
          this->_padding_ = (int)pOVar11;
          this->chargeLevel = pOVar4 + 1;
        }
      }
      else if (pOVar5->shotDelay < (float)this->_padding_) {
        this->_padding_ = (int)pOVar5->shotDelay;
      }
      pcVar9 = (char *)(this->_padding_ + 0x58);
      if (*pcVar9 != '\0') {
        if (this->go == (_gas_object *)0x0) {
          InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
          local_24 = 0x2001;
          InitGASPrep(&local_6c);
          local_6c.loopMode = 1;
          if ((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) {
            local_6c.pri = 0x41;
          }
          p_Var10 = StartGASEvent((char *)(this->_padding_ + 0x58),(_OBJ76 *)this->_padding_,
                                  (GAS_CTRL *)(local_48 + 0x14),&local_6c);
        }
        else {
          p_Var10 = FindGASObject(pcVar9,(_OBJ76 *)this->_padding_);
        }
        this->go = p_Var10;
        if (p_Var10 != (_gas_object *)0x0) {
          local_50 = SUB84((double)(*(float *)(this->_padding_ + 0x84) * (float)this->_padding_ +
                                    *(float *)(this->_padding_ + 0x80) + (float)Float2Int),0);
          (p_Var10->gpi).sampleRate = local_50;
          local_50 = SUB84((double)(*(float *)(this->_padding_ + 0x8c) * (float)this->_padding_ +
                                    *(float *)(this->_padding_ + 0x88) + (float)Float2Int),0);
          (this->go->gpi).volume = local_50;
          puVar1 = &(this->go->gc).flags;
          *puVar1 = *puVar1 | 0x60;
        }
      }
      *(undefined1 *)&this->_padding_ = 0;
      goto LAB_0052cc02;
    }
    if ((float)this->_padding_ <= 0.0) goto LAB_0052cc02;
    if (this->go != (_gas_object *)0x0) {
      p_Var10 = FindGASObject((char *)(this->_padding_ + 0x58),(_OBJ76 *)this->_padding_);
      this->go = p_Var10;
      if (p_Var10 != (_gas_object *)0x0) {
        StopGASEvent(p_Var10);
        this->go = (_gas_object *)0x0;
      }
    }
    this->_padding_ = 0;
    iVar12 = this->chargeLevel->salvoCount;
    this->salvoCount = iVar12;
    if (0 < iVar12) {
      *(undefined1 *)&this->_padding_ = 1;
      goto LAB_0052cc02;
    }
    this->chargeLevel = this->emptyLevel;
    pOVar11 = this->emptyLevel->ordnanceClass;
  }
  else {
    if (((char)this->_padding_ != '\0') &&
       (*(undefined1 *)&this->_padding_ = 0, this->chargeLevel->fireSound[0] != '\0')) {
      InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
      local_24 = 0x800;
      InitGASPrep(&local_6c);
      if ((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) {
        local_6c.pri = 0x41;
      }
      StartGASEvent(this->chargeLevel->fireSound,(_OBJ76 *)this->_padding_,
                    (GAS_CTRL *)(local_48 + 0x14),&local_6c);
    }
    this->_padding_ = (int)((float)this->_padding_ + param_1);
    pMVar7 = obj_rel_parent_matrix
                       ((MAT_3D *)local_48,(_OBJ76 *)this->_padding_,(_OBJ76 *)this->_padding_);
    pMVar13 = &local_ac;
    for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
      pMVar13->right_x = pMVar7->right_x;
      pMVar7 = (MAT_3D *)&pMVar7->right_y;
      pMVar13 = (MAT_3D *)&pMVar13->right_y;
    }
    while( true ) {
      if ((this->salvoCount < 1) || ((float)this->_padding_ <= 0.0)) goto LAB_0052ca0f;
      iVar12 = this->_padding_;
      if ((int)(((int *)this->_padding_)[0x82] ^ 0x33333333U) < *(int *)(iVar12 + 0x48)) break;
      if (iVar12 != 0) {
        (**(code **)(*(int *)this->_padding_ + 0x18))(-*(int *)(iVar12 + 0x48));
        _local_50 = CONCAT44(this->_padding_ + 0x108,local_50);
        pMVar7 = Spinner(&local_ec,(MAT_3D *)(this->_padding_ + 0x20),
                         *(VECTOR_3D *)(this->_padding_ + 300),-(float)this->_padding_);
        pfVar14 = (float *)local_48;
        for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
          *pfVar14 = pMVar7->right_x;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
          pfVar14 = pfVar14 + 1;
        }
        local_20 = (double)((float)local_20 - *(float *)(iStack_4c + 0x18) * (float)this->_padding_)
        ;
        local_18 = (double)((float)local_18 - *(float *)(iStack_4c + 0x1c) * (float)this->_padding_)
        ;
        local_10 = (double)((float)local_10 - *(float *)(iStack_4c + 0x20) * (float)this->_padding_)
        ;
        pMVar7 = Matrix_Multiply(&local_ec,&local_ac,(MAT_3D *)local_48);
        p_Var3 = (_OBJ76 *)this->_padding_;
        pfVar14 = (float *)local_48;
        for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
          *pfVar14 = pMVar7->right_x;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
          pfVar14 = pfVar14 + 1;
        }
        pOVar8 = OrdnanceClass::Build((OrdnanceClass *)this->_padding_,(MAT_3D *)local_48,p_Var3);
        pOVar8->dt = (float)this->_padding_ - param_1;
      }
      this->salvoCount = this->salvoCount + -1;
      this->_padding_ = (int)((float)this->_padding_ - this->chargeLevel->salvoDelay);
    }
    this->salvoCount = 0;
LAB_0052ca0f:
    if (this->salvoCount != 0) goto LAB_0052cc02;
    this->chargeLevel = this->emptyLevel;
    pOVar11 = this->emptyLevel->ordnanceClass;
    this->_padding_ = 0;
  }
  this->_padding_ = (int)pOVar11;
LAB_0052cc02:
  this->_padding_ = this->chargeLevel->wpnReticle;
  return;
}
