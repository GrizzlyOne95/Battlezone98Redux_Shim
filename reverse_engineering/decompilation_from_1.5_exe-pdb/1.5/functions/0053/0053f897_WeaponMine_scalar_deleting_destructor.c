/*
 * Entry: 0053f897
 * Name: WeaponMine::`scalar_deleting_destructor'
 * Namespace: WeaponMine
 * Signature: void * `scalar_deleting_destructor'(WeaponMine * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall WeaponMine::_scalar_deleting_destructor_(WeaponMine *this,uint param_1)

{
  ~WeaponMine(this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
