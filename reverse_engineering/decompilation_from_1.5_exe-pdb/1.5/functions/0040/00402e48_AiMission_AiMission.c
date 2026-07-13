/*
 * Entry: 00402e48
 * Name: AiMission::AiMission
 * Namespace: AiMission
 * Signature: AiMission * AiMission(AiMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall AiMission::AiMission(AiMission *this)

{
  SObject::SObject((SObject *)this);
  this->_padding_ = (int)&_vftable_;
  std::list<AiProcess_*,std::allocator<AiProcess_*>_>::
  list<AiProcess_*,std::allocator<AiProcess_*>_>(&this->processes);
  this->shutdownTime = 0.0;
  this->done = false;
  this->failed = false;
  this->resultName[0] = '\0';
  this->resultName[1] = '\0';
  this->resultName[2] = '\0';
  this->resultName[3] = '\0';
  this->resultName[4] = '\0';
  this->resultName[5] = '\0';
  this->resultName[6] = '\0';
  this->resultName[7] = '\0';
  this->resultName[8] = '\0';
  this->resultName[9] = '\0';
  this->resultName[10] = '\0';
  this->resultName[0xb] = '\0';
  this->resultName[0xc] = '\0';
  this->resultName[0xd] = '\0';
  AISchedule_PreLoad();
  AISchedule_SetAIControl(2,1);
  return this;
}
