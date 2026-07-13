/*
 * Entry: 0045b575
 * Name: RescueTask::RescueTask
 * Namespace: RescueTask
 * Signature: RescueTask * RescueTask(RescueTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RescueTask * __thiscall RescueTask::RescueTask(RescueTask *this)

{
  UnitTask::UnitTask((UnitTask *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
