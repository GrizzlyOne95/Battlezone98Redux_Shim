/*
 * Entry: 00469384
 * Name: UnitProcess::~UnitProcess
 * Namespace: UnitProcess
 * Signature: void ~UnitProcess(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::~UnitProcess(UnitProcess *this)

{
  this->_padding_ = (int)&_vftable_;
  CleanState(this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
