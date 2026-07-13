/*
 * Entry: 00470b73
 * Name: RocketTankAttack::~RocketTankAttack
 * Namespace: RocketTankAttack
 * Signature: void ~RocketTankAttack(RocketTankAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketTankAttack::~RocketTankAttack(RocketTankAttack *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
