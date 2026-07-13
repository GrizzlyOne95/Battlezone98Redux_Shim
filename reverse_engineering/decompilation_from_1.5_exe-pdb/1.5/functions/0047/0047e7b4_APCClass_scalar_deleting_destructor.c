/*
 * Entry: 0047e7b4
 * Name: APCClass::`scalar_deleting_destructor'
 * Namespace: APCClass
 * Signature: void * `scalar_deleting_destructor'(APCClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall APCClass::_scalar_deleting_destructor_(APCClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
