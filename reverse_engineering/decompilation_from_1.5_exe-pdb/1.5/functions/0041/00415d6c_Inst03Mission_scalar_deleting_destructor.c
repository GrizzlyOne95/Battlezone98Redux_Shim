/*
 * Entry: 00415d6c
 * Name: Inst03Mission::`scalar_deleting_destructor'
 * Namespace: Inst03Mission
 * Signature: void * `scalar_deleting_destructor'(Inst03Mission * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Inst03Mission::_scalar_deleting_destructor_(Inst03Mission *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  LuaMission::~LuaMission((LuaMission *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
