/*
 * Entry: 0053178f
 * Name: MagnetMine::~MagnetMine
 * Namespace: MagnetMine
 * Signature: void ~MagnetMine(MagnetMine * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MagnetMine::~MagnetMine(MagnetMine *this)

{
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  Mine::~Mine((Mine *)this);
  return;
}
