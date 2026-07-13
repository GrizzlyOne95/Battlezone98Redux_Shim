/*
 * Entry: 004671b4
 * Name: TurretTankProcess::TurretTankProcess
 * Namespace: TurretTankProcess
 * Signature: TurretTankProcess * TurretTankProcess(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretTankProcess * __thiscall TurretTankProcess::TurretTankProcess(TurretTankProcess *this)

{
  UnitProcess::UnitProcess((UnitProcess *)this);
  this->_padding_ = 0;
  this->_padding_ = (int)&_vftable_;
  this->waitDeploy = false;
  this->attackUser = false;
  return this;
}
