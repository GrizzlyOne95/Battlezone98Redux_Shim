/*
 * Entry: 004030f0
 * Name: AiMissionClass::AiMissionClass
 * Namespace: AiMissionClass
 * Signature: AiMissionClass * AiMissionClass(AiMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMissionClass * __thiscall AiMissionClass::AiMissionClass(AiMissionClass *this,char *param_1)

{
  this->_padding_ = (int)&_vftable_;
  this->name = param_1;
  AiMission::Register(this);
  return this;
}
