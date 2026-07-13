/*
 * Entry: 00458d9a
 * Name: RecyclerProcess::CleanState
 * Namespace: RecyclerProcess
 * Signature: void CleanState(RecyclerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerProcess::CleanState(RecyclerProcess *this)

{
  State SVar1;
  AiTask *pAVar2;
  
  SVar1 = this->curState;
  if ((int)SVar1 < 1) goto LAB_00458df4;
  if ((int)SVar1 < 4) {
LAB_00458def:
    (**(code **)(this->_padding_ + 0x28))();
    goto LAB_00458df4;
  }
  if (SVar1 == GOTO) {
    if (this->release != false) {
      AiPath::Release(this->where);
    }
LAB_00458ddc:
    pAVar2 = this->task;
    if (pAVar2 != (AiTask *)0x0) goto LAB_00458de3;
  }
  else {
    if (SVar1 == FOLLOW) goto LAB_00458ddc;
    if (SVar1 == BUILD) goto LAB_00458def;
    if (SVar1 != RECYCLE) {
      if (SVar1 != GOTO_GEYSER) goto LAB_00458df4;
      goto LAB_00458ddc;
    }
    pAVar2 = this->task;
    if (pAVar2 == (AiTask *)0x0) goto LAB_00458df4;
LAB_00458de3:
    (**(code **)pAVar2->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
LAB_00458df4:
  GameObject::ClearCommand((GameObject *)this->craft);
  return;
}
