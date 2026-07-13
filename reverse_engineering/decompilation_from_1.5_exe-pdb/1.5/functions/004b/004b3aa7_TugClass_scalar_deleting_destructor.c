/*
 * Entry: 004b3aa7
 * Name: TugClass::`scalar_deleting_destructor'
 * Namespace: TugClass
 * Signature: void * `scalar_deleting_destructor'(TugClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TugClass::_scalar_deleting_destructor_(TugClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
