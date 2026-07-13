/*
 * Entry: 00459897
 * Name: RecyclerFriend::InitWait
 * Namespace: RecyclerFriend
 * Signature: void InitWait(RecyclerFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerFriend::InitWait(RecyclerFriend *this)

{
  CoastTask *pCVar1;
  SitTask *this_00;
  
  RecyclerProcess::TryToDeploy((RecyclerProcess *)this);
  if (*(float *)(this->_padding_ + 0x124) <= 10.0) {
    this_00 = operator_new(0x138);
    if (this_00 != (SitTask *)0x0) {
      pCVar1 = (CoastTask *)SitTask::SitTask(this_00,(Craft *)this->_padding_);
      goto LAB_004598e8;
    }
  }
  else {
    pCVar1 = operator_new(0x138);
    if (pCVar1 != (CoastTask *)0x0) {
      pCVar1 = CoastTask::CoastTask(pCVar1,(Craft *)this->_padding_);
      goto LAB_004598e8;
    }
  }
  pCVar1 = (CoastTask *)0x0;
LAB_004598e8:
  this->_padding_ = (int)pCVar1;
  return;
}
