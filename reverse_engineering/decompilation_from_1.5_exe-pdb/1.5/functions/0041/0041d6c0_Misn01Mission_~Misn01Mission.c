/*
 * Entry: 0041d6c0
 * Name: Misn01Mission::~Misn01Mission
 * Namespace: Misn01Mission
 * Signature: void ~Misn01Mission(Misn01Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn01Mission::~Misn01Mission(Misn01Mission *this)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  return;
}
