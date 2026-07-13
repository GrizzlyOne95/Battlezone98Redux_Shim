/*
 * Entry: 00403cd2
 * Name: AiProcess::~AiProcess
 * Namespace: AiProcess
 * Signature: void ~AiProcess(AiProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiProcess::~AiProcess(AiProcess *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->fOwner != (GameObject *)0x0) {
    GameObject::SetAIProcess(this->fOwner,(AiProcess *)0x0);
    GameObject::ClearCommand(this->fOwner);
    GameObject::SetCommand(this->fOwner,CMD_NONE);
  }
  AiMission::RemoveProcess(this->fMission,this);
  SObject::~SObject((SObject *)this);
  return;
}
