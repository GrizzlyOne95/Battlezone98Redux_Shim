/*
 * Entry: 0048293d
 * Name: BarracksClass::~BarracksClass
 * Namespace: BarracksClass
 * Signature: void ~BarracksClass(BarracksClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BarracksClass::~BarracksClass(BarracksClass *this)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
