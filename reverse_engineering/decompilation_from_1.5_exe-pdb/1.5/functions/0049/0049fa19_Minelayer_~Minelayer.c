/*
 * Entry: 0049fa19
 * Name: Minelayer::~Minelayer
 * Namespace: Minelayer
 * Signature: void ~Minelayer(Minelayer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Minelayer::~Minelayer(Minelayer *this)

{
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this->_padding_)(1);
  }
  HoverCraft::~HoverCraft((HoverCraft *)this);
  return;
}
