/*
 * Entry: 004703df
 * Name: BomberEnemy::~BomberEnemy
 * Namespace: BomberEnemy
 * Signature: void ~BomberEnemy(BomberEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BomberEnemy::~BomberEnemy(BomberEnemy *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
