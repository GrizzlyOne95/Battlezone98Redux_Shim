/*
 * Entry: 0044bec6
 * Name: MultDMEvent::~MultDMEvent
 * Namespace: MultDMEvent
 * Signature: void ~MultDMEvent(MultDMEvent * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultDMEvent::~MultDMEvent(MultDMEvent *this)

{
  this->_padding_ = (int)&AiProcess::_vftable_;
  if ((GameObject *)this->_padding_ != (GameObject *)0x0) {
    GameObject::SetAIProcess((GameObject *)this->_padding_,(AiProcess *)0x0);
    GameObject::ClearCommand((GameObject *)this->_padding_);
    GameObject::SetCommand((GameObject *)this->_padding_,CMD_NONE);
  }
  AiMission::RemoveProcess((AiMission *)this->_padding_,(AiProcess *)this);
  SObject::~SObject((SObject *)this);
  return;
}
