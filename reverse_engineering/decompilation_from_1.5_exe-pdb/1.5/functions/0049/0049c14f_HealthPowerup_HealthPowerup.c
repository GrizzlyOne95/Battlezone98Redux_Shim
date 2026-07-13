/*
 * Entry: 0049c14f
 * Name: HealthPowerup::HealthPowerup
 * Namespace: HealthPowerup
 * Signature: HealthPowerup * HealthPowerup(HealthPowerup * this, _OBJ76 * param_1, HealthPowerupClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HealthPowerup * __thiscall
HealthPowerup::HealthPowerup(HealthPowerup *this,_OBJ76 *param_1,HealthPowerupClass *param_2)

{
  PowerUp::PowerUp((PowerUp *)this,param_1,(PowerUpClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  return this;
}
