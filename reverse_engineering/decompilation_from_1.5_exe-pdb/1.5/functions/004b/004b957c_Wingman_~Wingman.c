/*
 * Entry: 004b957c
 * Name: Wingman::~Wingman
 * Namespace: Wingman
 * Signature: void ~Wingman(Wingman * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Wingman::~Wingman(Wingman *this)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)&this->field_0x268;
  *(undefined ***)this = &HoverCraft::_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &HoverCraft::_vftable__for__DistributedObject__;
  if (puVar1 != (undefined4 *)0x0) {
    (**(code **)*puVar1)(1);
    *(undefined4 *)&this->field_0x268 = 0;
  }
  Craft::~Craft((Craft *)this);
  return;
}
