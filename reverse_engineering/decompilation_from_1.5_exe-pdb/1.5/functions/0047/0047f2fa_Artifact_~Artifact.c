/*
 * Entry: 0047f2fa
 * Name: Artifact::~Artifact
 * Namespace: Artifact
 * Signature: void ~Artifact(Artifact * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Artifact::~Artifact(Artifact *this)

{
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  Building::~Building((Building *)this);
  return;
}
