/*
 * Entry: 004702dd
 * Name: TankProcess::TankProcess
 * Namespace: TankProcess
 * Signature: TankProcess * TankProcess(TankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TankProcess * __thiscall TankProcess::TankProcess(TankProcess *this)

{
  WingmanProcess::WingmanProcess((WingmanProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
