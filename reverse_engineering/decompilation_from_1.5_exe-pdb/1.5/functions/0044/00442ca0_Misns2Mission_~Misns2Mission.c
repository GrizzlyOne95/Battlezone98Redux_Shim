/*
 * Entry: 00442ca0
 * Name: Misns2Mission::~Misns2Mission
 * Namespace: Misns2Mission
 * Signature: void ~Misns2Mission(Misns2Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns2Mission::~Misns2Mission(Misns2Mission *this)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  return;
}
