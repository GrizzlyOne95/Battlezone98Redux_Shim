/*
 * Entry: 0049fd44
 * Name: MinelayerClass::`scalar_deleting_destructor'
 * Namespace: MinelayerClass
 * Signature: void * `scalar_deleting_destructor'(MinelayerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MinelayerClass::_scalar_deleting_destructor_(MinelayerClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
