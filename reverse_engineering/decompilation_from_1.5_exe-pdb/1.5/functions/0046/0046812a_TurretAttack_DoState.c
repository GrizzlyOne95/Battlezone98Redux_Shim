/*
 * Entry: 0046812a
 * Name: TurretAttack::DoState
 * Namespace: TurretAttack
 * Signature: void DoState(TurretAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretAttack::DoState(TurretAttack *this)

{
  int iVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  bool bVar5;
  char cVar6;
  GameObject *pGVar7;
  VECTOR_3D *pVVar8;
  int *piVar9;
  AttackerInfo *pAVar10;
  float *pfVar11;
  float *pfVar12;
  
  if (this->_padding_ == 0xd) {
    return;
  }
  pGVar7 = GameObjectHandle::GetObj(this->_padding_);
  this->_padding_ = (int)pGVar7;
  if (this->_padding_ == this->_padding_) {
    if (((pGVar7 == (GameObject *)0x0) ||
        (bVar5 = GameObject::FriendP((GameObject *)this->_padding_,pGVar7), bVar5)) ||
       (*(int *)(this->_padding_ + 0x198) == 0)) {
      this->_padding_ = 0xd;
      return;
    }
  }
  else if (pGVar7 == (GameObject *)0x0) {
    this->_padding_ = 1;
    return;
  }
  pVVar8 = (VECTOR_3D *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
  pGVar7 = NearestVehicle((GameObject *)this->_padding_,pVVar8);
  this->_padding_ = (int)pGVar7;
  *(undefined1 *)&this->_padding_ = 0;
  iVar1 = *(int *)(this->_padding_ + 0x228);
  switch(this->_padding_) {
  case 2:
    bVar5 = UnitTask::AbleToHit((UnitTask *)this);
    *(bool *)&this->_padding_ = bVar5;
    if (bVar5) {
      this->_padding_ = 10;
    }
    else {
      bVar5 = UnitTask::IsStuck((UnitTask *)this);
      if (bVar5) {
LAB_00468268:
        this->_padding_ = 3;
      }
      else {
        pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        fVar2 = *pfVar11 - (float)this->_padding_;
        fVar3 = pfVar11[2] - (float)this->_padding_;
        if ((10000.0 < fVar3 * fVar3 + fVar2 * fVar2) ||
           (pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))(),
           fVar2 = *pfVar11 - (float)this->_padding_, fVar3 = pfVar11[2] - (float)this->_padding_,
           fVar3 * fVar3 + fVar2 * fVar2 < 100.0)) goto LAB_004681e4;
LAB_004682d6:
        UnitTask::DoGoto((UnitTask *)this);
      }
    }
    break;
  case 3:
    UnitTask::DoStuck((UnitTask *)this);
    break;
  case 4:
    bVar5 = CheckFollowing(this);
    if (!bVar5) {
      pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      pfVar12 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      if ((pfVar12[2] - pfVar11[2]) * (pfVar12[2] - pfVar11[2]) +
          (*pfVar12 - *pfVar11) * (*pfVar12 - *pfVar11) <= 10000.0) {
        bVar5 = UnitTask::IsStuck((UnitTask *)this);
        if (bVar5) goto LAB_00468268;
        UnitTask::DoFollow((UnitTask *)this);
      }
      else {
        piVar9 = (int *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        this->_padding_ = *piVar9;
        this->_padding_ = piVar9[1];
        this->_padding_ = piVar9[2];
        this->_padding_ = 0xc;
      }
    }
    break;
  case 5:
    bVar5 = UnitTask::AbleToHit((UnitTask *)this);
    *(bool *)&this->_padding_ = bVar5;
    if ((bVar5) || (cVar6 = (**(code **)(*(int *)this->_padding_ + 100))(), cVar6 != '\0'))
    goto LAB_004681fd;
LAB_004681e4:
    this->_padding_ = 2;
    break;
  case 6:
    bVar5 = CheckWaiting(this);
    if (!bVar5) {
      UnitTask::DoSit((UnitTask *)this);
    }
    break;
  case 8:
    bVar5 = UnitTask::AbleToHit((UnitTask *)this);
    *(bool *)&this->_padding_ = bVar5;
    if (*(float *)(this->_padding_ + 0x1e0) <= (float)this->_padding_) {
      UnitTask::DoStand((UnitTask *)this);
    }
    else {
      this->_padding_ = 9;
    }
    break;
  case 10:
    bVar5 = UnitTask::AbleToHit((UnitTask *)this);
    *(bool *)&this->_padding_ = bVar5;
LAB_004681fd:
    UnitTask::DoBlast((UnitTask *)this);
    break;
  case 0xb:
    pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    fVar2 = *pfVar11 - (float)this->_padding_;
    fVar3 = pfVar11[2] - (float)this->_padding_;
    if (this->waitRangeSq <= fVar3 * fVar3 + fVar2 * fVar2) {
      bVar5 = UnitTask::IsStuck((UnitTask *)this);
      if (bVar5) goto LAB_00468268;
      pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      fVar2 = *pfVar11 - (float)this->_padding_;
      fVar3 = pfVar11[2] - (float)this->_padding_;
      if (fVar3 * fVar3 + fVar2 * fVar2 <= 10000.0) goto LAB_004682d6;
      this->_padding_ = 0xb;
    }
    else {
      this->_padding_ = 6;
    }
    break;
  case 0xc:
    bVar5 = CheckFollowing(this);
    if (!bVar5) {
      pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      pfVar12 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
      if (2500.0 <= (pfVar12[2] - pfVar11[2]) * (pfVar12[2] - pfVar11[2]) +
                    (*pfVar12 - *pfVar11) * (*pfVar12 - *pfVar11)) {
        pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
        fVar2 = *pfVar11 - (float)this->_padding_;
        fVar3 = pfVar11[2] - (float)this->_padding_;
        if (fVar3 * fVar3 + fVar2 * fVar2 <= 10000.0) {
          bVar5 = UnitTask::IsStuck((UnitTask *)this);
          if (bVar5) goto LAB_00468268;
          pfVar11 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
          fVar2 = *pfVar11 - (float)this->_padding_;
          fVar3 = pfVar11[2] - (float)this->_padding_;
          if (225.0 <= fVar3 * fVar3 + fVar2 * fVar2) {
            UnitTask::DoGoto((UnitTask *)this);
            if (*(float *)(iVar1 + 0xd0) == 1.0) {
              *(undefined4 *)(iVar1 + 0xd4) = 1;
            }
            else {
              *(undefined4 *)(iVar1 + 0xd4) = 0;
            }
            break;
          }
        }
        this->_padding_ = 0xc;
      }
      else {
        this->_padding_ = 4;
      }
    }
  }
  if ((char)this->_padding_ == '\0') {
    bVar5 = false;
    goto LAB_004685a1;
  }
  bVar5 = MayHitFriends((GameObject *)this->_padding_,(float)this->_padding_,0.3,1.0);
  pAVar10 = AttackGroup::GetLeft((AttackGroup *)this->_padding_,(GameObject *)this->_padding_);
  if (pAVar10 == (AttackerInfo *)0x0) {
LAB_0046857d:
    if (bVar5) {
      uVar4 = 0x3e800000;
    }
    else {
      uVar4 = 0;
    }
  }
  else {
    pfVar11 = (float *)(**(code **)(pAVar10->attacker->_padding_ + 0xc))();
    pfVar12 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    if (25.0 <= (pfVar12[2] - pfVar11[2]) * (pfVar12[2] - pfVar11[2]) +
                (*pfVar12 - *pfVar11) * (*pfVar12 - *pfVar11)) goto LAB_0046857d;
    uVar4 = 0x3f800000;
  }
  bVar5 = !bVar5;
  *(undefined4 *)(iVar1 + 0xcc) = uVar4;
LAB_004685a1:
  UnitTask::UpdateWeapon((UnitTask *)this,bVar5);
  UnitTask::UpdateSpecial((UnitTask *)this);
  return;
}
