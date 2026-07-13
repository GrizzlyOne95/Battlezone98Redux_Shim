/*
 * Entry: 0041039a
 * Name: RigProcess::~RigProcess
 * Namespace: RigProcess
 * Signature: void ~RigProcess(RigProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RigProcess::~RigProcess(RigProcess *this)

{
  *(undefined ***)this = &_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
