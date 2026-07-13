/*
 * Entry: 0044daa2
 * Name: OffensiveProcess::OffensiveProcess
 * Namespace: OffensiveProcess
 * Signature: OffensiveProcess * OffensiveProcess(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OffensiveProcess * __thiscall OffensiveProcess::OffensiveProcess(OffensiveProcess *this)

{
  UnitProcess::UnitProcess((UnitProcess *)this);
  this->engageRange = 40000.0;
  this->who1 = (GameObject *)0x0;
  this->followRange = 15625.0;
  this->who2 = (GameObject *)0x0;
  this->attackUser = false;
  this->weaponRange = 40000.0;
  this->_padding_ = (int)&_vftable_;
  this->isFriend = true;
  this->madTime = 30.0;
  this->_padding_ = 0;
  return this;
}
