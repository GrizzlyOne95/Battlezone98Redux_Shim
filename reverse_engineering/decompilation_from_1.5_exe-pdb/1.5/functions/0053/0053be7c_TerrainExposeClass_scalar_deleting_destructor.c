/*
 * Entry: 0053be7c
 * Name: TerrainExposeClass::`scalar_deleting_destructor'
 * Namespace: TerrainExposeClass
 * Signature: void * `scalar_deleting_destructor'(TerrainExposeClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
TerrainExposeClass::_scalar_deleting_destructor_(TerrainExposeClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  SpecialItemClass::~SpecialItemClass((SpecialItemClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
