/*
 * Entry: 00469304
 * Name: UnitProcess::InitRecycle
 * Namespace: UnitProcess
 * Signature: void InitRecycle(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitRecycle(UnitProcess *this)

{
  GameObject *pGVar1;
  GotoTask *pGVar2;
  
  pGVar1 = GetClosestScrapDropoff((GameObject *)this->me);
  if (pGVar1 == (GameObject *)0x0) {
    this->task = (AiTask *)0x0;
  }
  else {
    pGVar2 = operator_new(0x150);
    if (pGVar2 == (GotoTask *)0x0) {
      pGVar2 = (GotoTask *)0x0;
    }
    else {
      pGVar2 = GotoTask::GotoTask(pGVar2,this->me,pGVar1);
    }
    this->task = (AiTask *)pGVar2;
  }
  return;
}
