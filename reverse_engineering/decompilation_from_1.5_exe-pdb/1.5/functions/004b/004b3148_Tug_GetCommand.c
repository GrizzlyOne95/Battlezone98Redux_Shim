/*
 * Entry: 004b3148
 * Name: Tug::GetCommand
 * Namespace: Tug
 * Signature: AiCommand GetCommand(Tug * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall Tug::GetCommand(Tug *this,GameObject *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  AiCommand AVar5;
  
  if (param_1 == (GameObject *)0x0) {
    return CMD_NONE;
  }
  iVar2 = (**(code **)param_1->_padding_)();
  iVar4 = *(int *)(iVar2 + 0x20);
  iVar2 = *(int *)(iVar2 + 0x28);
  iVar3 = GameObject::GetActiveMode((GameObject *)this);
  if ((((iVar3 == 1) && ((Tug *)param_1 != this)) && (iVar4 != 0x53435250)) && (iVar4 != 0x4745495a)
     ) {
    if (iVar2 == 3) {
      return CMD_GO;
    }
    if ((iVar2 == 2) || (iVar2 == 5)) {
      if ((this->cargo != (GameObject *)0x0) ||
         (iVar4 = (**(code **)(param_1->_padding_ + 0x28))(), iVar4 == 0)) goto LAB_004b31e2;
    }
    else if (((this->cargo != (GameObject *)0x0) || ((iVar2 != 6 && (iVar2 != 1)))) ||
            (param_1->aiProcess != (AiProcess *)0x0)) {
      bVar1 = GameObject::FriendP((GameObject *)this,param_1);
      return -(uint)bVar1 & CMD_FOLLOW;
    }
    AVar5 = CMD_PICKUP;
  }
  else {
LAB_004b31e2:
    AVar5 = CMD_NONE;
  }
  return AVar5;
}
