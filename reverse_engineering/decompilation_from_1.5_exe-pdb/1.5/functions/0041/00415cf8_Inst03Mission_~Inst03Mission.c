/*
 * Entry: 00415cf8
 * Name: Inst03Mission::~Inst03Mission
 * Namespace: Inst03Mission
 * Signature: void ~Inst03Mission(Inst03Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst03Mission::~Inst03Mission(Inst03Mission *this)

{
  this->_padding_ = (int)&_vftable_;
  LuaMission::~LuaMission((LuaMission *)this);
  return;
}
