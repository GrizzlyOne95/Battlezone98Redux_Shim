/*
 * Entry: 00489a85
 * Name: CraftClass::~CraftClass
 * Namespace: CraftClass
 * Signature: void ~CraftClass(CraftClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CraftClass::~CraftClass(CraftClass *this)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
