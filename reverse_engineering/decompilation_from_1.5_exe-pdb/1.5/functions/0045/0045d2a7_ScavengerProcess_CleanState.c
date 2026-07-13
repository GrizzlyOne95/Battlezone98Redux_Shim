/*
 * Entry: 0045d2a7
 * Name: ScavengerProcess::CleanState
 * Namespace: ScavengerProcess
 * Signature: void CleanState(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::CleanState(ScavengerProcess *this)

{
  State SVar1;
  AiTask *pAVar2;
  
  SVar1 = this->curState;
  if ((int)SVar1 < 1) goto LAB_0045d2e8;
  if ((int)SVar1 < 5) {
LAB_0045d2d7:
    pAVar2 = this->task;
    if (pAVar2 != (AiTask *)0x0) goto LAB_0045d2de;
  }
  else {
    if (SVar1 == REPAIR) {
      CleanRepair(this);
      goto LAB_0045d2e8;
    }
    if ((int)SVar1 < 6) goto LAB_0045d2e8;
    if ((int)SVar1 < 8) goto LAB_0045d2d7;
    if ((SVar1 != CASH_OUT) || (pAVar2 = this->task, pAVar2 == (AiTask *)0x0)) goto LAB_0045d2e8;
LAB_0045d2de:
    (**(code **)pAVar2->_padding_)(1);
  }
  this->task = (AiTask *)0x0;
LAB_0045d2e8:
  GameObject::ClearCommand((GameObject *)this->craft);
  return;
}
