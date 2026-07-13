/*
 * Entry: 0040eb60
 * Name: AttackTask::AttackTask
 * Namespace: AttackTask
 * Signature: AttackTask * AttackTask(AttackTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AttackTask * __thiscall AttackTask::AttackTask(AttackTask *this)

{
  UnitTask::UnitTask((UnitTask *)this);
  this->_padding_ = (int)&_vftable_;
  return this;
}
