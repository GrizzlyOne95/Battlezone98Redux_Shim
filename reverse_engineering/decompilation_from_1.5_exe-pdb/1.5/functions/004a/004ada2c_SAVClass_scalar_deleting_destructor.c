/*
 * Entry: 004ada2c
 * Name: SAVClass::`scalar_deleting_destructor'
 * Namespace: SAVClass
 * Signature: void * `scalar_deleting_destructor'(SAVClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SAVClass::_scalar_deleting_destructor_(SAVClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
