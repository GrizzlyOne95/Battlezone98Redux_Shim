/*
 * Entry: 004b91e3
 * Name: WeaponPowerup::`scalar_deleting_destructor'
 * Namespace: WeaponPowerup
 * Signature: void * `scalar_deleting_destructor'(WeaponPowerup * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall WeaponPowerup::_scalar_deleting_destructor_(WeaponPowerup *this,uint param_1)

{
  PowerUp::~PowerUp((PowerUp *)this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
