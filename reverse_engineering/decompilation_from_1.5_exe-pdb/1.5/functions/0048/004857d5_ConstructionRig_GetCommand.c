/*
 * Entry: 004857d5
 * Name: ConstructionRig::GetCommand
 * Namespace: ConstructionRig
 * Signature: AiCommand GetCommand(ConstructionRig * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall ConstructionRig::GetCommand(ConstructionRig *this,GameObject *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  if ((((param_1 != (GameObject *)0x0) &&
       (iVar2 = GameObject::GetActiveMode((GameObject *)this), this->_padding_ == 0)) &&
      (iVar2 != 0)) && (iVar2 == 1)) {
    iVar2 = (**(code **)param_1->_padding_)();
    puVar1 = (undefined4 *)param_1->_padding_;
    if (*(int *)(iVar2 + 0x28) == 2) {
      iVar2 = (*(code *)*puVar1)();
      return -(uint)(*(int *)(iVar2 + 0x20) != 0x4745495a) & CMD_RECYCLE;
    }
    iVar2 = (*(code *)*puVar1)();
    if (*(int *)(iVar2 + 0x20) == 0x54555252) {
      return CMD_RECYCLE;
    }
  }
  return CMD_NONE;
}
