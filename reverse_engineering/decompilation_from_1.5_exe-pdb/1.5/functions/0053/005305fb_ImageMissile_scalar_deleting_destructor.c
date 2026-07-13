/*
 * Entry: 005305fb
 * Name: ImageMissile::`scalar_deleting_destructor'
 * Namespace: ImageMissile
 * Signature: void * `scalar_deleting_destructor'(ImageMissile * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ImageMissile::_scalar_deleting_destructor_(ImageMissile *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Missile::~Missile((Missile *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
