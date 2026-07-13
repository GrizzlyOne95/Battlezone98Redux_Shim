/*
 * Entry: 005305b3
 * Name: ImageMissileClass::`scalar_deleting_destructor'
 * Namespace: ImageMissileClass
 * Signature: void * `scalar_deleting_destructor'(ImageMissileClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ImageMissileClass::_scalar_deleting_destructor_(ImageMissileClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  MissileClass::~MissileClass((MissileClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
