/*
 * Entry: 0046a084
 * Name: UnitProcess::InitReload
 * Namespace: UnitProcess
 * Signature: void InitReload(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitReload(UnitProcess *this)

{
  Craft *this_00;
  Team *this_01;
  AiPath *pAVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  GameObject *pGVar5;
  float *pfVar6;
  float *pfVar7;
  AiPath *this_02;
  SitSpinTask *pSVar8;
  float fVar9;
  float local_18;
  GameObject *local_14;
  AiPath *local_10;
  int local_c;
  Armory *local_8;
  
  this_00 = this->me;
  iVar4 = GameObject::GetHandle((GameObject *)this_00);
  if (this_00->_padding_ == iVar4) {
    this->nextState = WAIT;
    return;
  }
  this_01 = (Team *)this_00->_padding_;
  local_8 = (Armory *)Team::GetSlot(this_01,3);
  if ((0 < this->me->_padding_) ||
     (((local_8 != (Armory *)0x0 && (bVar2 = Armory::CanSendReload(local_8), !bVar2)) &&
      (bVar2 = Producer::IsBusy((Producer *)local_8), !bVar2)))) {
    local_8 = (Armory *)0x0;
  }
  local_18 = 3.4028235e+38;
  local_10 = (AiPath *)0x0;
  local_14 = GameObjectHandle::GetObj(this->me->_padding_);
  if (local_14 == (GameObject *)0x0) {
    if ((local_8 != (Armory *)0x0) &&
       (cVar3 = (**(code **)(this->me->_padding_ + 0x68))(), cVar3 == '\0')) goto LAB_0046a221;
    local_c = 0x41;
    do {
      pGVar5 = Team::GetSlot(this_01,local_c);
      pAVar1 = local_10;
      if (pGVar5 != (GameObject *)0x0) {
        pfVar6 = (float *)(**(code **)(pGVar5->_padding_ + 0xc))();
        pfVar7 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
        if ((local_8 == (Armory *)0x0) ||
           ((pfVar7[2] - pfVar6[2]) * (pfVar7[2] - pfVar6[2]) +
            (*pfVar7 - *pfVar6) * (*pfVar7 - *pfVar6) < 90000.0)) {
          this_02 = FindPlan((GameObject *)this->me,pGVar5);
          fVar9 = AiPath::GetLength(this_02);
          if (local_18 <= fVar9) {
            if (this_02 != (AiPath *)0x0) {
              AiPath::~AiPath(this_02);
              operator_delete(this_02);
            }
          }
          else {
            local_18 = fVar9;
            local_14 = pGVar5;
            pAVar1 = this_02;
            if (local_10 != (AiPath *)0x0) {
              AiPath::~AiPath(local_10);
              operator_delete(local_10);
            }
          }
        }
      }
      local_10 = pAVar1;
      local_c = local_c + 1;
    } while (local_c < 0x46);
  }
  else {
    FindPlan((GameObject *)this->me,local_14);
  }
  if (local_14 != (GameObject *)0x0) {
    cVar3 = (**(code **)(this->me->_padding_ + 0x68))();
    if (cVar3 == '\0') {
      (**(code **)(this->me->_padding_ + 0x60))();
    }
    iVar4 = GameObject::GetHandle(local_14);
    this->whoHandle = iVar4;
    this->nextState = DEFEND;
    return;
  }
LAB_0046a221:
  if ((local_8 == (Armory *)0x0) ||
     (cVar3 = (**(code **)(this->me->_padding_ + 0x68))(), cVar3 == '\0')) {
    this->nextState = WAIT;
  }
  else {
    pSVar8 = operator_new(0x138);
    if (pSVar8 == (SitSpinTask *)0x0) {
      pSVar8 = (SitSpinTask *)0x0;
    }
    else {
      pSVar8 = SitSpinTask::SitSpinTask(pSVar8,this->me);
    }
    this->task = (AiTask *)pSVar8;
    iVar4 = GameObject::GetHandle((GameObject *)local_8);
    this->whoHandle = iVar4;
  }
  return;
}
