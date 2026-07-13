/*
 * Entry: 0045d617
 * Name: ScavengerProcess::ScavengerProcess
 * Namespace: ScavengerProcess
 * Signature: ScavengerProcess * ScavengerProcess(ScavengerProcess * this, AiMission * param_1, Scavenger * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScavengerProcess * __thiscall
ScavengerProcess::ScavengerProcess(ScavengerProcess *this,AiMission *param_1,Scavenger *param_2)

{
  AiProcess::AiProcess((AiProcess *)this);
  this->_padding_ = (int)&_vftable_;
  this->task = (AiTask *)0x0;
  this->whoHandle = 0;
  this->my_escorts = (tag_c_linked_list *)0x0;
  Init(this,param_1,(GameObject *)param_2);
  return this;
}
