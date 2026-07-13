/*
 * Entry: 00467425
 * Name: TurretTankProcess::InitRescue
 * Namespace: TurretTankProcess
 * Signature: void InitRescue(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::InitRescue(TurretTankProcess *this)

{
  (**(code **)(*(int *)this->_padding_ + 0x60))();
  UnitProcess::InitRescue((UnitProcess *)this);
  return;
}
