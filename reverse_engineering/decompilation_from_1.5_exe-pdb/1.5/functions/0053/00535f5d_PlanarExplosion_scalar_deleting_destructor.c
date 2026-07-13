/*
 * Entry: 00535f5d
 * Name: PlanarExplosion::`scalar_deleting_destructor'
 * Namespace: PlanarExplosion
 * Signature: void * `scalar_deleting_destructor'(PlanarExplosion * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PlanarExplosion::_scalar_deleting_destructor_(PlanarExplosion *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Explosion::~Explosion((Explosion *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
