/*
 * Entry: 0052d3a4
 * Name: DayWreckerClass::~DayWreckerClass
 * Namespace: DayWreckerClass
 * Signature: void ~DayWreckerClass(DayWreckerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DayWreckerClass::~DayWreckerClass(DayWreckerClass *this)

{
  this->_padding_ = (int)&PowerUpClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
