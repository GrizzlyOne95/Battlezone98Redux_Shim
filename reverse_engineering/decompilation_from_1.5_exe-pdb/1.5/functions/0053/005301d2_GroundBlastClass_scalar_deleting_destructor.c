/*
 * Entry: 005301d2
 * Name: GroundBlastClass::`scalar_deleting_destructor'
 * Namespace: GroundBlastClass
 * Signature: void * `scalar_deleting_destructor'(GroundBlastClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
GroundBlastClass::_scalar_deleting_destructor_(GroundBlastClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
