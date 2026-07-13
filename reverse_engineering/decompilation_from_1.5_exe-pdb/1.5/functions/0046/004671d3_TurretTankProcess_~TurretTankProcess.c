/*
 * Entry: 004671d3
 * Name: TurretTankProcess::~TurretTankProcess
 * Namespace: TurretTankProcess
 * Signature: void ~TurretTankProcess(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::~TurretTankProcess(TurretTankProcess *this)

{
  this->_padding_ = (int)&_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  this->_padding_ = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
