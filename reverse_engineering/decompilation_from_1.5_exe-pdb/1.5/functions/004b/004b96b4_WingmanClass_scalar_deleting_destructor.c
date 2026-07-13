/*
 * Entry: 004b96b4
 * Name: WingmanClass::`scalar_deleting_destructor'
 * Namespace: WingmanClass
 * Signature: void * `scalar_deleting_destructor'(WingmanClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall WingmanClass::_scalar_deleting_destructor_(WingmanClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  HoverCraftClass::~HoverCraftClass((HoverCraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
