/*
 * Entry: 00415c1d
 * Name: Inst02Mission::~Inst02Mission
 * Namespace: Inst02Mission
 * Signature: void ~Inst02Mission(Inst02Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst02Mission::~Inst02Mission(Inst02Mission *this)

{
  this->_padding_ = (int)&_vftable_;
  AiMission::~AiMission((AiMission *)this);
  return;
}
