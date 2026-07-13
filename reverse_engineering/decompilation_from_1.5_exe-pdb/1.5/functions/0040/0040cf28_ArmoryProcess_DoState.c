/*
 * Entry: 0040cf28
 * Name: ArmoryProcess::DoState
 * Namespace: ArmoryProcess
 * Signature: void DoState(ArmoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArmoryProcess::DoState(ArmoryProcess *this)

{
  State SVar1;
  Armory *this_00;
  char cVar2;
  bool bVar3;
  GameObject *this_01;
  SPHERE *pSVar4;
  float *pfVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  UnitMsg UVar9;
  float fVar10;
  
  cVar2 = (**(code **)(this->craft->_padding_ + 100))();
  if ((cVar2 == '\0') && (cVar2 = (**(code **)(this->craft->_padding_ + 0x68))(), cVar2 == '\0')) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  this->isInTransition = bVar3;
  if ((this->wasInTransition != false) && (bVar3 == false)) {
    cVar2 = (**(code **)(this->craft->_padding_ + 100))();
    if (cVar2 == '\0') {
      UVar9 = PACKED_MSG;
    }
    else {
      UVar9 = DEPLOYED_MSG;
    }
    Say((Craft *)this->craft,UVar9,0);
  }
  SVar1 = this->curState;
  if ((int)SVar1 < 1) goto LAB_0040d0da;
  if ((int)SVar1 < 4) {
    (**(code **)(this->_padding_ + 0x28))();
    goto LAB_0040d0da;
  }
  if ((int)SVar1 < 6) {
LAB_0040cfa6:
    cVar2 = (**(code **)(this->task->_padding_ + 0x18))();
    if (cVar2 != '\0') {
      this->nextState = WAIT;
      goto LAB_0040d0da;
    }
  }
  else {
    if (SVar1 != RECYCLE) {
      if (SVar1 != GOTO_GEYSER) goto LAB_0040d0da;
      goto LAB_0040cfa6;
    }
    if ((this->task == (AiTask *)0x0) ||
       (cVar2 = (**(code **)(this->task->_padding_ + 0x18))(), cVar2 != '\0')) {
      this_01 = GameObjectHandle::GetObj(this->task[2]._padding_);
      if (this_01 != (GameObject *)0x0) {
        this_00 = this->craft;
        fVar10 = 40.0;
        pSVar4 = GameObject::GetSphere((GameObject *)this_00);
        fVar7 = Max((float)this_00->_padding_,pSVar4->radius);
        pSVar4 = GameObject::GetSphere(this_01);
        fVar8 = Max(this_01->collisionRadius,pSVar4->radius);
        fVar8 = Max(fVar8 + fVar7 + 20.0,fVar10);
        pfVar5 = (float *)(**(code **)(this_01->_padding_ + 0xc))();
        fVar7 = *pfVar5;
        pfVar5 = (float *)(**(code **)(this->craft->_padding_ + 0xc))();
        if (ABS(fVar7 - *pfVar5) < fVar8) {
          iVar6 = (**(code **)(this_01->_padding_ + 0xc))();
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
      this->nextState = WAIT;
      return;
    }
  }
  (**(code **)(this->task->_padding_ + 0x1c))();
LAB_0040d0da:
  this->wasInTransition = this->isInTransition;
  return;
}
