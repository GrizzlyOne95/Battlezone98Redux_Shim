/*
 * Entry: 004b70e8
 * Name: Walker::`scalar_deleting_destructor'
 * Namespace: Walker
 * Signature: void * `scalar_deleting_destructor'(Walker * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Walker::_scalar_deleting_destructor_(Walker *this,uint param_1)

{
  ~Walker(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
