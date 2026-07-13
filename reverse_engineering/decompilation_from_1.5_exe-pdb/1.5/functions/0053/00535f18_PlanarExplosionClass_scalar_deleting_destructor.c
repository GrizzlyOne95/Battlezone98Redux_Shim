/*
 * Entry: 00535f18
 * Name: PlanarExplosionClass::`scalar_deleting_destructor'
 * Namespace: PlanarExplosionClass
 * Signature: void * `scalar_deleting_destructor'(PlanarExplosionClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
PlanarExplosionClass::_scalar_deleting_destructor_(PlanarExplosionClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
