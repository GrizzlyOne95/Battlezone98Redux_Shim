/*
 * Entry: 004ab194
 * Name: Producer::GetCommand
 * Namespace: Producer
 * Signature: AiCommand GetCommand(Producer * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall Producer::GetCommand(Producer *this,GameObject *param_1)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  
  if ((((param_1 != (GameObject *)0x0) &&
       (iVar3 = GameObject::GetActiveMode((GameObject *)this), iVar3 != 0)) && (iVar3 == 1)) &&
     ((Producer *)param_1 != this)) {
    piVar1 = &param_1->_padding_;
    iVar3 = (**(code **)*piVar1)();
    if (*(int *)(iVar3 + 0x20) != 0x53435250) {
      iVar3 = (**(code **)*piVar1)();
      if (*(int *)(iVar3 + 0x20) == 0x4745495a) {
        if (*(char *)((int)&param_1[1]._padding_ + 1) == '\0') {
          return CMD_GO;
        }
      }
      else {
        iVar3 = (**(code **)*piVar1)();
        if (*(int *)(iVar3 + 0x28) == 3) {
          return CMD_GO;
        }
        iVar3 = (**(code **)(*piVar1 + 4))();
        if (((iVar3 != 0) || (param_1->isObjective != false)) &&
           (bVar2 = GameObject::EnemyP((GameObject *)this,param_1), !bVar2)) {
          iVar3 = (**(code **)*piVar1)();
          if ((*(int *)(iVar3 + 0x28) != 1) &&
             (iVar3 = (**(code **)*piVar1)(), *(int *)(iVar3 + 0x28) != 6)) {
            iVar3 = (**(code **)*piVar1)();
            return -(uint)(*(int *)(iVar3 + 0x28) != 5) & CMD_GO;
          }
          return CMD_FOLLOW;
        }
      }
    }
  }
  return CMD_NONE;
}
