/*
 * Entry: 00403c9c
 * Name: AiProcess::AiProcess
 * Namespace: AiProcess
 * Signature: AiProcess * AiProcess(AiProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiProcess * __thiscall AiProcess::AiProcess(AiProcess *this,AiMission *param_1,GameObject *param_2)

{
  SObject::SObject((SObject *)this);
  this->_padding_ = (int)&_vftable_;
  this->fMission = param_1;
  AiMission::AddProcess(param_1,this);
  this->exited = 0;
  this->fOwner = param_2;
  if (param_2 != (GameObject *)0x0) {
    GameObject::SetAIProcess(param_2,this);
  }
  return this;
}
