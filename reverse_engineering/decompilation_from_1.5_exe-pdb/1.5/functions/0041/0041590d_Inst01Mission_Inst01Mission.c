/*
 * Entry: 0041590d
 * Name: Inst01Mission::Inst01Mission
 * Namespace: Inst01Mission
 * Signature: Inst01Mission * Inst01Mission(Inst01Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Inst01Mission * __thiscall Inst01Mission::Inst01Mission(Inst01Mission *this)

{
  Inst01Event *this_00;
  
  AiMission::AiMission((AiMission *)this);
  this->_padding_ = (int)&_vftable_;
  this_00 = operator_new(0x2c);
  if (this_00 != (Inst01Event *)0x0) {
    Inst01Event::Inst01Event(this_00,(AiMission *)this);
  }
  return this;
}
