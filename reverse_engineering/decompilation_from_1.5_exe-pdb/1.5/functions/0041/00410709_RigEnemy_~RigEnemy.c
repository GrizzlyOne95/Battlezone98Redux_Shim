/*
 * Entry: 00410709
 * Name: RigEnemy::~RigEnemy
 * Namespace: RigEnemy
 * Signature: void ~RigEnemy(RigEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RigEnemy::~RigEnemy(RigEnemy *this)

{
  *(undefined ***)this = &RigProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
