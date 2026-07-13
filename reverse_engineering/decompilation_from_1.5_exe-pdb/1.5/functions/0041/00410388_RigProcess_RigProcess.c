/*
 * Entry: 00410388
 * Name: RigProcess::RigProcess
 * Namespace: RigProcess
 * Signature: RigProcess * RigProcess(RigProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RigProcess * __thiscall RigProcess::RigProcess(RigProcess *this)

{
  UnitProcess::UnitProcess((UnitProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
