/*
 * Entry: 0049c177
 * Name: HealthPowerup::`scalar_deleting_destructor'
 * Namespace: HealthPowerup
 * Signature: void * `scalar_deleting_destructor'(HealthPowerup * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall HealthPowerup::_scalar_deleting_destructor_(HealthPowerup *this,uint param_1)

{
  PowerUp::~PowerUp((PowerUp *)this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
