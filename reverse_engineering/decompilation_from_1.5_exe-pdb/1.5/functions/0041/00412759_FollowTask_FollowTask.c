/*
 * Entry: 00412759
 * Name: FollowTask::FollowTask
 * Namespace: FollowTask
 * Signature: FollowTask * FollowTask(FollowTask * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FollowTask * __thiscall FollowTask::FollowTask(FollowTask *this,Craft *param_1,GameObject *param_2)

{
  FollowGroup *this_00;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  if (*(int *)&this->field_0x18 == 0) {
    *(undefined4 *)&this->field_0x120 = 0;
    *(undefined4 *)&this->field_0xc = 0xd;
  }
  else {
    this_00 = FollowGroup::Find(param_2);
    *(FollowGroup **)&this->field_0x120 = this_00;
    FollowGroup::Join(this_00,(GameObject *)param_1);
    *(undefined4 *)&this->field_0x114 = 0;
    *(undefined4 *)&this->field_0x118 = 0xc1a00000;
    *(undefined4 *)&this->field_0xc = 1;
    *(undefined4 *)&this->field_0x10 = 1;
  }
  return this;
}
