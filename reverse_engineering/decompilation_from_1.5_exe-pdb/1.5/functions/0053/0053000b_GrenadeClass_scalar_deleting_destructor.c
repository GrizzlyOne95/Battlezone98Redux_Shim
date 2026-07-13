/*
 * Entry: 0053000b
 * Name: GrenadeClass::`scalar_deleting_destructor'
 * Namespace: GrenadeClass
 * Signature: void * `scalar_deleting_destructor'(GrenadeClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GrenadeClass::_scalar_deleting_destructor_(GrenadeClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  RocketClass::~RocketClass((RocketClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
