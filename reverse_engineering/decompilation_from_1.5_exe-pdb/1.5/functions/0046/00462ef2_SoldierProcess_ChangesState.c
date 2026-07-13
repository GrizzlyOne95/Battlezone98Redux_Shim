/*
 * Entry: 00462ef2
 * Name: SoldierProcess::ChangesState
 * Namespace: SoldierProcess
 * Signature: bool ChangesState(SoldierProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SoldierProcess::ChangesState(SoldierProcess *this,AiCommand param_1)

{
  bool bVar1;
  
  if (param_1 == CMD_GET_IN) {
    *(undefined4 *)&this->field_0x1c = 0x11;
    return true;
  }
  bVar1 = OffensiveProcess::ChangesState((OffensiveProcess *)this,param_1);
  return bVar1;
}
