/*
 * Entry: 0047bca1
 * Name: AmmoPowerup::AmmoPowerup
 * Namespace: AmmoPowerup
 * Signature: AmmoPowerup * AmmoPowerup(AmmoPowerup * this, _OBJ76 * param_1, AmmoPowerupClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AmmoPowerup * __thiscall
AmmoPowerup::AmmoPowerup(AmmoPowerup *this,_OBJ76 *param_1,AmmoPowerupClass *param_2)

{
  PowerUp::PowerUp((PowerUp *)this,param_1,(PowerUpClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  return this;
}
