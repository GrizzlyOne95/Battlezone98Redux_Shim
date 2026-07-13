/*
 * Entry: 0045bb09
 * Name: SAVAttackVehicleTask::SAVAttackVehicleTask
 * Namespace: SAVAttackVehicleTask
 * Signature: SAVAttackVehicleTask * SAVAttackVehicleTask(SAVAttackVehicleTask * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SAVAttackVehicleTask * __thiscall
SAVAttackVehicleTask::SAVAttackVehicleTask
          (SAVAttackVehicleTask *this,Craft *param_1,GameObject *param_2)

{
  AttackGroup *this_00;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  this_00 = AttackGroup::Find(param_2);
  *(AttackGroup **)&this->field_0x108 = this_00;
  AttackGroup::Join(this_00,(GameObject *)param_1,(UnitTask *)this);
  *(undefined4 *)&this->field_0x68 = 0x3c6a0ea1;
  *(undefined4 *)&this->field_0xc = 1;
  *(undefined4 *)&this->field_0x10 = 1;
  this->field_0x20 = 1;
  return this;
}
