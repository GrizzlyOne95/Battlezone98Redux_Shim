/*
 * Entry: 0052fa42
 * Name: FlareMineClass::~FlareMineClass
 * Namespace: FlareMineClass
 * Signature: void ~FlareMineClass(FlareMineClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlareMineClass::~FlareMineClass(FlareMineClass *this)

{
  this->_padding_ = (int)&_vftable_;
  MineClass::~MineClass((MineClass *)this);
  return;
}
