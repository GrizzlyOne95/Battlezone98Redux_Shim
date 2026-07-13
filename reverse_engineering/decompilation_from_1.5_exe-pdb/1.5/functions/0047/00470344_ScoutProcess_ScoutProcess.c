/*
 * Entry: 00470344
 * Name: ScoutProcess::ScoutProcess
 * Namespace: ScoutProcess
 * Signature: ScoutProcess * ScoutProcess(ScoutProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScoutProcess * __thiscall ScoutProcess::ScoutProcess(ScoutProcess *this)

{
  WingmanProcess::WingmanProcess((WingmanProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
