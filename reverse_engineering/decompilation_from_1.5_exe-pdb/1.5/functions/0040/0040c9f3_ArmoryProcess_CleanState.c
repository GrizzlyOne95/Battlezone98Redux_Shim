/*
 * Entry: 0040c9f3
 * Name: ArmoryProcess::CleanState
 * Namespace: ArmoryProcess
 * Signature: void CleanState(ArmoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArmoryProcess::CleanState(ArmoryProcess *this)

{
  State SVar1;
  AiTask *pAVar2;
  
  SVar1 = this->curState;
  if ((int)SVar1 < 1) goto LAB_0040ca48;
  if ((int)SVar1 < 4) {
    (**(code **)(this->_padding_ + 0x24))();
    goto LAB_0040ca48;
  }
  if (SVar1 == GOTO) {
    if (this->release != false) {
      AiPath::Release(this->where);
    }
LAB_0040ca30:
    pAVar2 = this->task;
    if (pAVar2 != (AiTask *)0x0) goto LAB_0040ca37;
  }
  else {
    if (SVar1 == FOLLOW) goto LAB_0040ca30;
    if (SVar1 != RECYCLE) {
      if (SVar1 != GOTO_GEYSER) goto LAB_0040ca48;
      goto LAB_0040ca30;
    }
    pAVar2 = this->task;
    if (pAVar2 == (AiTask *)0x0) goto LAB_0040ca48;
LAB_0040ca37:
    (**(code **)pAVar2->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
LAB_0040ca48:
  GameObject::ClearCommand((GameObject *)this->craft);
  return;
}
