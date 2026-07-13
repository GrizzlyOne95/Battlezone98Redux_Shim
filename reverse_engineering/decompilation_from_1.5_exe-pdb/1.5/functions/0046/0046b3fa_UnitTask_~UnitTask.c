/*
 * Entry: 0046b3fa
 * Name: UnitTask::~UnitTask
 * Namespace: UnitTask
 * Signature: void ~UnitTask(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::~UnitTask(UnitTask *this)

{
  this->_padding_ = (int)&_vftable_;
  this->me->_padding_ = 0;
  AiTask::~AiTask((AiTask *)this);
  return;
}
