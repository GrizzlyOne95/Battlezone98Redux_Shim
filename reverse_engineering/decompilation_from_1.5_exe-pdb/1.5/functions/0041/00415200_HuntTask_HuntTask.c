/*
 * Entry: 00415200
 * Name: HuntTask::HuntTask
 * Namespace: HuntTask
 * Signature: HuntTask * HuntTask(HuntTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HuntTask * __thiscall HuntTask::HuntTask(HuntTask *this)

{
  GotoTask::GotoTask((GotoTask *)this);
  this->total_tries = 0;
  this->_padding_ = (int)&_vftable_;
  this->time_of_Mth_last_try[0] = -1.0;
  this->time_of_Mth_last_try[1] = -1.0;
  this->time_of_Mth_last_try[2] = -1.0;
  this->time_of_Mth_last_try[3] = -1.0;
  this->time_of_Mth_last_try[4] = -1.0;
  return this;
}
