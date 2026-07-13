/*
 * Entry: 0045a20f
 * Name: RecycleTask::DrawStateA
 * Namespace: RecycleTask
 * Signature: void DrawStateA(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall RecycleTask::DrawStateA(RecycleTask *this)

{
  GameObject *pGVar1;
  float *pfVar2;
  float *pfVar3;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  sprintf(local_58," RecycleTask:");
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," curState (%s)",stateText[this->curState]);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  sprintf(local_58," nextState (%s)",stateText[this->nextState]);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  if (this->curState == 2) {
    pGVar1 = GameObjectHandle::GetObj(this->scrapHandle);
    if (pGVar1 != (GameObject *)0x0) {
      pfVar2 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
      pfVar3 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
      sprintf(local_58," Scrap dist (%f)",
              (double)SQRT((pfVar3[2] - pfVar2[2]) * (pfVar3[2] - pfVar2[2]) +
                           (*pfVar3 - *pfVar2) * (*pfVar3 - *pfVar2)));
      DisplayInterface::DrawTextA
                (local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    }
  }
  if (this->subtask != (AiTask *)0x0) {
    (**(code **)(this->subtask->_padding_ + 0x20))();
  }
  return;
}
