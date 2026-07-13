/*
 * Entry: 0040bb61
 * Name: APCProcess::~APCProcess
 * Namespace: APCProcess
 * Signature: void ~APCProcess(APCProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCProcess::~APCProcess(APCProcess *this)

{
  *(undefined ***)this = &_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
