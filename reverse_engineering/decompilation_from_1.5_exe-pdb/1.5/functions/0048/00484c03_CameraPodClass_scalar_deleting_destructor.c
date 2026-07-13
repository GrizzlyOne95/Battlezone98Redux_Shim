/*
 * Entry: 00484c03
 * Name: CameraPodClass::`scalar_deleting_destructor'
 * Namespace: CameraPodClass
 * Signature: void * `scalar_deleting_destructor'(CameraPodClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CameraPodClass::_scalar_deleting_destructor_(CameraPodClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
