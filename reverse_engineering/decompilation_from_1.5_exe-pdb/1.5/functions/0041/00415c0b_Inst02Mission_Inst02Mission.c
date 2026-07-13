/*
 * Entry: 00415c0b
 * Name: Inst02Mission::Inst02Mission
 * Namespace: Inst02Mission
 * Signature: Inst02Mission * Inst02Mission(Inst02Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Inst02Mission * __thiscall Inst02Mission::Inst02Mission(Inst02Mission *this)

{
  AiMission::AiMission((AiMission *)this);
  this->_padding_ = (int)&_vftable_;
  return this;
}
