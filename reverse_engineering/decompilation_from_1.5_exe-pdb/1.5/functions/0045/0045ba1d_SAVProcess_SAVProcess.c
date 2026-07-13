/*
 * Entry: 0045ba1d
 * Name: SAVProcess::SAVProcess
 * Namespace: SAVProcess
 * Signature: SAVProcess * SAVProcess(SAVProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SAVProcess * __thiscall SAVProcess::SAVProcess(SAVProcess *this)

{
  UnitProcess::UnitProcess((UnitProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
