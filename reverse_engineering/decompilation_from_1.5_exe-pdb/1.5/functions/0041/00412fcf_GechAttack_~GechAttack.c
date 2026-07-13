/*
 * Entry: 00412fcf
 * Name: GechAttack::~GechAttack
 * Namespace: GechAttack
 * Signature: void ~GechAttack(GechAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechAttack::~GechAttack(GechAttack *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
