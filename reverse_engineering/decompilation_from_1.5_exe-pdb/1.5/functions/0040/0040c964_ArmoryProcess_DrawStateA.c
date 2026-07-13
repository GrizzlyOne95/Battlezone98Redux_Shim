/*
 * Entry: 0040c964
 * Name: ArmoryProcess::DrawStateA
 * Namespace: ArmoryProcess
 * Signature: void DrawStateA(ArmoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall ArmoryProcess::DrawStateA(ArmoryProcess *this)

{
  State SVar1;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  sprintf(local_58," ArmoryProcess:");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," State (%s)",stateText[this->curState]);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  SVar1 = this->curState;
  if ((3 < (int)SVar1) && (((int)SVar1 < 6 || (SVar1 == GOTO_GEYSER)))) {
    (**(code **)(this->task->_padding_ + 0x20))();
  }
  return;
}
