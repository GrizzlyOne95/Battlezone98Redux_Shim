/*
 * Entry: 0046d623
 * Name: SitSpinTask::~SitSpinTask
 * Namespace: SitSpinTask
 * Signature: void ~SitSpinTask(SitSpinTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SitSpinTask::~SitSpinTask(SitSpinTask *this)

{
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
