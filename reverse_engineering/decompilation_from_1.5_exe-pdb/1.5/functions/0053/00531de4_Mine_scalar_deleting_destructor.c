/*
 * Entry: 00531de4
 * Name: Mine::`scalar_deleting_destructor'
 * Namespace: Mine
 * Signature: void * `scalar_deleting_destructor'(Mine * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Mine::_scalar_deleting_destructor_(Mine *this,uint param_1)

{
  ~Mine(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
