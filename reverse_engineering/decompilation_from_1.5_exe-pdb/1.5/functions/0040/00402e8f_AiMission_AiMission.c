/*
 * Entry: 00402e8f
 * Name: AiMission::AiMission
 * Namespace: AiMission
 * Signature: AiMission * AiMission(AiMission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall AiMission::AiMission(AiMission *this,int param_1)

{
  SObject::SObject((SObject *)this);
  this->_padding_ = (int)&_vftable_;
  std::list<AiProcess_*,std::allocator<AiProcess_*>_>::
  list<AiProcess_*,std::allocator<AiProcess_*>_>(&this->processes);
  this->shutdownTime = 0.0;
  this->done = false;
  this->failed = false;
  if (GameObject::userObject != (GameObject *)0x0) {
    AddObject(this,GameObject::userObject);
  }
  AISchedule_PreLoad();
  AISchedule_SetAIControl(2,1);
  return this;
}
