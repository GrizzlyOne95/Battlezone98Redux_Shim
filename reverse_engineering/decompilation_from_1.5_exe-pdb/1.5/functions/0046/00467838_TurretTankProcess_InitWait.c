/*
 * Entry: 00467838
 * Name: TurretTankProcess::InitWait
 * Namespace: TurretTankProcess
 * Signature: void InitWait(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::InitWait(TurretTankProcess *this)

{
  float fVar1;
  
  if ((float)((int *)this->_padding_)[0x49] <= 10.0) {
    (**(code **)(*(int *)this->_padding_ + 0x5c))();
  }
  else {
    fVar1 = Get_Time();
    this->waitDeployTime = fVar1 + 10.0;
  }
  UnitProcess::InitWait((UnitProcess *)this);
  return;
}
