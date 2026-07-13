/*
 * Entry: 00410b68
 * Name: DefendTask::DefendTask
 * Namespace: DefendTask
 * Signature: DefendTask * DefendTask(DefendTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DefendTask * __thiscall DefendTask::DefendTask(DefendTask *this)

{
  UnitTask::UnitTask((UnitTask *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
