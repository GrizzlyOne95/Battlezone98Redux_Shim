/*
 * Entry: 00412720
 * Name: FollowTask::FollowTask
 * Namespace: FollowTask
 * Signature: FollowTask * FollowTask(FollowTask * this, Craft * param_1, GameObject * param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FollowTask * __thiscall
FollowTask::FollowTask
          (FollowTask *this,Craft *param_1,GameObject *param_2,float param_3,float param_4)

{
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(float *)&this->field_0x114 = param_3;
  *(undefined4 *)&this->field_0xc = 1;
  *(float *)&this->field_0x118 = param_4;
  *(undefined4 *)&this->field_0x10 = 1;
  *(undefined ***)this = &_vftable_;
  return this;
}
