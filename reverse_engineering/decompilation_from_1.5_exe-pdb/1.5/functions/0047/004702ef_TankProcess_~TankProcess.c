/*
 * Entry: 004702ef
 * Name: TankProcess::~TankProcess
 * Namespace: TankProcess
 * Signature: void ~TankProcess(TankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TankProcess::~TankProcess(TankProcess *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
