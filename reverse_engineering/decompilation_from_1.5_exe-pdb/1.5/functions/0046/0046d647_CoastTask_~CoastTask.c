/*
 * Entry: 0046d647
 * Name: CoastTask::~CoastTask
 * Namespace: CoastTask
 * Signature: void ~CoastTask(CoastTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CoastTask::~CoastTask(CoastTask *this)

{
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
