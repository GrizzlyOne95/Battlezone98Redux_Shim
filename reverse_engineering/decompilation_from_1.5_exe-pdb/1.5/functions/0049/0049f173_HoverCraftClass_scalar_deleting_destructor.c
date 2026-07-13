/*
 * Entry: 0049f173
 * Name: HoverCraftClass::`scalar_deleting_destructor'
 * Namespace: HoverCraftClass
 * Signature: void * `scalar_deleting_destructor'(HoverCraftClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall HoverCraftClass::_scalar_deleting_destructor_(HoverCraftClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  CraftClass::~CraftClass((CraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
