/*
 * Entry: 0045c9b8
 * Name: ScavengerProcess::ScavengerProcess
 * Namespace: ScavengerProcess
 * Signature: ScavengerProcess * ScavengerProcess(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScavengerProcess * __thiscall ScavengerProcess::ScavengerProcess(ScavengerProcess *this)

{
  AiProcess::AiProcess((AiProcess *)this);
  this->task = (AiTask *)0x0;
  this->whoHandle = 0;
  this->my_escorts = (tag_c_linked_list *)0x0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
