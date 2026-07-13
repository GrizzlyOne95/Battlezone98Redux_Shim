/*
 * Entry: 0052fa88
 * Name: FlareMine::~FlareMine
 * Namespace: FlareMine
 * Signature: void ~FlareMine(FlareMine * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlareMine::~FlareMine(FlareMine *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  Mine::~Mine((Mine *)this);
  return;
}
