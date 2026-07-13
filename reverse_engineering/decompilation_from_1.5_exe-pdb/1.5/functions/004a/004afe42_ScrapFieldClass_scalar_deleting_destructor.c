/*
 * Entry: 004afe42
 * Name: ScrapFieldClass::`scalar_deleting_destructor'
 * Namespace: ScrapFieldClass
 * Signature: void * `scalar_deleting_destructor'(ScrapFieldClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScrapFieldClass::_scalar_deleting_destructor_(ScrapFieldClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
