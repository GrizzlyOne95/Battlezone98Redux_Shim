/*
 * Entry: 004afea0
 * Name: ShieldTower::`scalar_deleting_destructor'
 * Namespace: ShieldTower
 * Signature: void * `scalar_deleting_destructor'(ShieldTower * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ShieldTower::_scalar_deleting_destructor_(ShieldTower *this,uint param_1)

{
  ~ShieldTower(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
