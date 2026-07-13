/*
 * Entry: 00469b98
 * Name: UnitProcess::InitGoto
 * Namespace: UnitProcess
 * Signature: void InitGoto(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitGoto(UnitProcess *this)

{
  VEHICLE *pVVar1;
  GotoTask *pGVar2;
  GoGet *pGVar3;
  GameObject *pGVar4;
  int iVar5;
  
  pVVar1 = this->me->vhcl;
  (pVVar1->control).steer = 0.0;
  (pVVar1->control).pitch = 0.0;
  if (this->whoHandle == 0) {
    pGVar2 = operator_new(0x150);
    if (pGVar2 == (GotoTask *)0x0) {
      pGVar3 = (GoGet *)0x0;
    }
    else {
      pGVar3 = (GoGet *)GotoTask::GotoTask(pGVar2,this->me,this->where,this->exact);
    }
  }
  else {
    pGVar4 = GameObjectHandle::GetObj(this->whoHandle);
    if (pGVar4 == (GameObject *)0x0) {
      pGVar2 = operator_new(0x150);
      if (pGVar2 != (GotoTask *)0x0) {
        pGVar3 = (GoGet *)GotoTask::GotoTask(pGVar2,this->me,this->where,false);
        goto LAB_00469c60;
      }
    }
    else {
      iVar5 = (**(code **)pGVar4->_padding_)();
      if ((*(int *)(iVar5 + 0x28) == 3) && (*(int *)(iVar5 + 0x20) != 0x43504f44)) {
        pGVar3 = operator_new(0x160);
        if (pGVar3 != (GoGet *)0x0) {
          pGVar3 = GoGet::GoGet(pGVar3,this->me,pGVar4);
          goto LAB_00469c60;
        }
      }
      else {
        pGVar2 = operator_new(0x150);
        if (pGVar2 != (GotoTask *)0x0) {
          pGVar3 = (GoGet *)GotoTask::GotoTask(pGVar2,this->me,pGVar4);
          goto LAB_00469c60;
        }
      }
    }
    pGVar3 = (GoGet *)0x0;
  }
LAB_00469c60:
  this->task = (AiTask *)pGVar3;
  return;
}
