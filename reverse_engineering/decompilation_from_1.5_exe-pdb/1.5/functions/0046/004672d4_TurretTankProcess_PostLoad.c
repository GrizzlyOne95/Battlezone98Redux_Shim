/*
 * Entry: 004672d4
 * Name: TurretTankProcess::PostLoad
 * Namespace: TurretTankProcess
 * Signature: bool PostLoad(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTankProcess::PostLoad(TurretTankProcess *this)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  bool bVar4;
  
  this->weapon = (Weapon *)0x0;
  pfVar1 = &this->time;
  *pfVar1 = 1.0;
  pfVar2 = &this->rangeSquared;
  *pfVar2 = 150.0;
  pfVar3 = &this->closeSquared;
  CalcRange((Craft *)this->_padding_,pfVar3,pfVar2,pfVar1,&this->weapon);
  this->shotSpeed = *pfVar2 / *pfVar1;
  this->shotSpeedInv = *pfVar1 / *pfVar2;
  *pfVar3 = *pfVar3 * *pfVar3;
  *pfVar2 = *pfVar2 * *pfVar2;
  bVar4 = UnitProcess::PostLoad((UnitProcess *)this);
  return bVar4;
}
