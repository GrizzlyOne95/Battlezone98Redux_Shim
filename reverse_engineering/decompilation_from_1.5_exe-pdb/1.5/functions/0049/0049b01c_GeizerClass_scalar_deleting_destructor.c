/*
 * Entry: 0049b01c
 * Name: GeizerClass::`scalar_deleting_destructor'
 * Namespace: GeizerClass
 * Signature: void * `scalar_deleting_destructor'(GeizerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GeizerClass::_scalar_deleting_destructor_(GeizerClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
