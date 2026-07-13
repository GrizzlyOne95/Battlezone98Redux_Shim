/*
 * Entry: 004671ed
 * Name: TurretTankProcess::Init
 * Namespace: TurretTankProcess
 * Signature: void Init(TurretTankProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
TurretTankProcess::Init(TurretTankProcess *this,AiMission *param_1,GameObject *param_2)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  
  UnitProcess::Init((UnitProcess *)this,param_1,param_2);
  pfVar1 = &this->time;
  *pfVar1 = 1.0;
  pfVar2 = &this->closeSquared;
  pfVar3 = &this->rangeSquared;
  *pfVar2 = 0.0;
  *pfVar3 = 150.0;
  this->who1 = (GameObject *)0x0;
  this->who2 = (GameObject *)0x0;
  this->attackUser = false;
  this->weapon = (Weapon *)0x0;
  CalcRange((Craft *)this->_padding_,pfVar2,pfVar3,pfVar1,&this->weapon);
  this->shotSpeed = *pfVar3 / *pfVar1;
  this->shotSpeedInv = *pfVar1 / *pfVar3;
  *pfVar2 = *pfVar2 * *pfVar2;
  *pfVar3 = *pfVar3 * *pfVar3;
  return;
}
