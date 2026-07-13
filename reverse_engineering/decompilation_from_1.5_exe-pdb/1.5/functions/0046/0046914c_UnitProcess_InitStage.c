/*
 * Entry: 0046914c
 * Name: UnitProcess::InitStage
 * Namespace: UnitProcess
 * Signature: void InitStage(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitStage(UnitProcess *this)

{
  VEHICLE *pVVar1;
  GotoTask *pGVar2;
  
  pVVar1 = this->me->vhcl;
  (pVVar1->control).steer = 0.0;
  (pVVar1->control).pitch = 0.0;
  pGVar2 = operator_new(0x150);
  if (pGVar2 == (GotoTask *)0x0) {
    pGVar2 = (GotoTask *)0x0;
  }
  else {
    pGVar2 = GotoTask::GotoTask(pGVar2,this->me,this->where,true);
  }
  this->task = (AiTask *)pGVar2;
  return;
}
