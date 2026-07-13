/*
 * Entry: 0040bccf
 * Name: APCEnemy::~APCEnemy
 * Namespace: APCEnemy
 * Signature: void ~APCEnemy(APCEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCEnemy::~APCEnemy(APCEnemy *this)

{
  *(undefined ***)this = &APCProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
