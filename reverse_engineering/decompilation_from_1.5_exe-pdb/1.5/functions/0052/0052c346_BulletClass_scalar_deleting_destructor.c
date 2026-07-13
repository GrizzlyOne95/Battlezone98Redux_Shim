/*
 * Entry: 0052c346
 * Name: BulletClass::`scalar_deleting_destructor'
 * Namespace: BulletClass
 * Signature: void * `scalar_deleting_destructor'(BulletClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BulletClass::_scalar_deleting_destructor_(BulletClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  OrdnanceClass::~OrdnanceClass((OrdnanceClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
