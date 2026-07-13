/*
 * Entry: 004994ee
 * Name: GameObjectClass::`scalar_deleting_destructor'
 * Namespace: GameObjectClass
 * Signature: void * `scalar_deleting_destructor'(GameObjectClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GameObjectClass::_scalar_deleting_destructor_(GameObjectClass *this,uint param_1)

{
  ~GameObjectClass(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
