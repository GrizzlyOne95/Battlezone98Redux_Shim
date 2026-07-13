/*
 * Entry: 0040bd01
 * Name: APCAttack::APCAttack
 * Namespace: APCAttack
 * Signature: APCAttack * APCAttack(APCAttack * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

APCAttack * __thiscall APCAttack::APCAttack(APCAttack *this,Craft *param_1,GameObject *param_2)

{
  undefined4 *puVar1;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 1;
  if (param_2 == (GameObject *)0x0) {
    *(undefined4 *)&this->field_0x10 = 0xd;
  }
  else {
    puVar1 = (undefined4 *)(**(code **)(param_2->_padding_ + 0xc))();
    *(undefined4 *)&this->field_0x2c = *puVar1;
    *(undefined4 *)&this->field_0x30 = puVar1[1];
    *(undefined4 *)&this->field_0x34 = puVar1[2];
    *(undefined4 *)&this->field_0x10 = 2;
  }
  return this;
}
