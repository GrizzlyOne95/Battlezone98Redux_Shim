/*
 * Entry: 004667b6
 * Name: TugProcess::DoRepair
 * Namespace: TugProcess
 * Signature: void DoRepair(TugProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugProcess::DoRepair(TugProcess *this)

{
  char cVar1;
  GameObject *this_00;
  int iVar2;
  GoGet *pGVar3;
  Armory *this_01;
  bool bVar4;
  float10 fVar5;
  
  if (this->task == (AiTask *)0x0) {
    this->nextState = WAIT;
    return;
  }
  if (this->whoHandle == 0) {
    this_00 = GetClosestObject((GameObject *)this->craft,0x524b4954,-1,30.0);
    if (this_00 == (GameObject *)0x0) goto LAB_00466890;
    iVar2 = GameObject::GetHandle(this_00);
    this->whoHandle = iVar2;
    if (this->task != (AiTask *)0x0) {
      (**(code **)this->task->_padding_)(1);
    }
    pGVar3 = operator_new(0x160);
    if (pGVar3 == (GoGet *)0x0) {
      pGVar3 = (GoGet *)0x0;
    }
    else {
      pGVar3 = GoGet::GoGet(pGVar3,this->craft,this_00);
    }
    this->task = (AiTask *)pGVar3;
    bVar4 = pGVar3 == (GoGet *)0x0;
  }
  else {
    this_01 = (Armory *)GameObjectHandle::GetObj(this->whoHandle);
    if (this_01 == (Armory *)0x0) goto LAB_004668be;
    iVar2 = this_01->_padding_;
    if ((iVar2 < 0x3c) || (0x40 < iVar2)) {
      if (iVar2 != 3) {
        cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
        if (cVar1 != '\0') goto LAB_004668be;
        goto LAB_00466890;
      }
      bVar4 = Armory::CanSendRepair(this_01);
      if ((bVar4) && (this_01->_padding_ == 0)) {
        GameObject::SetCommand((GameObject *)this_01,CMD_GET_REPAIR,(GameObject *)this->craft);
        this->whoHandle = 0;
        goto LAB_00466890;
      }
      bVar4 = Armory::CanSendRepair(this_01);
      if (bVar4) goto LAB_00466890;
      bVar4 = Producer::IsBusy((Producer *)this_01);
      bVar4 = !bVar4;
    }
    else {
      fVar5 = (float10)(**(code **)(this->craft->_padding_ + 0x1c))();
      bVar4 = (float10)1.0 <= fVar5;
    }
  }
  if (!bVar4) {
LAB_00466890:
                    /* WARNING: Could not recover jumptable at 0x00466897. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->task->_padding_ + 0x1c))();
    return;
  }
LAB_004668be:
  this->nextState = WAIT;
  return;
}
