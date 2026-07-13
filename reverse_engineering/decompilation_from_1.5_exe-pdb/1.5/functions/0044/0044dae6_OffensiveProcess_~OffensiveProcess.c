/*
 * Entry: 0044dae6
 * Name: OffensiveProcess::~OffensiveProcess
 * Namespace: OffensiveProcess
 * Signature: void ~OffensiveProcess(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OffensiveProcess::~OffensiveProcess(OffensiveProcess *this)

{
  this->_padding_ = (int)&_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  this->_padding_ = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
