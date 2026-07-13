/*
 * Entry: 00530737
 * Name: ImageRefractClass::`scalar_deleting_destructor'
 * Namespace: ImageRefractClass
 * Signature: void * `scalar_deleting_destructor'(ImageRefractClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ImageRefractClass::_scalar_deleting_destructor_(ImageRefractClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  SpecialItemClass::~SpecialItemClass((SpecialItemClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
