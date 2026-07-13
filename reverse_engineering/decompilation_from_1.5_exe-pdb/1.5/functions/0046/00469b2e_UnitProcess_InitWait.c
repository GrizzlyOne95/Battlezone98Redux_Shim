/*
 * Entry: 00469b2e
 * Name: UnitProcess::InitWait
 * Namespace: UnitProcess
 * Signature: void InitWait(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitWait(UnitProcess *this)

{
  CoastTask *pCVar1;
  SitTask *this_00;
  float fVar2;
  
  if (this->me->_padding_ == CMD_STOP) {
    GameObject::ClearCommand((GameObject *)this->me);
  }
  fVar2 = Get_Time();
  this->waitStart = fVar2;
  if ((float)this->me->_padding_ <= 10.0) {
    this_00 = operator_new(0x138);
    if (this_00 != (SitTask *)0x0) {
      pCVar1 = (CoastTask *)SitTask::SitTask(this_00,this->me);
      goto LAB_00469b93;
    }
  }
  else {
    pCVar1 = operator_new(0x138);
    if (pCVar1 != (CoastTask *)0x0) {
      pCVar1 = CoastTask::CoastTask(pCVar1,this->me);
      goto LAB_00469b93;
    }
  }
  pCVar1 = (CoastTask *)0x0;
LAB_00469b93:
  this->task = (AiTask *)pCVar1;
  return;
}
