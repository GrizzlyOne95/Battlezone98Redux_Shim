/*
 * Entry: 0045b99c
 * Name: SAVProcess::~SAVProcess
 * Namespace: SAVProcess
 * Signature: void ~SAVProcess(SAVProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVProcess::~SAVProcess(SAVProcess *this)

{
  *(undefined ***)this = &_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
