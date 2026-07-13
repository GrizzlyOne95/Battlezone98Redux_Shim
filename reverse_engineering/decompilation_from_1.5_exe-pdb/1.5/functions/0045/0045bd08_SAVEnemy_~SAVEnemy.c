/*
 * Entry: 0045bd08
 * Name: SAVEnemy::~SAVEnemy
 * Namespace: SAVEnemy
 * Signature: void ~SAVEnemy(SAVEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVEnemy::~SAVEnemy(SAVEnemy *this)

{
  *(undefined ***)this = &SAVProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
