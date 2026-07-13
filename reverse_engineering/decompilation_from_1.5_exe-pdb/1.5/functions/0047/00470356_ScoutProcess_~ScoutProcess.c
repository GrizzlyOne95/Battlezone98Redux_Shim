/*
 * Entry: 00470356
 * Name: ScoutProcess::~ScoutProcess
 * Namespace: ScoutProcess
 * Signature: void ~ScoutProcess(ScoutProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScoutProcess::~ScoutProcess(ScoutProcess *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
