/*
 * Entry: 004673ba
 * Name: TurretTankProcess::DoWait
 * Namespace: TurretTankProcess
 * Signature: void DoWait(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::DoWait(TurretTankProcess *this)

{
  int iVar1;
  char cVar2;
  float fVar3;
  
  iVar1 = ((int *)this->_padding_)[0x8a];
  cVar2 = (**(code **)(*(int *)this->_padding_ + 0x68))();
  if ((cVar2 != '\0') && (*(int *)(iVar1 + 0xe0) == 0)) {
    fVar3 = Get_Time();
    if (this->waitDeployTime < fVar3) {
      (**(code **)(*(int *)this->_padding_ + 0x5c))();
    }
  }
  UnitProcess::DoWait((UnitProcess *)this);
  return;
}
