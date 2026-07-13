/*
 * Entry: 004a7922
 * Name: PersonClass::~PersonClass
 * Namespace: PersonClass
 * Signature: void ~PersonClass(PersonClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonClass::~PersonClass(PersonClass *this)

{
  this->_padding_ = (int)&_vftable_;
  CraftClass::~CraftClass((CraftClass *)this);
  return;
}
