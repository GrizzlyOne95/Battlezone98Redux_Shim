/*
 * Entry: 0046a26b
 * Name: UnitProcess::DoReload
 * Namespace: UnitProcess
 * Signature: void DoReload(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoReload(UnitProcess *this)

{
  float fVar1;
  bool bVar2;
  char cVar3;
  GameObject *this_00;
  int iVar4;
  GoGet *pGVar5;
  Armory *this_01;
  
  if (this->task == (AiTask *)0x0) {
    this->nextState = WAIT;
    return;
  }
  if (this->whoHandle == 0) {
    this_00 = GetClosestObject((GameObject *)this->me,0x414d4d4f,-1,30.0);
    if (this_00 != (GameObject *)0x0) {
      iVar4 = GameObject::GetHandle(this_00);
      this->whoHandle = iVar4;
      if (this->task != (AiTask *)0x0) {
        (**(code **)this->task->_padding_)(1);
      }
      pGVar5 = operator_new(0x160);
      if (pGVar5 == (GoGet *)0x0) {
        pGVar5 = (GoGet *)0x0;
      }
      else {
        pGVar5 = GoGet::GoGet(pGVar5,this->me,this_00);
      }
      this->task = (AiTask *)pGVar5;
      if (pGVar5 == (GoGet *)0x0) goto LAB_0046a31b;
    }
  }
  else {
    this_01 = (Armory *)GameObjectHandle::GetObj(this->whoHandle);
    if (this_01 == (Armory *)0x0) {
LAB_0046a31b:
      this->nextState = WAIT;
      return;
    }
    iVar4 = this_01->_padding_;
    if ((iVar4 < 0x41) || (0x41 < iVar4)) {
      if (iVar4 == 3) {
        bVar2 = Armory::CanSendReload(this_01);
        if ((bVar2) && (this_01->_padding_ == 0)) {
          GameObject::SetCommand((GameObject *)this_01,CMD_GET_RELOAD,(GameObject *)this->me);
          this->whoHandle = 0;
        }
        else {
          bVar2 = Armory::CanSendReload(this_01);
          if ((!bVar2) && (bVar2 = Producer::IsBusy((Producer *)this_01), !bVar2))
          goto LAB_0046a37f;
        }
      }
      else {
        cVar3 = (**(code **)(this->task->_padding_ + 0x18))();
        if (cVar3 != '\0') {
LAB_0046a37f:
          this->nextState = WAIT;
          return;
        }
      }
    }
    else {
      fVar1 = (float)this->me->_padding_;
      if (!NAN(fVar1) && 1.0 < fVar1 != (fVar1 == 1.0)) goto LAB_0046a31b;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x0046a2ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->task->_padding_ + 0x1c))();
  return;
}
