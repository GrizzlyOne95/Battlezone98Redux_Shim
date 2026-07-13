/*
 * Entry: 0046d611
 * Name: SitTask::~SitTask
 * Namespace: SitTask
 * Signature: void ~SitTask(SitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SitTask::~SitTask(SitTask *this)

{
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
