/*
 * Entry: 004a8a2f
 * Name: PowerPlant::`scalar_deleting_destructor'
 * Namespace: PowerPlant
 * Signature: void * `scalar_deleting_destructor'(PowerPlant * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PowerPlant::_scalar_deleting_destructor_(PowerPlant *this,uint param_1)

{
  ~PowerPlant(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
