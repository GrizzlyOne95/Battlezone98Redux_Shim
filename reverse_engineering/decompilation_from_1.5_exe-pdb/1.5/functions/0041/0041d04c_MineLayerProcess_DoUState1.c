/*
 * Entry: 0041d04c
 * Name: MineLayerProcess::DoUState1
 * Namespace: MineLayerProcess
 * Signature: void DoUState1(MineLayerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MineLayerProcess::DoUState1(MineLayerProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(**(int **)&this->field_0x30 + 0x18))();
  if (cVar1 != '\0') {
    *(undefined4 *)&this->field_0x1c = 3;
    if (((*(GameObject **)&this->field_0x2c)->curCmd).what == CMD_LAY_MINES) {
      GameObject::ClearCommand(*(GameObject **)&this->field_0x2c);
      Say(*(Craft **)&this->field_0x2c,USER2_MSG,0);
    }
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0041d08a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)&this->field_0x30 + 0x1c))();
  return;
}
