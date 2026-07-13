/*
 * Entry: 004a8fe3
 * Name: PowerUp::`scalar_deleting_destructor'
 * Namespace: PowerUp
 * Signature: void * `scalar_deleting_destructor'(PowerUp * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PowerUp::_scalar_deleting_destructor_(PowerUp *this,uint param_1)

{
  ~PowerUp(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
