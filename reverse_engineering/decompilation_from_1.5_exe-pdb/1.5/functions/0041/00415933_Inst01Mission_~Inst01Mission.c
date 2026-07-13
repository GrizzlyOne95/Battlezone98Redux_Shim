/*
 * Entry: 00415933
 * Name: Inst01Mission::~Inst01Mission
 * Namespace: Inst01Mission
 * Signature: void ~Inst01Mission(Inst01Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst01Mission::~Inst01Mission(Inst01Mission *this)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  return;
}
