/*
 * Entry: 00470322
 * Name: TankEnemy::~TankEnemy
 * Namespace: TankEnemy
 * Signature: void ~TankEnemy(TankEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TankEnemy::~TankEnemy(TankEnemy *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
