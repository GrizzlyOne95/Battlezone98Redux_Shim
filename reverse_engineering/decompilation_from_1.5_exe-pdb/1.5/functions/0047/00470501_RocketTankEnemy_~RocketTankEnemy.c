/*
 * Entry: 00470501
 * Name: RocketTankEnemy::~RocketTankEnemy
 * Namespace: RocketTankEnemy
 * Signature: void ~RocketTankEnemy(RocketTankEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketTankEnemy::~RocketTankEnemy(RocketTankEnemy *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
