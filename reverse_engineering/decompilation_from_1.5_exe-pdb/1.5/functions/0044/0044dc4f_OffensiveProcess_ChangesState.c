/*
 * Entry: 0044dc4f
 * Name: OffensiveProcess::ChangesState
 * Namespace: OffensiveProcess
 * Signature: bool ChangesState(OffensiveProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall OffensiveProcess::ChangesState(OffensiveProcess *this,AiCommand param_1)

{
  bool bVar1;
  
  if (param_1 == CMD_NONE) {
    bVar1 = false;
  }
  else {
    if (param_1 == CMD_FOLLOW) {
      param_1 = CMD_FOLLOW;
      this->followRange = 15625.0;
    }
    else if (param_1 == CMD_FORMATION) {
      this->followRange = 0.0;
      Say((Craft *)this->_padding_,FOLLOW_MSG,0);
      this->_padding_ = 8;
      return true;
    }
    bVar1 = UnitProcess::ChangesState((UnitProcess *)this,param_1);
  }
  return bVar1;
}
