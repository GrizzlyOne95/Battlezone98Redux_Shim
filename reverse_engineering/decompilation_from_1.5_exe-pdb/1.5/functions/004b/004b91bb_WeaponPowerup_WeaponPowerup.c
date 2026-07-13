/*
 * Entry: 004b91bb
 * Name: WeaponPowerup::WeaponPowerup
 * Namespace: WeaponPowerup
 * Signature: WeaponPowerup * WeaponPowerup(WeaponPowerup * this, _OBJ76 * param_1, WeaponPowerupClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponPowerup * __thiscall
WeaponPowerup::WeaponPowerup(WeaponPowerup *this,_OBJ76 *param_1,WeaponPowerupClass *param_2)

{
  PowerUp::PowerUp((PowerUp *)this,param_1,(PowerUpClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  return this;
}
