/*
 * Entry: 0041cfd5
 * Name: MineLayerProcess::ChangesState
 * Namespace: MineLayerProcess
 * Signature: bool ChangesState(MineLayerProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall MineLayerProcess::ChangesState(MineLayerProcess *this,AiCommand param_1)

{
  bool bVar1;
  
  if (param_1 == CMD_NONE) {
LAB_0041d025:
    bVar1 = false;
  }
  else {
    if (param_1 == CMD_SELECT) {
      if (*(int *)&this->field_0x18 == 0x10) {
        Say(*(Craft **)&this->field_0x2c,SELECT_USER1_MSG,0);
        GameObject::GetWhat(*(GameObject **)&this->field_0x2c);
        goto LAB_0041d025;
      }
      param_1 = CMD_SELECT;
    }
    else if (param_1 == CMD_LAY_MINES) {
      Say(*(Craft **)&this->field_0x2c,USER1_MSG,0);
      *(undefined4 *)&this->field_0x1c = 0x10;
      return true;
    }
    bVar1 = UnitProcess::ChangesState((UnitProcess *)this,param_1);
  }
  return bVar1;
}
