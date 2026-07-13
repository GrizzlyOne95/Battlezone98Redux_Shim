/*
 * Entry: 004701a8
 * Name: WingmanProcess::~WingmanProcess
 * Namespace: WingmanProcess
 * Signature: void ~WingmanProcess(WingmanProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanProcess::~WingmanProcess(WingmanProcess *this)

{
  *(undefined ***)this = &_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
