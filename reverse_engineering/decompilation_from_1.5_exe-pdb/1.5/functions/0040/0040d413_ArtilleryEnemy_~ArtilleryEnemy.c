/*
 * Entry: 0040d413
 * Name: ArtilleryEnemy::~ArtilleryEnemy
 * Namespace: ArtilleryEnemy
 * Signature: void ~ArtilleryEnemy(ArtilleryEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryEnemy::~ArtilleryEnemy(ArtilleryEnemy *this)

{
  *(undefined ***)this = &OffensiveProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
