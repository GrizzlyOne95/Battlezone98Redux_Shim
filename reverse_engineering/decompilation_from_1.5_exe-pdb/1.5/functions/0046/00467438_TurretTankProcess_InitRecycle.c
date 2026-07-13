/*
 * Entry: 00467438
 * Name: TurretTankProcess::InitRecycle
 * Namespace: TurretTankProcess
 * Signature: void InitRecycle(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::InitRecycle(TurretTankProcess *this)

{
  (**(code **)(*(int *)this->_padding_ + 0x60))();
  UnitProcess::InitRecycle((UnitProcess *)this);
  return;
}
