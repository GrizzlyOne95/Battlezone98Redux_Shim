/*
 * Entry: 004701c2
 * Name: WingmanProcess::ChangesState
 * Namespace: WingmanProcess
 * Signature: bool ChangesState(WingmanProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall WingmanProcess::ChangesState(WingmanProcess *this,AiCommand param_1)

{
  bool bVar1;
  
  if (param_1 == CMD_NONE) {
    bVar1 = false;
  }
  else if (param_1 == CMD_HUNT) {
    *(undefined4 *)&this->field_0x1c = 0x10;
    Say(*(Craft **)&this->field_0x2c,USER1_MSG,0);
    bVar1 = true;
  }
  else {
    bVar1 = OffensiveProcess::ChangesState((OffensiveProcess *)this,param_1);
  }
  return bVar1;
}
