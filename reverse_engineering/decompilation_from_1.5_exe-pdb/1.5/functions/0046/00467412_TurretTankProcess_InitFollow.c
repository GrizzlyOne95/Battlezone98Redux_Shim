/*
 * Entry: 00467412
 * Name: TurretTankProcess::InitFollow
 * Namespace: TurretTankProcess
 * Signature: void InitFollow(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::InitFollow(TurretTankProcess *this)

{
  (**(code **)(*(int *)this->_padding_ + 0x60))();
  UnitProcess::InitFollow((UnitProcess *)this);
  return;
}
