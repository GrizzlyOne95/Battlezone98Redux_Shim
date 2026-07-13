/*
 * Entry: 00415808
 * Name: Inst01Event::~Inst01Event
 * Namespace: Inst01Event
 * Signature: void ~Inst01Event(Inst01Event * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst01Event::~Inst01Event(Inst01Event *this)

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
