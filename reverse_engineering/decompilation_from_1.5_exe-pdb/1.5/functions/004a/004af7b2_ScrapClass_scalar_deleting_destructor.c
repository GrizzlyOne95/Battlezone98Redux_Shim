/*
 * Entry: 004af7b2
 * Name: ScrapClass::`scalar_deleting_destructor'
 * Namespace: ScrapClass
 * Signature: void * `scalar_deleting_destructor'(ScrapClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScrapClass::_scalar_deleting_destructor_(ScrapClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
