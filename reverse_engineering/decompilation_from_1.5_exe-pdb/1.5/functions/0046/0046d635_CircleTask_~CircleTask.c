/*
 * Entry: 0046d635
 * Name: CircleTask::~CircleTask
 * Namespace: CircleTask
 * Signature: void ~CircleTask(CircleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CircleTask::~CircleTask(CircleTask *this)

{
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
