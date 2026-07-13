/*
 * Entry: 0053e808
 * Name: Weapon::`scalar_deleting_destructor'
 * Namespace: Weapon
 * Signature: void * `scalar_deleting_destructor'(Weapon * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Weapon::_scalar_deleting_destructor_(Weapon *this,uint param_1)

{
  ~Weapon(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
