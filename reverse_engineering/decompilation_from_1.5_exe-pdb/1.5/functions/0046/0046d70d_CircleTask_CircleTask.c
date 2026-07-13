/*
 * Entry: 0046d70d
 * Name: CircleTask::CircleTask
 * Namespace: CircleTask
 * Signature: CircleTask * CircleTask(CircleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CircleTask * __thiscall CircleTask::CircleTask(CircleTask *this)

{
  UnitTask::UnitTask((UnitTask *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
