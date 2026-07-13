/*
 * Entry: 00415724
 * Name: HuntTask::HuntTask
 * Namespace: HuntTask
 * Signature: HuntTask * HuntTask(HuntTask * this, Craft * param_1, AiPath * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HuntTask * __thiscall HuntTask::HuntTask(HuntTask *this,Craft *param_1,AiPath *param_2)

{
  GotoTask::GotoTask((GotoTask *)this,param_1,param_2,true);
  this->total_tries = 0;
  this->my_craft = param_1;
  this->_padding_ = (int)&_vftable_;
  this->time_of_Mth_last_try[0] = -1.0;
  this->time_of_Mth_last_try[1] = -1.0;
  this->time_of_Mth_last_try[2] = -1.0;
  this->time_of_Mth_last_try[3] = -1.0;
  this->time_of_Mth_last_try[4] = -1.0;
  Hunt_New_Spot(this);
  return this;
}
