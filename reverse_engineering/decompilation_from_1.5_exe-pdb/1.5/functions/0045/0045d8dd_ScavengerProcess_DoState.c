/*
 * Entry: 0045d8dd
 * Name: ScavengerProcess::DoState
 * Namespace: ScavengerProcess
 * Signature: void DoState(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::DoState(ScavengerProcess *this)

{
  Scavenger *this_00;
  char cVar1;
  float *pfVar2;
  GameObject *pGVar3;
  SPHERE *pSVar4;
  float *pfVar5;
  int iVar6;
  GameObject *unaff_EDI;
  float fVar7;
  float fVar8;
  float fVar9;
  
  switch(this->curState) {
  case WAIT:
    fVar7 = Get_Time();
    if (this->wait_time < fVar7) {
      this->nextState = RECYCLE;
    }
    break;
  case GOTO:
    cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
    if (cVar1 != '\0') {
      if (this->recycle == false) {
        this->nextState = WAIT;
        this->wait_time = 1e+30;
      }
      else {
        this->nextState = RECYCLE;
      }
      this->recycle = false;
      return;
    }
    break;
  case FOLLOW:
  case RESCUE:
    cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
    if (cVar1 != '\0') {
LAB_0045db79:
      this->nextState = WAIT;
      return;
    }
    break;
  case RECYCLE:
    cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
    if (cVar1 != '\0') goto LAB_0045db79;
    fVar7 = Get_Time();
    if ((this->wait_time < fVar7) &&
       (((fVar7 = (float)this->craft->_padding_, fVar8 = Get_Time(), fVar8 - fVar7 < 5.0 ||
         (fVar7 = (float)this->craft->_padding_, fVar8 = Get_Time(), fVar8 - fVar7 < 5.0)) &&
        (pGVar3 = FindBase(unaff_EDI), pGVar3 != (GameObject *)0x0)))) {
      pfVar5 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
      pfVar2 = (float *)(**(code **)(this->craft->_padding_ + 0xc))();
      if (5625.0 < (pfVar2[2] - pfVar5[2]) * (pfVar2[2] - pfVar5[2]) +
                   (*pfVar2 - *pfVar5) * (*pfVar2 - *pfVar5)) {
        this->nextState = RETREAT;
        return;
      }
    }
    break;
  case REPAIR:
    DoRepair(this);
    return;
  case RETREAT:
    cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
    if ((cVar1 != '\0') ||
       (pfVar5 = (float *)(**(code **)(this->craft->_padding_ + 0xc))(),
       fVar7 = *pfVar5 - (this->where).x, fVar8 = pfVar5[2] - (this->where).z,
       fVar8 * fVar8 + fVar7 * fVar7 < 1600.0)) goto LAB_0045db79;
    break;
  case CASH_OUT:
    if ((this->task == (AiTask *)0x0) ||
       (cVar1 = (**(code **)(this->task->_padding_ + 0x18))(), cVar1 != '\0')) {
      pGVar3 = GameObjectHandle::GetObj(this->task[2]._padding_);
      if (pGVar3 != (GameObject *)0x0) {
        this_00 = this->craft;
        fVar9 = 40.0;
        pSVar4 = GameObject::GetSphere((GameObject *)this_00);
        fVar7 = Max((float)this_00->_padding_,pSVar4->radius);
        pSVar4 = GameObject::GetSphere(pGVar3);
        fVar8 = Max(pGVar3->collisionRadius,pSVar4->radius);
        fVar8 = Max(fVar8 + fVar7 + 20.0,fVar9);
        pfVar5 = (float *)(**(code **)(pGVar3->_padding_ + 0xc))();
        fVar7 = *pfVar5;
        pfVar5 = (float *)(**(code **)(this->craft->_padding_ + 0xc))();
        if (ABS(fVar7 - *pfVar5) < fVar8) {
          iVar6 = (**(code **)(pGVar3->_padding_ + 0xc))();
          fVar7 = *(float *)(iVar6 + 8);
          iVar6 = (**(code **)(this->craft->_padding_ + 0xc))();
          if (ABS(fVar7 - *(float *)(iVar6 + 8)) < fVar8) {
            (**(code **)(this->craft->_padding_ + 0x24))();
          }
        }
      }
      if (this->craft->_padding_ == CMD_RECYCLE) {
        GameObject::ClearCommand((GameObject *)this->craft);
      }
      goto LAB_0045db79;
    }
    break;
  default:
    goto switchD_0045d8f6_default;
  }
  (**(code **)(this->task->_padding_ + 0x1c))();
switchD_0045d8f6_default:
  return;
}
