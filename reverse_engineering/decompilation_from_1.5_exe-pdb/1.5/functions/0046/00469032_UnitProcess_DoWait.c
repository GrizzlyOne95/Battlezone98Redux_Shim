/*
 * Entry: 00469032
 * Name: UnitProcess::DoWait
 * Namespace: UnitProcess
 * Signature: void DoWait(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoWait(UnitProcess *this)

{
  SitTask *pSVar1;
  
  if (this->task == (AiTask *)0x0) {
    pSVar1 = operator_new(0x138);
    if (pSVar1 == (SitTask *)0x0) {
      pSVar1 = (SitTask *)0x0;
    }
    else {
      pSVar1 = SitTask::SitTask(pSVar1,this->me);
    }
    this->task = (AiTask *)pSVar1;
  }
                    /* WARNING: Could not recover jumptable at 0x00469061. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->task->_padding_ + 0x1c))();
  return;
}
