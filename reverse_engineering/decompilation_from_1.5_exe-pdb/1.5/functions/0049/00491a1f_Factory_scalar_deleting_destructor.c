/*
 * Entry: 00491a1f
 * Name: Factory::`scalar_deleting_destructor'
 * Namespace: Factory
 * Signature: void * `scalar_deleting_destructor'(Factory * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Factory::_scalar_deleting_destructor_(Factory *this,uint param_1)

{
  ~Factory(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
