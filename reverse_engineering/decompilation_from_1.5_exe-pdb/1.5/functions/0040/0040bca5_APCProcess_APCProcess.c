/*
 * Entry: 0040bca5
 * Name: APCProcess::APCProcess
 * Namespace: APCProcess
 * Signature: APCProcess * APCProcess(APCProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

APCProcess * __thiscall APCProcess::APCProcess(APCProcess *this)

{
  UnitProcess::UnitProcess((UnitProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
