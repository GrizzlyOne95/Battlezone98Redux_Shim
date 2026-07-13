/*
 * Entry: 0046a384
 * Name: UnitProcess::InitRescue
 * Namespace: UnitProcess
 * Signature: void InitRescue(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitRescue(UnitProcess *this)

{
  GameObject *pGVar1;
  RescueTask *pRVar2;
  
  pGVar1 = GameObjectHandle::GetObj(this->whoHandle);
  pRVar2 = operator_new(0x138);
  if (pRVar2 == (RescueTask *)0x0) {
    pRVar2 = (RescueTask *)0x0;
  }
  else {
    pRVar2 = RescueTask::RescueTask(pRVar2,this->me,pGVar1);
  }
  this->task = (AiTask *)pRVar2;
  return;
}
