/*
 * Entry: 0045981d
 * Name: RecyclerProcess::InitWait
 * Namespace: RecyclerProcess
 * Signature: void InitWait(RecyclerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerProcess::InitWait(RecyclerProcess *this)

{
  bool bVar1;
  CoastTask *pCVar2;
  SitTask *this_00;
  
  if ((float)this->craft->_padding_ <= 10.0) {
    this_00 = operator_new(0x138);
    if (this_00 != (SitTask *)0x0) {
      pCVar2 = (CoastTask *)SitTask::SitTask(this_00,(Craft *)this->craft);
      goto LAB_00459869;
    }
  }
  else {
    pCVar2 = operator_new(0x138);
    if (pCVar2 != (CoastTask *)0x0) {
      pCVar2 = CoastTask::CoastTask(pCVar2,(Craft *)this->craft);
      goto LAB_00459869;
    }
  }
  pCVar2 = (CoastTask *)0x0;
LAB_00459869:
  this->task = (AiTask *)pCVar2;
  bVar1 = TryToDeploy(this);
  if (!bVar1) {
    this->nextState = GOTO_GEYSER;
  }
  return;
}
