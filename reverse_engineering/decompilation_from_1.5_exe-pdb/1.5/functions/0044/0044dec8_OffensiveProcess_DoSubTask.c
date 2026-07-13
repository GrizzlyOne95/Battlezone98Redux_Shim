/*
 * Entry: 0044dec8
 * Name: OffensiveProcess::DoSubTask
 * Namespace: OffensiveProcess
 * Signature: bool DoSubTask(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall OffensiveProcess::DoSubTask(OffensiveProcess *this)

{
  bool bVar1;
  GameObject *pGVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  GameObject *pGVar6;
  char cVar7;
  float fVar8;
  float local_14;
  float local_10;
  int local_c;
  GameObject *local_8;
  
  if (this->_padding_ == 0) {
    return false;
  }
  iVar3 = *(int *)(this->_padding_ + 0xa0);
  local_8 = (GameObject *)0x0;
  if ((iVar3 != 0) && (*(int *)(iVar3 + 0xc) == 0x534e4950)) {
    local_10 = *(float *)(this->_padding_ + 0x1e0);
    fVar8 = Get_Time();
    if (fVar8 - local_10 < 3.0) {
      local_8 = GameObjectHandle::GetObj(*(int *)(this->_padding_ + 0x1ec));
    }
  }
  pGVar6 = GameObject::userObject;
  local_c = this->_padding_;
  if (local_c == 0) {
    local_c = this->_padding_;
    local_10 = (float)this->_padding_;
    if (local_8 != (GameObject *)0x0) {
      this->who2 = local_8;
      goto LAB_0044e0aa;
    }
    if (this->attackUser != false) {
      this->who2 = GameObject::userObject;
      if (pGVar6 == (GameObject *)0x0) {
LAB_0044e03b:
        bVar1 = false;
      }
      else {
        pfVar4 = (float *)(**(code **)(pGVar6->_padding_ + 0xc))();
        pfVar5 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        if (this->engageRange <=
            (pfVar5[2] - pfVar4[2]) * (pfVar5[2] - pfVar4[2]) +
            (*pfVar5 - *pfVar4) * (*pfVar5 - *pfVar4)) goto LAB_0044e03b;
        bVar1 = true;
      }
      this->attackUser = bVar1;
      if (bVar1 != false) goto LAB_0044e0aa;
    }
    fVar8 = Get_Time();
    if ((float)this->_padding_ <= fVar8) {
      local_14 = this->engageRange;
      pGVar6 = (GameObject *)(**(code **)(this->_padding_ + 0xe4))(&local_14);
      this->who2 = pGVar6;
      if (pGVar6 != (GameObject *)0x0) goto LAB_0044e0aa;
      Rand_Counter = Rand_Counter + 1U & 0xff;
      local_10 = Pseudo_Rand_Number[Rand_Counter];
      fVar8 = Get_Time();
      this->_padding_ = (int)(local_10 * 3.0 + fVar8 + 7.0);
    }
LAB_0044e114:
    bVar1 = false;
  }
  else {
    local_10 = (float)this->_padding_;
    if (this->_padding_ == 0xf) {
      pGVar2 = GameObjectHandle::GetObj(this->_padding_);
      this->who2 = pGVar2;
      pGVar6 = GameObject::userObject;
      if ((this->attackUser != false) && (pGVar2 != GameObject::userObject)) {
        if (pGVar2 == (GameObject *)0x0) {
          if (((GameObject::userObject == (GameObject *)0x0) ||
              (iVar3 = (**(code **)(GameObject::userObject->_padding_ + 0x30))(), iVar3 == 0)) ||
             ((*(int *)(iVar3 + 0xac) != 4 && ((*(uint *)(iVar3 + 0x14) & 0x200) == 0)))) {
            this->attackUser = true;
            if (pGVar6 != (GameObject *)0x0) {
              iVar3 = (**(code **)(pGVar6->_padding_ + 4))();
              GameObject::SetPerceivedTeam(pGVar6,iVar3);
            }
          }
          else {
            this->attackUser = false;
          }
        }
        else {
          this->who2 = (GameObject *)0x0;
          this->attackUser = true;
        }
      }
      if (this->who2 != (GameObject *)0x0) {
        iVar3 = (**(code **)(this->who2->_padding_ + 4))();
        bVar1 = GameObject::FriendP((GameObject *)this->_padding_,iVar3);
        if (bVar1) goto LAB_0044dfd3;
      }
    }
    else {
LAB_0044dfd3:
      this->who2 = (GameObject *)0x0;
    }
LAB_0044e0aa:
    if ((local_c < 7) || (8 < local_c)) {
      this->who1 = (GameObject *)0x0;
    }
    else {
      pGVar6 = GameObjectHandle::GetObj((int)local_10);
      this->who1 = pGVar6;
    }
    if ((this->who2 == (GameObject *)0x0) || (*(int *)(this->_padding_ + 0x198) == 0)) {
      cVar7 = '\0';
    }
    else if (local_8 == (GameObject *)0x0) {
      cVar7 = (**(code **)(this->_padding_ + 0xe8))(local_c);
    }
    else {
      cVar7 = this->who2 == local_8;
    }
    if (this->_padding_ == 0) {
      if (cVar7 == '\0') goto LAB_0044e114;
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
      if (cVar7 != '\0') goto LAB_0044e114;
      this->_padding_ = this->_padding_;
      this->_padding_ = this->_padding_;
      this->_padding_ = 0;
    }
    bVar1 = true;
  }
  return bVar1;
}
