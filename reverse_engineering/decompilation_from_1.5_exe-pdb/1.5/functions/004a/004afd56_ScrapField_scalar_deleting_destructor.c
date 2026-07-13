/*
 * Entry: 004afd56
 * Name: ScrapField::`scalar_deleting_destructor'
 * Namespace: ScrapField
 * Signature: void * `scalar_deleting_destructor'(ScrapField * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScrapField::_scalar_deleting_destructor_(ScrapField *this,uint param_1)

{
  Building::~Building((Building *)this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
