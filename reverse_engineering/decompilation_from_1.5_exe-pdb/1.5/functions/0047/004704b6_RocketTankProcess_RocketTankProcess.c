/*
 * Entry: 004704b6
 * Name: RocketTankProcess::RocketTankProcess
 * Namespace: RocketTankProcess
 * Signature: RocketTankProcess * RocketTankProcess(RocketTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RocketTankProcess * __thiscall RocketTankProcess::RocketTankProcess(RocketTankProcess *this)

{
  WingmanProcess::WingmanProcess((WingmanProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
