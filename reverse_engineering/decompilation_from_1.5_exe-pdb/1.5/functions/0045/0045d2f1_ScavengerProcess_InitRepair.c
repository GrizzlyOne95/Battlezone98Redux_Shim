/*
 * Entry: 0045d2f1
 * Name: ScavengerProcess::InitRepair
 * Namespace: ScavengerProcess
 * Signature: void InitRepair(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::InitRepair(ScavengerProcess *this)

{
  Team *this_00;
  AiPath *pAVar1;
  bool bVar2;
  Armory *pAVar3;
  float *pfVar4;
  float *pfVar5;
  AiPath *this_01;
  int iVar6;
  SPHERE *pSVar7;
  GoNearAndSit *pGVar8;
  SitSpinTask *this_02;
  float fVar9;
  float local_18;
  int local_14;
  Armory *local_10;
  AiPath *local_c;
  Armory *local_8;
  
  this_00 = (Team *)this->craft->_padding_;
  local_8 = (Armory *)Team::GetSlot(this_00,3);
  if ((0 < this->craft->_padding_) ||
     (((local_8 != (Armory *)0x0 && (bVar2 = Armory::CanSendRepair(local_8), !bVar2)) &&
      (bVar2 = Producer::IsBusy((Producer *)local_8), !bVar2)))) {
    local_8 = (Armory *)0x0;
  }
  local_18 = 3.4028235e+38;
  local_c = (AiPath *)0x0;
  local_10 = (Armory *)GameObjectHandle::GetObj(this->craft->_padding_);
  if (local_10 == (Armory *)0x0) {
    if ((local_8 == (Armory *)0x0) || (this->craft->_padding_ == 0)) {
      local_14 = 0x3c;
      do {
        pAVar3 = (Armory *)Team::GetSlot(this_00,local_14);
        pAVar1 = local_c;
        if (pAVar3 != (Armory *)0x0) {
          pfVar4 = (float *)(**(code **)(pAVar3->_padding_ + 0xc))();
          pfVar5 = (float *)(**(code **)(this->craft->_padding_ + 0xc))();
          if ((local_8 == (Armory *)0x0) ||
             ((pfVar5[2] - pfVar4[2]) * (pfVar5[2] - pfVar4[2]) +
              (*pfVar5 - *pfVar4) * (*pfVar5 - *pfVar4) < 90000.0)) {
            this_01 = FindPlan((GameObject *)this->craft,(GameObject *)pAVar3);
            fVar9 = AiPath::GetLength(this_01);
            if (local_18 <= fVar9) {
              if (this_01 != (AiPath *)0x0) {
                AiPath::~AiPath(this_01);
                operator_delete(this_01);
              }
            }
            else {
              local_18 = fVar9;
              local_10 = pAVar3;
              pAVar1 = this_01;
              if (local_c != (AiPath *)0x0) {
                AiPath::~AiPath(local_c);
                operator_delete(local_c);
              }
            }
          }
        }
        local_c = pAVar1;
        local_14 = local_14 + 1;
      } while (local_14 < 0x41);
      goto LAB_0045d44d;
    }
  }
  else {
    local_c = FindPlan((GameObject *)this->craft,(GameObject *)local_10);
LAB_0045d44d:
    if (local_10 != (Armory *)0x0) {
      if (this->craft->_padding_ != 0) {
        (**(code **)(this->craft->_padding_ + 0x60))();
      }
      iVar6 = (**(code **)local_10->_padding_)();
      if (*(int *)(iVar6 + 0x20) == 0x52444550) {
        iVar6 = (**(code **)local_10->_padding_)();
        fVar9 = *(float *)(iVar6 + 0x160);
      }
      else {
        pSVar7 = GameObject::GetSphere((GameObject *)local_10);
        fVar9 = pSVar7->radius + (float)this->craft->_padding_;
      }
      pGVar8 = operator_new(0x160);
      local_8 = local_10;
      if (pGVar8 == (GoNearAndSit *)0x0) {
        pGVar8 = (GoNearAndSit *)0x0;
      }
      else {
        pGVar8 = GoNearAndSit::GoNearAndSit
                           (pGVar8,(Craft *)this->craft,(GameObject *)local_10,local_c,fVar9);
      }
      goto LAB_0045d4ec;
    }
  }
  if (local_8 == (Armory *)0x0) {
    this->nextState = WAIT;
    return;
  }
  this_02 = operator_new(0x138);
  if (this_02 == (SitSpinTask *)0x0) {
    pGVar8 = (GoNearAndSit *)0x0;
  }
  else {
    pGVar8 = (GoNearAndSit *)SitSpinTask::SitSpinTask(this_02,(Craft *)this->craft);
  }
LAB_0045d4ec:
  this->task = (AiTask *)pGVar8;
  iVar6 = GameObject::GetHandle((GameObject *)local_8);
  this->whoHandle = iVar6;
  return;
}
