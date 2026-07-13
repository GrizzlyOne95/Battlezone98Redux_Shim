/*
 * Entry: 004af608
 * Name: Scrap::`scalar_deleting_destructor'
 * Namespace: Scrap
 * Signature: void * `scalar_deleting_destructor'(Scrap * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Scrap::_scalar_deleting_destructor_(Scrap *this,uint param_1)

{
  ~Scrap(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
