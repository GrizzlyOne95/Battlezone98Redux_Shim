/*
 * Entry: 0052d6d9
 * Name: Dispenser::~Dispenser
 * Namespace: Dispenser
 * Signature: void ~Dispenser(Dispenser * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Dispenser::~Dispenser(Dispenser *this)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  return;
}
