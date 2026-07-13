/*
 * Entry: 0045b5b4
 * Name: RescueTask::RescueTask
 * Namespace: RescueTask
 * Signature: RescueTask * RescueTask(RescueTask * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RescueTask * __thiscall RescueTask::RescueTask(RescueTask *this,Craft *param_1,GameObject *param_2)

{
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined4 *)&this->field_0x114 = 0;
  *(undefined4 *)&this->field_0x118 = 0;
  *(undefined4 *)&this->field_0xc = 1;
  *(undefined4 *)&this->field_0x10 = 1;
  *(undefined ***)this = &_vftable_;
  return this;
}
