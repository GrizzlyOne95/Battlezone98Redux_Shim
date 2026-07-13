/*
 * Entry: 00458f6f
 * Name: RecyclerProcess::DoWait
 * Namespace: RecyclerProcess
 * Signature: void DoWait(RecyclerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerProcess::DoWait(RecyclerProcess *this)

{
  SitTask *pSVar1;
  
  if (this->task == (AiTask *)0x0) {
    pSVar1 = operator_new(0x138);
    if (pSVar1 == (SitTask *)0x0) {
      pSVar1 = (SitTask *)0x0;
    }
    else {
      pSVar1 = SitTask::SitTask(pSVar1,(Craft *)this->craft);
    }
    this->task = (AiTask *)pSVar1;
  }
                    /* WARNING: Could not recover jumptable at 0x00458f9e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->task->_padding_ + 0x1c))();
  return;
}
