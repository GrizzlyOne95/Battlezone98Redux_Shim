/*
 * Entry: 004849c1
 * Name: CameraPod::~CameraPod
 * Namespace: CameraPod
 * Signature: void ~CameraPod(CameraPod * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CameraPod::~CameraPod(CameraPod *this)

{
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  PowerUp::~PowerUp((PowerUp *)this);
  return;
}
