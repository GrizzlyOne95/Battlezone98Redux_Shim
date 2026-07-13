/*
 * Entry: 00530217
 * Name: GroundBlast::`scalar_deleting_destructor'
 * Namespace: GroundBlast
 * Signature: void * `scalar_deleting_destructor'(GroundBlast * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GroundBlast::_scalar_deleting_destructor_(GroundBlast *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Explosion::~Explosion((Explosion *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
