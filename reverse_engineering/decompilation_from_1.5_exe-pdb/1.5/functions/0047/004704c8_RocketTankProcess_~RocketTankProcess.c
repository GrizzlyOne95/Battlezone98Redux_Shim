/*
 * Entry: 004704c8
 * Name: RocketTankProcess::~RocketTankProcess
 * Namespace: RocketTankProcess
 * Signature: void ~RocketTankProcess(RocketTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketTankProcess::~RocketTankProcess(RocketTankProcess *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
