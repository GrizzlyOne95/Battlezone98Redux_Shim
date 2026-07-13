/*
 * Entry: 004afaa4
 * Name: ScrapDropoff::`scalar_deleting_destructor'
 * Namespace: ScrapDropoff
 * Signature: void * `scalar_deleting_destructor'(ScrapDropoff * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScrapDropoff::_scalar_deleting_destructor_(ScrapDropoff *this,uint param_1)

{
  ~ScrapDropoff(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
