/*
 * Entry: 0053995c
 * Name: ShockBlastClass::`scalar_deleting_destructor'
 * Namespace: ShockBlastClass
 * Signature: void * `scalar_deleting_destructor'(ShockBlastClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ShockBlastClass::_scalar_deleting_destructor_(ShockBlastClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
