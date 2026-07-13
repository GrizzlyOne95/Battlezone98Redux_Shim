/*
 * Entry: 00457237
 * Name: PersonProcess::~PersonProcess
 * Namespace: PersonProcess
 * Signature: void ~PersonProcess(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonProcess::~PersonProcess(PersonProcess *this)

{
  this->_padding_ = (int)&_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  this->_padding_ = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
