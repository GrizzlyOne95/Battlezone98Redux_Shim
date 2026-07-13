/*
 * Entry: 0047def4
 * Name: APC::GetCommand
 * Namespace: APC
 * Signature: AiCommand GetCommand(APC * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall APC::GetCommand(APC *this,GameObject *param_1)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  
  if (((param_1 == (GameObject *)0x0) ||
      (iVar3 = GameObject::GetActiveMode((GameObject *)this), iVar3 != 1)) ||
     ((APC *)param_1 == this)) {
    return CMD_NONE;
  }
  piVar1 = &param_1->_padding_;
  iVar3 = (**(code **)*piVar1)();
  if ((*(int *)(iVar3 + 0x20) != 0x53435250) &&
     (iVar3 = (**(code **)*piVar1)(), *(int *)(iVar3 + 0x20) != 0x4745495a)) {
    iVar3 = (**(code **)*piVar1)();
    if (*(int *)(iVar3 + 0x28) == 3) {
      return CMD_GO;
    }
    iVar3 = (**(code **)(*piVar1 + 4))();
    if ((iVar3 != 0) || (param_1->isObjective != false)) {
      bVar2 = GameObject::EnemyP((GameObject *)this,param_1);
      if (bVar2) {
        if (0 < this->soldierCount) {
          return CMD_ATTACK;
        }
      }
      else {
        iVar3 = (**(code **)*piVar1)();
        if ((*(int *)(iVar3 + 0x28) == 1) ||
           (iVar3 = (**(code **)*piVar1)(), *(int *)(iVar3 + 0x28) == 6)) {
          return CMD_FOLLOW;
        }
        iVar3 = (**(code **)*piVar1)();
        if ((*(int *)(iVar3 + 0x28) != 5) || (param_1->isObjective != false)) {
          return CMD_DEFEND;
        }
      }
    }
  }
  return CMD_NONE;
}
