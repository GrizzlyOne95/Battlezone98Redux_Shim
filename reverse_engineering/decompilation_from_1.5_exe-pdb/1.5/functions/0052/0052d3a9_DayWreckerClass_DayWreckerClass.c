/*
 * Entry: 0052d3a9
 * Name: DayWreckerClass::DayWreckerClass
 * Namespace: DayWreckerClass
 * Signature: DayWreckerClass * DayWreckerClass(DayWreckerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DayWreckerClass * __thiscall DayWreckerClass::DayWreckerClass(DayWreckerClass *this)

{
  PowerUpClass::PowerUpClass((PowerUpClass *)this);
  this->xplClass = (ExplosionClass *)0x0;
  this[1]._padding_ = 0;
  *(undefined2 *)&this->craterDepth = 0;
  this[1]._padding_ = 0x40a00000;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x5752434b;
  this->_padding_ = (int)"daywrecker";
  return this;
}
