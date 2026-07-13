/*
 * Entry: 0045b64e
 * Name: RescueTask::~RescueTask
 * Namespace: RescueTask
 * Signature: void ~RescueTask(RescueTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RescueTask::~RescueTask(RescueTask *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
