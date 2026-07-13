/*
 * Entry: 0040bfd6
 * Name: APCAttack::~APCAttack
 * Namespace: APCAttack
 * Signature: void ~APCAttack(APCAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCAttack::~APCAttack(APCAttack *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
