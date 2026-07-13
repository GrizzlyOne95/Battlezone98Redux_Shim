/*
 * Entry: 00529cd8
 * Name: AnchorRocket::`scalar_deleting_destructor'
 * Namespace: AnchorRocket
 * Signature: void * `scalar_deleting_destructor'(AnchorRocket * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AnchorRocket::_scalar_deleting_destructor_(AnchorRocket *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Rocket::~Rocket((Rocket *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
