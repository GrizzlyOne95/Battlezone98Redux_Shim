/*
 * Entry: 00482c3a
 * Name: Building::`scalar_deleting_destructor'
 * Namespace: Building
 * Signature: void * `scalar_deleting_destructor'(Building * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Building::_scalar_deleting_destructor_(Building *this,uint param_1)

{
  ~Building(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
