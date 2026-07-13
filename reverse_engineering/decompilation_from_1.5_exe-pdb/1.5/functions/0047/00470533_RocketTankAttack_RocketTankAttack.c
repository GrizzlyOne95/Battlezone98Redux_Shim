/*
 * Entry: 00470533
 * Name: RocketTankAttack::RocketTankAttack
 * Namespace: RocketTankAttack
 * Signature: RocketTankAttack * RocketTankAttack(RocketTankAttack * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RocketTankAttack * __thiscall
RocketTankAttack::RocketTankAttack(RocketTankAttack *this,Craft *param_1,GameObject *param_2)

{
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined4 *)&this->field_0xf8 = 0x3ca3d70a;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 1;
  *(undefined4 *)&this->field_0xfc = 0;
  *(undefined4 *)&this->field_0x10 = 5;
  *(undefined4 *)&this->field_0xf4 = 0x42960000;
  return this;
}
