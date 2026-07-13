/*
 * Entry: 0053c696
 * Name: Torpedo::~Torpedo
 * Namespace: Torpedo
 * Signature: void ~Torpedo(Torpedo * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Torpedo::~Torpedo(Torpedo *this)

{
  this->_padding_ = (int)&PowerUp::_vftable__for__Attachable__;
  this->_padding_ = (int)&PowerUp::_vftable__for__DistributedObject__;
  GameObject::~GameObject((GameObject *)this);
  return;
}
