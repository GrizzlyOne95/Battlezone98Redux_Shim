/*
 * Entry: 00410be1
 * Name: DefendTask::~DefendTask
 * Namespace: DefendTask
 * Signature: void ~DefendTask(DefendTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DefendTask::~DefendTask(DefendTask *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
