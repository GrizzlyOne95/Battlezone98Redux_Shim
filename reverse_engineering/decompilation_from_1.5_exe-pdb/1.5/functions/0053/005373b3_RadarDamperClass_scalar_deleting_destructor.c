/*
 * Entry: 005373b3
 * Name: RadarDamperClass::`scalar_deleting_destructor'
 * Namespace: RadarDamperClass
 * Signature: void * `scalar_deleting_destructor'(RadarDamperClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
RadarDamperClass::_scalar_deleting_destructor_(RadarDamperClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  SpecialItemClass::~SpecialItemClass((SpecialItemClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
