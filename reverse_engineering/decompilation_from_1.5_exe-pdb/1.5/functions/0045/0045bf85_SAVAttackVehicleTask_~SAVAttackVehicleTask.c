/*
 * Entry: 0045bf85
 * Name: SAVAttackVehicleTask::~SAVAttackVehicleTask
 * Namespace: SAVAttackVehicleTask
 * Signature: void ~SAVAttackVehicleTask(SAVAttackVehicleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVAttackVehicleTask::~SAVAttackVehicleTask(SAVAttackVehicleTask *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  if (*(AttackGroup **)&this->field_0x108 != (AttackGroup *)0x0) {
    AttackGroup::Leave(*(AttackGroup **)&this->field_0x108,*(GameObject **)&this->field_0x14);
  }
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
