/*
 * Entry: 00415ce1
 * Name: Inst03Mission::Inst03Mission
 * Namespace: Inst03Mission
 * Signature: Inst03Mission * Inst03Mission(Inst03Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Inst03Mission * __thiscall Inst03Mission::Inst03Mission(Inst03Mission *this)

{
  LuaMission::LuaMission((LuaMission *)this);
  this->pathSpawn = (PathSpawn *)0x0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
