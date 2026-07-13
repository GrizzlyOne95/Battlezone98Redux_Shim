/*
 * Entry: 004673ff
 * Name: TurretTankProcess::InitGoto
 * Namespace: TurretTankProcess
 * Signature: void InitGoto(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::InitGoto(TurretTankProcess *this)

{
  (**(code **)(*(int *)this->_padding_ + 0x60))();
  UnitProcess::InitGoto((UnitProcess *)this);
  return;
}
