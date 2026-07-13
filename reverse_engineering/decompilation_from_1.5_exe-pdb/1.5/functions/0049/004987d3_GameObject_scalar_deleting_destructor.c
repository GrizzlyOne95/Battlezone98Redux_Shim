/*
 * Entry: 004987d3
 * Name: GameObject::`scalar_deleting_destructor'
 * Namespace: GameObject
 * Signature: void * `scalar_deleting_destructor'(GameObject * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GameObject::_scalar_deleting_destructor_(GameObject *this,uint param_1)

{
  ~GameObject(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
