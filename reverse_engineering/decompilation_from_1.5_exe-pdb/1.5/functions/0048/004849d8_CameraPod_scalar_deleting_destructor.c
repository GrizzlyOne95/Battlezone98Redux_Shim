/*
 * Entry: 004849d8
 * Name: CameraPod::`scalar_deleting_destructor'
 * Namespace: CameraPod
 * Signature: void * `scalar_deleting_destructor'(CameraPod * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CameraPod::_scalar_deleting_destructor_(CameraPod *this,uint param_1)

{
  ~CameraPod(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
