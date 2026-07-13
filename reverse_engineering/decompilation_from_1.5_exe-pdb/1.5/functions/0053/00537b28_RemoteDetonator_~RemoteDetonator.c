/*
 * Entry: 00537b28
 * Name: RemoteDetonator::~RemoteDetonator
 * Namespace: RemoteDetonator
 * Signature: void ~RemoteDetonator(RemoteDetonator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RemoteDetonator::~RemoteDetonator(RemoteDetonator *this)

{
  this->_padding_ = (int)&_vftable_;
  Detonate(this);
  Mortar::~Mortar((Mortar *)this);
  return;
}
