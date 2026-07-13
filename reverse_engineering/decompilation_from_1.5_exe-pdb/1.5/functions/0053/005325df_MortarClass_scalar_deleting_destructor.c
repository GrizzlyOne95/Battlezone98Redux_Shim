/*
 * Entry: 005325df
 * Name: MortarClass::`scalar_deleting_destructor'
 * Namespace: MortarClass
 * Signature: void * `scalar_deleting_destructor'(MortarClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MortarClass::_scalar_deleting_destructor_(MortarClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  CannonClass::~CannonClass((CannonClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
