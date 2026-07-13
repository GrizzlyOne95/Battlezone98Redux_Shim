/*
 * Entry: 004be002
 * Name: ActionMode::GetCommand
 * Namespace: ActionMode
 * Signature: AiCommand GetCommand(ActionMode * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall ActionMode::GetCommand(ActionMode *this,GameObject *param_1)

{
  int *piVar1;
  bool bVar2;
  char cVar3;
  GameObject *pGVar4;
  AiCommand AVar5;
  int iVar6;
  int iVar7;
  
  pGVar4 = GameObject::userObject;
  if (0 < controlPanel.selectNum) {
    pGVar4 = GameObject::GetObj(controlPanel.selectList[0]);
                    /* WARNING: Could not recover jumptable at 0x004be01b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    AVar5 = (**(code **)(pGVar4->_padding_ + 0x34))();
    return AVar5;
  }
  if (param_1 == (GameObject *)0x0) {
    return CMD_NONE;
  }
  iVar6 = ControlPanel::GetCurrentMode(&controlPanel);
  if (iVar6 == 0) {
    if (pGVar4 != (GameObject *)0x0) {
      iVar6 = (**(code **)(pGVar4->_padding_ + 4))();
      iVar7 = (**(code **)(param_1->_padding_ + 4))();
      if (((iVar7 == iVar6) && (-1 < param_1->teamSlot)) &&
         (((cVar3 = (**(code **)(param_1->_padding_ + 0x38))(), cVar3 != '\0' &&
           (param_1->isCargo == false)) ||
          ((iVar6 = param_1->teamSlot, 0x22 < iVar6 && (iVar6 < 0x2d)))))) {
        return CMD_SELECT;
      }
    }
  }
  else if (iVar6 == 1) {
    piVar1 = &param_1->_padding_;
    iVar6 = (**(code **)*piVar1)();
    if (*(int *)(iVar6 + 0x28) == 3) {
      return CMD_GO;
    }
    iVar6 = (**(code **)*piVar1)();
    if ((*(int *)(iVar6 + 0x20) != 0x53435250) &&
       (iVar6 = (**(code **)*piVar1)(), *(int *)(iVar6 + 0x20) != 0x4745495a)) {
      if ((pGVar4 != (GameObject *)0x0) && (bVar2 = GameObject::FriendP(pGVar4,param_1), bVar2)) {
        return CMD_FOLLOW;
      }
      return CMD_ATTACK;
    }
  }
  return CMD_NONE;
}
