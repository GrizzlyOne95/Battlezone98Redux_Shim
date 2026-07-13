/*
 * Entry: 00531e5b
 * Name: MineClass::~MineClass
 * Namespace: MineClass
 * Signature: void ~MineClass(MineClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MineClass::~MineClass(MineClass *this)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
