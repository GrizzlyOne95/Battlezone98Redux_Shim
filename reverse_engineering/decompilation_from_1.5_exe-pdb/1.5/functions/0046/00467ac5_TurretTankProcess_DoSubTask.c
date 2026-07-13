/*
 * Entry: 00467ac5
 * Name: TurretTankProcess::DoSubTask
 * Namespace: TurretTankProcess
 * Signature: bool DoSubTask(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTankProcess::DoSubTask(TurretTankProcess *this)

{
  bool bVar1;
  GameObject *pGVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  GameObject *pGVar6;
  float fVar7;
  float local_14;
  float local_10;
  State local_c;
  GameObject *local_8;
  
  iVar3 = *(int *)(this->_padding_ + 0xa0);
  local_8 = (GameObject *)0x0;
  if ((iVar3 != 0) && (*(int *)(iVar3 + 0xc) == 0x534e4950)) {
    local_10 = *(float *)(this->_padding_ + 0x1e0);
    fVar7 = Get_Time();
    if (fVar7 - local_10 < 3.0) {
      local_8 = GameObjectHandle::GetObj(*(int *)(this->_padding_ + 0x1ec));
    }
  }
  pGVar6 = GameObject::userObject;
  local_c = this->_padding_;
  if (local_c == NO_STATE) {
    local_c = this->_padding_;
    local_10 = (float)this->_padding_;
    if (local_8 != (GameObject *)0x0) {
      this->who2 = local_8;
      goto LAB_00467c94;
    }
    if (this->attackUser != false) {
      this->who2 = GameObject::userObject;
      if (pGVar6 == (GameObject *)0x0) {
LAB_00467c22:
        bVar1 = false;
      }
      else {
        pfVar4 = (float *)(**(code **)(pGVar6->_padding_ + 0xc))();
        pfVar5 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        if (this->rangeSquared <=
            (pfVar5[2] - pfVar4[2]) * (pfVar5[2] - pfVar4[2]) +
            (*pfVar5 - *pfVar4) * (*pfVar5 - *pfVar4)) goto LAB_00467c22;
        bVar1 = true;
      }
      this->attackUser = bVar1;
      if (bVar1 != false) goto LAB_00467c94;
    }
    fVar7 = Get_Time();
    if ((float)this->_padding_ <= fVar7) {
      local_14 = this->rangeSquared;
      pGVar6 = GetClosestEnemyWithin((GameObject *)this->_padding_,&local_14);
      this->who2 = pGVar6;
      if (pGVar6 != (GameObject *)0x0) goto LAB_00467c94;
      Rand_Counter = Rand_Counter + 1U & 0xff;
      local_10 = Pseudo_Rand_Number[Rand_Counter];
      fVar7 = Get_Time();
      this->_padding_ = (int)(local_10 * 3.0 + fVar7 + 7.0);
    }
LAB_00467c3a:
    bVar1 = false;
  }
  else {
    local_10 = (float)this->_padding_;
    pGVar2 = GameObjectHandle::GetObj(this->_padding_);
    this->who2 = pGVar2;
    pGVar6 = GameObject::userObject;
    if ((this->attackUser != false) && (pGVar2 != GameObject::userObject)) {
      if (pGVar2 == (GameObject *)0x0) {
        if (GameObject::userObject != (GameObject *)0x0) {
          iVar3 = (**(code **)(GameObject::userObject->_padding_ + 0x30))();
          if ((iVar3 != 0) &&
             ((*(int *)(iVar3 + 0xac) == 4 || ((*(uint *)(iVar3 + 0x14) & 0x200) != 0)))) {
            this->attackUser = false;
            goto LAB_00467b96;
          }
        }
        this->attackUser = true;
        if (pGVar6 != (GameObject *)0x0) {
          iVar3 = (**(code **)(pGVar6->_padding_ + 4))();
          GameObject::SetPerceivedTeam(pGVar6,iVar3);
        }
      }
      else {
        this->who2 = (GameObject *)0x0;
        this->attackUser = true;
      }
    }
LAB_00467b96:
    if (this->who2 != (GameObject *)0x0) {
      iVar3 = (**(code **)(this->who2->_padding_ + 4))();
      bVar1 = GameObject::FriendP((GameObject *)this->_padding_,iVar3);
      if (bVar1) {
        this->who2 = (GameObject *)0x0;
      }
    }
LAB_00467c94:
    if (((int)local_c < 7) || (8 < (int)local_c)) {
      this->who1 = (GameObject *)0x0;
    }
    else {
      pGVar6 = GameObjectHandle::GetObj((int)local_10);
      this->who1 = pGVar6;
    }
    if ((this->who2 == (GameObject *)0x0) || (*(int *)(this->_padding_ + 0x198) == 0)) {
      bVar1 = false;
    }
    else if (local_8 == (GameObject *)0x0) {
      bVar1 = ShouldAttack(this,local_c);
    }
    else {
      bVar1 = this->who2 == local_8;
    }
    if (this->_padding_ == 0) {
      if (bVar1 == false) goto LAB_00467c3a;
      pGVar6 = this->who2;
      this->_padding_ = this->_padding_;
      this->_padding_ = 0xf;
      this->_padding_ = this->_padding_;
      if (pGVar6 == (GameObject *)0x0) {
        iVar3 = 0;
      }
      else {
        iVar3 = GameObject::GetHandle(pGVar6);
      }
      this->_padding_ = iVar3;
      this->attackUser = pGVar6 == GameObject::userObject;
    }
    else {
      if (bVar1 != false) goto LAB_00467c3a;
      this->_padding_ = this->_padding_;
      this->_padding_ = this->_padding_;
      this->_padding_ = 0;
    }
    bVar1 = true;
  }
  return bVar1;
}
