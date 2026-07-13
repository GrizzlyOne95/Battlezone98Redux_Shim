/*
 * Entry: 00469d44
 * Name: UnitProcess::InitDefend
 * Namespace: UnitProcess
 * Signature: void InitDefend(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitDefend(UnitProcess *this)

{
  SitTask *pSVar1;
  GameObject *pGVar2;
  DefendTask *this_00;
  
  if (this->whoHandle == 0) {
    pSVar1 = operator_new(0x138);
    if (pSVar1 == (SitTask *)0x0) {
      pSVar1 = (SitTask *)0x0;
    }
    else {
      pSVar1 = SitTask::SitTask(pSVar1,this->me);
    }
  }
  else {
    pGVar2 = GameObjectHandle::GetObj(this->whoHandle);
    this_00 = operator_new(0x138);
    if (this_00 == (DefendTask *)0x0) {
      pSVar1 = (SitTask *)0x0;
    }
    else {
      pSVar1 = (SitTask *)DefendTask::DefendTask(this_00,this->me,pGVar2);
    }
  }
  this->task = (AiTask *)pSVar1;
  return;
}
