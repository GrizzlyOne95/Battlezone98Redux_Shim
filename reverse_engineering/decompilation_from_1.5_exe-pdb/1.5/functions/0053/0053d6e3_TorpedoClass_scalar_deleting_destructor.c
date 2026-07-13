/*
 * Entry: 0053d6e3
 * Name: TorpedoClass::`scalar_deleting_destructor'
 * Namespace: TorpedoClass
 * Signature: void * `scalar_deleting_destructor'(TorpedoClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TorpedoClass::_scalar_deleting_destructor_(TorpedoClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
