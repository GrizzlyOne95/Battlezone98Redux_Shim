/*
 * Entry: 00412c56
 * Name: GechProcess::~GechProcess
 * Namespace: GechProcess
 * Signature: void ~GechProcess(GechProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechProcess::~GechProcess(GechProcess *this)

{
  *(undefined ***)this = &_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
