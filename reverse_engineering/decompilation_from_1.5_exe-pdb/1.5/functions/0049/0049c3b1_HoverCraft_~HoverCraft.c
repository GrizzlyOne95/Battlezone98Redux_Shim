/*
 * Entry: 0049c3b1
 * Name: HoverCraft::~HoverCraft
 * Namespace: HoverCraft
 * Signature: void ~HoverCraft(HoverCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::~HoverCraft(HoverCraft *this)

{
  HoverInterface *pHVar1;
  
  pHVar1 = this->hi;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  if (pHVar1 != (HoverInterface *)0x0) {
    (**(code **)pHVar1->_padding_)(1);
    this->hi = (HoverInterface *)0x0;
  }
  Craft::~Craft((Craft *)this);
  return;
}
