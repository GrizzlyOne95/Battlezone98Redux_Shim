/*
 * Entry: 00440249
 * Name: Misns1Mission::~Misns1Mission
 * Namespace: Misns1Mission
 * Signature: void ~Misns1Mission(Misns1Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns1Mission::~Misns1Mission(Misns1Mission *this)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  return;
}
