/*
 * Entry: 00470104
 * Name: UserProcess::UserProcess
 * Namespace: UserProcess
 * Signature: UserProcess * UserProcess(UserProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UserProcess * __thiscall
UserProcess::UserProcess(UserProcess *this,AiMission *param_1,GameObject *param_2)

{
  AiProcess::AiProcess((AiProcess *)this,param_1,param_2);
  this->cycle = 0;
  this->linked = 0;
  this->_padding_ = (int)&_vftable_;
  Init(this);
  return this;
}
