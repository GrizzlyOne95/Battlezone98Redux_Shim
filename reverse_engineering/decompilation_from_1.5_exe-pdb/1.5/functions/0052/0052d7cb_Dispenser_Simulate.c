/*
 * Entry: 0052d7cb
 * Name: Dispenser::Simulate
 * Namespace: Dispenser
 * Signature: void Simulate(Dispenser * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Dispenser::Simulate(Dispenser *this,float param_1)

{
  GameObjectClass *pGVar1;
  OBJECT_CLASS_T OVar2;
  float fVar3;
  bool bVar4;
  int iVar5;
  GameObject *this_00;
  AiMission *pAVar6;
  GameObject *pGVar7;
  int *piVar8;
  MAT_3D *pMVar9;
  GAS_PREP_INFO local_94;
  MAT_3D local_78;
  GameObjectClass *local_38;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_78;
  fVar3 = param_1 + this->shotTimer;
  this->shotTimer = fVar3;
  if (this->triggered == false) {
    if (0.0 < fVar3) {
      this->shotTimer = 0.0;
    }
  }
  else {
    if ((0.0 < fVar3) && (bVar4 = Weapon::PermissionToFire((Weapon *)this), bVar4)) {
      pGVar1 = (GameObjectClass *)this->_padding_;
      local_38 = pGVar1;
      if (((pGVar1->categoryMin == -1) ||
          ((pGVar1->categoryMax == -1 ||
           (iVar5 = Team::FirstEmptySlot
                              (this->carrier->teamList,pGVar1->categoryMin,pGVar1->categoryMax),
           -1 < iVar5)))) && (pGVar1->maxAmmo <= (int)(this->carrier->curAmmo ^ 0x33333333U))) {
        if (*(char *)(this->_padding_ + 0x58) != '\0') {
          InitGASCtrl(&local_34);
          local_34.flags = 0x800;
          InitGASPrep(&local_94);
          if ((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) {
            local_94.pri = 0x41;
          }
          StartGASEvent((char *)(this->_padding_ + 0x58),(_OBJ76 *)this->_padding_,&local_34,
                        &local_94);
        }
        (**(code **)(this->carrier->_padding_ + 0x18))(-pGVar1->maxAmmo);
        piVar8 = &this->_padding_;
        pMVar9 = &local_78;
        for (iVar5 = 0x10; pGVar1 = local_38, iVar5 != 0; iVar5 = iVar5 + -1) {
          pMVar9->right_x = (float)*piVar8;
          piVar8 = piVar8 + 1;
          pMVar9 = (MAT_3D *)&pMVar9->right_y;
        }
        OVar2 = local_38->class_id;
        if (((OVar2 != CLASS_ID_STRUCTURE1) && (OVar2 != CLASS_ID_SCRAP)) &&
           (OVar2 != CLASS_ID_SIGN)) {
          local_78.posit_x = (double)(local_78.front_x + (float)local_78.posit_x);
          local_78.posit_y = (double)(local_78.front_x + (float)local_78.posit_y);
          local_78.posit_z = (double)(local_78.front_x + (float)local_78.posit_z);
        }
        iVar5 = Net_IsNetGame();
        if ((iVar5 == 0) ||
           (bVar4 = DistributedObject::IsLocal((DistributedObject *)&this->carrier->_padding_),
           bVar4)) {
          this_00 = GameObjectClass::Build
                              (pGVar1,&local_78,*(ushort *)(this->_padding_ + 0x16) & 0xf,0,-1,
                               (char *)0x0);
          OVar2 = pGVar1->class_id;
          if ((OVar2 != CLASS_ID_STRUCTURE1) &&
             ((OVar2 != CLASS_ID_SCRAP && (OVar2 != CLASS_ID_SIGN)))) {
            GameObject::SetVelocity(this_00,&(this->carrier->euler).v);
          }
          pAVar6 = AiMission::GetCurrent();
          (**(code **)(pAVar6->_padding_ + 0x18))(this_00);
          pGVar7 = GameObject::GetObj(this->carrier->targetHandle);
          GameObject::SetTarget(this_00,pGVar7);
          GameObject::SetOwner(this_00,this->carrier);
          iVar5 = Net_IsNetGame();
          if (iVar5 != 0) {
            DistributedObject::SetLocal((DistributedObject *)&this_00->_padding_);
          }
        }
      }
      this->shotTimer = this->shotTimer - *(float *)(this->_padding_ + 0x78);
    }
    this->triggered = false;
  }
  return;
}
