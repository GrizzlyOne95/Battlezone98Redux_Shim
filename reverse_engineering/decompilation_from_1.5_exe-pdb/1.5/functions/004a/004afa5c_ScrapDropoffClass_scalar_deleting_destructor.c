/*
 * Entry: 004afa5c
 * Name: ScrapDropoffClass::`scalar_deleting_destructor'
 * Namespace: ScrapDropoffClass
 * Signature: void * `scalar_deleting_destructor'(ScrapDropoffClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ScrapDropoffClass::_scalar_deleting_destructor_(ScrapDropoffClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
